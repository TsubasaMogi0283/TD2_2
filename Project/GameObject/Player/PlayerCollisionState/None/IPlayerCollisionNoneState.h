#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerCollisionNoneState */
class IPlayerCollisionNoneState : public IPlayerCollisionState {

public:

	void onCollision(Player* pPla) override;

};