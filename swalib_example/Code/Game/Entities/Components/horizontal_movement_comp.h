#ifndef _HORIZONTAL_MOVEMENT_COMP_H_
#define _HORIZONTAL_MOVEMENT_COMP_H_

#include "../../../../../common/core.h"
#include "component.h"

// Velocity component.
// Update new position using linear velocity.
class cHorizontalMovementComp : public cComponent
{
private:
	vec2	m_vPos;	// Position. Coord. window.
	vec2	m_vVel;	// Velocity.
	int		m_iDirection;
	vec2	m_vInitialVel;

	bool bCanMoveRight = true;
	bool bCanMoveLeft = true;

public:
	cHorizontalMovementComp();

	virtual void Slot(double fTimeDiff) override;
	inline const vec2& GetPos() const { return m_vPos; }
	inline void SetPos(const vec2& vPos) { m_vPos = vPos; }
	inline const vec2& GetVel() const { return m_vVel; }
	inline void SetVel(const vec2& vVel) { m_vVel = vVel; }
	inline const vec2& GetInitialVel() const { return m_vInitialVel; }
	inline void SetInitialVel(const vec2& vVel) { m_vInitialVel = vVel; }

	virtual void ReceiveMsg(const cMessage& message) override;
};


#endif // !_HORIZONTAL_MOVEMENT_COMP_H_
