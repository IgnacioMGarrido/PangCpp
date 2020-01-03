#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class cEntity;
class cMessage;

// Component of a entity.
class cComponent
{
private:
	cEntity* m_pOwner;	// Entity.
	bool m_isActive;
public:
	cComponent() : m_pOwner(nullptr), m_isActive(false)
	{}
	inline void SetOwner(cEntity &ent) { m_pOwner = &ent; }
	inline cEntity *GetOwner() const { return m_pOwner; }

	// Component activation when it's running first time.
	virtual void Activate()
	{ m_isActive = true; }
	// Component deactivation before is deleted.
	virtual void Deactivate()
	{ m_isActive = false; }
	// Process slot.
	virtual void Slot(double fTimeDiff) = 0;

	// Receive from another component.
	virtual void ReceiveMsg(const cMessage& message)
	{};

	inline bool GetIsActive() const { return m_isActive; }
};

#endif // !_COMPONENT_H_
