#include "menuwidget.h"
#include "ui_menuwidget.h"

#include "scorewidget.h"
#include "gamewidget.h"
#include <QMessageBox>
#include <QFile>
#include <iostream>
#include <QCoreApplication>


MenuWidget::MenuWidget(QWidget *parent) :
    Panel(parent),
    ui(new Ui::MenuWidget)

{
    ui->setupUi(this);

    QObject::connect(ui->b_Settings,SIGNAL(clicked()),this,SLOT(showScore()));
    QObject::connect(ui->b_Exit,SIGNAL(clicked()),this,SLOT(exitApp()));
    QObject::connect(ui->b_Race,SIGNAL(clicked()),this,SLOT(showChoose()));
    QObject::connect(ui->b_Credits,SIGNAL(clicked()),this,SLOT(showCredits()));
    QObject::connect(ui->b_Help,SIGNAL(clicked()),this,SLOT(showHelp()));

    this->setStyleSheet("QWidget{background-image : url(./data/img/Fond.png);}");
    ui->b_Race->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/PLAY.png);}QPushButton::hover{background-image : url(./data/img/PLAY-COULEUR.png);}");
    ui->b_Help->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/CONTROLS.png);}QPushButton::hover{background-image : url(./data/img/CONTROLS-COULEUR.png);}");
    ui->b_Settings->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/SCORES.png);}QPushButton::hover{background-image : url(./data/img/SCORES-COULEURS.png);}");
    ui->b_Exit->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/QUIT.png);}QPushButton::hover{background-image : url(./data/img/QUIT-COULEUR.png);}");
    ui->b_Credits->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/CREDITS.png);}QPushButton::hover{background-image : url(./data/img/CREDITS-COULEUR.png);}");
    ui->l_Name->setStyleSheet("background-image : url(./data/img/NOM-COURSE.png);");

}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::showScore()
{
    emit showPanel("Score");
}

void MenuWidget::exitApp()
{
   qApp->quit();
}

void MenuWidget::showChoose ()
{
    emit showPanel("Choose");
}
void MenuWidget::showCredits()
{
    emit showPanel("Credit");
}
void MenuWidget::showHelp()
{
    emit showPanel("Help");
}




