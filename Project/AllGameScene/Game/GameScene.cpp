#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"

#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>
#include "AllGameScene/Result/Win/WinScene.h"
#include "AllGameScene/Result/Lose/LoseScene.h"

#include "AllGameScene/Game/Ready/ReadyScene.h"


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

	//// エネミー
	//enemy_ = std::make_unique<Enemy>();
	//enemy_->Initialize();
	//enemy_->SetPlayer(player_.get());

	//// コリジョンマネージャー
	//collisionManager_ = std::make_unique<CollisionManager>();

	////制限時間
	//countDown_ =std::make_unique<CountDown>();
	//countDown_->Initialize();

	////スコア
	//score_ = std::make_unique<Score>();
	//score_->Initialize();
	



#pragma region 後でクラスにする





	

	//Finish
	finish_ = std::make_unique<Sprite>();
	uint32_t finishTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Finish/Finish.png");
	finish_.reset(Sprite::Create(finishTextureHandle, { 0.0f,0.0f }));


	//WhiteOut
	white_ = std::make_unique<Sprite>();
	uint32_t whiteTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/White.png");
	white_.reset(Sprite::Create(whiteTextureHandle, { 0.0f,0.0f }));

	//BlackOut
	black_ = std::make_unique<Sprite>();
	uint32_t blackTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Black.png");
	black_.reset(Sprite::Create(blackTextureHandle, { 0.0f,0.0f }));


#pragma endregion

	//カメラ
	//cameraPosition_ = { 0.0f,2.2f,0.0f };
	//cameraRotate_ = { 0.015f,0.0f,0.0f };



	//GameSceneにさらにStatePatternで分けるよ
	currentGamaScene_ = new ReadyScene();
	currentGamaScene_->Initialize(this);
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* gamaManager) {

	//とうもろこしの更新
	corn_->Update();

	//オーブンの更新
	oven_->Update();

	//電熱線
	lamp_->Update();

	// プレイヤー
	player_->Update();

	

	//// 衝突判定
	//CheckAllCollision();
	
	

	

#ifdef _DEBUG

	ImGui::Begin("Game");
	ImGui::End();

	//ImGui::Begin("Camera");
	//ImGui::SliderFloat3("Translate", &cameraPosition_.x, -20.0f, 10.0f);
	//ImGui::SliderFloat3("Rotate", &cameraRotate_.x, -5.0f, 5.0f);
	//ImGui::End();

#endif // _DEBUG

	currentGamaScene_->Update(this);


	//Ready
	
	
	//Play
	if (gamePlayScene_ == 3) {
		//// エネミー
		//enemy_->Update();

		////制限時間
		//countDown_->Update();

		////スコア
		//score_->Update();

		////負け(仮)
		//if (Input::GetInstance()->IsTriggerKey(DIK_L) == true) {
		//	gamePlayScene_ = 6;
		//}

		////勝ちへ
		//if (countDown_->GetTime() < 0) {
		//	gamePlayScene_ = 4;
		//}
	}
	//勝ち
	if (gamePlayScene_ == 4) {
		finishDisplayTime_ += 1;
		if (finishDisplayTime_ > 60 * 2) {
			gamePlayScene_ = 5;
		}
	}
	if (gamePlayScene_ == 5) {
		//ズーム
		//ホワイトアウト
		//cameraPosition_.y +=0.02f ;
		//cameraPosition_.z +=0.05f ;
		whiteTransparency_ += 0.01f;
		white_->SetTransparency(whiteTransparency_);

		if (whiteTransparency_ > 1.0f) {
			whiteTransparency_ = 1.0f;

			loadingTime += 1;
			
			
		}
	}

	//負け
	if (gamePlayScene_ == 6) {
		theta += 1.0f;
		//cameraPosition_.x += std::sinf(theta)*0.5f;
		
		blackTransparency_ += 0.01f;
		black_->SetTransparency(blackTransparency_);
		if (blackTransparency_ > 1.0f) {
			loseLodingTime_ += 1;
		}
		
	}
	

	if (loseLodingTime_ >= 60) {
		gamaManager->ChangeScene(new LoseScene());
	}

	if (loadingTime > 60) {
		gamaManager->ChangeScene(new WinScene());
	}

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


	

	if (gamePlayScene_ == 3) {
		//enemy_->Draw();


		////制限時間
		//countDown_->Draw();
		//
		////スコア
		//score_->Draw();

	}
	if (gamePlayScene_ == 4) {
		if (finishDisplayTime_ <= 60 * 2) {
			finish_->Draw();
		}
		
	}
	if (gamePlayScene_ == 5) {
		white_->Draw();
	}
	if (gamePlayScene_ == 6) {
		black_->Draw();
	}

	currentGamaScene_->Draw(this);
}

void GameScene::ChangeScene(IGamePlayScene* newGameScene){
	//一度消してから次のシーンにいく
	delete currentGamaScene_;

	currentGamaScene_ = newGameScene;
	//今は言っているシーンが引数
	currentGamaScene_->Initialize(this);
}


/// <summary>
/// 衝突判定
/// </summary>
//void GameScene::CheckAllCollision() {
//
//	// オブジェクトの設定
//	collisionManager_->SetPlayer(player_.get());
//	collisionManager_->SetEnemy(enemy_.get());
//
//	// 衝突判定
//	collisionManager_->CheckAllCollision();
//}



GameScene::~GameScene() {
	delete currentGamaScene_;
};