#include "choosewidget.h"
#include "ui_choosewidget.h"
#include "settings.h"

ChooseWidget::ChooseWidget(QWidget *parent) :
    Panel(parent),
    ui(new Ui::ChooseWidget)
{
    ui->setupUi(this);

    //Connecte les actions des différents boutons
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextTrack()));
    connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(previousTrack()));
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(launchGame()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backToMenu()));

    m_trackList = new TrackList();
    m_trackList->load();

    this->setStyleSheet("#ChooseWidget{background-image : url(./data/img/Fond.png);}");
    ui->label->setStyleSheet("QLabel{background-color:rgba(255,255,255,0);background-image : url(./data/img/FOND-COURSE.png);}");
    ui->previousButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/GFLECHE.png);}QPushButton::hover{background-image : url(./data/img/GFLECHE-COULEUR.png);}");
    ui->nextButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/DFLECHE.png);}QPushButton::hover{background-image : url(./data/img/DFLECHE-COULEUR.png);}");
    ui->backButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/BACK.png);}QPushButton::hover{background-image : url(./data/img/BACK-COULEUR.png);}");
    ui->startButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/START.png);}QPushButton::hover{background-image : url(./data/img/START-COULEUR.png);}");
    ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());

}

ChooseWidget::~ChooseWidget()
{
    delete ui;
    delete m_trackList;
}

void ChooseWidget::nextTrack()
{
    m_trackList->next();
    ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
}

void ChooseWidget::previousTrack()
{
    m_trackList->previous();
    ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
}

void ChooseWidget::launchGame()
{
    Settings *_setting=new Settings;
    _setting->setDynamicZoom(ui->cb_dynamicZoom->isChecked());
    emit startGame(m_trackList->currentTrack(), "Car", _setting);
}

void ChooseWidget::backToMenu()
{
    emit showPanel("Menu");
}
