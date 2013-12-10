#pragma once

#include <QMainWindow>
#include <QString>
#include "panel.h"
#include "gamewidget.h"
#include "settings.h"
#include "jukebox.h"
namespace Ui {
class MainWindow;
}

///
/// Fenêtre principale. Créée au début du jeu, détruite à la fin.
/// Contient les différents panels de menu, ainsi que gamewidget.
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ///
    /// Getters
    ///
    Panel      *panel() const;
    GameWidget *gameWidget() const;

public slots:

    ///
    /// Provoque le changement de menu
    ///
    void showPanel(const QString& menuName);

    ///
    /// Provoque le lancement du jeu.
    ///
    void startGame(const QString& levelName, const QString& carClassName,Settings *setting );

    ///
    /// Provoque la mise en pause du jeu
    ///
    void pauseGame(QTime);

    ///
    /// Provoque la fin de la pause
    ///
    void continueGame();
    ///
    /// Appel la musique suivante
    ///
    void nextTrack();
    ///
    /// Appel la musique précédente
    ///
    void previousTrack();
    ///
    /// Stop la musique
    ///
    void playStopTrack();

protected:
    ///
    /// Gère les événements du clavier
    ///
    void keyPressEvent(QKeyEvent *event);



private:

    Ui::MainWindow *ui;

    Panel      *m_panel;
    GameWidget *m_gameWidget;
    JukeBox *m_JukeBox;
    bool m_musicPlay;
};

