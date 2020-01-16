#include "../../../../common/stdafx.h"
#include "background.h"
#include "../../../../common/sys.h"

cBackground::cBackground(const char *sFileName, const vec2 &fSize) : m_Sprite(sFileName, fSize)
{
}

void cBackground::Render()
{
	m_Sprite.SetSize(vmake(1280, 720));
    m_Sprite.SetPos(vmake(1280/2, 720/2));
    m_Sprite.Render();

}