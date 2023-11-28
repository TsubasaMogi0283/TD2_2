#pragma once
#include "AllGameScene/GameManager/IGamePlayScene.h"

class GameScene;

class PlayScene  : public IGamePlayScene{
public:
	PlayScene() {};
	~PlayScene() {};

	void Initialize(GameScene* gamaManager) override;
	void Update(GameScene* gamaManager) override;
	void Draw(GameScene* gamaManager) override;




private:




};

