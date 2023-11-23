#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>

GameScene::GameScene(){

}

void GameScene::Initialize(GameManager* gamaManager){
	input_ = Input::GetInstance();
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


}

void GameScene::Draw(GameManager* gamaManager){

}

GameScene::~GameScene(){

}


