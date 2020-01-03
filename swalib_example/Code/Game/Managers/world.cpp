#include "../../../../common/stdafx.h"
#include "world.h"
#include "../../../../common/core.h"
#include "../../../../common/sys.h"
#include "../../../../common/font.h"
#include "../Entities/EntityTypes/player_entity.h"
#include "../Entities/EntityTypes/ball_entity.h"
#include "../Entities/Entity.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Components/collision_comp.h"
#include "../Entities/Components/render_comp.h"
#include "../Graphics/background.h"
#include "graphics_engine.h"
#include <assert.h>
#include "../Entities/Components/input_comp.h"
#include "../Entities/Components/life_comp.h"



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

void cWorld::Init()
{
	// Background creation.
	m_pBackground = new cBackground("data/circle-bkg-128.png", vmake(128.f, 128.f));
	assert(m_pBackground != nullptr);
	// Registering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().InsertRenderObj(*m_pBackground);

	// Init game state
	// Add balls
	for (size_t i = 0; i < m_bMaxBalls; i++) {
		cEntity *pEnt = new cEBall("data/ball128.png",16.0f);
		assert(pEnt != nullptr);
		// Insert entity.
		m_Entities.push_back(pEnt);
		// Activation.
		pEnt->Activate();
	}
	//Add Player.
	for(size_t i = 0; i < m_bMaxPlayers; ++i)
	{
		cEntity* pEnt = new cEPlayer("data/pang_player.png",16.0f);
		assert(pEnt != nullptr);

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
