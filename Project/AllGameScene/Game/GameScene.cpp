#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>



/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize(GameManager* gamaManager) {

	//とうもろこし
	corn_ = std::make_unique<Corn>();
	corn_->Initialize();

	//オーブン
	oven_ = std::make_unique<Oven>();
	oven_->Initialize();

	//オーブンの電熱線 (ランプって表記している)
	lamp_ = std::make_unique<Lamp>();
	lamp_->Initialize();

	// プレイヤー
	player_ = std::make_unique<Player>();
	player_->Initialize();

	// エネミー
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize();
	enemy_->SetPlayer(player_.get());

	// コリジョンマネージャー
	collisionManager_ = std::make_unique<CollisionManager>();


	//カウントダウン
	numberTextureHandle[0] = TextureManager::LoadTexture("Resources/Number/0.png");
	numberTextureHandle[1] = TextureManager::LoadTexture("Resources/Number/1.png");
	numberTextureHandle[2] = TextureManager::LoadTexture("Resources/Number/2.png");
	numberTextureHandle[3] = TextureManager::LoadTexture("Resources/Number/3.png");
	numberTextureHandle[4] = TextureManager::LoadTexture("Resources/Number/4.png");
	numberTextureHandle[5] = TextureManager::LoadTexture("Resources/Number/5.png");
	numberTextureHandle[6] = TextureManager::LoadTexture("Resources/Number/6.png");
	numberTextureHandle[7] = TextureManager::LoadTexture("Resources/Number/7.png");
	numberTextureHandle[8] = TextureManager::LoadTexture("Resources/Number/8.png");
	numberTextureHandle[9] = TextureManager::LoadTexture("Resources/Number/9.png");

	//カウントダウン
	uint32_t frameTextureHandle = TextureManager::LoadTexture("Resources/Frame/Frame.png");
	countDownBackPosition_ = { 590.0f,18.0f };
	countDownBackSize_ = { 0.11f,0.12f };
	countDownBack_.reset(Sprite::Create(frameTextureHandle,countDownBackPosition_ ));
	
	

	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		//代入の時はresetを使ってね
		timeTensPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { 600.0f,30.0f }));
		timeOnesPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { 680.0f,30.0f }));
	}

	//スコア
	score_ = std::make_unique<Score>();
	score_->Initialize();

	//カメラ
	cameraPosition_ = { 0.0f,2.2f,-8.0f };
	cameraRotate_ = { 0.015f,0.0f,0.0f };

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* gamaManager) {

	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);

	//カウントダウン
	CountDown();

	//とうもろこしの更新
	corn_->Update();

	//オーブンの更新
	oven_->Update();

	//電熱線
	lamp_->Update();

	// プレイヤー
	player_->Update();

	// エネミー
	enemy_->Update();

	// 衝突判定
	CheckAllCollision();
	
	//スコア
	score_->Update();

#ifdef _DEBUG

	ImGui::Begin("Game");
	ImGui::End();

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Translate", &cameraPosition_.x, -20.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &cameraRotate_.x, -5.0f, 5.0f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw(GameManager* gamaManager) {
	//とうもろこし
	corn_->Draw();

	//オーブン
	oven_->Draw();

	//電熱線
	lamp_->Draw();

	//プレイヤー
	player_->Draw();
	enemy_->Draw();

	

	//制限時間の後ろのテクスチャ
	countDownBack_->Draw();

	//スプライトは後ろに描画してね
	//透明部分がすり抜けてしまうから
	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		if (tensPlace_ == i) {
			timeTensPlane_[i]->Draw();
		}
		if (onesPlace_ == i) {
			timeOnesPlane_[i]->Draw();
		}
	}

	//スコアの描画
	score_->Draw();
	

}


/// <summary>
/// 衝突判定
/// </summary>
void GameScene::CheckAllCollision() {

	// オブジェクトの設定
	collisionManager_->SetPlayer(player_.get());
	collisionManager_->SetEnemy(enemy_.get());

	// 衝突判定
	collisionManager_->CheckAllCollision();
}


/// <summary>
/// カウントダウン
/// </summary>
void GameScene::CountDown() {
	//仮で60秒
	gameTime_ -= 1;

	displayTime_ = gameTime_ / 60;

	tensPlace_ = displayTime_ / 10;
	onesPlace_ = displayTime_ % 10;

	countDownBack_->SetScale(countDownBackSize_);
	countDownBack_->SetPosition(countDownBackPosition_);
}

