#include "pausemenu.h"
#include <iostream>
#include <mainwindow.h>

PauseMenu::PauseMenu(const int time, QWidget *parent): Panel(parent), m_time(time)
{
    this->setGeometry(200,150,400,300);
    this->setStyleSheet("background-image:url(./data/img/FOND-PAUSE.png);");


    m_continueButton = new QPushButton(this);
    m_continueButton->setGeometry(75,50,254,50);
    m_continueButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);background-image:url(./data/img/CONTINUE.png);} QPushButton::hover{background-image:url(./data/img/CONTINUE-COULEUR.png);}");
    connect(m_continueButton,SIGNAL(clicked()),this,SLOT(continueClicked()));

    m_quitButton = new QPushButton(this);
    m_quitButton->setGeometry(125,175,160,55);
    m_quitButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);background-image:url(./data/img/QUIT.png);} QPushButton::hover{background-image:url(./data/img/QUIT-COULEUR.png);}");
    connect(m_quitButton,SIGNAL(clicked()),this,SLOT(quitClicked()));
}

void PauseMenu::quitClicked()
{
    (dynamic_cast<MainWindow*> (this->parent()->parent()))->showPanel("Menu");
}

void PauseMenu::continueClicked()
{
    (dynamic_cast<MainWindow*> (this->parent()->parent()))->continueGame();
}

PauseMenu::~PauseMenu()
{
    delete m_continueButton;
    delete m_quitButton;
}

int PauseMenu::time()const
{
    return m_time;
}

