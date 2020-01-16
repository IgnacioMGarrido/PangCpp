#ifndef _DEACTIVATION_COMP_H_
#define _DEACTIVATION_COMP_H_

#include "component.h"

class cDeactivationComponent : public cComponent
{
public:
    cDeactivationComponent(){};
    ~cDeactivationComponent() {}

    virtual void Slot(double fTimeDiff) override {};

    virtual void ReceiveMsg(const cMessage& message) override;

};

#endif
