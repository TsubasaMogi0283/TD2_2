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
    mapModel_ = Model::Create("Resources/TD_obj", "groundCube.obj");
    mapModelPosition_ = initialPosition;
    mapModelRotate_ = Vector3(0.0f, 0.0f, 0.0f);

    mapModel_->SetTranslate(mapModelPosition_);
    mapModel_->SetRotate(mapModelRotate_);
    
    sample_ = std::make_unique<Model>();
    sample_.reset(Model::Create("Resources/TD_obj", "groundCube.obj"));



}

void Map::Update() {
    UpdateModel();
}

void Map::Draw() {
    mapModel_->Draw();
    sample_->Draw();
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
   // mapModelRotate_.x = sin(angle);

    // モデルのプロパティを更新
    mapModel_->SetTranslate(mapModelPosition_);
    mapModel_->SetRotate(mapModelRotate_);




#pragma region サンプルっすよ
    
    sampleRotate_.x += 0.1f;

    sample_->SetRotate(sampleRotate_);

    


    ImGui::Begin("SampleCorn");
    ImGui::SliderFloat3("Rotate", &sampleRotate_.x, -3.0f, 3.0f);
    ImGui::End();
#pragma endregion

}