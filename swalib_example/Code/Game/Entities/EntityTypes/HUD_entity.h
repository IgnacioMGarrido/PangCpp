#ifndef _HUD_ENTITY_H_
#define _HUD_ENTITY_H_

#include "../entity.h"
class cRenderComp;
class cEHud : public cEntity
{
private:
    std::vector<cRenderComp*> m_vHeartRenderComp;
public:
    cEHud(const char* cHeartPath, float fRadius);
    virtual ~cEHud() {};

    inline std::vector<cRenderComp*>&  GetHeartRenderComps() { return m_vHeartRenderComp; }
};



#endif
