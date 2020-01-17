#ifndef _SHOOTING_COMP_H_
#define _SHOOTING_COMP_H_

#include "component.h"

class cShootingComp : public cComponent
{
private:
    bool m_bCanShoot;
    float m_fNextFire;
    float m_fFireRate;

public:
    cShootingComp() : m_bCanShoot(false) , m_fNextFire(0.0f), m_fFireRate(0.5f)
    {}
    ~cShootingComp()
    {}

    inline float GetFireRate() const { return m_fFireRate; }

    inline void SetFireRate(float _fNewFireRate) { m_fFireRate = _fNewFireRate; }

    virtual void Slot(double fTimeDiff) override;

    virtual void ReceiveMsg(const cMessage& message) override;

private:
    void Shoot();
};

#endif
