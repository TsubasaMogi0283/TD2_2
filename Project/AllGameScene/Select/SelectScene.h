#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include "Polygon/Sprite/Sprite.h"
#include "Polygon/Model/Model.h"
#include "Audio/Audio.h"

#include <Xinput.h>

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
	//WhiteOut
	std::unique_ptr<Sprite> whiteBack_ = nullptr;
	float transparency_ = 0.0f;

	//タイトルに戻る
	std::unique_ptr<Sprite> returnToTile_ = nullptr;

	//ゲームへ
	std::unique_ptr<Sprite> gameMode_ = nullptr;

	//スコアアタック
	std::unique_ptr<Sprite> scoreAttackMode_ = nullptr;

	//カーソル
	std::unique_ptr<Sprite> cursor_ = nullptr;
	
	//とうもろこし
	std::unique_ptr<Model> corn_ = nullptr;
	Vector3 cornPosition_ = { 0.0f,0.0f,0.0f };
	Vector3 scale_ = { 1.0f,1.0f,1.0f };
	Vector3 rotate_ = { 0.0f,0.0f,0.0f };


	const Vector2 INITIALE_POSITION = {300.0f,500.0f};
	const Vector2 ICON_INTERVAL_ = {300.0f,0.0f};
	Vector2 cursorPosition_ = {};
	Vector2 move_ = {};


	int waitingTimeToTitle_ = 0;
	bool isToTitle_ = false;

	int waitingTimeToGame_ = 0;
	bool isToGame_ = false;

	int waitingTimeToScoreAttack_ = 0;
	bool isToScoreAttack_ = false;


	bool isFadeIn_ = true;
	bool isFadeOut_ = false;

	//コントローラー
	XINPUT_STATE joyState{};

	int triggerButtonLeftTime;

	int triggerButtonRightTime;

	int triggerButtonBTime;


	//BGM
	Audio* bgm_ = nullptr;
	uint32_t selectBGMHandle_ = 0u;
	//DecideSE
	Audio* decideSE_ = nullptr;
	uint32_t decideSEHandle_ = 0u;
	//MoveSE
	Audio* moveSE_ = nullptr;
	uint32_t moveSEHandle_ = 0u;


};

