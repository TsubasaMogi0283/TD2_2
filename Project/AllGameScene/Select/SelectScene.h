#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include "Polygon/Sprite/Sprite.h"
#include "Polygon/Model/Model.h"

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

	const Vector2 ICON_INTERVAL_ = {300.0f};
	Vector2 cursorPosition_ = {};
	Vector2 move_ = {};


};

