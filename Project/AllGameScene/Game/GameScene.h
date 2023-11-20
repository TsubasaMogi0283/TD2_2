#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"
#include "Math/Vector/Transform.h"

#include <Math/Matrix/Calculation/Matrix4x4Calculation.h>
#include "Camera/Camera.h"
#include "Polygon/Model/Model.h"

class GameScene : public IGameScene{
public:

	GameScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~GameScene();


private:
	void ShowImGui();

	void MoveModel(float angleDegrees);

private:
	Input* input_ = nullptr;

	Model* model_ = nullptr;

	static const int mapSize = 10;

	Transform mapTransforms_ = {};

	Camera *mainCamera_;

	Vector3 cameraPosition_;
	Vector3 cameraRotate_;
};

