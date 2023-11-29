#include "SelectScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "AllGameScene/Game/GameScene.h"
#include "AllGameScene/Title/TitleScene.h"
#include "AllGameScene/Game/ScoreAttack/ScoreAttackScene.h"

#include "Input/Input.h"
#include "TextureManager/TextureManager.h"

SelectScene::SelectScene(){


}

void SelectScene::Initialize(GameManager* gamaManager){
	//背景
	whiteBack_ = std::make_unique<Sprite>();
	uint32_t whiteTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/White.png");
	whiteBack_.reset(Sprite::Create(whiteTextureHandle, { 0.0f,0.0f }));

	
	

	//タイトル
	returnToTile_ = std::make_unique<Sprite>();
	uint32_t returnTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Select/Return.png");
	returnToTile_.reset(Sprite::Create(returnTextureHandle, INITIALE_POSITION));
	

	//ゲームへ
	gameMode_ = std::make_unique<Sprite>();
	uint32_t gameModeTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Select/Game.png");
	gameMode_.reset(Sprite::Create(gameModeTextureHandle, {INITIALE_POSITION.x + ICON_INTERVAL_.x, INITIALE_POSITION.y + ICON_INTERVAL_.y }));
	

	//スコアアタック
	scoreAttackMode_ = std::make_unique<Sprite>();
	uint32_t scoreAttackTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Select/ScoreAttack.png");
	scoreAttackMode_.reset(Sprite::Create(scoreAttackTextureHandle, { INITIALE_POSITION.x + ICON_INTERVAL_.x * 2, INITIALE_POSITION.y + ICON_INTERVAL_.y }));

	//カーソル
	cursor_ = std::make_unique<Sprite>();
	uint32_t cursorTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Select/cursor.png");
	cursorPosition_ = INITIALE_POSITION;
	cursor_.reset(Sprite::Create(cursorTextureHandle, cursorPosition_));


	//とうもろこし
	corn_ = std::make_unique<Model>();
	corn_.reset(Model::Create("Resources/Corn","Corn.obj"));
	cornPosition_ = { 0.0f,0.0f,0.0f };
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };

	corn_->SetScale(scale_);
	corn_->SetRotate(rotate_);
	corn_->SetTranslate(cornPosition_);


}

void SelectScene::ShowImGui(){
	ImGui::Begin("Select");
	ImGui::SliderFloat3("Scale", &scale_.x, -1.0f, 1.0f);
	ImGui::SliderFloat3("Rotate", &rotate_.x, -1.0f, 1.0f);

	
	ImGui::SliderFloat3("Position", &cornPosition_.x, -3.0f, 3.0f);

	ImGui::End();
}

void SelectScene::Update(GameManager* gamaManager){
	ShowImGui();

	rotate_.y += 0.01f;
	corn_->SetScale(scale_);
	corn_->SetRotate(rotate_);
	corn_->SetTranslate(cornPosition_);

	
	// コントローラー
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		//左ボタン
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			triggerButtonLeftTime += 1;
		}
		//右ボタン
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			triggerButtonRightTime += 1;
		}
		//Bボタン
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			triggerButtonBTime += 1;

		}

	}
	if (isFadeIn_ == true) {
		transparency_ += 0.05f;
		if (transparency_ > 1.0f) {
			transparency_ = 1.0f;
			isFadeIn_ = false;
		}

		cursor_->SetPosition(cursorPosition_);

		//背景
		whiteBack_->SetTransparency(transparency_);
		//タイトル
		returnToTile_->SetTransparency(transparency_);
		
		//ゲームへ
		gameMode_->SetTransparency(transparency_);

	}


	//押していない時
	if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0) {
		triggerButtonRightTime = 0;
	}
	if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0) {
		triggerButtonLeftTime = 0;
	}
	if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) == 0) {
		triggerButtonBTime = 0;
	}
	
	
	//選択
	if (isFadeIn_ == false) {
		cursor_->SetPosition(cursorPosition_);

		//背景
		whiteBack_->SetTransparency(transparency_);
		//タイトル
		returnToTile_->SetTransparency(transparency_);
		
		//ゲームへ
		gameMode_->SetTransparency(transparency_);
		
		//スコアアタック
		scoreAttackMode_->SetTransparency(transparency_);
		
		//カーソル
		cursor_->SetTransparency(transparency_);
		
		corn_->SetTransparency(transparency_);

		//選択
		//左
		if (Input::GetInstance()->IsTriggerKey(DIK_LEFT) == true || triggerButtonLeftTime == 1) {


			if (cursorPosition_.x <= INITIALE_POSITION.x) {
			}
			else {
				cursorPosition_.x -= ICON_INTERVAL_.x;
			}
		}

		//右
		if (Input::GetInstance()->IsTriggerKey(DIK_RIGHT) == true || triggerButtonRightTime == 1) {
			if (cursorPosition_.x > INITIALE_POSITION.x * 2) {
			}
			else {
				cursorPosition_.x += ICON_INTERVAL_.x;
			}
		}


		
	
		if (cursorPosition_.x == ICON_INTERVAL_.x) {
			if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
				isToTitle_ = true;
				isFadeOut_ = false;

			}
		}
		if (cursorPosition_.x == INITIALE_POSITION.x + ICON_INTERVAL_.x) {
			if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
				isToGame_ = true;
				isFadeOut_ = false;

			}
			
		}
		if (cursorPosition_.x == INITIALE_POSITION.x + ICON_INTERVAL_.x*2) {
			if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
				isToScoreAttack_ = true;
				isFadeOut_ = false;
				

			}
			
		}

	}
	

	//フェードアウト
	if (isFadeOut_ == false) {
		if (isToTitle_ == true) {
			transparency_ -= 0.05f;
			if (transparency_ < 0.0f) {
				transparency_ = 0.0f;
				waitingTimeToTitle_ += 1;

			}
		}

		if (isToGame_ == true) {
			transparency_ -= 0.05f;
			if (transparency_ < 0.0f) {
				transparency_ = 0.0f;
				waitingTimeToGame_ += 1;
			
			}
		}

		if (isToScoreAttack_ == true) {
			transparency_ -= 0.05f;
			if (transparency_ < 0.0f) {
				transparency_ = 0.0f;
				waitingTimeToScoreAttack_ += 1;
			
			}
		}

	}
		

	

	//シーンチェンジ
	if (waitingTimeToTitle_ > 60 * 2) {
		gamaManager->ChangeScene(new TitleScene());
	}
	if (waitingTimeToGame_ > 60 * 2) {
		gamaManager->ChangeScene(new GameScene());
	}
	if (waitingTimeToScoreAttack_ > 60 * 2) {
		gamaManager->ChangeScene(new ScoreAttackScene());
	}
}

void SelectScene::Draw(GameManager* gamaManager){
	whiteBack_->Draw();

	//タイトル
	returnToTile_->Draw();

	//ゲームへ
	gameMode_->Draw();

	//スコアアタック
	scoreAttackMode_->Draw();

	//corn_->Draw();

	cursor_->Draw();
}

SelectScene::~SelectScene(){


}


