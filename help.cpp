#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    Panel(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    ui->label->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/N.png");
    ui->label_3->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/P.png");
    ui->label_5->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/Esc.png");
    ui->label_7->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/high.png");
    ui->label_8->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/right.png");
    ui->label_9->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/left.png");
    ui->label_10->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/down.png");
    ui->label_18->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/S.png");

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(backToMenu()));
}

Help::~Help()
{
    delete ui;
}
void Help::backToMenu()
{
    emit showPanel("Menu");
}
