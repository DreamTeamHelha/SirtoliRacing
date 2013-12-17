#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menuwidget.h"
#include "scorewidget.h"
#include <QMessageBox>
#include "pausemenu.h"
#include "credits.h"
#include "choosewidget.h"
#include "scorewindow.h"
#include "settings.h"
#include "help.h"
#include <QSound>
#include "jukebox.h"
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QJsonObject>
#include "introwidget.h"
#include <QException>
#include "_params.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_panel(nullptr),
    m_gameWidget(nullptr),
    m_musicPlay(true),
    m_playlist(nullptr),
    m_player(nullptr),
    m_videoWidget(nullptr)
{
    ui->setupUi(this);

    if(!m_videoWidget)
    {
        m_playlist=new QMediaPlaylist();
        #ifdef VIDEO_AT_START
            m_player=new QMediaPlayer();
            m_playlist->addMedia(QUrl(QCoreApplication::applicationDirPath()+"/data/sounds/trailerSirtoli.wmv"));
            m_playlist->setCurrentIndex(0);
            m_player = new QMediaPlayer;
            m_player->setPlaylist(m_playlist);
            m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
            m_videoWidget = new QVideoWidget(this);
            m_player->setVideoOutput(m_videoWidget);
            m_videoWidget->setGeometry(0,0,800,600);
            m_videoWidget->show();
            m_player->play();
        #else
            lancerMenu();
        #endif
    }




}

MainWindow::~MainWindow()
{
    delete ui;

    if(m_player)
    {
        delete m_player;
        delete m_playlist;
        m_player=nullptr;
        m_playlist=nullptr;
    }

    if(m_gameWidget)
    {
        m_gameWidget->close();
        m_gameWidget->deleteLater();
        m_gameWidget=nullptr;
    }
}

Panel *MainWindow::panel() const
{
    return m_panel;
}

GameWidget *MainWindow::gameWidget() const
{
    return m_gameWidget;
}

void MainWindow::showPanel(const QString &menuName)
{
    // nettoyage
    if (m_panel)
    {
        m_panel->close();
        m_panel->deleteLater();
        m_panel = nullptr;
    }


    // crée le panel correspondant
    if (menuName == "Menu")
    {
        m_panel = new MenuWidget(this);
    }
    else if (menuName == "Score")
    {
        m_panel = new ScoreWidget(this);
    }
    else if (menuName == "Credit")
    {
        m_panel = new credits(this);
    }
    else if (menuName == "Choose")
    {
        m_panel = new ChooseWidget(this);
    }
    else if (menuName == "EndGame")
    {
        m_panel = new ScoreWindow(this,m_gameWidget->scene()->time().elapsed(),m_gameWidget->scene()->trackName());
    }
    else if (menuName == "Help")
    {
       m_panel = new Help(this);
    }

    if(m_gameWidget)
    {
        m_gameWidget->close();
        m_gameWidget->deleteLater();
        m_gameWidget = nullptr;
    }

    // crée les connexions
    if (m_panel)
    {
        connect(m_panel, SIGNAL(showPanel(QString)), this, SLOT(showPanel(QString)));
        connect(m_panel, SIGNAL(startGame(QString,QString,Settings*)), this, SLOT(startGame(QString,QString,Settings*)));
        m_panel->show();
    }
}

void MainWindow::startGame(const QString &levelName, const QString &carClassName, Settings *setting)
{
    Scene *scene = new Scene;
    if (scene->load(levelName, carClassName))
    {
        // changement de niveau
        if (m_panel)
        {
            m_panel->close();
            m_panel->deleteLater();
            m_panel = nullptr;
        }
        if (m_gameWidget)
        {
            m_gameWidget->close();
            m_gameWidget->deleteLater();
            m_gameWidget = nullptr;
        }
        scene->setDynamicZoom(setting->dynamicZoom());

        m_gameWidget = new GameWidget(scene, this);
        m_gameWidget->setGeometry(0,0,800,600);
        m_gameWidget->show();
        connect(m_gameWidget,SIGNAL(gamePaused(QTime)),this,SLOT(pauseGame(QTime)));
        connect(m_gameWidget, SIGNAL(showScore(QString)), this, SLOT(showPanel(QString)));
    }
    else
    {
        // reste où il est
        delete scene;
        QMessageBox::information(this, "Erreur", "Le chargement du niveau '" + levelName + "' avec le véhicule '" + carClassName + "' a échoué!", 0);
    }
    //libération setting
    delete setting;
}

void MainWindow::pauseGame(QTime)
{
    if(!m_gameWidget)
    {
        return;
    }
    m_panel = new PauseMenu(m_gameWidget->scene()->time().elapsed(),m_gameWidget);
    m_panel->show();
}

void MainWindow::continueGame()
{
    m_gameWidget->scene()->setTime((dynamic_cast<PauseMenu*>(m_panel))->time());
    m_panel->close();
    m_panel->deleteLater();
    m_panel = nullptr;
    m_gameWidget->setCursor(Qt::BlankCursor);
    m_gameWidget->setPaused(false);

}

void MainWindow::playStopTrack()
{
    if(m_musicPlay==true)
    {
         m_player->stop();
         m_musicPlay=false;
    }
    else
    {
       m_player->play();
       m_musicPlay=true;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_S:

        MainWindow::playStopTrack();
        break;

    case Qt::Key_P:
        m_playlist->previous();
        break;

    case Qt::Key_N:
        m_playlist->next();
        break;
    case Qt::Key_Space:

        MainWindow::lancerMenu();
        break;

    default:
         QMainWindow::keyReleaseEvent(event);
    }
}

void MainWindow::lancerMenu()
{
    if(m_videoWidget)
    {
        m_videoWidget->close();
        m_player->stop();
        m_playlist->clear();
        delete m_videoWidget;
        delete m_playlist;
        delete m_player;
        m_videoWidget=nullptr;
        m_playlist=nullptr;
        m_player=nullptr;
    }

    if(!m_playlist)
    {
        m_playlist=new QMediaPlaylist;
        m_player=new QMediaPlayer;
        MainWindow::load();
        m_playlist->setCurrentIndex(0);
        m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        m_player->setPlaylist(m_playlist);
        m_player->play();
    }
    showPanel("Menu");
}

void MainWindow::load()
{
    QJsonArray root = utils::readJsonFile(QCoreApplication::applicationDirPath()+"/data/jukebox.json");
    QJsonObject item;
    for(int i=0;i<root.count();i++)
    {
        item =root[i].toObject();
        m_playlist->addMedia(QUrl(QCoreApplication::applicationDirPath()+"/data/sounds/"+item["track"].toString()));
    }
}
