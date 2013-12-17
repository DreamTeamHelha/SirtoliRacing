#pragma once

///
/// Classe encapsulant la gestion des contrôle de jeu.
///
class PlayerInput
{
public:

    PlayerInput();

    bool throttle() const;
    void setThrottle(bool enabled);

    bool brakes() const;
    void setBrakes(bool enabled);

    bool turnLeft() const;
    void setTurnLeft(bool enabled);

    bool turnRight() const;
    void setTurnRight(bool enabled);

    bool pause() const;
    void setPause(bool enabled);

private:

    bool m_throttle;//condition accelerer
    bool m_brakes;// condition freiner
    bool m_turnLeft;//condition tourner gauche
    bool m_turnRight;//condition tourner a droite
    bool m_pause;// condition avec pause
};
