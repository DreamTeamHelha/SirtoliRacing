#include "scorewindow.h"
#include "ui_scorewindow.h"
#include <iostream>
#include <QMessageBox>
#include <utils.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>
#include <QVector>

ScoreWindow::ScoreWindow(QWidget *parent,int timeElapsed,QString track) :
    Panel(parent),
    m_time(timeElapsed),
    m_track(track),
    m_rank(10),
    ui(new Ui::ScoreWindow),
    m_scoreManager(new ScoreManager(this))
{
    ui->setupUi(this);
<<<<<<< HEAD
    this->setStyleSheet("#ScoreWindow{background-image : url(./data/img/Fond.png);}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);background-image:url(./data/img/CONTINUE.png);} QPushButton::hover{background-image:url(./data/img/CONTINUE-COULEUR.png);}");
    ui->label->setStyleSheet("QLabel#label{background-image:url(./data/img/FOND-SCORE.png);}");

=======

    connect(m_scoreManager, SIGNAL(scoreReceived(QString,QVector<Score*>)), this, SLOT(loaded(QString,QVector<Score*>)));
    connect(m_scoreManager, SIGNAL(error(QString)), this, SLOT(error(QString)));

    m_scoreManager->getScores(m_track);
    /*
>>>>>>> 222aa4f23bbea0be87c9dad593648be073bb6622
    load();
    m_rank = ranked();
    if(m_rank<10)
    {
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addScore()));
        m_scoreVector.insert(m_rank,new Score(m_time,"YOURNAME"));
        if(m_scoreVector.size()>10)
        {
            delete m_scoreVector[10];
            m_scoreVector.remove(10);
        }
        ui->textLabel->setText("Good Game ! you're in the position : " + QString::number(m_rank+1) + ".Your time is : "+ utils::showableTime(m_time) + ". Please enter your name to save this time :" );
        ui->nameText->insertPlainText("YOURNAME");
    }
    else
    {
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(backToMenu()));
        ui->nameText->hide();
    }

    loadTableView();
    //*/
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
    for(Score* score : m_scoreVector)
    {
        delete score;
    }
    std::cout<<"ScoreWindow deleted"<<std::endl;
}

void ScoreWindow::addScore()
{
    m_scoreVector[m_rank]->setName(ui->nameText->toPlainText());

    m_scoreManager->sendScores(m_track, m_scoreVector);
    connect(m_scoreManager, SIGNAL(scoreSent()), this, SLOT(backToMenu()));
    /*
    QJsonArray array;

    for(Score*  score: m_scoreVector)
    {
        QJsonObject object;
        object.insert("Name",score->name());
        object.insert("Time",score->time());
        array.append(object);
    }

    QFile file(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_track +".score");
    file.open(QFile::WriteOnly | QFile::Truncate);
    if(!file.isOpen())
    {
        QMessageBox::information(nullptr, "Erreur", "Le fichier de score n'est pas trouve!");
    }

    file.write(QJsonDocument(array).toJson());

    emit showPanel("Menu");
    /*/
}

void ScoreWindow::load()
{

    QJsonArray root = utils::readJsonFile(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_track +".score");
    for(int i=0;i<root.count();i++)
    {
        QJsonObject item =root[i].toObject();
        Score * score = new Score(item["Time"].toDouble(),item["Name"].toString());
        m_scoreVector.append(score);
     }
}

void ScoreWindow::loadTableView()
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

int ScoreWindow::ranked() const
{

    for(int cpt = 0;cpt<(m_scoreVector.size());cpt++)
    {
        if(m_time < m_scoreVector[cpt]->time())
            return cpt;
    }
    if(m_scoreVector.size()<10)
        return m_scoreVector.size();
    return 10;
}

void ScoreWindow::backToMenu()
{
    emit showPanel("Menu");
}

void ScoreWindow::loaded(QString, QVector<Score *> scores)
{
    m_scoreVector = scores;

    m_rank = ranked();
    if(m_rank<10)
    {
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addScore()));
        m_scoreVector.insert(m_rank,new Score(m_time,"YOURNAME"));
        if(m_scoreVector.size()>10)
        {
            delete m_scoreVector[10];
            m_scoreVector.remove(10);
        }
        ui->textLabel->setText("Good Game ! you're in the position : " + QString::number(m_rank+1) + ".Your time is : "+ utils::showableTime(m_time) + ". Please enter your name to save this time :" );
        ui->pushButton->setText("Confirm & Back to the menu");
        ui->nameText->insertPlainText("YOURNAME");
    }
    else
    {
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(backToMenu()));
        ui->nameText->hide();
    }

    loadTableView();
}

void ScoreWindow::error(QString errorMsg)
{
    // NOTE: on devrait ptêt aussi connecter le bouton pour qu'il fasse retour en cas d'erreur,
    //       pour ne pas être bloqué sur cette page.
    QMessageBox::information(this, "Error", errorMsg, 0);
}
