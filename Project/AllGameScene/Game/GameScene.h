#pragma once

#include "AllGameScene/GameManager/IGameScene.h"

#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>

#include "Polygon/Sprite/Sprite.h"
#include "Polygon/Model/Model.h"

#include "Object/Oven/Oven.h"
#include <Object/Corn/Corn.h>
#include <Object/Lamp/Lamp.h>
#include <Object/Player/Player.h>
#include <Object/Enemy/Enemy.h>
#include "CollisionManager/CollisionManager.h"
#include <Object/CountDown/CountDown.h>
#include <Object/Score/Score.h>
#include <AllGameScene/GameManager/IGamePlayScene.h>


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
	/// エネミーリストの処理をまとめたもの
	/// </summary>
	void EnemysUpdate();

	/// <summary>
	/// エネミーのリストのカウント
	/// </summary>
	uint32_t CalcEnemysList();
	
	/// <summary>
	/// 新しいエネミーをプッシュバックする
	/// </summary>
	void PushBackEnemy();

	////シーンチェンジ
	//void ChangeScene(IGamePlayScene* newGameScene);


private:
	//switch文の中身
	void ReadyUpdate();

	void PlayUpdate();

	void SucceededUpdate();

	void FailedUpdate();

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
	std::list<Enemy*> enemys_;
	uint32_t enemysCountTimer_;

	// コリジョンマネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;

	//制限時間
	std::unique_ptr<CountDown> countDown_ = nullptr;

	//スコア
	std::unique_ptr<Score> score_ = nullptr;


	//カメラ
	Vector3 cameraPosition_ = {};
	Vector3 cameraRotate_ = {};


	int readyTime_ = 0;

	//Ready
	std::unique_ptr<Sprite> ready_ = nullptr;
	//Go
	std::unique_ptr<Sprite> go_ = nullptr;
	
	//Finish
	std::unique_ptr<Sprite> finish_ = nullptr;
	int finishDisplayTime_ = 0;

	//WhiteOut
	std::unique_ptr<Sprite> white_ = nullptr;
	float whiteTransparency_ = 0.0f;
	int loadingTime = 0;
	bool isWhiteOut_ = false;

	//BlackOut
	std::unique_ptr<Sprite> black_ = nullptr;
	float blackTransparency_ = 0.0f;
	

	//負け
	float theta = 0.0f;
	int loseLodingTime_ = 0;



	//enum宣言
	enum Phase {
		Ready,	
		Play,
		Succeeded,
		Failed,
	};

	int phaseNo_= 0;

	//StatePatternに必要な変数
	IGamePlayScene* currentGamaScene_ = nullptr;


};

