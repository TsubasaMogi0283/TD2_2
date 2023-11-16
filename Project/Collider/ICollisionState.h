#pragma once



// 衝突の種類
enum CollisionType {
	FRONT,
	BACK,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NONE,
};


/* ICollisionStateクラス */
class ICollisionState {

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void onCollision() = 0;
};