#ifndef _SPAWN_BALL_MSG_H_
#define _SPAWN_BALL_MSG_H_

#include "message.h"

// New position message.
class cSpawnBallMessage : public cMessage
{
	bool m_bSpawned;
public:
	cSpawnBallMessage(bool bBallSpawned) : m_bSpawned(bBallSpawned)
	{}
};

#endif