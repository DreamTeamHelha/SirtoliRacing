#include <QApplication>
#include "objectfactories.h"
#include "mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QLayout>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    // initialisation des factories
    ObjectFactories::initialize();

    // création de la fenêtre et exécution
    MainWindow w;
    w.setFixedSize(800,600);
    w.show();
    w.setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/data/icon.ico"));

    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}
