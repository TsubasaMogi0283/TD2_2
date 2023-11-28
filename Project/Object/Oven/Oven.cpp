#include "Oven.h"

Oven::Oven()
{
}

void Oven::Initialize(){
	//オーブン
	oven_ = Model::Create("Resources/Oven", "Oven.obj");

	//スケールとポジションを初期化する
	ovenPosition_ = { 0.0f,0.6f,0.0f };
	ovenRotate_ = { 0.0f,0.0f,0.0f };
}

void Oven::DisplayText(){
	ImGui::Begin("Oven");
	ImGui::SliderFloat3("Translate", &ovenPosition_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &ovenRotate_.x, -4.0f, 4.0f);
	ImGui::End();
}

void Oven::Update(){
	//スケールととポジションををセットする
	oven_->SetTranslate(ovenPosition_);
	oven_->SetRotate(ovenRotate_);


	DisplayText();

	

}

void Oven::Draw(){
	//描画
	oven_->Draw();
}

Oven::~Oven(){
	delete oven_;
}
