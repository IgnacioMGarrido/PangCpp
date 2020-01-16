#include "../../../../common/stdafx.h"
#include "world.h"
#include "../../../../common/core.h"
#include "../../../../common/font.h"
#include "../Entities/EntityTypes/player_entity.h"
#include "../Entities/EntityTypes/ball_entity.h"
#include "../Entities/Entity.h"
#include "../Entities/Components/render_comp.h"
#include "../Graphics/background.h"
#include "graphics_engine.h"
#include <assert.h>
#include "../Entities/EntityTypes/bullet_entity.h"
#include "../Entities/EntityTypes/HUD_entity.h"


cWorld& cWorld::GetInstance()
{
	static cWorld world;
	return world;
}

cWorld::cWorld() : m_Entities(m_uMaxBalls)
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
	pHUD = new cEHud("data/heart.png", "data/GameOverText.png","data/WinText.png", 10);
	
	assert(pHUD != nullptr);
	m_Entities.push_back(pHUD);
	pHUD->Activate();

	cEHud* pWorldHud = dynamic_cast<cEHud*>(pHUD);
	assert(pWorldHud != nullptr);
	pWorldHud->GetGameOverComponent()->Deactivate();
	pWorldHud->GetWinComponent()->Deactivate();


	// Add balls
	for (size_t i = 0; i < m_uMaxBalls; i++) {
		cEntity *pEnt = new cEBall("data/ball128.png",16.0f);
		assert(pEnt != nullptr);
		// Insert entity.
		m_Entities.push_back(pEnt);
		// Activation.
		pEnt->Activate();
	}
	//Add Player.
	for(size_t i = 0; i < m_uMaxPlayers; ++i)
	{
		cEntity* pEnt = new cEPlayer("data/pang_player.png",16.0f);
		assert(pEnt != nullptr);

		m_Entities.push_back(pEnt);
		pEnt->Activate();
	}
    //Add Bullets
	for (size_t i = 0; i < m_uMaxBullets; ++i)
	{
		cEntity* pEnt = new cEBullet("data/tyrian_ball.png", 8.0f);
		assert(pEnt != nullptr);

		m_Entities.push_back(pEnt);
		pEnt->Deactivate();
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

void cWorld::CheckGameState(bool _bGameState)
{
	if (_bGameState == false)
	{
		cEHud* pWorldHud = dynamic_cast<cEHud*>(pHUD);
		assert(pWorldHud != nullptr);
		pWorldHud->GetGameOverComponent()->Activate();
	}
	else
	{
		cEHud* pWorldHud = dynamic_cast<cEHud*>(pHUD);
		assert(pWorldHud != nullptr);
		pWorldHud->GetWinComponent()->Activate();
	}
}

bool cWorld::CheckAllBallsActive()
{
	for (cEntity* pEntity : GetInstance().GetEntities())
	{
		if (pEntity->GetEntityType() == EntityType::BALL)
		{
			if (pEntity->GetIsActive() == true)
				return true;
		}
	}
	return false;
}

void cWorld::EntitySlot(double fTimeDiff)
{
	// Run entities
	for (cEntity* pEnt : m_Entities) {
		assert(pEnt != nullptr);
		pEnt->Slot(fTimeDiff);
	}
}
