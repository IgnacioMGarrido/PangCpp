#ifndef _LIFE_COMP_H_
#define _LIFE_COMP_H_

#include "component.h"

class cLifeComp : public cComponent
{
private:
    int m_iNumLifes;
public:
    cLifeComp() : m_iNumLifes(3) {};
    ~cLifeComp() {}
    virtual void Slot(double fTimeDiff) override {};
    inline int& GetLifes() { return m_iNumLifes; }
    inline void SetLifes(int iNumLifes) { m_iNumLifes = iNumLifes; }
    //virtual void ReceiveMsg(const cMessage& message) override;

};

#endif
