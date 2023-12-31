#pragma once

#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"
#include "Camera/Camera.h"

#include "Object/DemoPlayer/DemoPlayer.h"
#include "Object/DemoGround/DemoGround.h"
#include "CollisionManager/CollisionManager.h"


class DemoScene : public IGameScene {

public:

	DemoScene() {};
	~DemoScene() {};

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

private:

	void CheckAllCollision();

private:

	std::unique_ptr<DemoPlayer> dPlayer_ = nullptr;
	std::unique_ptr<DemoGround> dGround_ = nullptr;
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;


	Vector3 cameraPosition_ = {};
	Vector3 cameraRotate_ = {};
};