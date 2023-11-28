#pragma once
#include "Polygon/Sprite/Sprite.h"
#include <memory>

class CountDown{
public:
	//コンストラクタ
	CountDown();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~CountDown();


private:

	static const int NUMBER_AMOUNT_ = 10;
	std::unique_ptr<Sprite> timeTensPlane_[NUMBER_AMOUNT_] = { nullptr };
	std::unique_ptr<Sprite> timeOnesPlane_[NUMBER_AMOUNT_] = { nullptr };

	//背景
	std::unique_ptr<Sprite> countDownBack_ = nullptr;
	Vector2 countDownBackPosition_ = {};
	Vector2 countDownBackSize_ = {};

	//ゲームの時間
	const int timer_ = 40;
	int gameTime_ = 60 * timer_;

	//表示されている時間
	int displayTime_ = gameTime_ / 60;
	//1の位
	int onesPlace_ = 0;
	//10の位
	int tensPlace_ = 0;

	uint32_t numberTextureHandle[NUMBER_AMOUNT_] = {};



};

