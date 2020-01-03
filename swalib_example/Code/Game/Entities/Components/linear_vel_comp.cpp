#include "../../../../../common/stdafx.h"
#include "linear_vel_comp.h"
#include "render_comp.h"
#include "../entity.h"
#include <assert.h>
#include "../Messages/new_pos_msg.h"
#include "../Messages/collision_msg.h"
#include "../Messages/dir_change_msg.h"
#include "../Messages/shoot_msg.h"

cLinearVelComp::cLinearVelComp() : m_vPos(vmake(0, 0))
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
    if (pEntCollMsg != nullptr) {
        const cEntity* pEntColl = pEntCollMsg->GetEntToColl();
        assert(pEntColl != nullptr);
        cLinearVelComp* pMovCompCollEnt = pEntColl->FindComponent<cLinearVelComp>();
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
        return;
    }


    // Collision with limit world.
    const cLimitWorldCollMsg* pLimitMsg = dynamic_cast<const cLimitWorldCollMsg*>(&message);
    if (pLimitMsg != nullptr) {
        __int8 uLimit = pLimitMsg->GetTypeLimitWorldColl();


        if ((uLimit & cLimitWorldCollMsg::eType::LIMIT_X_NEG) ||
            (uLimit & cLimitWorldCollMsg::eType::LIMIT_X_POS)) {
            m_vVel.x *= -1.0f;
        }
        if ((uLimit & cLimitWorldCollMsg::eType::LIMIT_Y_NEG) ||
            (uLimit & cLimitWorldCollMsg::eType::LIMIT_Y_POS)) {
            m_vVel.y *= -1.0f;
        }
        return;
    }

    const cDirChangeMessage* pDirChangeMsg = dynamic_cast<const cDirChangeMessage*>(&message);
    if(pDirChangeMsg != nullptr)
    {
        m_vVel.x = m_vInitialVel.x * pDirChangeMsg->GetDir();
        m_vVel.y = 0;
    }

}
