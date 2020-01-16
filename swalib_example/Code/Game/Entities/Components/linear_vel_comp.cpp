#include "../../../../../common/stdafx.h"
#include "linear_vel_comp.h"
#include "../../Managers/world.h"
#include "render_comp.h"
#include "../entity.h"
#include <assert.h>
#include "../Messages/new_pos_msg.h"
#include "../Messages/collision_msg.h"
#include "../Messages/damage_taken.h"
#include "horizontal_movement_comp.h"
#include "../Messages/spawn_Ball_msg.h"

cLinearVelComp::cLinearVelComp()
    : m_vPos(vmake(0, 0))
    , m_vVel(vmake(0, 0))
{}

void cLinearVelComp::Slot(double fTimeDiff)
{
    // Slot updating position and velocity.
    vec2 vec2Vel = vscale(m_vVel, static_cast<float>(fTimeDiff));
    m_vPos = vadd(m_vPos, vec2Vel);

    // Sending message because we've updated position.
    cNewPosMsg msg(m_vPos);
    cEntity* pEnt = GetOwner();
    assert(pEnt != nullptr);
    pEnt->SendMsg(msg);
}

void cLinearVelComp::ReceiveMsg(const cMessage& message)
{
    // Collision with other entity.
    const cEntCollisionMsg* pEntCollMsg = dynamic_cast<const cEntCollisionMsg*>(&message);
    if (pEntCollMsg != nullptr && GetOwner()->GetIsActive()) {

        const cEntity* pEntColl = pEntCollMsg->GetEntToColl();
        assert(pEntColl != nullptr);
        if (pEntColl->GetIsActive())
        {
            switch (GetOwner()->GetEntityType())
            {
            case EntityType::BALL:

                switch (pEntColl->GetEntityType())
                {
                    cDamageTakenMessage *msg;
                    case EntityType::PLAYER:
                        //send message to the Player that damage has been taken
                        //TODO: Move this to the component implemented by the Player Entity.
                        msg = new cDamageTakenMessage(1);
                        pEntColl->SendMsg(*msg);
                        Rebound(pEntColl);
                    break;
                    case EntityType::BALL:
                        Rebound(pEntColl);
                        break;
                    case EntityType::BULLET:
                        cSpawnBallMessage msgBallSpawn(true);
                        GetOwner()->SendMsg(msgBallSpawn);
                        GetOwner()->Deactivate();
                        if (cWorld::GetInstance().CheckAllBallsActive() == false)
                            cWorld::GetInstance().CheckGameState(true);
                        break;
                    }
                break;
            case EntityType::BULLET:
                switch (pEntColl->GetEntityType()) {
                case EntityType::BALL:
                    //TODO: Fix collision with bullets
                    //GetOwner()->Deactivate();
                default: ;
                }
                break;

            }
        }
    }


    // Collision with limit world.
    const cLimitWorldCollMsg* pLimitMsg = dynamic_cast<const cLimitWorldCollMsg*>(&message);
    if (pLimitMsg != nullptr) {
        __int8 uLimit = pLimitMsg->GetTypeLimitWorldColl();

        if(GetOwner()->GetEntityType() == EntityType::BALL)
        {        
            if ((uLimit & cLimitWorldCollMsg::eType::LIMIT_X_NEG) ||
                (uLimit & cLimitWorldCollMsg::eType::LIMIT_X_POS)) {
                m_vVel.x *= -1.0f;
            }
            if ((uLimit & cLimitWorldCollMsg::eType::LIMIT_Y_NEG) ||
                (uLimit & cLimitWorldCollMsg::eType::LIMIT_Y_POS)) {
                m_vVel.y *= -1.0f;
            }
        }
        else if(GetOwner()->GetEntityType() == EntityType::BULLET)
        {
            if ((uLimit & cLimitWorldCollMsg::eType::LIMIT_Y_NEG) ||
                (uLimit & cLimitWorldCollMsg::eType::LIMIT_Y_POS)) {
                GetOwner()->Deactivate();
            }
        }
    }


}

void cLinearVelComp::Rebound(const cEntity* pEntColl)
{
    cDamageTakenMessage* msg;

    IDynamicMovementComp* pMovCompCollEnt = pEntColl->FindComponent<cLinearVelComp>();
    if (pMovCompCollEnt == nullptr)
        pMovCompCollEnt = pEntColl->FindComponent<cHorizontalMovementComp>();
    assert(pMovCompCollEnt != nullptr);

    // Transfer the velocity vector from collided ball.
    vec2 vPosCollEnt = pMovCompCollEnt->GetPos();
    vec2 vNewVel = vsub(m_vPos, vPosCollEnt);
    float fLenVec = vlen(vNewVel);
    if (fLenVec <= 0.0f) {	// Same position. Maintain vel.
        return;
    }
    vNewVel = vscale(vNewVel, 1.0f / fLenVec);	// Normalization.
    float fVel = vlen(m_vVel);
    SetVel(vscale(vNewVel, fVel));
}
