#include "ResultScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Title/TitleScene.h>

ResultScene::ResultScene() {

}

void ResultScene::Initialize(GameManager* gamaManager) {
	input_=Input::GetInstance();
}

void ResultScene::ShowImGui() {
	ImGui::Begin("Result");
	ImGui::End();


}

void ResultScene::Update(GameManager* gamaManager) {
	ShowImGui();

	if (input_->IsTriggerKey(DIK_1) == true) {
		gamaManager->ChangeScene(new TitleScene());
	}



}

void ResultScene::Draw(GameManager* gamaManager) {

}

ResultScene::~ResultScene() {

}