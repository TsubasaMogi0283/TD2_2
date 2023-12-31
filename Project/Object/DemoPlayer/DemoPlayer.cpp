#include "DemoPlayer.h"



void DemoPlayer::Init() {


	// モデル
	model_ = std::make_unique<Model>();
	model_.reset(Model::Create("Resources/DemoPlayer", "DemoPlayer.obj"));
	model_->SetLighting(false);

	// 座標
	transform_ = {
		.scale = {1.0f, 1.0f, 1.0f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 5.0f, 0.0f},
	};

	// 速度
	velocity_ = { 0.1f, 0.1f, 0.1f };

	// 回転量
	moveRotate_ = { 0.3f, 0.2f, 0.1f };

	//サイズ
	size_ = {
		.x = 1.0f * transform_.scale.x,
		.y = 1.0f * transform_.scale.y,
		.z = 1.0f * transform_.scale.z,
	};

	// カラー
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 線分
	segment_ = {
		.origin = {
			.x = transform_.translate.x,
			.y = transform_.translate.y + size_.y,
			.z = transform_.translate.z,},
		.diff = {
			.x = transform_.translate.x,
			.y = transform_.translate.y - size_.y,
			.z = transform_.translate.z, },
	};

	// 衝突フラグ
}


void DemoPlayer::Update() {



	SetPlayerProperty();






	ImGui::Begin("Player");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scale", &transform_.scale.x, 0.005f);
	ImGui::DragFloat3("Rotate", &transform_.rotate.x, 0.005f);
	ImGui::DragFloat3("translate", &transform_.translate.x, 0.02f);
	ImGui::Text("size");
	ImGui::DragFloat3("size", &size_.x, 0.01f);
	ImGui::Checkbox("isHit", &isHit_);
	ImGui::Text("Segment");
	ImGui::DragFloat3("Segment.Origin", &segment_.origin.x, 0.01f);
	ImGui::DragFloat3("Segment.Diff", &segment_.diff.x, 0.01f);
	ImGui::End();
}


void DemoPlayer::Draw() {

	model_->Draw();

}


void DemoPlayer::onCollisionToEnemy() {

	isHit_ = true;
}


void DemoPlayer::EndOverlapToEnemy() {

	isHit_ = false;
}


void DemoPlayer::Move() {


}


void DemoPlayer::SetPlayerProperty() {

	model_->SetColor(color_);
	model_->SetScale(transform_.scale);
	model_->SetRotate(transform_.rotate);
	model_->SetTranslate(transform_.translate);

	segment_ = {
		.origin = {
			.x = transform_.translate.x,
			.y = transform_.translate.y + size_.y,
			.z = transform_.translate.z,},
		.diff = {
			.x = transform_.translate.x,
			.y = transform_.translate.y - size_.y,
			.z = transform_.translate.z, },
	};
}
