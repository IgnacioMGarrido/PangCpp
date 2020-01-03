#ifndef _INPUT_COMP_H_
#define _INPUT_COMP_H_

#include "component.h"

class cInputComp : public cComponent
{
public:
    cInputComp() {};
    ~cInputComp(){}
    virtual void Slot(double fTimeDiff) override;
   //virtual void ReceiveMsg(const cMessage& message) override;

};

#endif
