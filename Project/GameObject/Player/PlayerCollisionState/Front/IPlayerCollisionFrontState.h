#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerCollisionFrontState */
class IPlayerCollisionFrontState : public IPlayerCollisionState {

public:

	void onCollision(Player* pPla) override;

};