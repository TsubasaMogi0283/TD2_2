#include "TitleScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include <AllGameScene/Select/SelectScene.h>
#include "AllGameScene/SampleScene/SampleScene.h"

TitleScene::TitleScene() {

}

void TitleScene::Initialize(GameManager* gamaManager) {
	//ロゴ
	logo_ = std::make_unique<Sprite>();
	
	//スタートのテキスト
	startText_ = std::make_unique<Sprite>();

	//背景
	backGround_ = std::make_unique<Sprite>();

	uint32_t logoTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Title/Logo/TitleLogo.png");
	uint32_t startTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Title/Start/Start.png");
	uint32_t backTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Title/Back/BackGround.png");

	logo_.reset(Sprite::Create(logoTextureHandle, { 0.0f,0.0f }));
	startText_.reset(Sprite::Create(startTextureHandle, { 0.0f,0.0f }));
	backGround_.reset(Sprite::Create(backTextureHandle, { 0.0f, 0.0f }));

}

void TitleScene::ShowImGui() {
	ImGui::Begin("Title");
	ImGui::InputInt("flashTime", &startFlashTime_);
	ImGui::End();


}

void TitleScene::Update(GameManager* gamaManager) {
	//ShowImGui();
	

	startText_->SetTransparency(spriteTransparency_);
	logo_->SetTransparency(spriteTransparency_);
	backGround_->SetTransparency(spriteTransparency_);
	//フェードイン
	if (isFadeIn_ == true) {
		spriteTransparency_ += 0.05f;

		if (spriteTransparency_ > 1.0f) {
			spriteTransparency_ = 1.0f;
			isFadeIn_ = false;
		}
			
	}


	if (isFadeIn_ == false) {
		//点滅
		flashTime_ += 1;
		if (flashTime_ > 0) {
			if (flashTime_ > 0 && flashTime_ <= 30) {
				startText_->SetInvisible(false);
			}
			if (flashTime_ > 30 && flashTime_ <= 60) {
				startText_->SetInvisible(true);
			}
			if (flashTime_ > 60) {
				flashTime_ = 0;
			}
		}


		if (Input::GetInstance()->GetJoystickState(joyState)) {

			//Bボタン
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				triggerButtonBTime += 1;

			}

		}

		if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
			isFadeOut_ = true;
			
		}

	}
	if (isFadeOut_ == true) {

		startFlashTime_ += 1;
		//高速点滅処理
		const int FLASH_INTERVAL = 2;
		if (startFlashTime_ > FLASH_INTERVAL * 0) {
			if (startFlashTime_ > FLASH_INTERVAL * 0 && startFlashTime_ <= FLASH_INTERVAL * 1) {
				startText_->SetInvisible(false);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 1 && startFlashTime_ <= FLASH_INTERVAL * 2) {
				startText_->SetInvisible(true);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 2 && startFlashTime_ <= FLASH_INTERVAL * 3) {
				startText_->SetInvisible(false);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 3 && startFlashTime_ <= FLASH_INTERVAL * 4) {
				startText_->SetInvisible(true);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 4 && startFlashTime_ <= FLASH_INTERVAL * 5) {
				startText_->SetInvisible(false);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 5 && startFlashTime_ <= FLASH_INTERVAL * 6) {
				startText_->SetInvisible(true);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 6 && startFlashTime_ <= FLASH_INTERVAL * 7) {
				startText_->SetInvisible(false);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 7 && startFlashTime_ <= FLASH_INTERVAL * 8) {
				startText_->SetInvisible(true);
			}
			if (startFlashTime_ > FLASH_INTERVAL * 8) {
				spriteTransparency_ -= 0.05f;
				if (spriteTransparency_ < 0.0f) {
					spriteTransparency_ = 0.0f;
					
					loadingTime_ += 1;


					if (loadingTime_ > 60 * 2) {
						gamaManager->ChangeScene(new SelectScene());
					}
				}
			}
			
		}
		
	}




}

void TitleScene::Draw(GameManager* gamaManager) {
	backGround_->Draw();
	logo_->Draw();
	startText_->Draw();
}

TitleScene::~TitleScene() {

}