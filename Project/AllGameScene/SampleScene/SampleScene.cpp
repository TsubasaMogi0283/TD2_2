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

	//カメラ
	cameraPosition_ = {0.0f,2.2f,-8.0f};
	cameraRotate_ = { 0.015f,0.0f,0.0f };

	

}

/// <summary>
/// 更新
/// </summary>
void SampleScene::Update(GameManager* gameManager) {

	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);


	

	

	
	//とうもろこしの更新
	corn_->Update();
	
	//オーブンの更新
	oven_->Update();

	//電熱線
	lamp_->Update();

	

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
	
}

/// <summary>
/// デストラクタ
/// </summary>
SampleScene::~SampleScene() {
	
	
	
}
