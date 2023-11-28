#pragma once
#include "AllGameScene/GameManager/IGamePlayScene.h"
#include <Object/Enemy/Enemy.h>
#include <Object/CountDown/CountDown.h>
#include <Object/Score/Score.h>
#include <Object/Player/Player.h>

class GameScene;

class PlayScene  : public IGamePlayScene{
public:
	PlayScene() {};
	~PlayScene();

	void Initialize(GameScene* gamaManager) override;
	void Update(GameScene* gamaManager) override;
	void Draw(GameScene* gamaManager) override;

private:

	/// <summary>
	/// 衝突判定
	/// </summary>
	void CheckAllCollision();


private:
	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;
	// エネミー
	std::unique_ptr<Enemy> enemy_ = nullptr;

	//制限時間
	std::unique_ptr<CountDown> countDown_ = nullptr;

	//スコア
	std::unique_ptr<Score> score_ = nullptr;

	// コリジョンマネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;

};

