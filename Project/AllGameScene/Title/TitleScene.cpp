#include "TitleScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Select/SelectScene.h>

TitleScene::TitleScene() {

}

void TitleScene::Initialize(GameManager* gamaManager) {
	input_=Input::GetInstance();
}

void TitleScene::ShowImGui() {
	ImGui::Begin("Title");
	ImGui::End();


}

void TitleScene::Update(GameManager* gamaManager) {
	ShowImGui();

	if (input_->IsTriggerKey(DIK_1) == true) {
		gamaManager->ChangeScene(new SelectScene());
	}



}

void TitleScene::Draw(GameManager* gamaManager) {

}

TitleScene::~TitleScene() {

}