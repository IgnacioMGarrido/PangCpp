#ifndef _BALL_ENTITY_H_
#define _BALL_ENTITY_H_

#include "../entity.h"

class cEBall : public cEntity
{
private:
    float m_fMaxBallVel;
    bool m_bIsOriginBall;
public:
    cEBall(const char* cSpritePath, float fRadius);
    virtual ~cEBall() {};

    inline void SetIsOriginBall(bool _bIsOriginBall) { m_bIsOriginBall = _bIsOriginBall; }
    inline bool GetIsOriginBall() const { return m_bIsOriginBall; }
};



#endif
