#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>

GameScene::GameScene(){

}

void GameScene::Initialize(GameManager* gamaManager){
	input_ = Input::GetInstance();


	cameraRotate_ = { 0.13f, 0.0f, 0.0f };
	cameraPos_ = { 0.0f, 9.0f, -5.0f };


	/* ---------- プレイヤー ---------- */
	player_ = std::make_unique<Player>();
	player_->Initialize();


	/* ---------- 床---------- */
	demoGround_ = std::make_unique<DemoGround>();
	demoGround_->Initialize();

}

void GameScene::ShowImGui(){
	ImGui::Begin("Game");
	ImGui::End();


}

void GameScene::Update(GameManager* gamaManager){
	ShowImGui();

	Camera::GetInstance()->SetTranslate(cameraPos_);
	Camera::GetInstance()->SetRotate(cameraRotate_);


	if (input_->IsTriggerKey(DIK_1) == true) {
		gamaManager->ChangeScene(new ResultScene());
	}



	/* ---------- プレイヤー ---------- */
	player_->Update();


	/* ---------- 床---------- */
	demoGround_->Update();



#ifdef _DEBUG

	ImGui::Begin("Camera");
	ImGui::DragFloat3("rotate", &cameraRotate_.x, 0.01f);
	ImGui::DragFloat3("translate", &cameraPos_.x, 0.01f);
	ImGui::End();

#endif // _DEBUG

}

void GameScene::Draw(GameManager* gamaManager){


	/* ---------- プレイヤー ---------- */
	player_->Draw();


	/* ---------- 床---------- */
	demoGround_->Draw();

}

GameScene::~GameScene(){

}


