#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QVector>
#include "score.h"

///
/// Classe permettant la récupération et l'envoi de scores au serveur.
/// Attention : il ne peut gérer qu'une seule demande à la fois!
///
class ScoreManager : public QObject
{
    Q_OBJECT

public:

    explicit ScoreManager(QObject *parent = 0);
    ~ScoreManager();

    ///
    /// True si le scoreManager est déjà en train de gérer une demande.
    ///
    bool locked() const;

signals:

    ///
    /// Signal envoyé lorsque les scores d'un circuit ont été reçus
    ///
    void scoreReceived(QString, QVector<Score*>);

    ///
    /// Signal envoyé lorsque les scores d'un circuit ont bien été envoyés
    ///
    void scoreSent();

    ///
    /// Signal envoyé en cas d'erreur
    ///
    void error(QString);

public slots:

    ///
    /// Envoie le tableau des scores pour un circuit.
    ///
    void sendScores(QString trackName, QVector<Score*> scores);

    ///
    /// Demande le tableau des scores pour un ciruit.
    ///
    void getScores(QString trackName);

private slots:

    ///
    /// Gère la réponse du serveur
    ///
    void replyFinised(QNetworkReply *);

private:

    QNetworkAccessManager * m_networkAccessManager;
    QString m_trackName;
    bool    m_get;
    bool    m_lock; // true lorsque le scoremanager est en train de gérer une demande.

    static const QString m_baseUrl; // adresse du serveur
};

