#ifndef _BULLET_ENTITY_H_
#define _BULLET_ENTITY_H_

#include "../entity.h"

class cEBullet : public cEntity
{
private:
    float m_fMaxBulletVel;
public:
    cEBullet(const char* cSpritePath, float fRadius);
    virtual ~cEBullet() {};
};



#endif
