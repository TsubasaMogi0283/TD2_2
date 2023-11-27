#include "IPlayerCollisionTopState.h"
#include "GameObject/Player/Player.h"


void IPlayerCollisionTopState::onCollision(Player* pPla) {

	pPla->SetgGravityEnable(false);
	pPla->SetIsHit(1);
}