#include "../../../../../common/stdafx.h"
#include "life_comp.h"
#include "../../Managers/world.h"
#include "../entity.h"
#include "../EntityTypes/HUD_entity.h"
#include "render_comp.h"
#include "../Messages/damage_taken.h"
#include <assert.h>

void cLifeComp::ReceiveMsg(const cMessage& message)
{
    const cDamageTakenMessage* pDamageTakenMsg = dynamic_cast<const cDamageTakenMessage*>(&message);
    if(pDamageTakenMsg != nullptr)
    {
        SetLifes(GetLifes() - pDamageTakenMsg->GetDamageTaken());

        cEHud* pWorldHud = dynamic_cast<cEHud*>( cWorld::GetInstance().GetHud());
        assert(pWorldHud != nullptr);
        for (cRenderComp* renderComp : pWorldHud->GetHeartRenderComps())
        {
            if (renderComp->GetIsActive()) {
                renderComp->Deactivate();
                break;
            }
        }

        if(GetLifes() <= 0)
        {
            //TODO: GameOver message
            GetOwner()->Deactivate();
            cWorld::GetInstance().CheckGameState(false);
        }
    }
}
