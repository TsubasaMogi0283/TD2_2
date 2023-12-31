#include "ResultScore.h"
#include "TextureManager/TextureManager.h"
#include "CollisionManager/CollisionManager.h"
#include "Object/Player/HitBox/PlayerHitBox.h"

ResultScore::ResultScore() {

}

void ResultScore::Initialize() {

	numberTextureHandle[0] = TextureManager::LoadTexture("Resources/Number/0.png");
	numberTextureHandle[1] = TextureManager::LoadTexture("Resources/Number/1.png");
	numberTextureHandle[2] = TextureManager::LoadTexture("Resources/Number/2.png");
	numberTextureHandle[3] = TextureManager::LoadTexture("Resources/Number/3.png");
	numberTextureHandle[4] = TextureManager::LoadTexture("Resources/Number/4.png");
	numberTextureHandle[5] = TextureManager::LoadTexture("Resources/Number/5.png");
	numberTextureHandle[6] = TextureManager::LoadTexture("Resources/Number/6.png");
	numberTextureHandle[7] = TextureManager::LoadTexture("Resources/Number/7.png");
	numberTextureHandle[8] = TextureManager::LoadTexture("Resources/Number/8.png");
	numberTextureHandle[9] = TextureManager::LoadTexture("Resources/Number/9.png");





	//スコア
	const float SPACE_INTERVAL = 60.0f;
	const float initialPositionX = 500.0f;

	uint32_t frameTextureHandle = TextureManager::LoadTexture("Resources/Frame/Frame.png");
	scoreBackPosition_ = { 320.0f,340.0f };
	scoreBackSize_ = { 0.5f,0.26f };
	scoreBack_.reset(Sprite::Create(frameTextureHandle, scoreBackPosition_));

	for (int i = 0; i < NUMBER_AMOUNT_; i++) {

		scoreTenThousandsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { initialPositionX + SPACE_INTERVAL * 0.0f,360.0f }));
		scoreThousandsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { initialPositionX + SPACE_INTERVAL * 1.0f,360.0f }));;
		scoreHundredsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { initialPositionX + SPACE_INTERVAL * 2.0f,360.0f }));;
		scoreTensPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { initialPositionX + SPACE_INTERVAL * 3.0f,360.0f }));;
		scoreOnesPlane_[i].reset(Sprite::Create(numberTextureHandle[i], { initialPositionX + SPACE_INTERVAL * 4.0f,360.0f }));;

		scoreTenThousandsPlane_[i]->SetScale(setScale_);
		scoreThousandsPlane_[i]->SetScale(setScale_);
		scoreHundredsPlane_[i]->SetScale(setScale_);
		scoreTensPlane_[i]->SetScale(setScale_);
		scoreOnesPlane_[i]->SetScale(setScale_);
	}

	scoreBack_->SetScale(scoreBackSize_);
	scoreBack_->SetPosition(scoreBackPosition_);
}

void ResultScore::Update() {

	//ImGui::Begin("Score");
	//ImGui::InputInt("killCount", &killCount_);
	//ImGui::InputInt("score", &score_);
	//
	//ImGui::InputInt("getScore", &getScore);
	//ImGui::End();


	if (playerHitBox_->GetIsKillEnemy() == true) {
		killCount_++;
		isUpScore_ = true;
	}
	if (isUpScore_ == true) {


		getScore = killCount_ * 100;
		if (score_ < getScore) {
			score_++;
		}
		else {
			isUpScore_ = false;
		}
	}



	scoreTenThousandsPlace_ = score_ / 10000;
	scoreThousandsPlace_ = (score_ % 10000) / 1000;
	scoreHundredsPlace_ = (score_ % 1000) / 100;
	scoreTensPlace_ = (score_ % 100) / 10;
	scoreOnesPlace_ = score_ % 10;



}

void ResultScore::Draw() {

	scoreBack_->Draw();
	//スコア
	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		if (scoreTenThousandsPlace_ == i) {
			scoreTenThousandsPlane_[i]->Draw();
		}
		if (scoreThousandsPlace_ == i) {
			scoreThousandsPlane_[i]->Draw();
		}
		if (scoreHundredsPlace_ == i) {
			scoreHundredsPlane_[i]->Draw();
		}
		if (scoreTensPlace_ == i) {
			scoreTensPlane_[i]->Draw();
		}
		if (scoreOnesPlace_ == i) {
			scoreOnesPlane_[i]->Draw();
		}
	}
}

ResultScore::~ResultScore() {

}
