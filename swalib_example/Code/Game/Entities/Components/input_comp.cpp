#include "../../../../../common/stdafx.h"
#include "linear_vel_comp.h"
#include "input_comp.h"
#include "../entity.h"

#include "../Messages/dir_change_msg.h"
#include "../Messages/shoot_msg.h"
#include "../../Managers/world.h"
#include "../EntityTypes/bullet_entity.h"
#include <vector>
#include <windows.h>
#include <assert.h>

void cInputComp::Slot(double fTimeDiff)
{
    if (GetAsyncKeyState('A') & 0x8000)
    {
        cDirChangeMessage msg(-1);
        GetOwner()->SendMsg(msg);
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        cDirChangeMessage msg(1);
        GetOwner()->SendMsg(msg);
    }
    else
    {
        cDirChangeMessage msg(0);
        GetOwner()->SendMsg(msg);
    }

    if(GetKeyState(VK_SPACE) & 0x8000)
    {
        cShootMessage msg(true);
        GetOwner()->SendMsg(msg);

        //cEntity* pEnt = new cEBullet("data/tyrian_ball.png", 8.0f);
        //cWorld::GetInstance().GetEntities().push_back(pEnt);
        //pEnt->FindComponent<cLinearVelComp>()->SetPos(GetOwner()->FindComponent<cLinearVelComp>()->GetPos());
        //pEnt->Activate();
       for (cEntity* bullet : cWorld::GetInstance().GetEntities())
        {
            cEBullet* myBullet = dynamic_cast<cEBullet*>(bullet);
            if (myBullet != nullptr)
            {
                if (myBullet->GetIsActive() == false) {
                    cLinearVelComp* myBulletComp = myBullet->FindComponent<cLinearVelComp>();
                    assert(myBulletComp != nullptr);
                    myBulletComp->SetPos(GetOwner()->FindComponent<cLinearVelComp>()->GetPos());
                    myBullet->Activate();
                    return;
                }
            }
        } 
    }

}
