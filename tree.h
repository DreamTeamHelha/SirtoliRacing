#pragma once

#include "object.h"
#include "objectfactory.h"

///
/// Crée un arbre
///
class TreeFactory : public ObjectFactory
{
public:

    Object *create() const;
};
