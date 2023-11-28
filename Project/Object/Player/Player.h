#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include "CollisionManager/CollisionManager.h"
#include "Object/Player/Particle/PlayerParticle.h"

#include <list>


struct PlayerProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
	Vector3 velocity{};
	Vector3 size{};
	Vector4 color{};
};
struct GravityProperty {
	Vector3 velocity{}; // 加算速度
	float accel; // 重力の強さ
	bool enable; // 重力が有効化のフラグ
	float maxVel; //最大速度
};
struct PlayerInitProperty {
	Transform transform{};
};



/* Playerクラス */
class Player {

public:

	Player() {};
	~Player();

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
	void onCollisionToEnemy();
	void EndOverlapToEnemy();


#pragma region Get

	/// <summary>
	/// Transformの取得
	/// </summary>
	Transform GetTransform() { return pla_.transform; }

	/// <summary>
	/// Sphereの取得
	/// </summary>
	Sphere GetSphere() { return plaSphere_; }

#pragma endregion 


#pragma region Set

	/// <summary>
	/// 重力のフラグの設定
	/// </summary>
	void SetgGravityEnable(bool f) { gravity_.enable = f; }

	void SetIsHit(uint32_t val) { isHit_ = val; }

#pragma endregion 


private:

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 重力の処理
	/// </summary>
	void CalcGravity();

	/// <summary>
	/// スフィアの計算
	/// </summary>
	void CalcSphere();

	/// <summary>
	/// いろいろ設定する
	/// </summary>
	void SetPlayerProperty();

	/// <summary>
	/// パーティクルの更新処理
	/// </summary>
	void UpdateParticle();

	/// <summary>
	/// プレイヤーパーティクルのプッシュバク処理
	/// </summary>
	void PushBackParticles();

private:

	// プレイヤー
	PlayerProperty pla_;

	// 重力
	GravityProperty gravity_;

	// 初期値
	PlayerInitProperty init_;

	// 回転量
	Vector3 moveRotate_{};

	// Sphere
	Sphere plaSphere_;

	uint32_t isHit_;


	// パーティクル
	std::list<PlayerParlicle*> particles_;
	uint32_t particlePushBackTimer_;

	// インプット
	Input* input = nullptr;


};