#include "SamplePlayer.h"
#include <Input/Input.h>


SamplePlayer::SamplePlayer(){

}

void SamplePlayer::Initialize(){
	model_ = Model::Create("Resources/Player", "Player.obj");
	const float SCALE = 0.3f;
	scale_ = { SCALE,SCALE,SCALE };
	position_ = {0.0f,1.2f,0.0f };
	move_ = { 1.0f,1.0f,0.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	color_ = { 1.0f,1.0f,0.2f,1.0f };

}

void SamplePlayer::DisplayText(){
	ImGui::Begin("Player");
	ImGui::SliderFloat3("Translate", &position_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotate", &rotate_.x, -4.0f, 4.0f);
	ImGui::SliderFloat4("Color", &color_.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Light", &lightDirection_.x, -1.0f, 1.0f);
	
	ImGui::End();
}

void SamplePlayer::Move(){
	const float SPEED = 0.1f;
	//左
	if (Input::GetInstance()->IsPushKey(DIK_LEFT)) {
		position_.x -= move_.x*SPEED;
	}

	//右
	if (Input::GetInstance()->IsPushKey(DIK_RIGHT)) {
		position_.x += move_.x*SPEED;
	}



}

void SamplePlayer::Attack() {

	static const int POPCORN_AMOUNT = 1;
	const float MOVE_INTERVAL = 0.01f;
	Vector3 move[POPCORN_AMOUNT] = {};
	
	const float POSITION_INTERVAL = 0.5f;
	Vector3 popcornRightPosition[POPCORN_AMOUNT] = {};

	
	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		Popcorn* popcornRight[POPCORN_AMOUNT] = { nullptr };

		for (int i = 0; i < POPCORN_AMOUNT; i++) {
			
			popcornRightPosition[i] = Add(position_, {POSITION_INTERVAL,-0.2f,0.0f});
			move[i] = {0.03f,0.35f,0.0f };

			//初期化
			popcornRight[i] = new Popcorn;
			popcornRight[i]->Initialize(popcornRightPosition[i], move[i]);

			popcornRight_.push_back(popcornRight[i]);

		}

	}


}

void SamplePlayer::Update(){
	model_->SetColor(color_);
	model_->SetScale(scale_);
	model_->SetTranslate(position_);
	model_->SetRotate(rotate_);

	Attack();

	Move();

	for (Popcorn* popcorn : popcornRight_) {
		popcorn->Update();
	}
	//デスフラグの立った玉を削除
	popcornRight_.remove_if([](Popcorn* popcorn) {
		if (popcorn->IsDead()) {
			delete popcorn;
			return true;
		}
		return false;
	});

	DisplayText();
}

void SamplePlayer::Draw(){
	model_->Draw();
	for (Popcorn* popcorn : popcornRight_) {
		popcorn->Draw();
	}
}

SamplePlayer::~SamplePlayer(){
	delete model_;
	for (Popcorn* popcorn : popcornRight_) {
		delete popcorn;
	}
}

