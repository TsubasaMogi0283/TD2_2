#pragma once

#include "Object/Enemy/State/IEnemyMoveState.h"


/* EnemyAttackState : 徘徊 */
class EnemyAttackState : public IEnemyMoveState {

public:

	void Move(Enemy* pEnemy) override;

};