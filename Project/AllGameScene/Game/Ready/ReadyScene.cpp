#include "ReadyScene.h"
#include "AllGameScene/Game/GameScene.h"
#include "Camera/Camera.h"

#include "AllGameScene/Game/Play/PlayScene.h"

ReadyScene::ReadyScene() {
}

void ReadyScene::Initialize(GameScene* gamaManager){
	//Ready
	ready_ = std::make_unique<Sprite>();
	uint32_t reeadyTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Start/Ready.png");
	ready_.reset(Sprite::Create(reeadyTextureHandle_, { 0.0f,0.0f }));

	//Go
	go_ = std::make_unique<Sprite>();
	uint32_t goTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Start/Go.png");
	go_.reset(Sprite::Create(goTextureHandle_, { 0.0f,0.0f }));

	cameraPosition_ = { 0.0f,2.2f,0.0f };
	cameraRotate_ = { 0.015f,0.0f,0.0f };

}

void ReadyScene::Update(GameScene* gamaManager){
	//カメラ
	Camera::GetInstance()->SetRotate(cameraRotate_);
	Camera::GetInstance()->SetTranslate(cameraPosition_);

	cameraPosition_.z -= 0.05f;
	if (cameraPosition_.z < -8.0f) {
		cameraPosition_.z = -8.0f;
		readyTime_ += 1;
		

	}
	
	//GamePlayへ
	if (readyTime_ > 60 * 4) {
		gamaManager->ChangeScene(new PlayScene());
	}

	

	
}

void ReadyScene::Draw(GameScene* gamaManager){
	if (readyTime_ > 0 && readyTime_ <= 60 * 2) {
		ready_->Draw();

	}

	if (readyTime_ > 60*2 && readyTime_ <= 60 * 4) {
		go_->Draw();
		
	}
}


ReadyScene::~ReadyScene() {

}
