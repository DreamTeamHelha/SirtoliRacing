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

    //modification de l'icon des boutons menu
    ui->b_Race->setIcon((QIcon)(QCoreApplication::applicationDirPath() + "/data/img/RaceMenu.png"));
    ui->b_Settings->setIcon((QIcon)(QCoreApplication::applicationDirPath() + "/data/img/tools.jpg"));
    ui->b_Exit->setIcon((QIcon)(QCoreApplication::applicationDirPath() + "/data/img/FormulaExit.jpg"));
    ui->label->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/SIRTOLI_LOGOMenu.jpg");

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




