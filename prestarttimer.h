#pragma once

#include <QObject>

class PreStartTimer : public QObject
{
    Q_OBJECT
public:
    explicit PreStartTimer(QObject *parent = 0);
    void timerEvent(QTimerEvent *);
    int timeRemaining()const;
    void startTimer();

signals:
    void startGame();

public slots:

private:
    int m_timeRemaining;

};

