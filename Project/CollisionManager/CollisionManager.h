#pragma once

#include "Math/Vector/Calculation/VectorCalculation.h"
#include "Math/Matrix/Calculation/Matrix4x4Calculation.h"
#include "Polygon/Model/Model.h"

#include <list>
#include <algorithm>




// 球
struct Sphere {
	Vector3 center;
	float radius;
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




class Player;
class PlayerHitBox;
class Enemy;


/* CollisionManagerクラス */
class CollisionManager {

public: // メンバ関数

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	void EnemyListPushBack(Enemy* enemy);


#pragma region Set

	/// <summary>
	/// プレイヤーの取得
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }

	void SetPlayerHitBox(PlayerHitBox* playerHitBox) { playerHitBox_ = playerHitBox; }

	/// <summary>
	/// エネミーの取得
	/// </summary>
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }


#pragma endregion 


#pragma region Get
	bool GetIsHitPlayerAndEnemy() {
		return isHitPlayerAndEnemy_;
	}

#pragma endregion
private: // メンバ関数

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(Player* player, Enemy* enemy);
	void CheckCollisionPair(PlayerHitBox* hitBox, Enemy* enemy);

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
	/// 球と球の当たり判定
	/// </summary>
	bool isCollision(const Sphere& s1, const Sphere& s2);

	/// <summary>
	/// AABB同士の当たり判定
	/// </summary>
	bool isCollision(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// AABBtoSphere
	/// </summary>
	bool isCollision(const AABB& aabb, const Sphere& s);

	/// <summary>
	/// OBBtoSphere
	/// </summary>
	bool isCollision(const OBB& obb, const Sphere& s);


	
private: // メンバ変数

	Player* player_;
	PlayerHitBox* playerHitBox_;
	Enemy* enemy_;
	std::list<Enemy*> enemys_;

	bool isHitPlayerAndEnemy_ = false;

};