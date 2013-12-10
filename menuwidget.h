#pragma once

#include "panel.h"
#include <QSound>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public Panel
{
    Q_OBJECT

public:

    ///
    /// Constructeur
    ///
    explicit MenuWidget(QWidget *parent = 0);

    ///
    /// Destructeur
    ///
    ~MenuWidget();

private slots:

    ///
    /// Affiche les scores des différents circuits
    ///
    void showScore();

    ///
    /// Quitte l'application
    ///
    void exitApp();

    ///
    /// Affiche le choix de niveau pour commencer une partie
    ///
    void showChoose();

    ///
    /// Affiche les crédits
    ///
    void showCredits();

private:

    Ui::MenuWidget *ui;


};
