#include "deactivation_component.h"
#include "../entity.h"
#include "../Messages/damage_taken.h"

void cDeactivationComponent::ReceiveMsg(const cMessage& message)
{
    const cDamageTakenMessage* pDamageTakenMsg = dynamic_cast<const cDamageTakenMessage*>(&message);
    if (pDamageTakenMsg != nullptr)
    {
        GetOwner()->Deactivate();
    }
}
