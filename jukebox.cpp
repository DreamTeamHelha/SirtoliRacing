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
}

JukeBox::~JukeBox()
{
    if(m_sound)
    {
        delete m_sound;
        m_sound=nullptr;
    }
}

JukeBox::JukeBox(const JukeBox &copy):
    m_currentIndex(copy.m_currentIndex)
{
    m_sound = copy.m_sound;
    m_trackList = copy.m_trackList;
}

JukeBox& JukeBox::operator =(const JukeBox& other)
{
    if(this != &other)
    {
        m_currentIndex = other.m_currentIndex;
        delete m_sound;
        m_sound = other.m_sound;
        m_trackList = other.m_trackList;
    }
}

void JukeBox::setTrackList(QVector<QString>trackList)
{
    m_trackList=trackList;
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
}
