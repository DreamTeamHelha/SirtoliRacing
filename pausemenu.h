#pragma once
#include "panel.h"
#include <QPushButton>
#include <QTime>

class PauseMenu : public Panel
{
    Q_OBJECT
public:
    PauseMenu(const int,QWidget *);
    ~PauseMenu();
    int time()const;

public slots:
    ///
    /// \brief continueClicked permet de continuer le jeu
    ///
    void continueClicked();
    ///
    /// \brief quitClicked permet de quitter la partie et retourner  au menu
    void quitClicked();
signals:
    ///
    /// \brief continueGame casse la pause
    ///
    void continueGame();

private:
    QPushButton *m_continueButton;
    QPushButton *m_quitButton;
    int        m_time;//temps du joueur

};

