#include "SampleScene.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "TextureManager/TextureManager.h"

/// <summary>
	/// コンストラクタ
	/// </summary>
SampleScene::SampleScene() {

}



/// <summary>
/// 初期化
/// </summary>
void SampleScene::Initialize(GameManager* gameManager) {
	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		model_[i] = Model::Create("Resources/05_02", "plane.obj");
	
	}

	uint32_t textureHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	sprite=Sprite::Create(textureHandle, {0.0f,0.0f});
	

}

/// <summary>
/// 更新
/// </summary>
void SampleScene::Update(GameManager* gameManager) {

#pragma region Sprite

	

	sprite->SetScale(scale_);
	sprite->SetRotate(rotate);
	sprite->SetPosition(position_);

	sprite->SetColor(color_);

	ImGui::Begin("Sprite");
	ImGui::SliderFloat4("color", &color_.x, 0.0f, 1.0f);
	ImGui::SliderFloat2("Scale", &scale_.x, 0.0f, 3.0f);
	ImGui::SliderFloat("Rotate", &rotate, 0.0f,3.0f);
	ImGui::SliderFloat2("Position", &position_.x, 0.0f,1000.0f);
	
	


	ImGui::End();


#pragma endregion

	
	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		model_[i]->SetColor(modelColor_);
		model_[i]->SetTranslate(modelTranslate_);
	}
	ImGui::Begin("Plane");
	ImGui::SliderFloat3("Translate", &modelTranslate_.x, -10.0f, 10.0f);
	ImGui::SliderFloat4("Color", &modelColor_.x, 0.0f, 1.0f);
	

	ImGui::End();
	

	


}

/// <summary>
/// 描画
/// </summary>
void SampleScene::Draw(GameManager* gameManager) {
	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		model_[i]->Draw();
	
	}
	sprite->Draw();
}

/// <summary>
/// デストラクタ
/// </summary>
SampleScene::~SampleScene() {
	for (int i = 0; i < MODEL_AMOUNT_; i++) {
		delete model_[i];
	}
	delete sprite;
}
