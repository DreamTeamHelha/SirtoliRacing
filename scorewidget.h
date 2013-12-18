#pragma once

#include "panel.h"
#include "tracklist.h"
#include "scoremanager.h"
#include "score.h"
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
    void loadTableView();


private:

    Ui::ScoreWidget *ui;
    TrackList *m_trackList;
    ScoreManager *m_scoreManager;
    QVector<Score*> m_scoreVector;

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

    /// Appelé lorsque le scoreManager a reçu les scores demandés
    void loaded(QString, QVector<Score*>);

    /// Appelé lors d'une erreur du scoreManager.
    void error(QString);

};
