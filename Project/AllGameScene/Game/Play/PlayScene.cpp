#include "PlayScene.h"
#include "AllGameScene/Game/GameScene.h"

#include "Camera/Camera.h"

void PlayScene::Initialize(GameScene* gamaManager){
	//Ready
	ready_ = std::make_unique<Sprite>();
	uint32_t reeadyTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Start/Ready.png");
	ready_.reset(Sprite::Create(reeadyTextureHandle_, { 0.0f,0.0f }));

	//Go
	go_ = std::make_unique<Sprite>();
	uint32_t goTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Start/Go.png");
	go_.reset(Sprite::Create(goTextureHandle_, { 0.0f,0.0f }));

	cameraPosition_ = { 0.0f,2.2f,0.0f };
	cameraRotate_ = { 0.015f,0.0f,0.0f };

	// プレイヤー
	player_ = std::make_unique<Player>();
	player_->Initialize();
	
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
	// プレイヤー
	player_->Update();
	
	// エネミー
	enemy_->Update();

	//制限時間
	countDown_->Update();

	//スコア
	score_->Update();

	// 衝突判定
	CheckAllCollision();


	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);

	cameraPosition_.z -= 0.05f;
	if (cameraPosition_.z < -8.0f) {
		cameraPosition_.z = -8.0f;
		readyTime_ += 1;
		

	}
	
	//GamePlayへ
	if (readyTime_ > 60 * 4) {
		//gamaManager->ChangeScene(new PlayScene());
	}

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
	if (readyTime_ > 0 && readyTime_ <= 60 * 2) {
		ready_->Draw();

	}

	if (readyTime_ > 60*2 && readyTime_ <= 60 * 4) {
		go_->Draw();
		
	}


	//プレイヤー
	player_->Draw();

	enemy_->Draw();


	//制限時間
	countDown_->Draw();
		
	//スコア
	score_->Draw();
}

PlayScene::~PlayScene() {

}
