#include "introwidget.h"
#include "ui_introwidget.h"
#include<QVideoWidget>
#include<iostream>
#include"mainwindow.h"
IntroWidget::IntroWidget(QWidget *parent) :
    Panel(parent),
    ui(new Ui::IntroWidget),
    m_player(nullptr),
    m_playlist(nullptr)
{
    ui->setupUi(this);
    if(!m_player)
    {
        m_player=new QMediaPlayer();
        m_playlist=new QMediaPlaylist();

        m_playlist->addMedia(QUrl(QCoreApplication::applicationDirPath()+"/data/sounds/video2.avi"));

        m_playlist->setCurrentIndex(1);

        m_player = new QMediaPlayer;
        m_player->setPlaylist(m_playlist);
         m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        m_videoWidget = new QVideoWidget(parent);
        m_player->setVideoOutput(m_videoWidget);
        m_videoWidget->setGeometry(0,100,800,600);

        m_videoWidget->show();


        m_player->play();
        QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(testDuboutton()));


    }

}

IntroWidget::~IntroWidget()
{
    delete ui;
    if(m_player)
    {
        delete m_player;
        delete m_playlist;
        m_player=nullptr;
        m_playlist=nullptr;
    }
}
void IntroWidget::testDuboutton()
{



    //m_videoWidget->close();
}


