#ifndef _NEW_POS_MSG_H_
#define _NEW_POS_MSG_H_

#include "message.h"

// New position message.
class cDirChangeMessage : public cMessage
{
private:
	int	m_vDir;

public:
	cDirChangeMessage(const int& vDir) : m_vDir(vDir)
	{}

	inline const int& GetDir() const { return m_vDir; }
};

#endif