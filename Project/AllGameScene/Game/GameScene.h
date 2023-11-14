#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"

#include "GameObject/Player/Player.h"


class GameScene : public IGameScene{
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


	// Player
	std::unique_ptr<Player> player_ = nullptr;


};

