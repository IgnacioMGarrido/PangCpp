#ifndef _DIR_DAMAGE_TAKEN_MSG_H_
#define _DIR_DAMAGE_TAKEN_MSG_H_

#include "message.h"

// New position message.
class cDamageTakenMessage : public cMessage
{
private:
    int	m_iAmount;

public:
    cDamageTakenMessage(const int& iAmount) : m_iAmount(iAmount)
    {}

    inline const int& GetDamageTaken() const { return m_iAmount; }
};

#endif