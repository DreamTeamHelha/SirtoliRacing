#include "scorewidget.h"
#include "ui_scorewidget.h"
#include "menuwidget.h"
#include <iostream>
#include"utils.h"
#include"tracklist.h"
#include"QMessageBox"
#include"QJsonDocument"
#include"QStandardItemModel"
#include"QJsonArray"
#include"QJsonObject"
#include"QList"
#include"QFile"

ScoreWidget::ScoreWidget(QWidget *parent) :
    Panel(parent),
    ui(new Ui::ScoreWidget),
     m_scoreManager(new ScoreManager(this))
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(afficherMenu()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextTrack()));
    connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(previousTrack()));

    m_trackList = new TrackList();
    m_trackList->load();
    this->setStyleSheet("#ScoreWidget{background-image : url(./data/img/Fond.png);}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/BACK.png);}QPushButton::hover{background-image : url(./data/img/BACK-COULEUR.png);}");
    ui->label->setStyleSheet("QLabel#label{background-image:url(./data/img/FOND-SCORE.png);}");
    ui->previousButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/GFLECHE.png);}QPushButton::hover{background-image : url(./data/img/GFLECHE-COULEUR.png);}");
    ui->nextButton->setStyleSheet("QPushButton{background-color:rgba(255, 255, 255, 0);background-image : url(./data/img/DFLECHE.png);}QPushButton::hover{background-image : url(./data/img/DFLECHE-COULEUR.png);}");
    ui->trackName->setText(m_trackList->currentTrackName());
    ui->label_2->hide();
    m_scoreManager->getScores(m_trackList->currentTrack());


    connect(m_scoreManager, SIGNAL(scoreReceived(QString,QVector<Score*>)), this, SLOT(loaded(QString,QVector<Score*>)));
    connect(m_scoreManager, SIGNAL(error(QString)), this, SLOT(error(QString)));

}


ScoreWidget::~ScoreWidget()
{
    delete ui;
    delete m_trackList;
    delete m_scoreManager;
}

void ScoreWidget::afficherMenu()
{
    emit showPanel("Menu");
}

void ScoreWidget::loadTableView()
{
    QStandardItemModel *model= new QStandardItemModel(0,0,0);
    QList<QStandardItem*> colTime;
    QList<QStandardItem*> colName;

    QStandardItem *item;
    for(Score * score: m_scoreVector)
    {
        item = new QStandardItem(score->name());
        colName.append(item);

        item = new QStandardItem(utils::showableTime(score->time()));
        colTime.append(item);
    }
    model->appendColumn(colName);
    model->appendColumn(colTime);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));

    ui->tableView->setModel(model);
}
void ScoreWidget::nextTrack()
{
    m_trackList->next();
    ui->trackName->setText(m_trackList->currentTrackName());
    m_scoreManager->getScores(m_trackList->currentTrack());
}

void ScoreWidget::previousTrack()
{
    m_trackList->previous();
    ui->trackName->setText(m_trackList->currentTrackName());
    m_scoreManager->getScores(m_trackList->currentTrack());
}

void ScoreWidget::loaded(QString trackName, QVector<Score *> scores)
{
    if(trackName == m_trackList->currentTrack())
    {
        m_scoreVector = scores;
        loadTableView();
        ui->label_2->hide();
    }
    else
    {
        m_scoreManager->getScores(m_trackList->currentTrack());
    }

}

void ScoreWidget::error(QString)
{
    ui->label_2->show();
    ui->tableView->setModel(new QStandardItemModel(0,0,0));
}
