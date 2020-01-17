#ifndef _LINEAR_VEL_COMP_H_
#define _LINEAR_VEL_COMP_H_

#include "../../../../../common/core.h"
#include "component.h"
#include "Interfazes/dynamic_movement.h"

// Velocity component.
// Update new position using linear velocity.
class cLinearVelComp : public cComponent, public IDynamicMovementComp
{
private:
	vec2	m_vPos;	// Position. Coord. window.
	vec2	m_vVel;	// Velocity.
	vec2	m_vInitialVel;


public:
	cLinearVelComp();

	virtual void Slot(double fTimeDiff) override;
    inline virtual const vec2& GetPos() const override { return m_vPos; }
	inline void SetPos(const vec2& vPos) { m_vPos = vPos; }
	inline const vec2 &GetVel() const { return m_vVel; }
	inline void SetVel(const vec2& vVel) { m_vVel = vVel; }
	inline const vec2& GetInitialVel() const { return m_vInitialVel; }
	inline void SetInitialVel(const vec2& vVel) { m_vInitialVel = vVel; }

	virtual void ReceiveMsg(const cMessage &message) override;
private:
    void Rebound(const cEntity* pEntColl);
};

#endif // !_LINEAR_VEL_COMP_H_
