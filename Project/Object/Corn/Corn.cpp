#include "Corn.h"

Corn::Corn(){

}

void Corn::DisplayText(){
	ImGui::Begin("Corn");
	ImGui::SliderFloat3("Translate", &position_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &rotate_.x, -4.0f, 4.0f);
	ImGui::SliderFloat4("Color", &color_.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Light", &lightDirection_.x, -1.0f, 1.0f);
	
	ImGui::End();
}


void Corn::Initialize(){
	model_ = Model::Create("Resources/Corn", "Corn.obj");
	position_ = { -0.3f,0.0f,0.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	color_ = { 1.0f,1.0f,0.2f,1.0f };

	lightDirection_ = { 0.0f,-1.0f,0.0f };
}

void Corn::Update(){
	model_->SetColor(color_);
	model_->SetTranslate(position_);
	model_->SetRotate(rotate_);

	rotate_.x += 0.01f;
	//lightDirection_.y += 0.1f;
	if (lightDirection_.y > 1.0f) {

	}

	//lightDirection_.y = std::cosf(theta_);
	model_->SetDirection(lightDirection_);


	DisplayText();

}

void Corn::Draw(){
	model_->Draw();
}

Corn::~Corn(){
	delete model_;
}

