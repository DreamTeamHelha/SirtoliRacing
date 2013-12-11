#pragma once

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>

namespace utils
{
    inline float pi()
    {
        return 3.14159265;
    }

    inline float toRadians(float degrees)
    {
        return pi() * degrees / 180;
    }

    inline float toDegrees(float radians)
    {
        return 180 * radians / pi();
    }
    inline QString showableTime(int ms)
    {
        QChar character(0x30);
        ms/=10;
        int csec = ms%100;
        ms/=100;
        int sec = ms%60;
        ms/=60;
        QString time;
        time= QString ("%1:%2:%3")
               .arg(ms,2,10,character)
               .arg(sec,2,10,character)
               .arg(csec,2,10,character);
        return time;

    }

    inline QJsonArray readJsonFile(QString path)
    {
        QFile file(path);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!file.isOpen())
        {
            QMessageBox::information(nullptr,"Erreur","Le fichier n'est pas disponible!");
        }

        QString val = file.readAll();
        file.close();

        QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
        if(document.isEmpty())
        {
            QMessageBox::information(nullptr,"Erreur","Le fichier est vide!");
        }

        return document.array();
    }

}
