#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>

GameScene::GameScene() {
}

void GameScene::Initialize(GameManager* gamaManager) {
    input_ = Input::GetInstance();

    mainCamera_ = Camera::GetInstance();
    cameraPosition_ = { 0.0f,0.0f,-100.0f };

    //Map用初期化
    mapRadius_ = 10.0f;
    mapInitialPosition_ = { -20.0f, 0.0f, 0.0f };

    mapManager_.Initialize(30, mapRadius_, 20.0f, mapInitialPosition_);
}

void GameScene::ShowImGui() {
    ImGui::Begin("Game");
    ImGui::SliderFloat3("MainCameraTranslate", &cameraPosition_.x, -30.0f, 30.0f);
    ImGui::SliderFloat3("MainCameraRotate", &cameraRotate_.x, -3.0f, 3.0f);

    ImGui::End();
}


void GameScene::Update(GameManager* gamaManager) {
    ShowImGui();
    cameraPosition_.x = 30.0f;
    cameraPosition_.z = 1.0f;
    cameraRotate_.y = -float(M_PI) / 2.0f;
    mainCamera_->SetTranslate(cameraPosition_);
    mainCamera_->SetRotate(cameraRotate_);

    if (input_->IsTriggerKey(DIK_1) == true) {
        gamaManager->ChangeScene(new ResultScene());
    }

    mapManager_.Update();
}

void GameScene::Draw(GameManager* gamaManager) {
    mapManager_.Draw();
}

GameScene::~GameScene() {
    
}

