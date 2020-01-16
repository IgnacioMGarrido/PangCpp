#ifndef _PLAYER_ENTITY_H_
#define _PLAYER_ENTITY_H_


#include "../entity.h"

class cEPlayer : public cEntity
{
private:
    float m_fMaxPlayerVel;
public:
    cEPlayer(const char* cSpritePath, float fRadius);
    virtual ~cEPlayer(){};
};

#endif