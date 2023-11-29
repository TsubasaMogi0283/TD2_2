#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include "CollisionManager/CollisionManager.h"
#include <Object/Popcorn/Popcorn.h>



class Player;

struct PlayerHitBoxProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
	Vector3 size{};
	Vector4 color{};
};


/* PlyerHitBoxクラス */
class PlayerHitBox {

public:

	PlayerHitBox() {};
	~PlayerHitBox() {
		for (Popcorn* popcorn : popcornRight_) {
			delete popcorn;
		}
		for (Popcorn* popcorn : popcornLeft_) {
			delete popcorn;
		}

	};

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
	/// AABBの取得
	/// </summary>
	AABB GetLeftAABB() { return aabbLeft_; }
	AABB GetRightAABB() { return aabbRight_; }

	/// <summary>
	/// ヒットボックス出現フラグの取得
	/// </summary>
	bool GetIsEmergeHitBox() { return isEmergeHitBox_; }

	bool GetIsKillEnemy() {
		return isKillEnemy_;
	}

#pragma endregion


#pragma region Set

	void SetPlayer(Player* player) { player_ = player; }
	

#pragma endregion 

private:

	/// <summary>
	/// もろもろの計算とか
	/// </summary>
	void SetPlayerHitBoxProperty();

	/// <summary>
	/// AABBの計算
	/// </summary>
	void CalcAABB();

private:

	// プレイヤーのヒットボックス
	PlayerHitBoxProperty hitBoxLeft_;
	PlayerHitBoxProperty hitBoxRight_;

	// AABB
	AABB aabbLeft_;
	AABB aabbRight_;

	// プレイヤー
	Player* player_;

	// ヒットボックス出現フラグ
	bool isEmergeHitBox_;


	Model* popcorn_ = nullptr;
	std::list<Popcorn*>popcornRight_;
	std::list<Popcorn*>popcornLeft_;

	bool isKillEnemy_ = false;

};