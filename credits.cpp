#include "credits.h"
#include "ui_credits.h"
#include "menuwidget.h"
#include <iostream>

credits::credits(QWidget *parent) :
    Panel(parent),
    ui(new Ui::credits)
{
    ui->setupUi(this);
    connect(ui->b_RetourMenu,SIGNAL(clicked()),this,SLOT(afficherMenu()));
    this->setStyleSheet("#credits{background-image : url(./data/img/Fond.png);}");
    ui->b_RetourMenu->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/BACK.png);}QPushButton::hover{background-image : url(./data/img/BACK-COULEUR.png);}");

}

credits::~credits()
{
    delete ui;
}
void credits::afficherMenu()
{
    emit showPanel("Menu");
}
