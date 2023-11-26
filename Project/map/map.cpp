#include "Map.h"

#include "Map.h"

Map::Map() : deltaTime_(0.016f) {
    // コンストラクタでの初期化
}

Map::~Map() {
    delete mapModel_;
}

void Map::Initialize(const Vector3& initialPosition, float radius, float rotationSpeed) {
    // 初期の位置や回転などを初期化する
    initialPosition_ = initialPosition;
    radius_ = radius;
    rotationSpeed_ = rotationSpeed;

    // 新しいModelを生成
    mapModel_ = Model::Create("Resources/Sample/Corn", "Corn.obj");
    mapModelPosition_ = initialPosition;
    mapModelRotate_ = Vector3(0.0f, 0.0f, 0.0f);

    mapModel_->SetTranslate(mapModelPosition_);
    mapModel_->SetRotate(mapModelRotate_);
    
    sample_ = std::make_unique<Model>();
    sample_.reset(Model::Create("Resources/Sample/Corn", "Corn.obj"));
    samplePosition_ = { 0.0f,sampleRadius_,0.0f };
    sample_->SetTranslate(samplePosition_);
    

    sampleBase_ = std::make_unique<Model>();
    sampleBase_.reset(Model::Create("Resources/Sample/Corn", "Corn.obj"));
    sampleBase_->SetTranslate({ 0.0f,0.0f,0.0f });

}

void Map::Update() {
    UpdateModel();
}

void Map::Draw() {
    mapModel_->Draw();
    sample_->Draw();
    sampleBase_->Draw();
}

void Map::UpdateModel() {
    // 回転の更新
    float angle = rotationSpeed_ * deltaTime_;

    // 新しい回転を適用（縦方向に回転）
    mapModelPosition_ = { mapModelPosition_.x + angle, mapModelPosition_.y, mapModelPosition_.z };

    // 新しい位置の計算
    float x = initialPosition_.x;
    float y = initialPosition_.y + radius_ * sin(mapModelPosition_.x);
    float z = initialPosition_.z + radius_ * cos(mapModelPosition_.x);

    mapModelPosition_ = { x, y, z };

    // モデルのプロパティを更新
    mapModel_->SetTranslate(mapModelPosition_);
    mapModel_->SetRotate(mapModelRotate_);




#pragma region サンプルっすよ
    



    //角度とかの動きは大体こんな感じっす
    float rotateInterval = float(M_PI / 64.0f);
    rotateMove_ += rotateInterval;
    sampleRotate_.x = -(rotateMove_);
    const float MOVE_INTERVAL = 0.5f;
    samplePosition_.y = 2.0f * sinf(rotateMove_);
    samplePosition_.z = 2.0f * cosf(rotateMove_);






    sample_->SetRotate(sampleRotate_);
    sample_->SetTranslate(samplePosition_);

    sampleBase_->SetTranslate({ 0.0f,0.0f,0.0f });


    ImGui::Begin("SampleCorn");
    ImGui::SliderFloat3("Translate", &samplePosition_.x, -3.0f, 3.0f);
    ImGui::SliderFloat3("Rotate", &sampleRotate_.x, -3.0f, 3.0f);
    ImGui::End();
#pragma endregion

}