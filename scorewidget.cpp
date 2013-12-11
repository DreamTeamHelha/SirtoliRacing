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
    ui(new Ui::ScoreWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(afficherMenu()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextTrack()));
    connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(previousTrack()));

    m_trackList = new TrackList();
    m_trackList->load();

    ui->trackName->setText(m_trackList->currentTrackName());
    load();
}


ScoreWidget::~ScoreWidget()
{
    delete ui;
    delete m_trackList;
}

void ScoreWidget::afficherMenu()
{
    emit showPanel("Menu");
}

void ScoreWidget::load()
{
    //Lecture du fichier de score


    QStandardItemModel *model= new QStandardItemModel(0,0,0);

    QList<QStandardItem*> colTime;
    QList<QStandardItem*> colName;

    //Remplissage de la liste des scores dans la listView
    QJsonArray root = utils::readJsonFile(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack() +".score");
    for(int i=0;i<root.count();i++)
    {
        QJsonObject item =root[i].toObject();


        colName.append( new QStandardItem(item["Name"].toString()));
        colTime.append( new QStandardItem(utils::showableTime(item["Time"].toDouble())));

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
    //ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());

    load();
}

void ScoreWidget::previousTrack()
{
    m_trackList->previous();
    //ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
    load();
}
