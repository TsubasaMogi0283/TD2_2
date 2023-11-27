#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerCollisionRightState */
class IPlayerCollisionRightState : public IPlayerCollisionState {

public:

	void onCollision(Player* pPla) override;

};