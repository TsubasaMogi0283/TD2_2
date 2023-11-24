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
	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		//代入の時はresetを使ってね
		timeTensPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {600.0f,30.0f}));
		timeOnesPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {680.0f,30.0f}));



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
	corn_->Draw();
	oven_->Draw();
	lamp_->Draw();
	player_->Draw();



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
	
	
}

/// <summary>
/// デストラクタ
/// </summary>
SampleScene::~SampleScene() {
	
	
	
}
