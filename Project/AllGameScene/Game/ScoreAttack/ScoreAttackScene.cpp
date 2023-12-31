#include "ScoreAttackScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"

#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>
#include "AllGameScene/Result/Win/WinScene.h"
#include "AllGameScene/Result/Lose/LoseScene.h"
#include "AllGameScene/Title/TitleScene.h"

/// <summary>
/// 初期化処理
/// </summary>
void ScoreAttackScene::Initialize(GameManager* gamaManager) {

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
	// プレイヤーヒットボックス
	playerHitBox_ = std::make_unique<PlayerHitBox>();
	playerHitBox_->Initialize();
	playerHitBox_->SetPlayer(player_.get());

	// エネミー
	enemy_ = std::make_unique<Enemy>();
	enemysCountTimer_ = 0;

	// コリジョンマネージャー
	collisionManager_ = std::make_unique<CollisionManager>();

	//制限時間
	countDown_ =std::make_unique<CountDown>();
	countDown_->Initialize();

	//スコア
	score_ = std::make_unique<Score>();
	score_->Initialize();
	score_->SetCollisionManager(collisionManager_.get());
	score_->SetPlayerHitBox(playerHitBox_.get());

#pragma region 後でクラスにする
	//Ready
	ready_ = std::make_unique<Sprite>();
	uint32_t reeadyTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Start/Ready.png");
	ready_.reset(Sprite::Create(reeadyTextureHandle_, { 0.0f,0.0f }));

	//Go
	go_ = std::make_unique<Sprite>();
	uint32_t goTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Start/Go.png");
	go_.reset(Sprite::Create(goTextureHandle_, { 0.0f,0.0f }));


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

	//プレイのテキスト
	playText_ = std::make_unique<Sprite>();
	uint32_t playTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/PlayUI.png");
	playText_.reset(Sprite::Create(playTextureHandle, { 1120.0f,500.0f }));

#pragma endregion

	//カメラ
	cameraPosition_ = { 0.0f,2.2f,0.0f };
	cameraRotate_ = { 0.015f,0.0f,0.0f };


	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);

	

	finishSE_ = Audio::GetInstance();
	finishHandle_ = finishSE_->LoadWave("Resources/Audio/Finish/Finish.wav");

	lose_ = Audio::GetInstance();
	loseHandle_ = lose_->LoadWave("Resources/Audio/Action/Damege.wav");

	bgm_ = Audio::GetInstance();
	bgmHandle_ = bgm_->LoadWave("Resources/Audio/BGM/ScoreAttack.wav");
	bgm_->PlayWave(bgmHandle_, true);
	bgm_->ChangeVolume(bgmHandle_, 0.2f);

}

//RedayScene
void ScoreAttackScene::ReadyUpdate() {
	cameraPosition_.z -= 0.05f;
	if (cameraPosition_.z < -8.0f) {
		cameraPosition_.z = -8.0f;
		readyTime_ += 1;

	}

	

	if (readyTime_ > 60 * 4) {
		phaseNo_ = Play;
	}
}

//PlayScene
void ScoreAttackScene::PlayUpdate() {

	bgm_->ChangeVolume(bgmHandle_, 0.7f);
	// エネミー
	EnemysUpdate();

	//制限時間
	countDown_->Update();

	//スコア

	score_->Update();
	
	

	//負け(仮)
	if (collisionManager_->GetIsHitPlayerAndEnemy() == true) {
		countDown_->ISetICounDown(false);
		phaseNo_ = Failed;
	}
	


}

//Succeeded
void ScoreAttackScene::SucceededUpdate() {
	finishDisplayTime_ += 1;
	if (finishDisplayTime_==1) {
		finishSE_->PlayWave(finishHandle_, false);
	}

	if (finishDisplayTime_ > 60 * 2) {
		isWhiteOut_ = true;
	}


	if (isWhiteOut_ == true) {
		//ズーム
		//ホワイトアウト
		cameraPosition_.y +=0.02f ;
		cameraPosition_.z +=0.05f ;
		whiteTransparency_ += 0.01f;
		white_->SetTransparency(whiteTransparency_);

		if (whiteTransparency_ > 1.0f) {
			whiteTransparency_ = 1.0f;


			bgm_->StopWave(bgmHandle_);
			if (countDown_->GetIsCountDown() == true) {
				loadingTime += 1;
			
			}
			
			
		}
	}
}

//Failed
void ScoreAttackScene::FailedUpdate() {
	bgm_->StopWave(bgmHandle_);

	loseTriggerTime_++;
	if (loseTriggerTime_ == 1) {
		lose_->PlayWave(loseHandle_, false);

	}
	
	theta += 1.0f;
	cameraPosition_.x += std::sinf(theta)*0.5f;
	
	blackTransparency_ += 0.01f;
	black_->SetTransparency(blackTransparency_);
	if (blackTransparency_ > 1.0f) {
		loseLodingTime_ += 1;
	}
}

/// <summary>
/// 更新処理
/// </summary>
void ScoreAttackScene::Update(GameManager* gamaManager) {
	

	//とうもろこしの更新
	corn_->Update();

	//オーブンの更新
	oven_->Update();

	//電熱線
	lamp_->Update();

	// プレイヤー
	player_->Update();
	playerHitBox_->Update();
	

	// 衝突判定
	CheckAllCollision();
	
	

	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);

	

#ifdef _DEBUG
	ImGui::Begin("Game");
	ImGui::InputInt("WinLoadingTime", &loadingTime);
	ImGui::InputInt("LoseLoadingTime", &loseLodingTime_);

	ImGui::End();
	

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Translate", &cameraPosition_.x, -20.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &cameraRotate_.x, -5.0f, 5.0f);
	ImGui::End();

#endif // _DEBUG


	switch (phaseNo_) {
	default:
	case Ready:
		//Readyのシーン
		ReadyUpdate();

		break;
	case Play:
		//ゲームプレイ時のシーン
		PlayUpdate();
		
		break;
	case Succeeded:
		//勝ち
		SucceededUpdate();
		
		if (loadingTime > 60) {
			gamaManager->ChangeScene(new WinScene());
		}

		break;

	case Failed:
		//負け
		FailedUpdate();

		//シーンチェンジ
		if (loseLodingTime_ > 60) {
			gamaManager->ChangeScene(new TitleScene());
		}

		break;
	};

	

	
	
	

	

}


/// <summary>
/// 描画処理
/// </summary>
void ScoreAttackScene::Draw(GameManager* gamaManager) {
	//とうもろこし
	corn_->Draw();

	//オーブン
	oven_->Draw();

	//電熱線
	lamp_->Draw();

	//プレイヤー
	player_->Draw();
	playerHitBox_->Draw();

	switch (phaseNo_) {
	case Ready:
	default:
		if (readyTime_ > 0 && readyTime_ <= 60 * 2) {
			ready_->Draw();

		}

		if (readyTime_ > 60 * 2 && readyTime_ <= 60 * 4) {
			go_->Draw();

		}

		break;
	case Play:
		for (Enemy* enemy : enemys_) {
			enemy->Draw();
		}


		//制限時間
		//countDown_->Draw();

		//スコア
		score_->Draw();

		//操作方法
		playText_->Draw();

		break;
	case Succeeded:

		if (finishDisplayTime_ <= 60 * 2) {
			finish_->Draw();
		}
		if (isWhiteOut_ == true) {
			white_->Draw();
		}
		break;

	case Failed:
		black_->Draw();
		break;
	};

}


void ScoreAttackScene::EnemysUpdate() {

	// 更新処理
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	// 衝突していたら削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
		}
	);


	// タイマーカウント
	enemysCountTimer_++;

	// タイマーカウントが５を超えたら
	if (enemysCountTimer_ >= 60) {

		// タイマーは0に戻す
		enemysCountTimer_ = 0;

		// エネミーのリストが５以下だったら新しくプッシュバックする
		if (CalcEnemysList() < 5) {

			// リスポーン
			PushBackEnemy();
		}
	}
	/*if (Input::GetInstance()->IsPushKey(DIK_RETURN)) {
		PushBackEnemy();
	}*/

#ifdef _DEBUG

	ImGui::Begin("EnemyList");
	ImGui::Text("timer = %d", enemysCountTimer_);
	ImGui::Text("enemyList = %d", CalcEnemysList());
	ImGui::End();

#endif // _DEBUG
}

uint32_t ScoreAttackScene::CalcEnemysList() {

	size_t count = enemys_.size();

	return static_cast<uint32_t>(count);
}

void ScoreAttackScene::PushBackEnemy() {

	// インスタンス生成
	Enemy* newEnemy = new Enemy();

	// 乱数生成
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());

	// X,Yは乱数で、Zはプレイヤーと揃える
	std::uniform_real_distribution<float> distributionX(-7.0f, 7.0f);
	std::uniform_real_distribution<float> distributionY(4.0f, 8.0f);

	// 敵の初期値を乱数で沸かせる
	Vector3 newPos = { 
		.x = distributionX(randomEngine),
		.y = distributionY(randomEngine),
		.z = player_->GetTransform().translate.z
	};
	newEnemy->Initialize(newPos);
	newEnemy->SetPlayer(player_.get());
	enemys_.push_back(newEnemy);
}


//void GameScene::ChangeScene(IGamePlayScene* newGameScene){
//	//一度消してから次のシーンにいく
//	delete currentGamaScene_;
//
//	currentGamaScene_ = newGameScene
//	//今は言っているシーンが引数
//	currentGamaScene_->Initialize(this);
//}


/// <summary>
/// 衝突判定
/// </summary>
void ScoreAttackScene::CheckAllCollision() {

	// オブジェクトの設定
	collisionManager_->SetPlayer(player_.get());
	collisionManager_->SetPlayerHitBox(playerHitBox_.get());
	for (Enemy* enemy : enemys_) {
		collisionManager_->EnemyListPushBack(enemy);
	}

	// 衝突判定
	collisionManager_->CheckAllCollision();
}

ScoreAttackScene::~ScoreAttackScene() {

	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
}