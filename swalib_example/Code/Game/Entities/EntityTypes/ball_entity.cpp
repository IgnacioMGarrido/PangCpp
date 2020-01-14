#include "../../../../../common/stdafx.h"
#include "ball_entity.h"
#include "../../../../../common/sys.h"
#include "../Components/render_comp.h"
#include "../Components/collision_comp.h"
#include "../Components/linear_vel_comp.h"
#include <assert.h>


cEBall::cEBall(const char* cSpritePath, float fRadius)
    :m_fMaxBallVel(8.0f * 60.0f)
{
    //Set Entity Type
    SetEntityType(EntityType::BALL);
    // Insert movement component.
    cLinearVelComp* pVelComp = new cLinearVelComp();
    assert(pVelComp != nullptr);
    pVelComp->SetPos(vmake(SCR_WIDTH / 2, SCR_HEIGHT));//CORE_FRand(0.0f, SCR_WIDTH), CORE_FRand(0.0f, SCR_HEIGHT)));
    pVelComp->SetVel(vmake(CORE_FRand(-m_fMaxBallVel, +m_fMaxBallVel), CORE_FRand(-m_fMaxBallVel, +m_fMaxBallVel)));
    AddComponent<cLinearVelComp&>(*pVelComp);

    // Insert collision component.
    cCollisionComp* pCollComp = new cCollisionComp(fRadius * 3.0f);
    assert(pCollComp != nullptr);
    AddComponent<cCollisionComp&>(*pCollComp);

    // Insert render component.
    cRenderComp* pRenderComp = new cRenderComp(cSpritePath, vmake(fRadius * 6.0f, fRadius * 6.0f));
    assert(pRenderComp != nullptr);
    AddComponent<cRenderComp&>(*pRenderComp);
}