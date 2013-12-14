#ifndef INTROWIDGET_H
#define INTROWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include<QVideoWidget>
#include"panel.h"
#include"mainwindow.h"
namespace Ui {
class IntroWidget;
}

class IntroWidget : public Panel
{
    Q_OBJECT

public:
    explicit IntroWidget(QWidget *parent = 0);
    ~IntroWidget();
    ///getter
    //QMediaPlaylist getPlayer()const{return *m_player;}
    //QMediaPlayer   getPlaylist()const{return *m_playlist;}
    //QVideoWidget getVideoWidget()const{return *m_videoWidget;}

private:
    Ui::IntroWidget *ui;
    QMediaPlaylist *m_playlist;
    QMediaPlayer *m_player;
    QVideoWidget *m_videoWidget;

private slots:
    void testDuboutton();


};

#endif // INTROWIDGET_H
