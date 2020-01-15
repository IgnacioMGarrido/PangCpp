#include "../../../../../common/stdafx.h"
#include "linear_vel_comp.h"
#include "render_comp.h"
#include "../entity.h"
#include <assert.h>
#include "../Messages/new_pos_msg.h"
#include "../Messages/collision_msg.h"

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
            case EntityType::PLAYER: break;
            case EntityType::BALL:

                switch (pEntColl->GetEntityType())
                {
                        vec2 vPosCollEnt;
                        vec2 vNewVel;
                        float fLenVec;
                        float fVel;
                        cLinearVelComp* pMovCompCollEnt;

                    case EntityType::PLAYER: break;
                    case EntityType::BALL:
                        pMovCompCollEnt = pEntColl->FindComponent<cLinearVelComp>();
                        assert(pMovCompCollEnt != nullptr);
                        // Transfer the velocity vector from collided ball.
                        vPosCollEnt = pMovCompCollEnt->GetPos();
                        vNewVel = vsub(m_vPos, vPosCollEnt);
                        fLenVec = vlen(vNewVel);
                        if (fLenVec <= 0.0f) {	// Same position. Maintain vel.
                            return;
                        }
                        vNewVel = vscale(vNewVel, 1.0f / fLenVec);	// Normalization.
                        fVel = vlen(m_vVel);
                        SetVel(vscale(vNewVel, fVel));
                        //return;

                        break;
                    case EntityType::BULLET:
                        GetOwner()->Deactivate();
                        break;
                    }
                break;
            case EntityType::BULLET:
                switch (pEntColl->GetEntityType()) {
                case EntityType::PLAYER: break;
                case EntityType::BALL:
                    GetOwner()->Deactivate();
                    break;
                case EntityType::BULLET: break;
                case EntityType::EMPTY: break;
                default: ;
                }
                break;

            }
        }
        //if(pEntColl->GetEntityType() == EntityType::BALL || pEntColl->GetEntityType() == EntityType::BULLET)
        //{
        //    cLinearVelComp* pMovCompCollEnt = pEntColl->FindComponent<cLinearVelComp>();
        //    assert(pMovCompCollEnt != nullptr);
        //    // Transfer the velocity vector from collided ball.
        //    vec2 vPosCollEnt = pMovCompCollEnt->GetPos();
        //    vec2 vNewVel = vsub(m_vPos, vPosCollEnt);
        //    float fLenVec = vlen(vNewVel);
        //    if (fLenVec <= 0.0f) {	// Same position. Maintain vel.
        //        return;
        //    }
        //    vNewVel = vscale(vNewVel, 1.0f / fLenVec);	// Normalization.
        //    float fVel = vlen(m_vVel);
        //    SetVel(vscale(vNewVel, fVel));
        //    return;
        //}


        
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
