#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Polygon/Sprite/Sprite.h"

#include <list>
#include <memory>

class LoseScene: public IGameScene{
	public:

	LoseScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~LoseScene();

private:
	void ShowImGui();


private:
	//背景
	std::unique_ptr<Sprite> back_ = nullptr;

	//テキスト
	std::unique_ptr<Sprite> text_ = nullptr;

	//フェード
	bool isFadeOut_ = false;
	float_t spriteTransparency_ = 1.0f;

	//点滅
	int32_t flashTime_ = 0;
	int32_t fastFlashTime_ = 0;

	//ローディング時間
	int32_t loadingTime_ = 0;


};

