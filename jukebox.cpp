#include "jukebox.h"
#include"QString"
#include"QMessageBox"
#include"QJsonDocument"
#include"QStandardItemModel"
#include"QJsonArray"
#include"QJsonObject"
#include"QList"
#include"QFile"
#include"QCoreApplication"
#include "QSound"
#include<iostream>
JukeBox::JukeBox(int currentIndex):
    m_currentIndex(currentIndex),
    m_sound(nullptr)
{
    m_trackList = QVector<QString>();
    m_nameList = QVector<QString>();
}

JukeBox::~JukeBox()
{
    if(!m_sound)
    {
        delete m_sound;
        m_sound=nullptr;
    }
}

void JukeBox::setTrackList(QVector<QString>trackList)
{
    m_trackList=trackList;
}

void JukeBox::setNameList(QVector<QString>nameList)
{
    m_nameList=nameList;
}

void JukeBox::next()
{
    if(m_currentIndex == (m_trackList.size()-1))
    {
        m_currentIndex=0;
    }
    else
    {
        m_currentIndex++;
    }
}

void JukeBox::previous()
{
    if(m_currentIndex == 0)
    {
        m_currentIndex = m_trackList.size()-1;
    }
    else
    {
        m_currentIndex--;
    }

}

QString JukeBox::currentTrackName()const
{
   return m_nameList.at(m_currentIndex);
}

void JukeBox::load()
{
    QString val;
    QJsonObject item;
    QFile file(QCoreApplication::applicationDirPath() + "/data/jukebox.json");

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
    {
        return;
    }

    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isEmpty())
    {
        return;
    }

    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {
        item =root[i].toObject();
        m_trackList.append(item["track"].toString());
        m_nameList.append(item["name"].toString());
    }
    m_currentIndex=0;
}

QString JukeBox::currentTrack()const
{
        return m_trackList.at(m_currentIndex);
}
void JukeBox::playSong(QString musicName)
{
    if(m_sound)
    {
        delete m_sound;
        m_sound= nullptr;
    }
    //std::cout<<musicName;
    if(!m_sound)
    {
    m_sound= new QSound(QCoreApplication::applicationDirPath() + "/data/sons/"+musicName);
    m_sound->play();
    }

}

void JukeBox::stopPlay()
{
    if(m_sound)
    {
        delete m_sound;
        m_sound= nullptr;
    }
   // m_sound->stop();
}
