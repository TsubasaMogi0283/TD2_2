#pragma once
#include <vector>
#include "Map.h"

class MapManager {
public:
    MapManager();
    ~MapManager();

    void Initialize(int count, float radius, float height, const Vector3& initialPosition);
    void Update();
    void Draw();

private:
    std::vector<Map*> maps_;
};