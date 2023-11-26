#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"
#include "Math/Vector/Transform.h"

#include <Math/Matrix/Calculation/Matrix4x4Calculation.h>
#include "Camera/Camera.h"
#include "Polygon/Model/Model.h"
#include "map/mapManager.h"

class GameScene : public IGameScene {
public:

	GameScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~GameScene();


private:
	void ShowImGui();

private:
	Input* input_ = nullptr;

	Model* model_ = nullptr;

	Camera* mainCamera_;

	Vector3 cameraPosition_;
	Vector3 cameraRotate_;

	MapManager mapManager_;

	float mapRadius_;
	Vector3 mapInitialPosition_;
};

