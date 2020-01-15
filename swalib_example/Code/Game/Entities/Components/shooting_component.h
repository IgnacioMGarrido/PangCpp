#ifndef _SHOOTING_COMP_H_
#define _SHOOTING_COMP_H_

#include "component.h"

class cShootingComp : public cComponent
{
private:
    bool m_bCanShoot = false;
    float m_fShootingRate = 0.5f;
    float m_fNextFire = 0.0f;
public:
    cShootingComp(){};
    ~cShootingComp() {}
    virtual void Slot(double fTimeDiff) override;

    virtual void ReceiveMsg(const cMessage& message) override;

private:
    void Shoot();
};

#endif
