#ifndef JUKEBOX_H
#define JUKEBOX_H
#include "QVector"
#include "QSound"
class JukeBox
{
public:
    JukeBox(int currentIndex=0);
    ~JukeBox();
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
    /// Renvoie la musique à afficher de la musique courante
    ///
    QString currentTrackName()const;

    ///
    /// Permet de charger la liste des circuits et de leur nom à afficher
    ///
    ///
    void load();
    ///
    /// \brief playSong
    /// \param musicName
    ///Permet je jouer le song, detruit le song précédent s'il existe
    ///
    void playSong(QString musicName);
    ///
    ///Permet de couper le son TOTALEMENT
    ///
    void stopPlay();





private:


    QVector<QString> m_trackList;
    QVector<QString> m_nameList;
    int              m_currentIndex;
    QSound           *m_sound;

private slots:
    void nextTrack();

    ///
    /// Affiche le circuit précédent
    ///
    void previousTrack();

};

#endif // JUKEBOX_H
