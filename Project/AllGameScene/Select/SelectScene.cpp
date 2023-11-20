#include "SelectScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "AllGameScene/Game/GameScene.h"

SelectScene::SelectScene(){

}

void SelectScene::Initialize(GameManager* gamaManager){
	input_ = Input::GetInstance();
}

void SelectScene::ShowImGui(){
	ImGui::Begin("Select");
	ImGui::End();
}

void SelectScene::Update(GameManager* gamaManager){
	ShowImGui();


	if (input_->IsTriggerKey(DIK_1) == true) {
		gamaManager->ChangeScene(new GameScene());
	}

}

void SelectScene::Draw(GameManager* gamaManager){


}

SelectScene::~SelectScene(){


}


