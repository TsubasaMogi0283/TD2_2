#include "ResultScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Title/TitleScene.h>

ResultScene::ResultScene() {

}

void ResultScene::Initialize(GameManager* gamaManager) {
}

void ResultScene::ShowImGui() {
	ImGui::Begin("Result");
	ImGui::End();


}

void ResultScene::Update(GameManager* gamaManager) {
	ShowImGui();

	if (Input::GetInstance()->IsTriggerKey(DIK_1) == true) {
		gamaManager->ChangeScene(new TitleScene());
	}



}

void ResultScene::Draw(GameManager* gamaManager) {

}

ResultScene::~ResultScene() {

}