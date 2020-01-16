#ifndef _HUD_ENTITY_H_
#define _HUD_ENTITY_H_

#include "../entity.h"
class cRenderComp;
class cEHud : public cEntity
{
private:
    std::vector<cRenderComp*> m_vHeartRenderComp;
    cRenderComp* m_pWinRenderComp;
    cRenderComp* m_pGameOverRenderComp;

public:
    cEHud(const char* cHeartSpritePath, const char* cGameOverSpritePath, const char* cWinSpritePath, float fRadius);
    virtual ~cEHud() {};

    inline std::vector<cRenderComp*>&  GetHeartRenderComps() { return m_vHeartRenderComp; }
    inline cRenderComp* GetWinComponent() const { return m_pWinRenderComp; }
    inline cRenderComp* GetGameOverComponent() const { return m_pGameOverRenderComp; }
};



#endif
