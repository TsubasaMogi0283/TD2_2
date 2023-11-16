#pragma once
#include "Collider/ICollisionState.h"


/* IPlayerCollisionFrontState */
class IPlayerCollisionFrontState : public ICollisionState {

public:

	void onCollision() override;

};