#pragma once

#include "GameObject/DemoGround/DemoGroundCollisionState/IDemoGroundCollisionState.h"


/* IDemoGroundCollisionFrontState */
class IDemoGroundCollisionFrontState : public IDemoGroundCollisionState {

public:

	void onCollision() override;

};