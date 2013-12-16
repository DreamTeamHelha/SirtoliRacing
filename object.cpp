#include "object.h"
#include "utils.h"

Object::Object(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    m_graphicsItem(graphicsItem),
    m_physicsBody(physicsBody)
{
}

Object::Object(const Object & copy) :
    m_graphicsItem(copy.m_graphicsItem),
    m_physicsBody(copy.m_physicsBody)
{
}

Object& Object::operator=(const Object &obj)
{
    if(this != &obj)
    {
        m_graphicsItem = obj.m_graphicsItem;
        m_physicsBody =  obj.m_physicsBody;
    }
    return *this;
}

Object::~Object()
{
    // rien à supprimer,
    // graphicsItem et physicsBody sont en aggrégation externe.
}


QGraphicsItem *Object::graphicsItem() const
{
    return m_graphicsItem;
}

b2Body *Object::physicsBody() const
{
    return m_physicsBody;
}

void Object::update()
{
    using utils::toDegrees;

    if (m_graphicsItem && m_physicsBody)
    {
        m_graphicsItem->setPos(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y);
        m_graphicsItem->setRotation(toDegrees(m_physicsBody->GetAngle()));
    }
}
