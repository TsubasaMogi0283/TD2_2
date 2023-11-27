#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include "CollisionManager/CollisionManager.h"


struct EnemyProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
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
	void Initialize();

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

private:

	// プレイヤー
	EnemyProperty ene_;

	// 初期値
	EnemyInitProperty init_;

	// Sphere
	Sphere eneSphere_;

	// インプット
	Input* input = nullptr;
};