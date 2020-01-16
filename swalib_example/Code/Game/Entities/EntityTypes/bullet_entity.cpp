#include "../../../../../common/stdafx.h"
#include "bullet_entity.h"
#include "../Components/render_comp.h"
#include "../Components/collision_comp.h"
#include "../Components/linear_vel_comp.h"
#include <assert.h>
cEBullet::cEBullet(const char* cSpritePath, float fRadius)
    :m_fMaxBulletVel(8.0f * 60.0f)

{
    //Set Entity Type
    SetEntityType(EntityType::BULLET);

    // Insert movement component.
    cLinearVelComp* pVelComp = new cLinearVelComp();
    assert(pVelComp != nullptr);
    pVelComp->SetPos(vmake(0, 0));//CORE_FRand(0.0f, SCR_WIDTH), CORE_FRand(0.0f, SCR_HEIGHT)));
    pVelComp->SetVel(vmake(0, m_fMaxBulletVel));
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
