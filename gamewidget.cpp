#include "gamewidget.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>
#include <QKeyEvent>
#include "utils.h"
#include <iostream>
#include "mainwindow.h"
#include "pausemenu.h"

GameWidget::GameWidget(Scene *scene, QWidget *parent) :
    QGraphicsView(parent),
    m_scene(scene),
    m_timeLabel(this),
    m_checkpointRemainingLabel(this),
    m_paused(false),
    m_cameraScale(1.f),
    m_frameCount(0),
    m_timeBeforeStartLabel(this)
{
    if (!scene)
    {
        QMessageBox::information(nullptr, "Erreur (GameWidget)", "Aucune scène a afficher!", 0);
    }
    else if (!scene->loaded())
    {
        QMessageBox::information(nullptr, "Erreur (GameWidget)", "Le niveau n'a pas été chargé!", 0);
    }
    else
    {       
        this->setCursor(Qt::BlankCursor);

        //Placement du label du timer
        m_timeLabel.setGeometry(0,0,500,50);
        m_timeLabel.setStyleSheet("color: white;font: 24pt \"Leelawadee UI\";");

        //Placement du label du nombre de checkpoints restants
        m_checkpointRemainingLabel.setGeometry(parent->width()-250,0,250,50);
        m_checkpointRemainingLabel.setStyleSheet("color: white;font: 14pt \"Leelawadee UI\";");

        //Placement du label du affichant le temps avant le début de la partie
        m_timeBeforeStartLabel.setGeometry(350,250,100,100);
        m_timeBeforeStartLabel.setStyleSheet("font: 72pt \"Leelawadee UI\";");

        // prépare la scène pour l'affichage
        this->setScene(scene->graphicsScene());
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // réglages du clavier
        grabKeyboard();
        scene->setPlayerInput(&m_playerInput);

        // démarrage du timer de rafraichissement du jeu
        startTimer(sf::seconds(1/60.f).asMilliseconds());

        //Centrage de la caméra
        View view = m_scene->calcViewPoint();
        centerOn(view.position());

        //Démarrage du timer de début de course ( 3,2,1 -> Go)
        m_preStartTimer = new PreStartTimer(this);
        m_preStartTimer->startTimer();
        connect(m_preStartTimer,SIGNAL(startGame()),this,SLOT(startGame()));

    }
}

GameWidget::~GameWidget()
{
    if (m_scene)
        delete m_scene;
    if(m_preStartTimer)
        delete m_preStartTimer;

}

Scene *GameWidget::scene() const
{
    return m_scene;
}

const PlayerInput& GameWidget::playerInput() const
{
    return m_playerInput;
}

bool GameWidget::paused()const
{
    return m_paused;
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        m_playerInput.setThrottle(true);
        break;

    case Qt::Key_Down:
        m_playerInput.setBrakes(true);
        break;

    case Qt::Key_Left:
        m_playerInput.setTurnLeft(true);
        break;

    case Qt::Key_Right:
        m_playerInput.setTurnRight(true);
        break;

    case Qt::Key_Escape:
        m_playerInput.setPause(true);
        pause();
        break;

    default:
         QGraphicsView::keyPressEvent(event);
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        m_playerInput.setThrottle(false);
        break;

    case Qt::Key_Down:
        m_playerInput.setBrakes(false);
        break;

    case Qt::Key_Left:
        m_playerInput.setTurnLeft(false);
        break;

    case Qt::Key_Right:
        m_playerInput.setTurnRight(false);
        break;

    case Qt::Key_Escape:
        m_playerInput.setPause(false);
        break;

    default:
         QGraphicsView::keyReleaseEvent(event);
    }
}

void GameWidget::timerEvent(QTimerEvent *timerEvent)
{
    //Vérifie si la partie a déjà commencé ou non
    if(m_preStartTimer->timeRemaining())
    {
        m_timeBeforeStartLabel.setText(QString::number(m_preStartTimer->timeRemaining()));
    }
    else{
        //Vérifie si le jeu est en pause ou non
        if(!m_paused)
        {
            if (m_scene)
            {
                //Vérifie si le jeu est en pause
                if(m_scene->isFinished())
                {
                    killTimer(timerEvent->timerId());
                    emit showScore("EndGame");
                }
                //Gère les actions dans le cas où la partie est en cours
                else
                {
                    /// mise à jour de la scène
                    m_scene->update();

                     /// mise à jour de la caméra
                    View view = m_scene->calcViewPoint();
                    centerOn(view.position());
                    // "crante" l'effet de zoom, car visiblement, changer l'échelle de la vue dans qt prend du temps
                    // et ralenti considérablement le jeu lorsque cela est fait à chaque frame.
                    //float zoom = (int)(view.zoom()*200)/200.f;
                    //std::cout << view.zoom() << " --- " << zoom << " --- " << m_cameraScale << std::endl;
                    //view.setZoom(.7);
                    m_frameCount++;
                    if (m_frameCount == 3)
                        m_frameCount = 0;
                    if (m_frameCount == 0)
                    {
                        if (view.zoom() != m_cameraScale)
                        {
                            float cameraScale = 1 - (m_cameraScale - view.zoom());
                            m_cameraScale = view.zoom();
                            scale(cameraScale, cameraScale);
                        }
                    }

                    /// mise à jour du compteur (Affichage
                    m_timeLabel.setText(utils::showableTime(m_scene->time().elapsed()));

                    /// mise à jour du nombre de checkpoint restant (Affichage)
                    QString checkpointRemainingString = "Checkpoint(s) Remaining : "+QString::number(m_scene->checkpointListener()->checkpointRemaining());
                    m_checkpointRemainingLabel.setText(checkpointRemainingString);
                }
            }
        }
    }
}

void GameWidget::pause()
{
    if(!m_paused)
    {
        this->setCursor(Qt::ArrowCursor);
        m_paused=true;
        emit gamePaused(m_scene->time());

    }
}

void GameWidget::setPaused(bool paused)
{
    m_paused=paused;
}

void GameWidget::startGame()
{
    m_timeBeforeStartLabel.hide();
    m_scene->start();

}
