#include "../../../../../common/stdafx.h"
#include "horizontal_movement_comp.h"
#include "../entity.h"
#include <assert.h>
#include "../Messages/dir_change_msg.h"
#include "../Messages/new_pos_msg.h"
#include "../Messages/collision_msg.h"

cHorizontalMovementComp::cHorizontalMovementComp()
    : m_vPos(vmake(0, 0))
    , m_vVel(vmake(0, 0))
    , m_iDirection(0)
    , m_vInitialVel(vmake(0,0))
    , bCanMoveRight(true)
    , bCanMoveLeft(true)
{
}

void cHorizontalMovementComp::Slot(double fTimeDiff)
{
    m_vVel.x = m_vInitialVel.x * m_iDirection;
    // Slot updating position and velocity.
    vec2 vec2Vel = vscale(m_vVel, static_cast<float>(fTimeDiff));
    m_vPos = vadd(m_vPos, vec2Vel);

    // Sending message because we've updated position.
    cNewPosMsg msg(m_vPos);
    cEntity* pEnt = GetOwner();
    assert(pEnt != nullptr);
    pEnt->SendMsg(msg);
    m_iDirection = 0;
    bCanMoveRight = true;
    bCanMoveLeft = true;
}

void cHorizontalMovementComp::ReceiveMsg(const cMessage& message)
{
    const cDirChangeMessage* pDirChangeMsg = dynamic_cast<const cDirChangeMessage*>(&message);
    if (pDirChangeMsg != nullptr)
    {
        if(pDirChangeMsg->GetDir() == -1 && bCanMoveLeft)
            m_iDirection = pDirChangeMsg->GetDir();
        if (pDirChangeMsg->GetDir() == 1 && bCanMoveRight)
            m_iDirection = pDirChangeMsg->GetDir();
       /* m_vVel.x = m_vInitialVel.x * m_iDirection;
        m_vVel.y = 0;*/
    }
    const cLimitWorldCollMsg* pLimitMsg = dynamic_cast<const cLimitWorldCollMsg*>(&message);
    if (pLimitMsg != nullptr) {
        __int8 uLimit = pLimitMsg->GetTypeLimitWorldColl();
        if ((uLimit & cLimitWorldCollMsg::eType::LIMIT_X_NEG))
        {
            bCanMoveLeft = false;
            m_vVel.x = 0;
        }
        if(uLimit & cLimitWorldCollMsg::eType::LIMIT_X_POS)
        {
            bCanMoveRight = false;
        }
        return;
    }

}
