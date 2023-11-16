#pragma once

#include "Collider/ICollisionState.h"
#include "Math/Vector/Vector3.h" 




// AABB
struct AABB {
	Vector3 min; // !< 最少点
	Vector3 max; // !< 最大点
};


/// 衝突判定オブジェクト
/* Colliderクラス */
class Collider {

public:

	/// <summary>
	/// 衝突時に呼ばれる関数
	/// </summary>
	virtual void onCollision(CollisionType type) = 0;

	/// <summary>
	/// 衝突判定に使うAABBの取得関数
	/// </summary>
	virtual AABB GetAABB() = 0;


private:


};