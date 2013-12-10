#pragma once

#include <QWidget>
#include "tracklist.h"
#include "panel.h"

namespace Ui {
class ChooseWidget;
}

class ChooseWidget : public Panel
{
    Q_OBJECT

public:

    ///
    /// Constructeur
    ///
    explicit ChooseWidget(QWidget *parent = 0);

    ///
    ///Destructeur
    ///
    ~ChooseWidget();

private slots:

    ///
    /// Lance le jeu avec le circuit choisis
    ///
    void launchGame();

    ///
    /// Affiche le circuit suivant
    ///
    void nextTrack();

    ///
    /// Affiche le circuit précédent
    ///
    void previousTrack();

    ///
    /// Affiche le menu principal
    ///
    void backToMenu();

private:
    Ui::ChooseWidget *ui;
    TrackList        *m_trackList;
};

