#pragma once

#include "object.h"
#include "objectfactory.h"

class Box : public Object
{
public:

    Box(QGraphicsItem *graphicsItem, b2Body *physicsBody);
};


class BoxFactory : public ObjectFactory
{
public:

    /// Crée un objet 'Box' et le retourne
    Object *create() const;
};
