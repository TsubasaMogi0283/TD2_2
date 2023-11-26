#include "MapManager.h"
#include <cmath>

MapManager::MapManager() {}

MapManager::~MapManager() {
    for (auto map : maps_) {
        delete map;
    }
    maps_.clear();
}

void MapManager::Initialize(int count, float radius, float height, const Vector3& initialPosition) {
    for (int i = 0; i < count; ++i) {
        Map* newMap = new Map();

        float angle = static_cast<float>(i) * (2.0f * 3.1416f) / static_cast<float>(count);

        // マップの位置を円周上に配置するための座標を計算
        float x = initialPosition.x;
        float y = initialPosition.y + radius * std::sin(angle);
        float z = initialPosition.z + radius * std::cos(angle);

        // 新しく作成したMapに新しいModelを生成して渡す
        newMap->Initialize(Vector3(x, y, z), radius, 1.0f);

        // Mapを追加
        maps_.push_back(newMap);
    }
}

void MapManager::Update() {
    for (auto map : maps_) {
        map->Update();
    }
}

void MapManager::Draw() {
    for (auto map : maps_) {
        map->Draw();
    }
}