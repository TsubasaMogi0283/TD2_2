#include "Score.h"
#include "TextureManager/TextureManager.h"
#include "CollisionManager/CollisionManager.h"

Score::Score(){

}

void Score::Initialize(){

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
	const float initialPositionX = 30.0f;


	uint32_t frameTextureHandle = TextureManager::LoadTexture("Resources/Frame/Frame.png");
	scoreBackPosition_ =  { 6.0f,488.0f};
	scoreBackSize_ = {0.25f,0.13f};
	scoreBack_.reset(Sprite::Create(frameTextureHandle,scoreBackPosition_));

	for (int i = 0; i < NUMBER_AMOUNT_; i++) {
		
		scoreTenThousandsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*0.0f,500.0f}));	
		scoreThousandsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*1.0f,500.0f}));;
		scoreHundredsPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*2.0f,500.0f}));;	
		scoreTensPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*3.0f,500.0f}));;
		scoreOnesPlane_[i].reset(Sprite::Create(numberTextureHandle[i], {initialPositionX+SPACE_INTERVAL*4.0f,500.0f}));;


	}

	scoreBack_->SetScale(scoreBackSize_);
	scoreBack_->SetPosition(scoreBackPosition_);
}

void Score::Update(){

	//ImGui::Begin("Score");
	//ImGui::InputInt("killCount", &killCount_);
	//ImGui::InputInt("score", &score_);
	//
	//ImGui::InputInt("getScore", &getScore);
	//ImGui::End();

	
	if (collisionManager_->GetIsKillEnemy() == true) {
		killCount_++;
		isUpScore_ = true;
	}
	if (isUpScore_ == true) {
		

		getScore = killCount_*100;
		if (score_ < getScore) {
			score_++;
		}
		else {
			isUpScore_ = false;
		}
	}
	


	scoreTenThousandsPlace_ = score_/10000;
	scoreThousandsPlace_ = (score_%10000)/1000;
	scoreHundredsPlace_ = (score_%1000)/100;
	scoreTensPlace_ = (score_%100)/10;
	scoreOnesPlace_ = score_ % 10;

	

}

void Score::Draw(){

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

Score::~Score(){

}
