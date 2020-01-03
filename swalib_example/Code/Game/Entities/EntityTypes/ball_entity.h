#ifndef _BALL_ENTITY_H_
#define _BALL_ENTITY_H_

#include "../entity.h"

class cEBall : public cEntity
{
private:
    float m_fMaxBallVel;
public:
    cEBall(const char* cSpritePath, float fRadius);
    virtual ~cEBall() {};
};



#endif
