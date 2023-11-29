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

	//選択Text
	selectText_ = std::make_unique<Sprite>();
	uint32_t selectTextTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Select/SelectText.png");
	selectText_.reset(Sprite::Create(selectTextTextureHandle, { 0.0f,0.0f }));

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

	//BGM
	bgm_ = Audio::GetInstance();
	selectBGMHandle_ = bgm_->LoadWave("Resources/Audio/BGM/TitleSelect.wav");
	
	bgm_->PlayWave(selectBGMHandle_, true);

	//DecideSE
	decideSE_ = Audio::GetInstance();
	decideSEHandle_ = decideSE_->LoadWave("Resources/Audio/Deside/Decide.wav");
	
	//MoveSE
	moveSE_ = Audio::GetInstance();
	moveSEHandle_ = moveSE_->LoadWave("Resources/Audio/Select/Select.wav");

}

void SelectScene::ShowImGui(){
	ImGui::Begin("Select");
	ImGui::InputFloat3("CursorPosition", &cursorPosition_.x);
	

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

			//セレクトのSE
			moveSE_->PlayWave(moveSEHandle_,false);

			if (cursorPosition_.x <= INITIALE_POSITION.x) {
			}
			else {
				cursorPosition_.x -= ICON_INTERVAL_.x;
			}
		}

		//右
		if (Input::GetInstance()->IsTriggerKey(DIK_RIGHT) == true || triggerButtonRightTime == 1) {
			
			//セレクトのSE
			moveSE_->PlayWave(moveSEHandle_,false);
			
			if (cursorPosition_.x > INITIALE_POSITION.x * 2) {
			}
			else {
				cursorPosition_.x += ICON_INTERVAL_.x;
			}
		}


		
	
		if (cursorPosition_.x == ICON_INTERVAL_.x && isFadeOut_ == false) {
			if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
				//決定SE
				decideSE_->PlayWave(decideSEHandle_, false);
				
				//BGM止める
				bgm_->StopWave(selectBGMHandle_);

				isToTitle_ = true;
				isFadeOut_ = true;

			}
		}
		if (cursorPosition_.x == INITIALE_POSITION.x + ICON_INTERVAL_.x&&  isFadeOut_ == false) {
			if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
				
				//決定SE
				decideSE_->PlayWave(decideSEHandle_, false);
				
				//BGM止める
				bgm_->StopWave(selectBGMHandle_);

				isToGame_ = true;
				isFadeOut_ = true;

			}
			
		}
		if (cursorPosition_.x == INITIALE_POSITION.x + ICON_INTERVAL_.x*2&& isFadeOut_ == false) {
			if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
				
				//決定SE
				decideSE_->PlayWave(decideSEHandle_, false);

				//BGM止める
				bgm_->StopWave(selectBGMHandle_);

				isToScoreAttack_ = true;
				isFadeOut_ = true;
				

			}
			
		}

	}
	
	//INITIALE_POSITION = {300.0f,500.0f};
	//const Vector2 ICON_INTERVAL_ = {300.0f};

	//フェードアウト
	if (isFadeOut_ == true) {
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

	//選択Text
	selectText_->Draw();

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


