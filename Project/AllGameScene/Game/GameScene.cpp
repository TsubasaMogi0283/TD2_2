#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>

GameScene::GameScene() {
}

void GameScene::Initialize(GameManager* gamaManager) {
    input_ = Input::GetInstance();

    Vector3 initialPosition = { 0.0f, 0.0f, 0.0f };
    CreateModels(10, 5.0f, initialPosition);

    model_ = new Model();
    model_->CreateObject("Resources/TD_obj", "groundCube.obj");
    mapTransforms_.scale = { 1.0f, 1.0f, 1.0f };

    mainCamera_ = Camera::GetInstance();
    cameraPosition_ = { 0.0f,0.0f,-100.0f };
    mapTransforms_.translate = { 0.0f, 0.0f, 50.0f };
}

void GameScene::ShowImGui() {
    ImGui::Begin("Game");
    ImGui::SliderFloat3("MainCameraTranslate", &cameraPosition_.x, 0.0f, 10.0f);
    ImGui::SliderFloat3("MainCameraRotate", &cameraRotate_.x, 0.0f, 1.0f);
    ImGui::End();
}


void GameScene::Update(GameManager* gamaManager) {
    ShowImGui();

    mainCamera_->SetTranslate(cameraPosition_);
    mainCamera_->SetRotate(cameraRotate_);

    if (input_->IsTriggerKey(DIK_1) == true) {
        gamaManager->ChangeScene(new ResultScene());
    }

    float radius = 10.0f;
    float angle = mapTransforms_.rotate.x + 0.01f;
    mapTransforms_.translate.y = radius * cos(angle);
    mapTransforms_.translate.z = radius * sin(angle);
    mapTransforms_.rotate.x -= 0.01f;
}

void GameScene::Draw(GameManager* gamaManager) {
    for (auto model : models_) {
        model->Draw(mapTransforms_);
    }
}

GameScene::~GameScene() {
    for (auto model : models_) {
        delete model;
    }
}

void GameScene::CreateModels(int count, float spacing, const Vector3& initialPosition)
{
    for (int i = 0; i < count; ++i) {
        Model* newModel = new Model();
        newModel->CreateObject("Resources/TD_obj", "groundCube.obj");

        // モデルの初期位置を設定
        Vector3 modelPosition = { initialPosition.x + i * spacing, initialPosition.y, initialPosition.z };
        newModel->SetPosition(modelPosition);

        models_.push_back(newModel);
    }
}