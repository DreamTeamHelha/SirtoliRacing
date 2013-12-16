#pragma once

#include "object.h"
#include "objectfactory.h"

///
/// Crée une boite
///
class BoxFactory : public ObjectFactory
{
public:

    Object *create() const;
};
