#pragma once
#include "object.h"
#include "objectfactory.h"

class Checkpoint : public Object
{
private:
    bool m_touched;
public:
    ///
    /// Constructeur
    ///
    Checkpoint(QGraphicsItem *graphicsItem=nullptr, b2Body *physicsBody=nullptr);

    ///
    /// Constructeur de copie
    ///
    Checkpoint(const Checkpoint & copy);

    ///
    ///
    ///
    Checkpoint& operator =(const Checkpoint & check);


    ///Permet de spécifier au Checkpoint qu'il est touché
    void touch();

    ///Permet de savoir si le Checkpoint a déjà été touché
    bool touched();

};

class CheckpointFactory : public ObjectFactory
{
public:

    ///Crée un objet 'Checkpoint' et le retourne
    Object *create() const;
};
