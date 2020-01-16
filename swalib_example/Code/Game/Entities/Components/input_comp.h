#ifndef _INPUT_COMP_H_
#define _INPUT_COMP_H_

#include "component.h"

class cInputComp : public cComponent
{
private:
    bool m_bKeyPressed;
public:
    cInputComp() : m_bKeyPressed(false) {};
    ~cInputComp(){}
    virtual void Slot(double fTimeDiff) override;
   //virtual void ReceiveMsg(const cMessage& message) override;

};

#endif
