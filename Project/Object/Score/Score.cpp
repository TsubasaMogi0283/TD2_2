#include "Score.h"

Score::Score()
{
}

void Score::Initialize(){
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
}

void Score::Update(){
	
	score_ += 1;


	scoreTenThousandsPlace_ = score_/10000;
	scoreThousandsPlace_ = (score_%10000)/1000;
	scoreHundredsPlace_ = (score_%1000)/100;
	scoreTensPlace_ = (score_%100)/10;
	scoreOnesPlace_ = score_ % 10;

	scoreBack_->SetScale(scoreBackSize_);
	scoreBack_->SetPosition(scoreBackPosition_);

}

void Score::Draw(){
	//スコアの後ろのテクスチャ
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
