#include <QApplication>
#include "objectfactories.h"
#include "mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>

/*
class Test : public QObject
{
    Q_OBJECT

public:

    void test()
    {
        QNetworkAccessManager * manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(reply(QNetworkReply*)));

        QNetworkRequest request(QUrl("localhost/SirtoliRacing/level1.json"));

        manager->get(request);
    }



    void reply(QNetworkReply *);
};

void Test::reply(QNetworkReply * reply)
{
    QMessageBox::information(nullptr, "Test", "Réception de la réponse");
}
//*/

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

    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}
