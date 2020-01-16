#include "../../../../../common/stdafx.h"
#include "linear_vel_comp.h"
#include "input_comp.h"
#include "../entity.h"

#include "../Messages/dir_change_msg.h"
#include "../Messages/shoot_msg.h"
#include "../../Managers/world.h"
#include "../EntityTypes/bullet_entity.h"
#include <vector>
#include <windows.h>
#include <assert.h>
#include "../../../../../common/sys.h"
#include "horizontal_movement_comp.h"

void cInputComp::Slot(double fTimeDiff)
{
    if (SYS_KeyPressed('A'))//GetAsyncKeyState('A') & 0x8000)
    {
        cDirChangeMessage msg(-1);
        GetOwner()->SendMsg(msg);
    }
    else if (SYS_KeyPressed('D'))
    {
        cDirChangeMessage msg(1);
        GetOwner()->SendMsg(msg);
    }

    if(SYS_KeyPressed(VK_SPACE))
    {
        cShootMessage msg(true);
        GetOwner()->SendMsg(msg);

    }

}
