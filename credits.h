#pragma once

#include <QWidget>
#include "panel.h"
namespace Ui {
class credits;
}

class credits : public Panel
{
    Q_OBJECT

public:

    ///
    /// Constructeur
    ///
    explicit credits(QWidget *parent = 0);

    ///
    /// Destructeur
    ///
    ~credits();
public slots:

    ///
    /// Slot permettant de retourner au menu principal
    ///
    void afficherMenu();

private:
    Ui::credits *ui;
};

