#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerCollisionBackState */
class IPlayerCollisionBackState : public IPlayerCollisionState {

public:

	void onCollision(Player* pPla) override;

};