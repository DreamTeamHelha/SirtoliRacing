#pragma once

#include "object.h"
#include "objectfactory.h"
#include "tilemap.h"

class Car : public Object
{
public:

    ///
    /// Constructeur
    ///
    Car(QGraphicsItem *graphicsItem=nullptr, b2Body *physicsBody=nullptr);

    ///
    /// Constructeur de copie
    ///
    Car(const Car &copy);

    ///
    /// Opérateur d'affectation
    ///
    Car& operator=(const Car &car);

    ///
    /// Destructeur
    ///
    ~Car();

    ///
    /// Défini le comportement de la voiture
    ///
    void step(qreal throttle, qreal brakes, qreal steering);

    ///
    /// Getters - Setters
    ///
    Tilemap *tilemap() const;
    void setTilemap(Tilemap *tilemap);

    float accelRate          (GroundType groundType) const;
    float brakeRate          (GroundType groundType) const;
    float maxTorque          (GroundType groundType) const;
    float angularAccel       (GroundType groundType) const;
    float maxLateralFriction (GroundType groundType) const;

    void setAccelRate          (GroundType groundType, float value);
    void setBrakeRate          (GroundType groundType, float value);
    void setMaxTorque          (GroundType groundType, float value);
    void setAngularAccel       (GroundType groundType, float value);
    void setMaxLateralFriction (GroundType groundType, float value);

private:

    Tilemap *m_tilemap;

    ///
    /// Propriétés de comportement
    ///
    float m_accelRate[GroundType::_count];          // facteur d'accélération
    float m_brakeRate[GroundType::_count];          // facteur de freinage / marche arrière
    float m_maxTorque[GroundType::_count];          // vitesse de rotation maximale
    float m_angularAccel[GroundType::_count];       // accélération angulaire (direction)
    float m_maxLateralFriction[GroundType::_count]; // adhérence
};


class CarFactory : public ObjectFactory
{
public:

    ///
    /// Crée un objet 'Car' et le retourne
    ///
    Object *create() const;
};
