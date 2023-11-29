#pragma once
#include "Polygon/Sprite/Sprite.h"

#include <memory>

class CollisionManager;
class PlayerHitBox;

class Score {
public:
	//コンストラクタ
	Score();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~Score();


	void SetScore(int score) {
		this->score_ = score;
	}

	int GetScore() {
		return score_;
	}


	void SetCollisionManager(CollisionManager* player) { collisionManager_ = player; }

	void SetPlayerHitBox(PlayerHitBox* hitBox) {
		playerHitBox_ = hitBox;
	}

	Vector2 GetScoreBackSizeScale() const {
		return scoreBackSize_;
	}

	void SetScoreBackSize(Vector2 size) {
		scoreBackSize_ = size;
	}

	Vector2 GetScoreScale() const {
		return setScale_;
	}

	void SetScoreScale(Vector2 scale) {
		setScale_ = scale;

	}

	void SetPosition(const Vector2& position) {
		scoreBackPosition_ = position;
	}

private:


	std::unique_ptr<Sprite> scoreBack_ = nullptr;
	Vector2 scoreBackPosition_ = {};
	Vector2 scoreBackSize_ = {};

	int32_t score_ = 0;

	int32_t scoreTenThousandsPlace_ = 0;
	int32_t scoreThousandsPlace_ = 0;
	int32_t scoreHundredsPlace_ = 0;
	int32_t scoreTensPlace_ = 0;
	int32_t scoreOnesPlace_ = 0;

	static const int NUMBER_AMOUNT_ = 10;
	std::unique_ptr<Sprite> scoreTenThousandsPlane_[NUMBER_AMOUNT_] = { nullptr };
	std::unique_ptr<Sprite> scoreThousandsPlane_[NUMBER_AMOUNT_] = { nullptr };
	std::unique_ptr<Sprite> scoreHundredsPlane_[NUMBER_AMOUNT_] = { nullptr };
	std::unique_ptr<Sprite> scoreTensPlane_[NUMBER_AMOUNT_] = { nullptr };
	std::unique_ptr<Sprite> scoreOnesPlane_[NUMBER_AMOUNT_] = { nullptr };

	uint32_t numberTextureHandle[NUMBER_AMOUNT_] = {};

	PlayerHitBox* playerHitBox_ = nullptr;

	CollisionManager* collisionManager_ = nullptr;
	int getScore = 0;
	bool isUpScore_ = false;
	bool isKillEnemy_;
	int killCount_ = 0;
	Vector2 setScale_ = { 1.0f,1.0f };

};