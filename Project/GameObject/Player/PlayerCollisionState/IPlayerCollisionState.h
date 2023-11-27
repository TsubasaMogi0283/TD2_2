#pragma once


// Playerの前方宣言
class Player;


/* ICollisionStateクラス */
class IPlayerCollisionState {

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void onCollision(Player* pPla) = 0;
};