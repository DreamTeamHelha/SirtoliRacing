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
}

credits::~credits()
{
    delete ui;
}
void credits::afficherMenu()
{
    emit showPanel("Menu");
}
