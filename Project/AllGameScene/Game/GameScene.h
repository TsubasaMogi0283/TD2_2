#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"
#include "Camera/Camera.h"

#include "GameObject/Player/Player.h"
#include "GameObject/DemoGround/DemoGround.h"
#include "Collider/CollisionManager/CollisionManager.h"


class GameScene : public IGameScene{
public:

	GameScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~GameScene();

private:
	void ShowImGui();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();


private:
	Input* input_ = nullptr;

	Vector3 cameraPos_{};
	Vector3 cameraRotate_{};


	// Player
	std::unique_ptr<Player> player_ = nullptr;

	// DemoGround
	std::unique_ptr<DemoGround> demoGround_ = nullptr;


	// CollisionManager
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;

};

