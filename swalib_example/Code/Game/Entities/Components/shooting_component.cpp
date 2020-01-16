#include "../../../../../common/stdafx.h"
#include "shooting_component.h"
#include "../../Managers/world.h"
#include "linear_vel_comp.h"
#include "horizontal_movement_comp.h"
#include "../Messages/shoot_msg.h"
#include "../EntityTypes/bullet_entity.h"
#include <assert.h>

void cShootingComp::Slot(double fTimeDiff)
{
    if (m_fNextFire >= m_fFireRate) 
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
        if (m_bCanShoot && GetOwner()->GetIsActive())
            Shoot();
    }
}

void cShootingComp::Shoot()
{
    m_fNextFire = 0;//reset the NextFire variable
    for (cEntity* bullet : cWorld::GetInstance().GetEntities())
    {
        //cEBullet* myBullet = dynamic_cast<cEBullet*>(bullet);
        if (bullet->GetEntityType() == EntityType::BULLET)
        {
            if (bullet->GetIsActive() == false) {
                cLinearVelComp* myBulletComp = bullet->FindComponent<cLinearVelComp>();
                assert(myBulletComp != nullptr);
                myBulletComp->SetPos(vadd(GetOwner()->FindComponent<cHorizontalMovementComp>()->GetPos(), vmake(0,80)));
                bullet->Activate();
                return;
            }
        }
    } 
}
