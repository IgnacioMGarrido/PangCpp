#include "../../../../../common/stdafx.h"
#include "HUD_entity.h"
#include "../../../../../common/sys.h"
#include "../Components/render_comp.h"
#include <assert.h>

cEHud::cEHud(const char* cHeartSpritePath, const char* cGameOverSpritePath, const char* cWinSpritePath, float fRadius)
{
    SetEntityType(EntityType::HUD);
    // Insert render component.
    cRenderComp* pRenderComp_1 = new cRenderComp(cHeartSpritePath, vmake(fRadius * 6.0f, fRadius * 6.0f));
    assert(pRenderComp_1 != nullptr);
    AddComponent<cRenderComp&>(*pRenderComp_1);    // Insert render component.
    pRenderComp_1->SetSpritePosition(vmake((SCR_WIDTH / 2) - 500, SCR_HEIGHT - 50));
    m_vHeartRenderComp.push_back(pRenderComp_1);

    cRenderComp* pRenderComp_2 = new cRenderComp(cHeartSpritePath, vmake(fRadius * 6.0f, fRadius * 6.0f));
    assert(pRenderComp_2!= nullptr);
    AddComponent<cRenderComp&>(*pRenderComp_2);    // Insert render component.
    pRenderComp_2->SetSpritePosition(vadd(pRenderComp_1->GetSpritePosition(), vmake(100 , 0)));
    m_vHeartRenderComp.push_back(pRenderComp_2);


    cRenderComp* pRenderComp_3 = new cRenderComp(cHeartSpritePath, vmake(fRadius * 6.0f, fRadius * 6.0f));
    assert(pRenderComp_3 != nullptr);
    AddComponent<cRenderComp&>(*pRenderComp_3);
    pRenderComp_3->SetSpritePosition(vadd(pRenderComp_1->GetSpritePosition(), vmake(200, 0)));
    m_vHeartRenderComp.push_back(pRenderComp_3);

    m_pWinRenderComp = new cRenderComp(cWinSpritePath, vmake(fRadius * 40.0f, fRadius * 40.0f));
    assert(m_pWinRenderComp != nullptr);
    AddComponent<cRenderComp&>(*m_pWinRenderComp);
    m_pWinRenderComp->SetSpritePosition(vmake(SCR_WIDTH/2, SCR_HEIGHT/2));

    m_pGameOverRenderComp = new cRenderComp(cGameOverSpritePath, vmake(fRadius * 40.0f, fRadius * 40.0f));
    assert(m_pGameOverRenderComp != nullptr);
    AddComponent<cRenderComp&>(*m_pGameOverRenderComp);
    m_pGameOverRenderComp->SetSpritePosition(vmake(SCR_WIDTH/2, SCR_HEIGHT/2));
}
