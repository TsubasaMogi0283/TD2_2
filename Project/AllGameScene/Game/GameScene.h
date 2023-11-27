#pragma once

#include "AllGameScene/GameManager/IGameScene.h"

#include <memory>

#include "Polygon/Sprite/Sprite.h"
#include "Polygon/Model/Model.h"

#include "Object/Oven/Oven.h"
#include <Object/Corn/Corn.h>
#include <Object/Lamp/Lamp.h>
#include <Object/Player/Player.h>
#include <Object/Enemy/Enemy.h>
#include "CollisionManager/CollisionManager.h"


//StatePatternを使う時は必ず前方宣言をするように
class Gamemanager;


class GameScene : public IGameScene{
public:

	GameScene() {};
	~GameScene() {};

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;


private:

	/// <summary>
	/// 衝突判定
	/// </summary>
	void CheckAllCollision();


	/// <summary>
	/// カウントダウン
	/// </summary>
	void CountDown();


private:

	//とうもろこし
	std::unique_ptr<Corn> corn_ = nullptr;

	//オーブン
	std::unique_ptr<Oven> oven_ = nullptr;

	//電熱線
	std::unique_ptr<Lamp> lamp_ = nullptr;

	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;

	// エネミー
	std::unique_ptr<Enemy> enemy_ = nullptr;

	// コリジョンマネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;


	//カメラ
	Vector3 cameraPosition_ = {};
	Vector3 cameraRotate_ = {};

	static const int NUMBER_AMOUNT_ = 10;
	std::unique_ptr<Sprite> timeTensPlane_[NUMBER_AMOUNT_] = { nullptr };
	std::unique_ptr<Sprite> timeOnesPlane_[NUMBER_AMOUNT_] = { nullptr };


	//ゲームの時間
	const int timer_ = 20;
	int gameTime_ = 60 * timer_;

	//表示されている時間
	int displayTime_ = gameTime_ / 60;
	//1の位
	int onesPlace_ = 0;
	//10の位
	int tensPlace_ = 0;

	uint32_t numberTextureHandle[10] = {};
};

