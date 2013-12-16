#include "utils.h"
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>

QString utils::showableTime(int ms)
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

QJsonArray utils::readJsonFile(QString path)
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

