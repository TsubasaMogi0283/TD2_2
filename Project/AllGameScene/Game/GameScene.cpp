#include "GameScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Result/ResultScene.h>

GameScene::GameScene() {
}

void GameScene::Initialize(GameManager* gamaManager) {
    input_ = Input::GetInstance();

    initialPosition_ = { 0.0f, 0.0f, 0.0f };
    CreateModels(10, 1.0f, initialPosition_);

    model_ = Model::Create("Resources/TD_obj", "groundCube.obj");
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
    for (size_t i = 0; i < models_.size(); ++i) {
        float angle = modelRotate_[i].x + 0.01f;
        modelPosition_[i].y = radius * cos(angle);
        modelPosition_[i].z = radius * sin(angle);
        modelRotate_[i].x -= 0.01f;

        models_[i]->SetTranslate(modelPosition_[i]);
        models_[i]->SetRotate(modelRotate_[i]);
    }
    
}

void GameScene::Draw(GameManager* gamaManager) {
    for (auto model : models_) {
        model->Draw();
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

        Model* newModel = Model::Create("Resources/TD_obj", "groundCube.obj");

        // モデルの初期位置を設定
        Vector3 modelPosition = { initialPosition.x + i * spacing, initialPosition.y, initialPosition.z };
        Vector3 modelRotate = { 0.0f, 0.0f, 0.0f };
        newModel->SetTranslate(modelPosition);


        models_.push_back(newModel);
        modelPosition_.push_back(modelPosition);
        modelRotate_.push_back(modelRotate);
    }
}