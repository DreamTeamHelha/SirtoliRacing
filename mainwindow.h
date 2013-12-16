#pragma once

#include <QMainWindow>
#include <QString>
#include "panel.h"
#include "gamewidget.h"
#include "settings.h"
#include "jukebox.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include<QVideoWidget>
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

    ///
    /// Constructeur
    ///
    explicit MainWindow(QWidget *parent = 0);

    ///
    /// Destructeur
    ///
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

    ///
    /// Stop la musique
    ///
    void playStopTrack();
    ///
    ///Load les pusique et les met dans la playlist
    ///
    void load();
    ///
    ///AfficherMenu+playlist
    ///
    void lancerMenu();




protected:
    ///
    /// Gère les événements du clavier
    ///
    void keyPressEvent(QKeyEvent *event);



private:

    Ui::MainWindow *ui;
    QMediaPlaylist *m_playlist;
    QMediaPlayer *m_player;
    QVideoWidget *m_videoWidget;
    Panel      *m_panel;
    GameWidget *m_gameWidget;
    bool m_musicPlay;

};

