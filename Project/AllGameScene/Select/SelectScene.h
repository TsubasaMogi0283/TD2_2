#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"


class SelectScene : public IGameScene{
public:

	SelectScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~SelectScene();

private:
	void ShowImGui();


private:
	Input* input_ = nullptr;



};

