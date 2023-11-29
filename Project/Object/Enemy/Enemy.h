#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include "CollisionManager/CollisionManager.h"



class Player;


struct EnemyProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
	Matrix4x4 matWorld{};
	Vector3 velocity{};
	Vector3 size{};
	Vector4 color{};
};
struct EnemyInitProperty {
	Transform transform{};
};



/* Enemyクラス */
class Enemy {

public:

	Enemy() {};
	~Enemy() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突時コールバック処理
	/// </summary>
	void onCollisionToPlayer();
	void EndOverlapToPlayer();

	/// <summary>
	/// 死亡判定
	/// </summary>
	bool IsDead() const { return isDead_; }


#pragma region Get

	/// <summary>
	/// Transformの取得
	/// </summary>
	Transform GetTransform() { return ene_.transform; }

	/// <summary>
	/// Sphereの取得
	/// </summary>
	Sphere GetSphere() { return eneSphere_; }

#pragma endregion 


#pragma region Set

	/// <summary>
	/// Playerの取得
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }

#pragma endregion 


private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// スフィアの計算
	/// </summary>
	void CalcSphere();

	/// <summary>
	/// いろいろ設定する
	/// </summary>
	void SetEnemyProperty();

	/// <summary>
	/// マットワールド作る
	/// </summary>
	void UpdateMat();

private:

	// エネミー
	EnemyProperty ene_;

	// プレイヤー
	Player* player_;

	// 初期値
	EnemyInitProperty init_;

	// 移動量
	float move_;

	// Sphere
	Sphere eneSphere_;

	// インプット
	Input* input = nullptr;

	// 
	uint32_t isHit_;

	bool isApproach_ = false;

	bool isDead_ = false;
};