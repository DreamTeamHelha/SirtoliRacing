#include <QApplication>
#include "objectfactories.h"
#include "mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    //Test test;
    //test.test();

    // initialisation des factories
    ObjectFactories::initialize();

    // création de la fenêtre et exécution
    MainWindow w;
    w.show();
    w.setMaximumSize(800,600);
    w.setMinimumSize(800,600);
    w.setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/data/icon.ico"));

    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}
