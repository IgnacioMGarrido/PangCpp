#include "../../../../../common/stdafx.h"
#include "collision_comp.h"
#include <assert.h>
#include "../entity.h"
#include "../../Managers/world.h"
#include ".././../../../../common/sys.h"
#include "../Messages/collision_msg.h"
#include "../Messages/new_pos_msg.h"

cCollisionComp::cCollisionComp(float fRadius) : m_fRadius(fRadius)
	, m_vPos(vmake(0.0f, 0.0f))
{
}

void cCollisionComp::Slot(double fTimeDiff)
{
	// Slot detecting collisions.
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	cEntity *pCollEnt = nullptr;
	for (cEntity* pEnt : cWorld::GetInstance().GetEntities()) {
		assert(pEnt != nullptr);
		if (pOwnEnt != pEnt) {
			cCollisionComp *pCollCompEnt = pEnt->FindComponent<cCollisionComp>();
			if (pCollCompEnt == nullptr) {
				continue;
			}
			float flimit2 = (m_fRadius + pCollCompEnt->GetRadius()) * (m_fRadius + pCollCompEnt->GetRadius());
			if (vlen2(vsub(m_vPos, pCollCompEnt->GetPos())) <= flimit2) {
				pCollEnt = pEnt;
				break;
			}
		}
	}

	// Sending message because we've detected collision with other entity.
	if (pCollEnt != nullptr) {
		// Rebound!
		cEntCollisionMsg msg(*pCollEnt);
		pOwnEnt->SendMsg(msg);
	}

	// Rebound on margins
	__int8 uLimit = 0;
	if (m_vPos.x > SCR_WIDTH) {
		uLimit = cLimitWorldCollMsg::eType::LIMIT_X_POS;
	}
	else if (m_vPos.x < 0) {
		uLimit = cLimitWorldCollMsg::eType::LIMIT_X_NEG;
	}
	if (m_vPos.y > SCR_HEIGHT) {
		uLimit |= cLimitWorldCollMsg::eType::LIMIT_Y_POS;
	}
	else if (m_vPos.y < 0) {
		uLimit |= cLimitWorldCollMsg::eType::LIMIT_Y_NEG;
	}
	// Sending message because we've detected margin collision.
	if (uLimit != 0) {
		cLimitWorldCollMsg msg(uLimit);
		pOwnEnt->SendMsg(msg);
	}
}

void cCollisionComp::ReceiveMsg(const cMessage &message)
{
	const cNewPosMsg *pMsg = dynamic_cast<const cNewPosMsg *>(&message);
	if (pMsg != nullptr) {
		m_vPos = pMsg->GetPos();
		return;
	}
}
