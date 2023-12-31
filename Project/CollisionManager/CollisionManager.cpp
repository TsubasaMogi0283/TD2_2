#include "CollisionManager.h"
#include "Object/DemoPlayer/DemoPlayer.h"
#include "Object/DemoGround/DemoGround.h"


/// <summary>
/// 衝突判定と応答
/// </summary>
void CollisionManager::CheckAllCollision() {

	CheckCollisionPair(dPlayer_, dGround_);

}



/// <summary>
/// コライダー2つの衝突判定と応答
/// </summary>
void CollisionManager::CheckCollisionPair(DemoPlayer* dPlayer, DemoGround* dGround) {

	if (isCollision(dGround->GetOBB(), dPlayer->GetSegment())) {

		dPlayer->onCollisionToEnemy();
	}
	else {

		dPlayer->EndOverlapToEnemy();
	}

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
/// SegmentとPlaneの衝突判定
/// </summary>
bool CollisionManager::isCollision(const Segment& s, const Plane& p) {

	// 法線と線の内積
	float dot = DotVector3(s.diff, p.normal);

	// 衝突 = 平行であるので、衝突しているはずがない
	if (dot == 0.0f) {

		// 当たってない
		return false;
	}

	// tを求める
	float t = (p.distance - DotVector3(s.origin, p.normal)) / dot;

	// tの値と線の種類で衝突判定
	if (0.0f <= t && t <= 1.0f) {

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
/// AABBとSegmentの衝突判定	/// </summary>
bool CollisionManager::isCollision(const AABB& aabb, const Segment& s) {

	Vector3 tMin = {
		.x = (aabb.min.x - s.origin.x) / s.diff.x,
		.y = (aabb.min.y - s.origin.y) / s.diff.y,
		.z = (aabb.min.z - s.origin.z) / s.diff.z,
	};
	Vector3 tMax = {
		.x = (aabb.max.x - s.origin.x) / s.diff.x,
		.y = (aabb.max.y - s.origin.y) / s.diff.y,
		.z = (aabb.max.z - s.origin.z) / s.diff.z,
	};

	if (std::isnan(tMin.x) || std::isnan(tMax.x) ||
		std::isnan(tMin.y) || std::isnan(tMax.y) ||
		std::isnan(tMin.z) || std::isnan(tMax.z)) {
		return true;
	}


	Vector3 tNear = {
		.x = min(tMin.x, tMax.x),
		.y = min(tMin.y, tMax.y),
		.z = min(tMin.z, tMax.z),
	};
	Vector3 tFar = {
		.x = max(tMin.x, tMax.x),
		.y = max(tMin.y, tMax.y),
		.z = max(tMin.z, tMax.z),
	};

	// AABBとの衝突点(貫通点)のtが小さいほう
	float ntMin = max(max(tNear.x, tNear.y), tNear.z);
	// AABBとの衝突点(貫通点)のtが大きいほう
	float ntMax = min(min(tFar.x, tFar.y), tFar.z);


	if (ntMin < 0.0f && ntMax < 0.0f || ntMin > 1.0f && ntMax > 1.0f) {
		return false;
	}

	if (ntMin < ntMax) {

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



/// <summary>
/// OBBとSegmentの衝突判定
/// </summary>
bool CollisionManager::isCollision(const OBB& obb, const Segment& s) {

	Matrix4x4 obbInverse = Inverse(CreateWorldMatrix(obb));

	AABB aabbOBBLocal = {
		.min = { -obb.size.x, -obb.size.y, -obb.size.z },
		.max = { obb.size.x, obb.size.y, obb.size.z }
	};


	Vector3 localOrigin = VecMatTransform(s.origin, obbInverse);
	Vector3 LocalEnd = VecMatTransform(Add(s.origin, s.diff), obbInverse);

	Segment localSegment = {
		.origin = localOrigin,
		.diff = Subtract(LocalEnd, localOrigin),
	};


	// AABBとSegmentの当たり判定を使う
	if (isCollision(aabbOBBLocal, localSegment)) {

		// 当たってる
		return true;
	}
	else {

		// 当たってない
		return false;
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
/// 座標変換
/// </summary>
Vector3 CollisionManager::VecMatTransform(const Vector3 vector, const Matrix4x4 matrix)
{
	Vector3 result{};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z *
		matrix.m[2][0] + 1.0f * matrix.m[3][0];

	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z *
		matrix.m[2][1] + 1.0f * matrix.m[3][1];

	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z *
		matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z *
		matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return  result;
}
