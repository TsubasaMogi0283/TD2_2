#include "DemoGround.h"



void DemoGround::Init() {


	// モデル
	model_ = std::make_unique<Model>();
	model_.reset(Model::Create("Resources/DemoGround", "DemoGround.obj"));
	model_->SetLighting(false);

	// 座標
	transform_ = {
		.scale = {1.0f, 1.0f, 1.0f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 0.0f, 0.0f},
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

	// OBB
	obb_ = {
		.center = transform_.translate,
		.orientations = {
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},},
		.size = { 10.0f, 1.0f, 10.0f },
	};

}


void DemoGround::Update() {



	SetGroundProperty();






	ImGui::Begin("Ground");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scale", &transform_.scale.x, 0.005f);
	ImGui::DragFloat3("Rotate", &transform_.rotate.x, 0.005f);
	ImGui::DragFloat3("translate", &transform_.translate.x, 0.02f);
	ImGui::Text("size");
	ImGui::DragFloat3("size", &size_.x, 0.01f);
	ImGui::Text("OBB");
	ImGui::DragFloat3("OBB.center", &obb_.center.x, 0.01f);
	ImGui::DragFloat3("OBB.rotate", &transform_.rotate.x, 0.01f);
	ImGui::DragFloat3("OBB.size", &obb_.size.x, 0.01f);
	ImGui::End();
}


void DemoGround::Draw() {

	model_->Draw();

}


void DemoGround::onCollisionToEnemy() {


}


void DemoGround::EndOverlapToEnemy() {



}


void DemoGround::Move() {


}


void DemoGround::SetGroundProperty() {

	model_->SetColor(color_);
	model_->SetScale(transform_.scale);
	model_->SetRotate(transform_.rotate);
	model_->SetTranslate(transform_.translate);



	Matrix4x4 rotateMat = MakeRotateXYZMatrix(
		transform_.rotate.x, transform_.rotate.y, transform_.rotate.z);

	obb_.orientations[0].x = rotateMat.m[0][0];
	obb_.orientations[0].y = rotateMat.m[0][1];
	obb_.orientations[0].z = rotateMat.m[0][2];

	obb_.orientations[1].x = rotateMat.m[1][0];
	obb_.orientations[1].y = rotateMat.m[1][1];
	obb_.orientations[1].z = rotateMat.m[1][2];

	obb_.orientations[2].x = rotateMat.m[2][0];
	obb_.orientations[2].y = rotateMat.m[2][1];
	obb_.orientations[2].z = rotateMat.m[2][2];

	obb_ = {
		.center = transform_.translate,
		.orientations = {
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},},
		.size = { 10.0f, 1.0f, 10.0f },
	};
}