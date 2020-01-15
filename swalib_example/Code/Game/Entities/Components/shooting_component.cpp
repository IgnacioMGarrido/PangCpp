#include "shooting_component.h"
#include "../Messages/shoot_msg.h"

void cShootingComp::ReceiveMsg(const cMessage& message)
{
    const cShootMessage* pShootMsg = dynamic_cast<const cShootMessage*>(&message);
    if (pShootMsg != nullptr) 
    {
    }
}
