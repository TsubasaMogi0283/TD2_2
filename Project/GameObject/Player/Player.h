#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"
#include "Collider/Collider.h"

#include "Collider/ICollisionState.h"
#include "GameObject/Player/PlayerCollisionState/Front/IPlayerCollisionFrontState.h"



struct PlayerProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
	Vector3 velocity{};
	float size;
};
struct GravityProperty {
	Vector3 velocity{}; // 加算速度
	float accel; // 重力の強さ
	bool enable; // 重力が有効化のフラグ
	float maxVel; //最大速度
};
struct InitProperty {
	Transform transform{};
};



/* Playerクラス */
class Player : public Collider {

public:

	Player() {};
	~Player() {};

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
	void onCollision(CollisionType type) override;


#pragma region Get

	/// <summary>
	/// AABBの取得
	/// </summary>
	AABB GetAABB() override { return aabb_; }

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

private:

	// プレイヤー
	PlayerProperty pla_;

	// 重力
	GravityProperty gravity_;

	// 初期値
	InitProperty init_;

	// コライダー
	std::unique_ptr<ICollisionState> collisionState_[10];

	// インプット
	Input* input = nullptr;

	// 
	AABB aabb_;


};