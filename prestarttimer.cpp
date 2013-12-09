#include "prestarttimer.h"
#include <QTimerEvent>
#include <QObject>

PreStartTimer::PreStartTimer(QObject *parent) :
    QObject(parent),
    m_timeRemaining(3)
{
}

void PreStartTimer::startTimer()
{
    QObject::startTimer(1000);
}

void PreStartTimer::timerEvent(QTimerEvent *event)
{
    if(m_timeRemaining)
        m_timeRemaining--;
    else
    {
        emit startGame();
        killTimer(event->timerId());
    }
}

int PreStartTimer::timeRemaining()const
{
    return m_timeRemaining;
}
