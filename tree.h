#pragma once

#include "object.h"
#include "objectfactory.h"

class Tree : public Object
{
public:
    Tree(QGraphicsItem *graphicsItem, b2Body *physicsBody);

    Tree(const Tree &copy);

    Tree& operator =(const Tree &t);

};

class TreeFactory : public ObjectFactory
{
public:

    Object *create() const;
};
