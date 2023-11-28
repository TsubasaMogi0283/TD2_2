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

	//制限時間
	countDown_ =std::make_unique<CountDown>();
	countDown_->Initialize();

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
	
	//制限時間
	countDown_->Update();

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


	//制限時間
	countDown_->Draw();
	
	//スコア
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



