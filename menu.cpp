#include "menu.h"
#include "ui_menu.h"

#include "formtools.h"
#include "gamewidget.h"
#include <QMessageBox>
#include <QFile>
#include <iostream>
#include <QCoreApplication>
#include <QSound>

Menu::Menu(QWidget *parent) :
    Panel(parent),
    ui(new Ui::Menu),
    m_soundMenu(nullptr)
{
    ui->setupUi(this);

    QObject::connect(ui->b_Settings,SIGNAL(clicked()),this,SLOT(afficherTools()));
    QObject::connect(ui->b_Exit,SIGNAL(clicked()),this,SLOT(exitApp()));
    QObject::connect(ui->b_Race,SIGNAL(clicked()),this,SLOT(AfficherJeu()));
    QObject::connect(ui->b_Credits,SIGNAL(clicked()),this,SLOT(afficherCredit()));
    //modification de l'icon des boutons menu
    ui->b_Race->setIcon((QIcon)(QCoreApplication::applicationDirPath() + "/data/img/RaceMenu.png"));
    ui->b_Settings->setIcon((QIcon)(QCoreApplication::applicationDirPath() + "/data/img/tools.jpg"));
    ui->b_Exit->setIcon((QIcon)(QCoreApplication::applicationDirPath() + "/data/img/FormulaExit.jpg"));
    ui->label->setPixmap(QCoreApplication::applicationDirPath() + "/data/img/SIRTOLI_LOGOMenu.jpg");

    m_soundMenu= new QSound(QCoreApplication::applicationDirPath() + "/data/sons/1.wav");
    m_soundMenu->play();
}

Menu::~Menu()
{
    std::cout << "Menu deleted" << std::endl;
    delete ui;
    //detruit le son si il est pas nul , comme sa on peut le detruire en cliquant sur play
    if (m_soundMenu)
        delete m_soundMenu;
}

void Menu::afficherTools()
{
    emit showPanel("Tools");
}

void Menu::exitApp()
{
   qApp->quit();
}

void Menu::AfficherJeu()
{
    delete m_soundMenu;
    m_soundMenu = nullptr;

    emit showPanel("Choose");
}
void Menu::afficherCredit()
{
    emit showPanel("Credit");
}
