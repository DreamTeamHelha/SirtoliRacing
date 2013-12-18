#include "scene.h"
#include "utils.h"
#include <SFML/System/Time.hpp>
#include <QCoreApplication>
#include <QGraphicsItem>
#include "objectfactories.h"
#include "tilemaploader.h"
#include "objectloader.h"
#include "vector.h"
#include <QMessageBox>
#include <iostream>

Scene::Scene() :
    m_graphicsScene(new QGraphicsScene),
    m_physicsWorld(new b2World(Vector(0,0))),
    m_playerInput(nullptr),
    m_car(nullptr),
    m_tilemap(nullptr),
    m_loaded(false),
    m_checkpointListener(new CheckpointListener),
    m_time(),
    m_dynamicZoom(false)
{
    //Ajout du listener de contact
    m_physicsWorld->SetContactListener(m_checkpointListener);

    std::cout << "Zoom dynamique = " << m_dynamicZoom << std::endl;
}

Scene::~Scene()
{
    for (Object *object : m_objects)
    {
        delete object;
    }
    m_objects.clear();
    delete m_graphicsScene;
    delete m_tilemap;
}

QGraphicsScene *Scene::graphicsScene() const
{
    return m_graphicsScene;
}

b2World *Scene::physicsWorld() const
{
    return m_physicsWorld;
}

bool Scene::load(const QString &trackName, const QString &carClassName)
{
    m_trackName = trackName;
    //Permet de vérifier que la scène ne soit pas chargée plusieurs fois
    if(m_loaded)
    {
        return false;
    }

    std::cout << "Chargement de la tilemap" << std::endl;
    //Chargement de la map
    m_tilemap= TilemapLoader::load(QCoreApplication::applicationDirPath()+"/data/tracks/"+m_trackName+".png");
    if (!m_tilemap)
    {
        return false;
    }

    std::cout << "LoadMap" << std::endl;
    if(!loadMap())
    {
        return false;
    }

    std::cout << "Chargement des objets" << std::endl;
    // chargement des objets
    ObjectLoader objectLoader(this, carClassName);
    if (!objectLoader.load(QCoreApplication::applicationDirPath()+"/data/Tracks/"+m_trackName+".json"))
    {
        return false;
    }

    m_checkpointListener->setCheckpointNumber(objectLoader.checkpointCount());
    std::cout << "Fin du chargement" << std::endl;
    m_loaded=true;
    return true;
}

bool Scene::addObject(Object *object)
{
    if (!object)
        return false;

    m_objects.insert(object);
    return true;
}

Car *Scene::createPlayerCar(const Vector &position, const Rotation &rotation, ObjectFactory *carFactory)
{
    // retourne la voiture actuelle si elle est déjà créée,
    // ou bien si aucune factory n'est passée en paramètre
    if (m_car || !carFactory)
    {
        return m_car;
    }

    // réglages pré-création
    carFactory->setScene(this);
    carFactory->setPosition(position);
    carFactory->setRotation(rotation);

    // création, et vérification du type (l'objet créé doit être de la classe Car)
    Object *object = carFactory->create();
    m_car = dynamic_cast<Car*>( object );

    if (m_car)
    {
        addObject(m_car);
        m_view.setPosition(Vector(m_car->physicsBody()->GetPosition()));
    }
    else
    {
        delete object;
        object = nullptr;
    }
    return m_car;
}

const PlayerInput *Scene::playerInput() const
{
    return m_playerInput;
}

void Scene::setPlayerInput(const PlayerInput *playerInput)
{
    m_playerInput = playerInput;
}

Tilemap *Scene::tilemap() const
{
    return m_tilemap;
}

void Scene::update()
{
    /// Commande le véhicule
    if (m_playerInput && m_car)
    {
        m_car->step(m_playerInput->throttle(), m_playerInput->brakes(), m_playerInput->turnRight()-m_playerInput->turnLeft());
    }

    /// Mise à jour de la physique
    m_physicsWorld->Step(sf::seconds(1.f/60.f).asSeconds(), 8, 3);

    /// Mise à jour de tous les objets.
    for (Object *object : m_objects)
    {
        object->update();
    }
}

bool Scene::loadMap()
{
    // chargement des images
    QPixmap *grassTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/GrassTile.png");
    if (grassTile->isNull())
    {
       return false;
    }

    QPixmap *roadTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/RoadTile.png");
    if (roadTile->isNull())
    {
        return false;
    }
    QPixmap *mudTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/MudTile.png");
    if (mudTile->isNull())
    {
        return false;
    }

    // remplissage de la scène graphique avec les tuiles
    for(int x=0;x<m_tilemap->width();x++)
    {
        for(int y=0;y<m_tilemap->height();y++)
        {
            QGraphicsPixmapItem *item;
            switch(m_tilemap->tile(x,y))
            {
            case GroundType::Asphalt :  item = new QGraphicsPixmapItem(*roadTile);
                      break;
            case GroundType::Mud :      item = new QGraphicsPixmapItem( *mudTile);
                      break;
            default : item = new QGraphicsPixmapItem(*grassTile);
            }
            item->setPos(x*32,y*32);
            this->graphicsScene()->addItem(item);
        }
    }

    // ajoute des "murs" autour de la scène pour éviter que des objets ne sortent de la zone de jeu
    Vector v1;
    Vector v2(m_tilemap->width()*32,0.f);
    Vector v3(0.f,m_tilemap->height()*32);
    Vector v4(m_tilemap->width()*32,m_tilemap->height()*32);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    b2Body *body = physicsWorld()->CreateBody(&bodyDef);
    b2EdgeShape lineUp;
    lineUp.Set(v1,v2);
    body->CreateFixture(&lineUp,1);
    b2EdgeShape lineLeft;
    lineLeft.Set(v1,v3);
    body->CreateFixture(&lineLeft,1);
    b2EdgeShape lineRight;
    lineRight.Set(v2,v4);
    body->CreateFixture(&lineRight,1);
    b2EdgeShape lineBottom;
    lineBottom.Set(v3,v4);
    body->CreateFixture(&lineBottom,1);

    return true;
}

View Scene::calcViewPoint()
{
    View view;
    if (m_car)
    {
        // calcul du point de vue
        Vector viewPoint;
        viewPoint = Vector(m_car->physicsBody()->GetPosition());
        viewPoint += Vector(m_car->physicsBody()->GetLinearVelocity()) * 0.5f;
        if ( (viewPoint - m_view.position()).length() < 1)
        {
            viewPoint = m_view.position();
        }
        else
        {

        }
        view.setPosition(viewPoint);

        // calcul du zoom
        if (m_dynamicZoom)
        {
            float velocity = (Vector(m_car->physicsBody()->GetLinearVelocity()).length() / 700.f) + 1;
            if (velocity > 0)
            {
                view.setZoom(1 / velocity);
            }
            else
            {
                view.setZoom(1.f);
            }
        }
        else
        {
            view.setZoom(0.7f);
        }
    }

    m_view = View::interp(m_view, view, 0.1);
    return m_view;
}

bool Scene::loaded() const
{
    return m_loaded;
}

bool Scene::isFinished()const
{
    return !m_checkpointListener->hasCheckpointRemaining();
}

void Scene::start()
{
    m_time.start();
}

const QTime & Scene::time()const
{
    return m_time;
}

const CheckpointListener * Scene::checkpointListener()const
{
    return m_checkpointListener;
}

void Scene::setTime(int time)
{
    m_time = QTime();
    m_time.start();
    m_time = m_time.addMSecs(-time);
}

const QString Scene::trackName() const
{
    return m_trackName;
}

bool Scene::dynamicZoom() const
{
    return m_dynamicZoom;
}

void Scene::setDynamicZoom(bool enabled)
{
    m_dynamicZoom = enabled;
}
