#ifndef _RENDER_COMP_H_
#define _RENDER_COMP_H_

#include "../../Graphics/sprite.h"
#include "component.h"

// Renderable component.
class cRenderComp : public cComponent
{
private:
	cSprite	m_Sprite;	// Sprite associated.

public:
	cRenderComp(const char *sFileName, const vec2 &vSize);
	~cRenderComp();

	void Slot(double fTimeDiff)
	{};

	virtual void ReceiveMsg(const cMessage &message) override;
};

#endif // !_RENDER_COMP_H_
