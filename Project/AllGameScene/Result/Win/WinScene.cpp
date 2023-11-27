#include "WinScene.h"
#include "Input/Input.h"
#include "AllGameScene/Title/TitleScene.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "TextureManager/TextureManager.h"

WinScene::WinScene(){

}

void WinScene::Initialize(GameManager* gamaManager){
	//テキスト
	text_ = std::make_unique<Sprite>();
	uint32_t textTexturehandle = TextureManager::GetInstance()->LoadTexture("Resources/Result/ReturnToTitle.png");
	text_->Create(textTexturehandle, { 0.0f,0.0f });
}

void WinScene::ShowImGui(){
	ImGui::Begin("Win");
	ImGui::End();
}

void WinScene::Update(GameManager* gamaManager){
	ShowImGui();

	if (isFadeOut_ == false) {
		//点滅
		flashTime_ += 1;
		if (flashTime_ > 0) {
			if (flashTime_ > 0 && flashTime_ <= 30) {
				text_->SetInvisible(false);
			}
			if (flashTime_ > 30 && flashTime_ <= 60) {
				text_->SetInvisible(true);
			}
			if (flashTime_ > 60) {
				flashTime_ = 0;
			}
		}

		if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
			isFadeOut_ = true;
			
		}

	}
	if (isFadeOut_ == true) {

		fastFlashTime_ += 1;
		//高速点滅処理
		const int FLASH_INTERVAL = 2;
		if (fastFlashTime_ > FLASH_INTERVAL * 0) {
			if (fastFlashTime_ > FLASH_INTERVAL * 0 && fastFlashTime_ <= FLASH_INTERVAL * 1) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 1 && fastFlashTime_ <= FLASH_INTERVAL * 2) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 2 && fastFlashTime_ <= FLASH_INTERVAL * 3) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 3 && fastFlashTime_ <= FLASH_INTERVAL * 4) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 4 && fastFlashTime_ <= FLASH_INTERVAL * 5) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 5 && fastFlashTime_ <= FLASH_INTERVAL * 6) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 6 && fastFlashTime_ <= FLASH_INTERVAL * 7) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 7 && fastFlashTime_ <= FLASH_INTERVAL * 8) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 8) {
				spriteTransparency_ -= 0.05f;
				if (spriteTransparency_ < 0.0f) {
					spriteTransparency_ = 0.0f;
					
					loadingTime_ += 1;


					if (loadingTime_ > 60 * 2) {
						gamaManager->ChangeScene(new TitleScene());
					}
				}
			}
			
		}
		
	}
}

void WinScene::Draw(GameManager* gamaManager){
	text_->Draw();
}

WinScene::~WinScene(){

}


