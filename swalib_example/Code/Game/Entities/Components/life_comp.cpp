#include "../../../../../common/stdafx.h"
#include "life_comp.h"
#include "../../Managers/world.h"
#include "../entity.h"

#include "../Messages/damage_taken.h"

void cLifeComp::ReceiveMsg(const cMessage& message)
{
    const cDamageTakenMessage* pDamageTakenMsg = dynamic_cast<const cDamageTakenMessage*>(&message);
    if(pDamageTakenMsg != nullptr)
    {
        SetLifes(GetLifes() - pDamageTakenMsg->GetDamageTaken());
        if(GetLifes() <= 0)
        {
            //TODO: GameOver message
            GetOwner()->Deactivate();
            cWorld::GetInstance().CheckGameState(false);
        }
    }
}
