#include "Lamp.h"

Lamp::Lamp(){

}

void Lamp::Initialize(){
	model_ = Model::Create("Resources/Lamp", "Lamp.obj");
	position_ = { 0.0f,4.0f,3.7f };
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 4.0f,0.0f,0.0f };
	color_ = { 1.0f,1.0f,1.0f,1.0f };
}

void Lamp::DebugText(){
	ImGui::Begin("Lamp");
	ImGui::SliderFloat3("Translate", &position_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &rotate_.x, -4.0f, 4.0f);
	ImGui::SliderFloat4("Color", &color_.x, 0.0f, 1.0f);

	ImGui::End();
}

void Lamp::Update(){
	model_->SetTranslate(position_);
	model_->SetScale(scale_);
	model_->SetRotate(rotate_);
	model_->SetColor(color_);

}

void Lamp::Draw(){
	model_->Draw();
}

Lamp::~Lamp(){
	delete model_;
}


