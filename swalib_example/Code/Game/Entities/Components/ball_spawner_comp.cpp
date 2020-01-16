#include "../../../../../common/stdafx.h"
#include "ball_spawner_comp.h"
#include  "../entity.h"
#include "../../Managers/world.h"
#include "../Messages/spawn_Ball_msg.h"
#include <assert.h>
#include "render_comp.h"
#include "linear_vel_comp.h"
#include "../EntityTypes/ball_entity.h"
#include "collision_comp.h"

void cBallSpawnerComp::ReceiveMsg(const cMessage& message)
{
    const cSpawnBallMessage* pSpawnBallMsg = dynamic_cast<const cSpawnBallMessage*>(&message);

    if(pSpawnBallMsg != nullptr)
    {
        int cont = 0;
        const cEBall* pOwnerBall = dynamic_cast<const cEBall*>(GetOwner());
        for (cEntity* ball : cWorld::GetInstance().GetEntities())
        {
            if(cont < 3 && ball->GetEntityType() == EntityType::BALL && ball->GetIsActive() == false && pOwnerBall->GetIsOriginBall() == true 
                && ball->GetHasAlreadyBeenSpawned() == false)
            {
                if(cont == 0)
                {
                    ball->Activate();
                    ball->FindComponent<cRenderComp>()->SetScale(vscale(GetOwner()->FindComponent<cRenderComp>()->GetScale(), .5f).x);
                    ball->FindComponent<cLinearVelComp>()->SetPos(vadd(GetOwner()->FindComponent<cLinearVelComp>()->GetPos(), vmake(20, 0)));
                    ball->FindComponent<cCollisionComp>()->SetCollisionRadius(ball->FindComponent<cCollisionComp>()->GetRadius() / 2);
                }
                else if(cont == 1)
                {
                    ball->Activate();
                    ball->FindComponent<cRenderComp>()->SetScale(vscale(GetOwner()->FindComponent<cRenderComp>()->GetScale(), .5f).x);
                    ball->FindComponent<cLinearVelComp>()->SetPos(vadd(GetOwner()->FindComponent<cLinearVelComp>()->GetPos(), vmake(0, 0)));
                    ball->FindComponent<cCollisionComp>()->SetCollisionRadius(ball->FindComponent<cCollisionComp>()->GetRadius() / 2);

                }
                else if(cont == 2)
                {
                    ball->Activate();
                    ball->FindComponent<cRenderComp>()->SetScale(vscale(GetOwner()->FindComponent<cRenderComp>()->GetScale(), .5f).x);
                    ball->FindComponent<cLinearVelComp>()->SetPos(vadd(GetOwner()->FindComponent<cLinearVelComp>()->GetPos(), vmake(-20, 0)));
                    ball->FindComponent<cCollisionComp>()->SetCollisionRadius(ball->FindComponent<cCollisionComp>()->GetRadius() / 2);

                }
                cont++;

            }
        }

    }


}
