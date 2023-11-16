#include "CollisionManager.h"



/// <summary>
/// コライダーを受け取り、リストに登録する
/// </summary>
void CollisionManager::ColliderPushBack(Collider* collider) {

	colliders_.push_back(collider);

}



/// <summary>
/// コライダーリストをクリアにする関数
/// </summary>
void CollisionManager::ColliderClear() {

	colliders_.clear();
}



/// <summary>
/// コライダー2つの衝突判定と応答
/// </summary>
void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	// 衝突していたら
	if (IsColliding(colliderA->GetAABB(), colliderB->GetAABB())) {

		// 衝突時の法線ベクトルを計算
		Vector3 collisionNormal = CalculateCollisionNormal(colliderA->GetAABB(), colliderB->GetAABB());

		// 衝突の方向を検出
		CollisionType collisionType = DetectCollisionType(collisionNormal);


		// コライダーの衝突時コールバックを呼び出す
		colliderA->onCollision(collisionType);
		colliderB->onCollision(collisionType);
	}
}



/// <summary>
/// 衝突判定と応答
/// </summary>
void CollisionManager::CheckAllCollision() {

	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		// イテレータAからコライダーAを取得する
		Collider* colliderA = *itrA;

		// イテレータBはイテレータAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {

			// イテレータBからコライダーBを取得する
			Collider* colliderB = *itrB;

			// ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}



/// <summary>
/// AABB同氏の当たり判定
/// </summary>
bool CollisionManager::IsColliding(const AABB& aabb1, const AABB& aabb2) {

	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {

		// 当たっている
		return true;
	}
	// 当たってない
	return false;
}



/// <summary>
/// 衝突の方向を検出
/// </summary>
CollisionType CollisionManager::DetectCollisionType(const Vector3& collisionNormal) {

	// ここでは、単純な方向の判定例を示しています。
	float absX = std::abs(collisionNormal.x);
	float absY = std::abs(collisionNormal.y);
	float absZ = std::abs(collisionNormal.z);


	// 最も大きな絶対値を持つ成分をもとに衝突の方向を判定
	if (absX > absY && absX > absZ) {
		if (collisionNormal.x > 0) {
			return LEFT; // 衝突は左から発生
		}
		else {
			return RIGHT; // 衝突は右から発生
		}
	}
	else if (absY > absX && absY > absZ) {
		if (collisionNormal.y > 0) {
			return BOTTOM; // 衝突は下から発生
		}
		else {
			return TOP; // 衝突は上から発生
		}
	}
	else {
		if (collisionNormal.z > 0) {
			return BACK; // 衝突は後ろから発生
		}
		else {
			return FRONT; // 衝突は前から発生
		}
	}
}



/// <summary>
/// AABB同士の衝突時に法線ベクトルを計算
/// </summary>
Vector3 CollisionManager::CalculateCollisionNormal(const AABB& aabb1, const AABB& aabb2) {

	// AABB同士の中心座標の差分を法線ベクトルとする
	Vector3 center1 = (Mul(Add(aabb1.min, aabb1.max), 0.5f));
	Vector3 center2 = (Mul(Add(aabb2.min, aabb2.max), 0.5f));

	return Normalize(Subtract(center2, center1));
}



/// <summary>
/// 長さ
/// </summary>
float CollisionManager::Length(const Vector3 v) {
	float result;
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}



/// <summary>
/// ベクトルの正規化
/// </summary>
Vector3 CollisionManager::Normalize(const Vector3& v) {

	Vector3 result{};
	float length = Length(v);
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;

	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}

	return result;
}



/// <summary>
/// 乗算
/// </summary>
Vector3 CollisionManager::Mul(const Vector3& v, float scalar) {

	Vector3 result{};

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;
}