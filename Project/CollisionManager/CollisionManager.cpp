#include "CollisionManager.h"
#include "Object/Player/Player.h"
#include "Object/Enemy/Enemy.h"



/// <summary>
/// 衝突判定と応答
/// </summary>
void CollisionManager::CheckAllCollision() {

	// エネミーの当たり判定
	for (Enemy* enemy : enemys_) {
		//CheckCollisionPair(player_, enemy);

		// ヒットボックスが出ている時だけ衝突判定
		if (playerHitBox_->GetIsEmergeHitBox()) {
			CheckCollisionPair(playerHitBox_, enemy);
		}
	}
}

void CollisionManager::EnemyListPushBack(Enemy* enemy) {

	enemys_.push_back(enemy);
}



/// <summary>
/// コライダー2つの衝突判定と応答
/// </summary>
// プレイヤー本体とエネミー
void CollisionManager::CheckCollisionPair(Player* player, Enemy* enemy) {

	if (isCollision(player->GetSphere(), enemy->GetSphere())) {

		// 衝突時判定
		player->onCollisionToEnemy();
		enemy->onCollisionToPlayer();
	}
	else {

		// 非衝突時処理
		player->EndOverlapToEnemy();
		enemy->EndOverlapToPlayer();
	}
}
// プレイヤーヒットボックスとエネミー
void CollisionManager::CheckCollisionPair(PlayerHitBox* hitBox, Enemy* enemy) {

	// HitBoxLeft
	if (isCollision(hitBox->GetLeftAABB(), enemy->GetSphere())) {

		// 衝突時判定
		hitBox->onCollisionToEnemy();
		enemy->onCollisionToPlayer();
	}
	else {

		// 非衝突判定
		hitBox->EndOverlapToEnemy();
		enemy->EndOverlapToPlayer();
	}
	// HitBoxRight
	if (isCollision(hitBox->GetRightAABB(), enemy->GetSphere())) {

		// 衝突時判定
		hitBox->onCollisionToEnemy();
		enemy->onCollisionToPlayer();
	}
	else {

		// 非衝突判定
		hitBox->EndOverlapToEnemy();
		enemy->EndOverlapToPlayer();
	}
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



/// <summary>
/// OBBのワールドマトリックス作成
/// </summary>
Matrix4x4 CollisionManager::CreateWorldMatrix(const OBB& obb) {

	Matrix4x4 worldMatrix{};

	for (int i = 0; i < 3; ++i) {
		worldMatrix.m[i][0] = obb.orientations[i].x;
		worldMatrix.m[i][1] = obb.orientations[i].y;
		worldMatrix.m[i][2] = obb.orientations[i].z;
		worldMatrix.m[i][3] = 0.0f;
	}

	worldMatrix.m[3][0] = obb.center.x;
	worldMatrix.m[3][1] = obb.center.y;
	worldMatrix.m[3][2] = obb.center.z;
	worldMatrix.m[3][3] = 1.0f;


	return worldMatrix;
}



/// <summary>
/// 球と球の当たり判定
/// </summary>
bool CollisionManager::isCollision(const Sphere& s1, const Sphere& s2) {

	// 中心からの距離
	float distance = Length(Subtract(s2.center, s1.center));

	// 距離と半径を比べる
	if (distance <= s1.radius + s2.radius) {

		// 当たってる
		return true;
	}
	// 当たってない
	return false;
}



/// <summary>
/// AABB同氏の当たり判定
/// </summary>
bool CollisionManager::isCollision(const AABB& aabb1, const AABB& aabb2) {

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
/// AABBtoSphere
/// </summary>
bool CollisionManager::isCollision(const AABB& aabb, const Sphere& s) {

	// 最近接点を求める
	const Vector3 ClosestPoint = {
		std::clamp(s.center.x, aabb.min.x, aabb.max.x),
		std::clamp(s.center.y, aabb.min.y, aabb.max.y),
		std::clamp(s.center.z, aabb.min.z, aabb.max.z), };

	// 最近接点と球の中心と距離を求める
	float dist = Length(Subtract(ClosestPoint, s.center));

	// 距離が半径よりも小さければ衝突
	if (dist <= s.radius) {

		// 当たってる
		return true;
	}
	else {
		// 当たってない
		return false;
	}
}



/// <summary>
/// OBBtoSphere
/// </summary>
bool CollisionManager::isCollision(const OBB& obb, const Sphere& s) {

	Matrix4x4 obbInverse = Inverse(CreateWorldMatrix(obb));

	Vector3 centerInOBBLocalSpace = {
		TransformNormal(s.center, obbInverse) };


	AABB aabbOBBLocal = {
		.min = { -obb.size.x, -obb.size.y, -obb.size.z },
		.max = { obb.size.x, obb.size.y, obb.size.z }
	};
	Sphere sphereOBBLocal = {
		centerInOBBLocalSpace,
		s.radius
	};

	// ローカル座標で衝突判定
	if (isCollision(aabbOBBLocal, sphereOBBLocal)) {

		// 当たってる
		return true;
	}
	else {

		// 当たってない
		return false;
	}
}