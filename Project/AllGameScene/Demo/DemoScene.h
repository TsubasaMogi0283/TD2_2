#pragma once

#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"


class DemoScene : public IGameScene {

public:

	DemoScene() {};
	~DemoScene() {};

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

private:



};