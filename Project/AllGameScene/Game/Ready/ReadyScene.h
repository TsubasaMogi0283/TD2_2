#pragma once
#include "AllGameScene/GameManager/IGamePlayScene.h"
#include "Polygon/Sprite/Sprite.h"

#include <memory>
class GameScene;

class ReadyScene  : public IGamePlayScene{
public:
	ReadyScene();
	~ReadyScene();

	void Initialize(GameScene* gamaManager) override;
	void Update(GameScene* gamaManager) override;
	void Draw(GameScene* gamaManager) override;

private:

	
	//Ready
	std::unique_ptr<Sprite> ready_ = nullptr;
	//Go
	std::unique_ptr<Sprite> go_ = nullptr;
	int readyTime_ = 0;

	//カメラ
	Vector3 cameraPosition_ = {};
	Vector3 cameraRotate_ = {};
};

