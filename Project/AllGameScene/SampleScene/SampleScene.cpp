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
	corn_ = Model::Create("Resources/Corn", "Corn.obj");
	cornPosition_ = { -0.3f,0.0f,0.0f };
	cornRotate_ = { 0.0f,0.0f,0.0f };
	cornColor_ = { 1.0f,1.0f,0.2f,1.0f };

	//オーブン
	oven_ = std::make_unique<Oven>();
	oven_->Initialize();

	//オーブンの電熱線
	//ランプって表記している
	lamp_ = Model::Create("Resources/Lamp", "Lamp.obj");
	lampPosition_ = { 0.0f,4.0f,3.7f };
	lampScale_ = { 1.0f,1.0f,1.0f };
	lampRotate_ = { 4.0f,0.0f,0.0f };
	lampColor_ = { 1.0f,1.0f,1.0f,1.0f };

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


	corn_->SetColor(cornColor_);
	corn_->SetTranslate(cornPosition_);
	corn_->SetRotate(cornRotate_);

	

	lamp_->SetTranslate(lampPosition_);
	lamp_->SetScale(lampScale_);
	lamp_->SetRotate(lampRotate_);
	lamp_->SetColor(lampColor_);

	ImGui::Begin("Corn");
	ImGui::SliderFloat3("Translate", &cornPosition_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &cornRotate_.x, -4.0f, 4.0f);
	ImGui::SliderFloat4("Color", &cornColor_.x, 0.0f, 1.0f);
	ImGui::End();
	
	//オーブンの更新
	oven_->Update();

	

	ImGui::Begin("Lamp");
	ImGui::SliderFloat3("Translate", &lampPosition_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &lampRotate_.x, -4.0f, 4.0f);
	ImGui::SliderFloat4("Color", &lampColor_.x, 0.0f, 1.0f);

	ImGui::End();

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
	delete corn_;
	
	delete lamp_;
}
