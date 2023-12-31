#pragma once

#include "Math/Vector/Calculation/VectorCalculation.h"
#include "Math/Matrix/Calculation/Matrix4x4Calculation.h"
#include "Polygon/Model/Model.h"

#include <list>
#include <algorithm>



// 線分
struct Segment {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};
// 平面
struct Plane {
	Vector3 normal;	// !< 法線
	float distance; // !< 距離
};
// 球
struct Sphere {
	Vector3 center; // !< 中心座標
	float radius;	// !< 半径
};
// AABB
struct AABB {
	Vector3 min; // !< 最少点
	Vector3 max; // !< 最大点
};
// OBB
struct OBB {
	Vector3 center;			   // !< 中心点
	Vector3 orientations[3]{}; // !< 座標軸。正規化・直交必須
	Vector3 size;			   // !< 座標軸方向の長さの半分。中心から面までの距離
};


class DemoPlayer;
class DemoGround;


/* CollisionManagerクラス */
class CollisionManager {

public: // メンバ関数

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

#pragma region Set

	void SetPlayer(DemoPlayer* dPlayer) { dPlayer_ = dPlayer; }
	void SetGround(DemoGround* dGround) { dGround_ = dGround; }

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(DemoPlayer* dPlayer, DemoGround* dGround);

	/// <summary>
	/// ShpereとSphereの衝突判定
	/// </summary>
	bool isCollision(const Sphere& s1, const Sphere& s2);

	/// <summary>
	/// SegmentとPlaneの衝突判定
	/// </summary>
	bool isCollision(const Segment& s, const Plane& p);

	/// <summary>
	/// AABB同士の衝突判定
	/// </summary>
	bool isCollision(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// AABBとSphereの衝突判定
	/// </summary>
	bool isCollision(const AABB& aabb, const Sphere& s);

	/// <summary>
	/// AABBとSegmentの衝突判定
	/// </summary>
	bool isCollision(const AABB& aabb, const Segment& s);

	/// <summary>
	/// OBBとSphereの衝突判定
	/// </summary>
	bool isCollision(const OBB& obb, const Sphere& s);

	/// <summary>
	/// OBBとSegmentの衝突判定
	/// </summary>
	bool isCollision(const OBB& obb, const Segment& s);


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

	/// <summary>
	/// OBBのワールドマトリックス作成
	/// </summary>
	Matrix4x4 CreateWorldMatrix(const OBB& obb);

	/// <summary>
	/// 座標変換
	/// </summary>
	Vector3 VecMatTransform(const Vector3 vector, const Matrix4x4 matrix);


private: // メンバ変数

	DemoPlayer* dPlayer_ = nullptr;
	DemoGround* dGround_ = nullptr;
};