#include "scoremanager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QNetworkRequest>

const QString ScoreManager::m_baseUrl = "http://193.190.66.14:6080/SirtoliRacing/";

ScoreManager::ScoreManager(QObject *parent) :
    QObject(parent),
    m_networkAccessManager(new QNetworkAccessManager(this)),
    m_get(false),
    m_lock(false)
{
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinised(QNetworkReply*)));
}

ScoreManager::~ScoreManager()
{
    delete m_networkAccessManager;
}

bool ScoreManager::locked() const
{
    return m_lock;
}

void ScoreManager::sendScores(QString trackName, QVector<Score*> scores)
{
    if (m_lock)
    {
        emit error("ScoreManager locked!");
        return;
    }

    QJsonArray jArray;
    for (Score * score : scores)
    {
        QJsonObject jObject;
        jObject.insert("Name", score->name());
        jObject.insert("Time,", score->time());
        jArray.append(jObject);
    }

    QJsonDocument jDoc(jArray);
    QNetworkRequest request(QUrl(m_baseUrl + "setTrack/" + m_trackName));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_networkAccessManager->post(request, jDoc.toJson());

    m_get = false;
    m_trackName = trackName;
}

void ScoreManager::getScores(QString trackName)
{
    if (m_lock)
    {
        emit error("ScoreManager locked!");
        return;
    }

    m_networkAccessManager->get(QNetworkRequest(QUrl(m_baseUrl + "track/" + trackName)));
    m_get = true;
    m_trackName = trackName;
}

void ScoreManager::replyFinised(QNetworkReply * reply)
{
    // gestion des erreurs
    if (reply->error() != QNetworkReply::NoError)
    {
        emit error(reply->errorString());
    }
    // gestion des résultats
    else
    {
        if (m_get) // réponse à une demande de réception des scores
        {
            QByteArray bytes = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(bytes);
            if (jDoc.isEmpty())
            {
                emit error("Empty document!");
            }
            else
            {
                QJsonArray jArray = jDoc.array();
                QVector<Score*> scores;

                for (int i=0; i<jArray.count(); i++)
                {
                    QJsonObject jObject = jArray[i].toObject();
                    Score * score = new Score(
                            jObject["Time"].toDouble(),
                            jObject["Name"].toString());
                    scores.append(score);
                }

                emit scoreReceived(m_trackName, scores);
            }
        }
        else // réponse à un envoi des scores
        {
            emit scoreSent();
        }
    }
    m_lock = false; // déverouille le scoremanager
}
