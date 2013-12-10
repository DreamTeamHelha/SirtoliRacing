#include "checkpointlistener.h"
#include <QMessageBox>
#include "checkpoint.h"
#include "car.h"

CheckpointListener::CheckpointListener():
    m_checkpointRemaining(-1)
{}

CheckpointListener::CheckpointListener(const CheckpointListener &checkList)
{
    m_checkpointRemaining=checkList.m_checkpointRemaining;
}

CheckpointListener& CheckpointListener::operator =(const CheckpointListener &checkList)
{
    if(this!= &checkList)
    {
        m_checkpointRemaining=checkList.m_checkpointRemaining;
    }
    return *this;
}

CheckpointListener::~CheckpointListener()
{}

void CheckpointListener::BeginContact (b2Contact *contact)
{
    void *dataCar = contact->GetFixtureA()->GetUserData();
    if(dataCar)
    {
        //Vérifie que la voiture soit bien l'objet qui entre en contact
        Car *car = (Car *)(contact->GetFixtureA()->GetUserData());
        if(car)
        {
            //Vérifie que l'objet touché soit bien un checkpoint
            void *dataCheckpoint = contact->GetFixtureB()->GetUserData();
            if(dataCheckpoint)
            {
                Checkpoint *checkpoint = (Checkpoint *)(contact->GetFixtureB()->GetUserData());
                if(checkpoint)
                {
                    if(!checkpoint->touched())
                    {
                        //Notifie le checkpoint qu'il a été touché
                        checkpoint->touch();
                        m_checkpointRemaining--;
                    }
                }
            }
        }
    }
}

void CheckpointListener::setCheckpointNumber(int number)
{
    if(m_checkpointRemaining == -1)
        m_checkpointRemaining = number;
}

bool CheckpointListener::hasCheckpointRemaining()
{
    return m_checkpointRemaining >0;
}

const int CheckpointListener::checkpointRemaining()const
{
    return m_checkpointRemaining;
}
