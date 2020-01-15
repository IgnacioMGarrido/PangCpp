#ifndef _SHOOTING_COMP_H_
#define _SHOOTING_COMP_H_

#include "component.h"

class cShootingComp : public cComponent
{

public:
    cShootingComp(){};
    ~cShootingComp() {}
    virtual void Slot(double fTimeDiff) override {};

    virtual void ReceiveMsg(const cMessage& message) override;

};

#endif
