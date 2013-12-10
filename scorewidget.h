#pragma once

#include "panel.h"
#include "tracklist.h"
namespace Ui {
class ScoreWidget;
}

class ScoreWidget : public Panel
{
    Q_OBJECT

public:

    ///
    /// Constructeur
    ///
    explicit ScoreWidget(QWidget *parent = 0);

    ///
    /// Destructeur
    ///
    ~ScoreWidget();

    ///
    /// Permet le chargement de la liste des scores du circuit sélectionnés
    ///
    void load();


private:

    Ui::ScoreWidget *ui;
    TrackList *m_trackList;
private slots:

    void afficherMenu();
    ///
    /// Affiche le circuit suivant
    ///
    void nextTrack();

    ///
    /// Affiche le circuit précédent
    ///
    void previousTrack();

};
