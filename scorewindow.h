#pragma once

#include "score.h"
#include <QString>
#include "panel.h"
#include <QWidget>
#include "scoremanager.h"

using namespace std;

namespace Ui {
class ScoreWindow;
}

class ScoreWindow : public Panel
{
    Q_OBJECT

public:

    explicit ScoreWindow(QWidget *parent = 0,int time =0,QString track = "noTrack");
    ~ScoreWindow();

    void loadTableView();
    int  ranked() const;

private slots:

    /// Appelé lorsque le scoreManager a reçu les scores demandés
    void loaded(QString, QVector<Score*>);

    /// Appelé lors d'une erreur du scoreManager.
    /// Affiche le message dans une MessageBox.
    void error(QString);

    void addScore();
    void backToMenu();

private:

    Ui::ScoreWindow   *ui;
    int               m_time;
    int               m_rank;
    QString           m_track;
    QVector<Score *>  m_scoreVector;
    ScoreManager    * m_scoreManager;
};
