#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include <memory>

#include "Polygon/Sprite/Sprite.h"
#include "Polygon/Model/Model.h"

#include "Object/Oven/Oven.h"
#include <Object/Corn/Corn.h>
#include <Object/Lamp/Lamp.h>
#include <Object/SamplePlayer/SamplePlayer.h>

//StatePatternを使う時は必ず前方宣言をするように
class Gamemanager;

class SampleScene : public IGameScene {
public:

	//コンストラクタ
	SampleScene();

	/// デストラクタ
	~SampleScene();

	/// 初期化
	void Initialize(GameManager* gameManager)override;

	/// 更新
	void Update(GameManager* gameManager)override;

	/// 描画
	void Draw(GameManager* gameManager)override;
private:
	void CountDown();



private:

	//とうもろこし
	std::unique_ptr<Corn> corn_ = nullptr;
	
	//オーブン
	std::unique_ptr<Oven> oven_ = nullptr;
	
	//電熱線
	std::unique_ptr<Lamp> lamp_ = nullptr;
	

	//サンプルプレイヤー
	std::unique_ptr<SamplePlayer> player_ = nullptr;


	//カメラ
	Vector3 cameraPosition_ = {};
	Vector3 cameraRotate_ = {};

	static const int NUMBER_AMOUNT_ = 10;
	std::unique_ptr<Sprite> timeTensPlane_[NUMBER_AMOUNT_] = {nullptr};
	std::unique_ptr<Sprite> timeOnesPlane_[NUMBER_AMOUNT_] = { nullptr };


	//ゲームの時間
	const int timer_ = 20;
	int gameTime_ = 60 * timer_;

	//表示されている時間
	int displayTime_ = gameTime_/60;
	//1の位
	int onesPlace_ = 0;
	//10の位
	int tensPlace_ = 0;
	
	uint32_t numberTextureHandle[10] = {};
};

