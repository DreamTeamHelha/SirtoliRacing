#include "objectloader.h"
#include "objectfactories.h"
#include <iostream>
#include "rotation.h"
#include "vector.h"
#include <cstdlib>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include "checkpoint.h"

using namespace::std;

ObjectLoader::ObjectLoader(Scene *scene, const QString &carClassName) :
    m_scene(scene),
    m_carClassName(carClassName),
    m_checkpointCount(0)
{}

ObjectLoader::ObjectLoader(const ObjectLoader &copy):m_scene(copy.m_scene),m_carClassName(copy.m_carClassName)
{}

ObjectLoader& ObjectLoader::operator=(const ObjectLoader &objLoad){
     if(this!=&objLoad)
     {
         delete m_scene;
         this->m_scene= new Scene(*objLoad.m_scene);
         this->m_carClassName=objLoad.m_carClassName;
     }
     return *this;
 }

Scene *ObjectLoader::scene()const
{
    return m_scene;
}

const QString& ObjectLoader::carClassName() const
{
    return m_carClassName;
}

bool ObjectLoader::load(const QString& filename)
{
    if (!m_scene)
        return false;

    QJsonObject item;
    QString className;

    QJsonArray root = utils::readJsonFile(filename);
    for(int i=0;i<root.count();i++)
    {
        item =root[i].toObject();
        className=item["class"].toString();
        float x=item["x"].toDouble();
        float y=item["y"].toDouble();
        Rotation rotation=Rotation::degrees(item["rot"].toDouble());
        Vector position(x,y);

        ObjectFactory *objectFactory(nullptr);

        /// Cas spécial : l'objet playerStart définis la position et la rotation de la voiture du joueur.
        if (className == "PlayerStart")
        {
           objectFactory = ObjectFactories::getFactory(m_carClassName);
           if (objectFactory)
           {
               m_scene->createPlayerCar(position, rotation, objectFactory);
           }
        }
        /// Sinon on recherche la factory et on crée un objet avec.
        else
        {
            objectFactory = ObjectFactories::getFactory(className);
            if(objectFactory)
            {
                objectFactory->setScene(m_scene);
                objectFactory->setPosition(position);
                objectFactory->setRotation(rotation);
                Object *obj=objectFactory->create();
                if(obj)
                {
                    m_scene->addObject(obj);

                    // compte les checkpoints
                    if (dynamic_cast<Checkpoint*>(obj))
                        m_checkpointCount++;
                }
            }
         }
    }
    return true;
}

int ObjectLoader::checkpointCount() const
{
    return m_checkpointCount;
}
