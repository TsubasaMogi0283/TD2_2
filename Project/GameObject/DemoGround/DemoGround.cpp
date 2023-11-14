#include "DemoGround.h"



// 初期化処理
void DemoGround::Initialize() {

	// モデル
	model_ = std::make_unique<Model>();
	model_->CreateObject("Resources/Ground", "Ground.obj");

	// 座標
	transform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, -5.0f, 50.0f},
	};
}



// 更新処理
void DemoGround::Update() {



#ifdef _DEBUG

	ImGui::Begin("DemoGround");
	ImGui::DragFloat3("Scele", &transform_.scale.x, 0.01f);
	ImGui::DragFloat3("Rotate", &transform_.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &transform_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG


}



// 描画処理
void DemoGround::Draw() {

	model_->Draw(transform_);
}