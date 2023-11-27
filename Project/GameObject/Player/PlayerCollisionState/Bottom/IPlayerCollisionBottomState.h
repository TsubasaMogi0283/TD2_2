#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerColisionBottomState */
class IPlayerColisionBottomState : public IPlayerCollisionState {

public: 

	void onCollision(Player* pPla) override;

};