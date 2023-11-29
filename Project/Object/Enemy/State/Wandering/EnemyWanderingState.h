#pragma once

#include "Object/Enemy/State/IEnemyMoveState.h"


/* EnemyWanderingState : 徘徊 */
class EnemyWanderingState : public IEnemyMoveState {

public:

	void Move(Enemy* pEnemy) override;

private:


private:

	float mapSizeX_ = 3.0f;

};