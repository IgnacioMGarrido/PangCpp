#include "input_comp.h"
#include "../entity.h"

#include <windows.h>
#include "../Messages/dir_change_msg.h"
#include "../Messages/shoot_msg.h"

void cInputComp::Slot(double fTimeDiff)
{
    if (GetAsyncKeyState('A') & 0x8000)
    {
        cDirChangeMessage msg(-1);
        GetOwner()->SendMsg(msg);
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        cDirChangeMessage msg(1);
        GetOwner()->SendMsg(msg);
    }
    else
    {
        cDirChangeMessage msg(0);
        GetOwner()->SendMsg(msg);
    }

    if(GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        cShootMessage msg(true);
        GetOwner()->SendMsg(msg);
    }
}
