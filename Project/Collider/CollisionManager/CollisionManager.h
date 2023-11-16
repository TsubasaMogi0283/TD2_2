#pragma once

#include "Collider/Collider.h"
#include "Math/Vector/Calculation/VectorCalculation.h"

#include <list>



/* CollisionManagerクラス */
class CollisionManager {

public: // メンバ関数

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// コライダーを受け取り、リストに登録する
	/// </summary>
	void ColliderPushBack(Collider* collider);

	/// <summary>
	/// コライダーリストをクリアにする関数
	/// </summary>
	void ColliderClear();


private: // メンバ関数

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

	/// <summary>
	/// AABB同氏の当たり判定
	/// </summary>
	bool IsColliding(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// 衝突の方向を検出
	/// </summary>
	CollisionType DetectCollisionType(const Vector3& collisionNormal);

	/// <summary>
	/// AABB同士の衝突時に法線ベクトルを計算
	/// </summary>
	Vector3 CalculateCollisionNormal(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// 長さ
	/// </summary>
	float Length(const Vector3 v);

	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 乗算
	/// </summary>
	Vector3 Mul(const Vector3& v, float scalar);


private: // メンバ変数

	// コライダーリスト
	std::list<Collider*> colliders_;

};