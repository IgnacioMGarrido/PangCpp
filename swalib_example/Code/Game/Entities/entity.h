#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>

class cComponent;
class cMessage;

enum class EntityType { PLAYER, BALL, BULLET, EMPTY };
class cEntity {
private:
	EntityType m_EType;
	std::vector<cComponent*>	m_Components;	// Component list.
	bool m_bIsActive;
public:
	cEntity() : m_bIsActive(false), m_EType(EntityType::EMPTY)
	{}
	virtual ~cEntity();

	// Entity activation when it's running first time.
	void Activate();
	// Entity deactivation before is deleted.
	void Deactivate();
	// Process slot.
	void Slot(double fTimeDiff);

	// Sends a message to its components.
	void SendMsg(const cMessage &message) const;

	// Add a component.
	template <class T>
	void AddComponent(T &component)
	{
		m_Components.push_back(&component);
		component.SetOwner(*this);
	}

	// Find a component.
	template <class T>
	T *FindComponent() const
	{
		for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
			T* pComp = dynamic_cast<T*>(*compIt);
			if (pComp != nullptr) {
				return pComp;
			}
		}
		return nullptr;
	}

	inline bool GetIsActive() const { return m_bIsActive; }

	inline EntityType GetEntityType() const{ return m_EType; }
	inline void SetEntityType(EntityType _myType) { m_EType = _myType; }
};

#endif // !_ENTITY_H_