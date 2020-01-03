#include "../../../../common/stdafx.h"
#include "world.h"
#include "../../../../common/core.h"
#include "../../../../common/sys.h"
#include "../../../../common/font.h"
#include "../Entities/Entity.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Components/collision_comp.h"
#include "../Entities/Components/render_comp.h"
#include "../Graphics/background.h"
#include "graphics_engine.h"
#include <assert.h>

cWorld& cWorld::GetInstance()
{
	static cWorld world;
	return world;
}

cWorld::cWorld() : m_Entities(m_bMaxBalls)
	, m_Timer(1.0f / 60.0f)
	, m_pBackground(nullptr)
{
	m_Entities.clear();
}

void cWorld::AddBallComponents(const float fMaxVelSpeed, const float fRadius, cEntity* pEnt)
{
    // Insert movement component.
    cLinearVelComp *pVelComp = new cLinearVelComp();
    assert(pVelComp != nullptr);
	pVelComp->SetPos(vmake(SCR_WIDTH / 2, SCR_HEIGHT));//CORE_FRand(0.0f, SCR_WIDTH), CORE_FRand(0.0f, SCR_HEIGHT)));
	pVelComp->SetVel(vmake(CORE_FRand(-fMaxVelSpeed, +fMaxVelSpeed), CORE_FRand(-fMaxVelSpeed, +fMaxVelSpeed)));
    pEnt->AddComponent<cLinearVelComp &>(*pVelComp);

    // Insert collision component.
    cCollisionComp *pCollComp = new cCollisionComp(fRadius * 3.0f);
    assert(pCollComp != nullptr);
    pEnt->AddComponent<cCollisionComp &>(*pCollComp);

    // Insert render component.
    cRenderComp *pRenderComp = new cRenderComp("data/ball128.png", vmake(fRadius * 6.0f, fRadius * 6.0f));
    assert(pRenderComp != nullptr);
    pEnt->AddComponent<cRenderComp &>(*pRenderComp);
}

void cWorld::Init()
{
	// Background creation.
	m_pBackground = new cBackground("data/circle-bkg-128.png", vmake(128.f, 128.f));
	assert(m_pBackground != nullptr);
	// Registering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().InsertRenderObj(*m_pBackground);

	// Init game state
	// Add balls
	const float fMaxVelSpeed = 8.0f * 60.0f;	// Max vel. of ball. (pixels/sec.). 8 pixels x 60 slot executions per second.
	const float fRadius = 16.0F;
	for (size_t i = 0; i < m_bMaxBalls; i++) {
		cEntity *pEnt = new cEntity();
		assert(pEnt != nullptr);
		AddBallComponents(fMaxVelSpeed, fRadius, pEnt);
		// Insert entity.
		m_Entities.push_back(pEnt);
		// Activation.
		pEnt->Activate();
	}

	for(size_t i = 0; i < m_bMaxPlayers; ++i)
	{
		cEntity* pEnt = new cEntity();
		assert(pEnt != nullptr);

		// Insert movement component.
		cLinearVelComp* pVelComp = new cLinearVelComp();
		assert(pVelComp != nullptr);
		pVelComp->SetPos(vmake(SCR_WIDTH / 2, 50));//CORE_FRand(0.0f, SCR_WIDTH), CORE_FRand(0.0f, SCR_HEIGHT)));
		pVelComp->SetVel(vmake(0, 0));
		pEnt->AddComponent<cLinearVelComp&>(*pVelComp);

		// Insert collision component.
		cCollisionComp* pCollComp = new cCollisionComp(fRadius * 3.0f);
		assert(pCollComp != nullptr);
		pEnt->AddComponent<cCollisionComp&>(*pCollComp);

		// Insert render component.
		cRenderComp* pRenderComp = new cRenderComp("data/pang_player.png", vmake(fRadius * 15.0f, fRadius * 15.0f));
		assert(pRenderComp != nullptr);
		pEnt->AddComponent<cRenderComp&>(*pRenderComp);


		m_Entities.push_back(pEnt);
		pEnt->Activate();
	}
}

void cWorld::Terminate()
{
	for (cEntity* pEnt : m_Entities) {
		assert(pEnt != nullptr);
		// Deactivation.
		pEnt->Deactivate();
		delete pEnt;
	}
	m_Entities.clear();
	// Derregistering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().DeleteRenderObj(*m_pBackground);
	delete m_pBackground;
}

void cWorld::Slot()
{
	// Calls to Timer to process logic slot.
	m_Timer.InitSlotsToProcess();
	while (m_Timer.ProcessSlots()) {
		// Call to world logic.
		EntitySlot(m_Timer.GetFixedTick());
	}
}

void cWorld::EntitySlot(double fTimeDiff)
{
	// Run entities
	for (cEntity* pEnt : m_Entities) {
		assert(pEnt != nullptr);
		pEnt->Slot(fTimeDiff);
	}
}
