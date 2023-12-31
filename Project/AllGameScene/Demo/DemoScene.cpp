#include "DemoScene.h"



void DemoScene::Initialize(GameManager* gamaManager) {

	dPlayer_ = std::make_unique<DemoPlayer>();
	dPlayer_->Init();
	
	dGround_ = std::make_unique<DemoGround>();
	dGround_->Init();

	collisionManager_ = std::make_unique<CollisionManager>();


	//カメラ
	cameraRotate_ = { 0.015f,0.0f,0.0f };
	cameraPosition_ = { 0.0f,4.5,-40.0f };


	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);
}


void DemoScene::Update(GameManager* gamaManager) {

	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);


	dPlayer_->Update();
	dGround_->Update();

	CheckAllCollision();

	ImGui::Begin("DemoScene");
	ImGui::End();

	ImGui::Begin("Camera");
	ImGui::DragFloat3("Rotate", &cameraRotate_.x, 0.01f);
	ImGui::DragFloat3("Translate", &cameraPosition_.x, 0.1f);
	ImGui::End();

}


void DemoScene::Draw(GameManager* gamaManager) {

	dPlayer_->Draw();
	dGround_->Draw();
}


void DemoScene::CheckAllCollision() {


	collisionManager_->SetPlayer(dPlayer_.get());
	collisionManager_->SetGround(dGround_.get());

	collisionManager_->CheckAllCollision();
}