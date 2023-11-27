#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerCollisionLeftState */
class IPlayerCollisionLeftState : public IPlayerCollisionState {

public:

	void onCollision(Player* pPla) override;

};