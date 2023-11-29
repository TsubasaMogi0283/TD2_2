#pragma once

#include "Object/Enemy/State/IEnemyMoveState.h"


/* EnemyApproachState : 接近 */
class EnemyApproachState : public IEnemyMoveState {

public:
	
	void Move(Enemy* pEnemy) override;

};