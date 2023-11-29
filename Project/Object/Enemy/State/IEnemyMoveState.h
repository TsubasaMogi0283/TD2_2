#pragma once

// Enemyの前方宣言
class Enemy;


/* IEnemyMoveStateクラス */
class IEnemyMoveState {

public:

	/// <summary>
	/// 挙動処理
	/// </summary>
	virtual void Move(Enemy* pEnemy) = 0;

};