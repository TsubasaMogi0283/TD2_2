#include "SampleScene.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "TextureManager/TextureManager.h"

#include "Camera/Camera.h"

/// <summary>
	/// コンストラクタ
	/// </summary>
SampleScene::SampleScene() {

}



/// <summary>
/// 初期化
/// </summary>
void SampleScene::Initialize(GameManager* gameManager) {
	//とうもろこし
	corn_ = std::make_unique<Corn>();
	corn_->Initialize();

	//オーブン
	oven_ = std::make_unique<Oven>();
	oven_->Initialize();

	//オーブンの電熱線
	//ランプって表記している
	lamp_= std::make_unique<Lamp>();
	lamp_->Initialize();

	//プレイヤー
	player_ = std::make_unique<SamplePlayer>();
	player_->Initialize();

	//数字

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
		timeTensPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {600.0f,30.0f}));
		timeOnesPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {680.0f,30.0f}));

	}



	//スコア
	const float SPACE_INTERVAL = 60.0f;
	const float initialPositionX = 30.0f;
	
	scoreBackPosition_ =  { 6.0f,488.0f};
	scoreBackSize_ = {0.25f,0.13f};
	scoreBack_.reset(Sprite::Create(frameTextureHandle,scoreBackPosition_));

	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		
		scoreTenThousandsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*0.0f,500.0f}));	
		scoreThousandsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*1.0f,500.0f}));;
		scoreHundredsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*2.0f,500.0f}));;	
		scoreTensPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*3.0f,500.0f}));;
		scoreOnesPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*4.0f,500.0f}));;


	}
	
	//カメラ
	cameraPosition_ = {0.0f,2.2f,-8.0f};
	cameraRotate_ = { 0.015f,0.0f,0.0f };

	

}

void SampleScene::CountDown() {
	//仮で60秒
	gameTime_ -= 1;

	displayTime_ = gameTime_ / 60;

	tensPlace_ = displayTime_ / 10;
	onesPlace_ = displayTime_ % 10;
	countDownBack_->SetScale(countDownBackSize_);
	countDownBack_->SetPosition(countDownBackPosition_);
}

void SampleScene::Score() {


	score_ += 1;


	scoreTenThousandsPlace_ = score_/10000;
	scoreThousandsPlace_ = (score_%10000)/1000;
	scoreHundredsPlace_ = (score_%1000)/100;
	scoreTensPlace_ = (score_%100)/10;
	scoreOnesPlace_ = score_ % 10;

	scoreBack_->SetScale(scoreBackSize_);
	scoreBack_->SetPosition(scoreBackPosition_);

	//ImGui::Begin("Score");
	//ImGui::SliderFloat2("Scale", &scoreBackSize_.x, 0.0f, 1.0f);
	//ImGui::SliderFloat2("CounDownBackPosition", &scoreBackPosition_.x, 0.0f, 1280.0f);
	//ImGui::End();

}

/// <summary>
/// 更新
/// </summary>
void SampleScene::Update(GameManager* gameManager) {

	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);


	
	//カウントダウン
	CountDown();
	
	//スコア表示
	Score();
	
	//とうもろこしの更新
	corn_->Update();
	
	//オーブンの更新
	oven_->Update();

	//電熱線
	lamp_->Update();

	//プレイヤー
	player_->Update();



	
	

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Translate", &cameraPosition_.x, -20.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &cameraRotate_.x, -5.0f, 5.0f);
	ImGui::End();
	

	
}

/// <summary>
/// 描画
/// </summary>
void SampleScene::Draw(GameManager* gameManager) {
	//トウモロコシ
	corn_->Draw();
	
	//オーブン
	oven_->Draw();
	
	//電熱線
	lamp_->Draw();
	
	//プレイヤー
	player_->Draw();

	//スコアの後ろのテクスチャ
	scoreBack_->Draw();

	//制限時間の後ろのテクスチャ
	countDownBack_->Draw();

	//スプライトは後ろに描画してね
	//透明部分がすり抜けてしまうから

	//制限時間
	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		if (tensPlace_ == i) {
			timeTensPlane_[i]->Draw();
		}
		if (onesPlace_ == i) {
			timeOnesPlane_[i]->Draw();
		}

	}

	//スコア
	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		if (scoreTenThousandsPlace_ == i) {
			scoreTenThousandsPlane_[i]->Draw();	
		}
		if (scoreThousandsPlace_ == i) {
			scoreThousandsPlane_[i]->Draw();
		}
		if (scoreHundredsPlace_ == i) {
			scoreHundredsPlane_[i]->Draw();	
		}
		if (scoreTensPlace_ == i) {
			scoreTensPlane_[i]->Draw();
		}
		if (scoreOnesPlace_ == i) {
			scoreOnesPlane_[i]->Draw();
		}
	}

}

/// <summary>
/// デストラクタ
/// </summary>
SampleScene::~SampleScene() {
	
	
	
}
