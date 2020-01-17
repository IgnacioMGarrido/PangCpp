#ifndef _RENDER_COMP_H_
#define _RENDER_COMP_H_

#include "../../Graphics/sprite.h"
#include "component.h"

// Renderable component.
class cRenderComp : public cComponent
{
private:
	cSprite	m_Sprite;	// Sprite associated.
	bool m_bIsActive;
public:
	cRenderComp(const char *sFileName, const vec2 &vSize);
	~cRenderComp();

	virtual void Activate() override;
	virtual void Deactivate() override;

	void Slot(double fTimeDiff)
	{};

	virtual void ReceiveMsg(const cMessage &message) override;

	inline void SetSpritePosition(const vec2& _myNewPos) { m_Sprite.SetPos(_myNewPos); }

	inline const vec2& GetSpritePosition() { return m_Sprite.GetPos(); }

	inline const bool& GetIsActive() { return m_bIsActive; }

	inline void SetScale(float _fScale) { m_Sprite.SetSize(vmake(_fScale, _fScale)); }

	inline const vec2& GetScale() { return m_Sprite.GetSize(); };
};

#endif // !_RENDER_COMP_H_
