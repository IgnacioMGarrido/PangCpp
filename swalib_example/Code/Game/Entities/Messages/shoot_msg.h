#ifndef _SHOOT_MSG_H_
#define _SHOOT_MSG_H_

#include "message.h"

// New position message.
class cShootMessage : public cMessage
{
private:
	bool m_bShoot;

public:
	cShootMessage(bool bShoot) : m_bShoot(bShoot)
	{}

	inline const bool& GetShootingState() const { return m_bShoot; }
};

#endif