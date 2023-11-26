#pragma once
#include "Input/Input.h"
#include "Math/Vector/Transform.h"

#include <Math/Matrix/Calculation/Matrix4x4Calculation.h>
#include "Camera/Camera.h"
#include "Polygon/Model/Model.h"
#include <list>
class Map {
public:
    Map();
    ~Map();

    void Initialize(const Vector3& initialPosition, float radius, float rotationSpeed);
    void Update();
    void Draw();

private:
    Vector3 initialPosition_;
    float radius_;
    float rotationSpeed_;
    Model* mapModel_;
    Vector3 mapModelPosition_;
    Vector3 mapModelRotate_;
    Vector3 mapDirection_;
    float deltaTime_;


    std::unique_ptr<Model> sample_ = nullptr;
    Vector3 samplePosition_ = {};
    Vector3 sampleRotate_ = {};
    float sampleRadius_ = 1.0f;
    float rotateMove_ = 0.0f;

    std::unique_ptr<Model> sampleBase_ = nullptr;
    Vector3 sampleBasePosition_ = {};
    Vector3 sampleBaseRotate_ = {};
    float sampleBaseRadius_ = 0.5f;

    void UpdateModel();
};