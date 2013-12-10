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
#include <QSound>
#include"jukebox.h"
#include<QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_panel(nullptr),
    m_gameWidget(nullptr),
    m_musicPlay(true),
    m_JukeBox(nullptr)
{
    ui->setupUi(this);

    if(!m_JukeBox)
    {
        m_JukeBox=new JukeBox();
        m_JukeBox->load();
        m_JukeBox->playSong(m_JukeBox->currentTrack());
    }
    showPanel("Menu");
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_JukeBox)
    {
        delete m_JukeBox;
        m_JukeBox=nullptr;
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

void MainWindow::nextTrack()
{
    m_JukeBox->next();
    m_JukeBox->playSong(m_JukeBox->currentTrack());
}


void MainWindow::previousTrack()
{
    m_JukeBox->previous();
    m_JukeBox->playSong(m_JukeBox->currentTrack());
}


void MainWindow::playStopTrack()
{
    if(m_musicPlay==true)
    {
         m_JukeBox->stopPlay();
         m_musicPlay=false;
    }
    else
    {
       m_JukeBox->playSong(m_JukeBox->currentTrack());
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
        MainWindow::previousTrack();
        break;

    case Qt::Key_N:
        MainWindow::nextTrack();
        break;

    default:
         QMainWindow::keyReleaseEvent(event);
    }
}
