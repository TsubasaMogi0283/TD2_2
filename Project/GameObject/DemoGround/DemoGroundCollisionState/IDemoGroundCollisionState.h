#pragma once



/* ICollisionStateクラス */
class IDemoGroundCollisionState {

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void onCollision() = 0;
};