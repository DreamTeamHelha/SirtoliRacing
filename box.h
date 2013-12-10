#pragma once

#include "object.h"
#include "objectfactory.h"

class Box : public Object
{
public:

    ///
    /// Constructeur
    ///
    Box(QGraphicsItem *graphicsItem=nullptr, b2Body *physicsBody=nullptr);

    ///
    /// Constructeur de copie
    ///
    Box(const Box &b);

    ///
    /// Opérateur d'affectation
    ///
    Box& operator=(const Box &b);

    ///
    ///Destructeur
    ///
    ~Box();
};


class BoxFactory : public ObjectFactory
{
public:

    /// Crée un objet 'Box' et le retourne
    Object *create() const;
};
