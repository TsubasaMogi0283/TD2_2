#pragma once

#include "GameObject/Player/PlayerCollisionState/IPlayerCollisionState.h"


/* IPlayerCollisionTopState */
class IPlayerCollisionTopState : public IPlayerCollisionState {

public: 
	
	void onCollision(Player* pPla) override;

};