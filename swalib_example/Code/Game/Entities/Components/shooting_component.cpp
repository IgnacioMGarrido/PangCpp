#include "shooting_component.h"
#include "../../Managers/world.h"

#include "../Messages/shoot_msg.h"

void cShootingComp::Slot(double fTimeDiff)
{
    if (m_fNextFire >= m_fShootingRate) 
    {
        m_bCanShoot = true;
    }
    else 
    {
        m_fNextFire += fTimeDiff;
        m_bCanShoot = false;
    }
}

void cShootingComp::ReceiveMsg(const cMessage& message)
{
    const cShootMessage* pShootMsg = dynamic_cast<const cShootMessage*>(&message);
    if (pShootMsg != nullptr) 
    {
        if (m_bCanShoot)
            Shoot();
    }
}

void cShootingComp::Shoot()
{
    m_fNextFire = 0;//reset the NextFire variable
    for (cEntity* bullet : cWorld::GetInstance().GetEntities())
    {
        cEBullet* myBullet = dynamic_cast<cEBullet*>(bullet);
        if (myBullet != nullptr)
        {
            if (myBullet->GetIsActive() == false) {
                cLinearVelComp* myBulletComp = myBullet->FindComponent<cLinearVelComp>();
                assert(myBulletComp != nullptr);
                myBulletComp->SetPos(GetOwner()->FindComponent<cHorizontalMovementComp>()->GetPos());
                myBullet->Activate();
                return;
            }
        }
    } 
}
