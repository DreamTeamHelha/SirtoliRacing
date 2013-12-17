#pragma once
#include <QWidget>
#include "panel.h"

namespace Ui {
class Help;
}

class Help : public Panel
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();
private slots:
    ///
    /// \brief backToMenu afficher le menu
    ///
    void backToMenu();

private:
    Ui::Help *ui;
};


