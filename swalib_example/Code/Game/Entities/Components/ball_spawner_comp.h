#ifndef _BALL_SPAWNER_COMP_H_
#define _BALL_SPAWNER_COMP_H_

#include "component.h"

class cBallSpawnerComp : public cComponent
{
    unsigned int m_iBallsToSpawn;
public:
    cBallSpawnerComp(int _iBallsToSpawn) : m_iBallsToSpawn(_iBallsToSpawn)
    {}
    ~cBallSpawnerComp()
    {}
    virtual void Slot(double fTimeDiff) override {};


    virtual void ReceiveMsg(const cMessage& message) override;

};
#endif