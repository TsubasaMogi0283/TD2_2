#include "Map.h"

Map::Map() : deltaTime_(0.016f) {
    // コンストラクタでの初期化
}

Map::~Map() {
    delete mapModel_;
}

void Map::Initialize(const Vector3& initialPosition, float radius, float rotationSpeed) {
    mapModel_ = Model::Create("Resources/TD_obj", "groundCube.obj");

    // 初期の位置や回転などを初期化する
    mapModelPosition_ = initialPosition;
    mapModelRotate_ = Vector3(0.0f, 0.0f, 0.0f);

    mapModel_->SetTranslate(mapModelPosition_);
    mapModel_->SetRotate(mapModelRotate_);
}

void Map::Update() {
    UpdateModel();
}

void Map::Draw() {
    mapModel_->Draw();
}

void Map::UpdateModel() {
    // 回転の更新
    float angle = rotationSpeed_ * deltaTime_;

    // 新しい回転を適用
    mapModelRotate_ = { 0.0f, mapModelRotate_.y + angle, 0.0f };

    // 新しい位置の計算
    float x = initialPosition_.x;
    float y = initialPosition_.y + radius_ * sin(mapModelRotate_.y);
    float z = initialPosition_.z + radius_ * cos(mapModelRotate_.y);

    mapModelPosition_ = { x, y, z };

    // モデルのプロパティを更新
    mapModel_->SetTranslate(mapModelPosition_);
    mapModel_->SetRotate(mapModelRotate_);
}