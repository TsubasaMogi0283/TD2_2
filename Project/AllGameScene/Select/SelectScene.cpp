#include "SelectScene.h"

#include "ImGuiManager/ImGuiManager.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "AllGameScene/Game/GameScene.h"

#include "Input/Input.h"
#include "TextureManager/TextureManager.h"
SelectScene::SelectScene(){


}

void SelectScene::Initialize(GameManager* gamaManager){
	//背景
	whiteBack_ = std::make_unique<Sprite>();
	uint32_t whiteTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/White.png");
	whiteBack_.reset(Sprite::Create(whiteTextureHandle, { 0.0f,0.0f }));

	const Vector2 INITIALE_POSITION = {200.0f,500.0f};
	

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
	corn_.reset(Model::Create("Resources/Corn","Corn.obj"));


}

void SelectScene::ShowImGui(){
	ImGui::Begin("Select");
	ImGui::End();
}

void SelectScene::Update(GameManager* gamaManager){
	ShowImGui();



	//選択
	if (Input::GetInstance()->IsTriggerKey(DIK_LEFT) == true) {
		cursorPosition_.x -= ICON_INTERVAL_.x;
	}
	if (Input::GetInstance()->IsTriggerKey(DIK_RIGHT) == true) {
		cursorPosition_.x += ICON_INTERVAL_.x;
	}

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gamaManager->ChangeScene(new GameScene());
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

	corn_->Draw();
}

SelectScene::~SelectScene(){


}


