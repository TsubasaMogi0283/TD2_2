#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>

GameScene::GameScene(){

}

void GameScene::Initialize(GameManager* gamaManager){
	input_ = Input::GetInstance();


	/* ---------- プレイヤー ---------- */

	player_ = std::make_unique<Player>();
	player_->Initialize();

}

void GameScene::ShowImGui(){
	ImGui::Begin("Game");
	ImGui::End();


}

void GameScene::Update(GameManager* gamaManager){
	ShowImGui();


	if (input_->IsTriggerKey(DIK_1) == true) {
		gamaManager->ChangeScene(new ResultScene());
	}


	/* ---------- プレイヤー ---------- */

	player_->Update();


}

void GameScene::Draw(GameManager* gamaManager){

	/* ---------- プレイヤー ---------- */

	player_->Draw();

}

GameScene::~GameScene(){

}


