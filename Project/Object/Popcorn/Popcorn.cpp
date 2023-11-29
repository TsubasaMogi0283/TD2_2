#include "Popcorn.h"


Popcorn::Popcorn(){

}

void Popcorn::Initialize(Vector3 position,Vector3 move){
	//moveは方向
	this->position_ = position;
	this->move_ = move;
	
	const float SCALE_SIZE = 0.2f;
	radius = SCALE_SIZE;
	this->scale_ = { SCALE_SIZE,SCALE_SIZE,SCALE_SIZE };

	model_ = Model::Create("Resources/Popcorn", "Popcorn.obj");
}

void Popcorn::DisplayText(){
	ImGui::Begin("Popcorn");
	ImGui::InputInt("Time", &deleteTime_);
	ImGui::End();
}

void Popcorn::Update(){

	//初速度
	//Vector3 initialVelocity = move_;

	//最終的は速度
	
	Vector3 acceleration = { 0.0f,-0.03f,0.0f };
	move_ = Add(move_, acceleration);

	position_ = Add(position_,move_);

	deleteTime_ -= 1;

	if (deleteTime_<0) {
		isDead_ = true;
	}

	model_->SetScale(scale_);
	model_->SetTranslate(position_);
	DisplayText();

	CalcSphere();
}

void Popcorn::Draw(){
	model_->Draw();
}

Popcorn::~Popcorn(){
	delete model_;
}


/// <summary>
/// スフィアの計算
/// </summary>
void Popcorn::CalcSphere() {

	sphere = {
		.center = position_,
		.radius = radius,
	};
}