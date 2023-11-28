#include "PlayScene.h"
#include "AllGameScene/Game/GameScene.h"

void PlayScene::Initialize(GameScene* gamaManager){

	// プレイヤー
	player_ = std::make_unique<Player>();
	player_->Initialize();
	// エネミー
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize();
	enemy_->SetPlayer(player_.get());
	//制限時間
	countDown_ =std::make_unique<CountDown>();
	countDown_->Initialize();

	//スコア
	score_ = std::make_unique<Score>();
	score_->Initialize();

	// コリジョンマネージャー
	collisionManager_ = std::make_unique<CollisionManager>();
}

/// <summary>
/// 衝突判定
/// </summary>
void PlayScene::CheckAllCollision() {

	// オブジェクトの設定
	collisionManager_->SetPlayer(player_.get());
	collisionManager_->SetEnemy(enemy_.get());

	// 衝突判定
	collisionManager_->CheckAllCollision();
}

void PlayScene::Update(GameScene* gamaManager){
	// エネミー
	enemy_->Update();

	//制限時間
	countDown_->Update();

	//スコア
	score_->Update();

	// 衝突判定
	CheckAllCollision();
	//負け(仮)
	if (Input::GetInstance()->IsTriggerKey(DIK_L) == true) {
		//gamePlayScene_ = 6;
	}

	//勝ちへ
	if (countDown_->GetTime() < 0) {
		//gamePlayScene_ = 4;
	}
}

void PlayScene::Draw(GameScene* gamaManager){
	enemy_->Draw();


	//制限時間
	countDown_->Draw();
		
	//スコア
	score_->Draw();
}

PlayScene::~PlayScene() {

}
