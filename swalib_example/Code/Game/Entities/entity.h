#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>

class cComponent;
class cMessage;

class cEntity {
private:
	std::vector<cComponent*>	m_Components;	// Component list.

public:
	cEntity()
	{}
	~cEntity();

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
};

#endif // !_ENTITY_H_