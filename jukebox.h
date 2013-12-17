#pragma once

#include "QVector"
#include "QSound"
class JukeBox
{
public:
    ///
    /// Constructeur
    ///
    JukeBox(int currentIndex=0);

    ///
    /// Destructeur
    ///
    ~JukeBox();

    ///
    /// Constructeur de copie
    ///
    JukeBox(const JukeBox& copy);

    ///
    /// Opérateur d'affectation
    ///
    JukeBox& operator=(const JukeBox& other);

    ///
    /// Modifie la liste de musiques
    ///
    void setTrackList(QVector<QString>);

    ///
    /// Modifie la liste de musiques
    ///
    void setNameList(QVector<QString>);

    ///
    /// Lance la musique suivante
    ///
    void next();

    ///
    /// Lance la musique précédente
    ///
    void previous();

    ///
    /// Renvoie le nom de la musique actuel, renvoi le nom du fichier
    ///
    QString currentTrack()const;


    ///
    /// Permet de charger la liste des musiques
    ///
    ///
    void load();

    ///
    ///Permet de jouer une chanson, detruit le song précédent si elle existe
    ///
    void playSong(QString musicName);

    ///
    ///Permet de couper la musique
    ///
    void stopPlay();





private:


    QVector<QString> m_trackList;//vector recevant les nom de musique
    int              m_currentIndex;// indice de la musique en cours
    QSound           *m_sound;//point qsound

private slots:

    ///
    /// Joue la chanson suivante
    ///
    void nextTrack();

    ///
    /// Joue la chanson précédente
    ///
    void previousTrack();

};

