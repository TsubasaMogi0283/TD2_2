#include "PlayerHitBox.h"
#include "Object/Player/Player.h"



// 初期化処理
void PlayerHitBox::Initialize() {

	// モデル
	// Left
	hitBoxLeft_.model = std::make_unique<Model>();
	hitBoxLeft_.model.reset(Model::Create("Resources/PlayerHitBox", "PlayerHitBox.obj"));
	hitBoxLeft_.model->SetLighting(false);
	// Right
	hitBoxRight_.model = std::make_unique<Model>();
	hitBoxRight_.model.reset(Model::Create("Resources/PlayerHitBox", "PlayerHitBox.obj"));
	hitBoxRight_.model->SetLighting(false);

	// 座標
	// Left
	hitBoxLeft_.transform = {
		.scale = {0.2f, 0.2f, 0.2f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 1.2f, 0.0f},
	};
	//Right
	hitBoxRight_.transform = {
		.scale = {0.2f, 0.2f, 0.2f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 1.2f, 0.0f},
	};

	// サイズ
	// Left
	hitBoxLeft_.size = {
		.x = 1.0f * hitBoxLeft_.transform.scale.x,
		.y = 1.0f * hitBoxLeft_.transform.scale.y,
		.z = 1.0f * hitBoxLeft_.transform.scale.z,
	};
	// Right
	hitBoxRight_.size = {
		.x = 1.0f * hitBoxRight_.transform.scale.x,
		.y = 1.0f * hitBoxRight_.transform.scale.y,
		.z = 1.0f * hitBoxRight_.transform.scale.z,
	};
	
	// カラー
	// Left
	hitBoxLeft_.color = { 1.0f, 1.0f, 1.0f, 0.5f };
	// Right
	hitBoxRight_.color = { 1.0f, 1.0f, 1.0f, 0.5f };

	// ヒットボックスの出現フラグ
	isEmergeHitBox_ = false;
}


// 更新処理
void PlayerHitBox::Update() {

	// キーを押してヒットボックスの出現フラグを立てる
	if (Input::GetInstance()->IsPushKey(DIK_SPACE) == true) {
		isEmergeHitBox_ = true;
	}
	else {
		isEmergeHitBox_ = false;
	}

	// もろもろの計算
	SetPlayerHitBoxProperty();


#ifdef _DEBUG

	ImGui::Begin("PlayerHitBox");
	ImGui::Text("LeftTransform");
	ImGui::DragFloat3("LeftScale", &hitBoxLeft_.transform.scale.x, 0.01f);
	ImGui::DragFloat3("LeftRotate", &hitBoxLeft_.transform.rotate.x, 0.01f);
	ImGui::DragFloat3("LeftTranslate", &hitBoxLeft_.transform.translate.x, 0.01f);
	ImGui::Text("RightTransform");
	ImGui::DragFloat3("RightScale", &hitBoxRight_.transform.scale.x, 0.01f);
	ImGui::DragFloat3("RightRotate", &hitBoxRight_.transform.rotate.x, 0.01f);
	ImGui::DragFloat3("RightTranslate", &hitBoxRight_.transform.translate.x, 0.01f);
	ImGui::Text("Size");
	ImGui::DragFloat3("Leftsize", &hitBoxLeft_.size.x, 0.01f);
	ImGui::DragFloat3("Rightsize", &hitBoxRight_.size.x, 0.01f);
	ImGui::Text("LeftAABB");
	ImGui::DragFloat3("Leftaabb.min", &aabbLeft_.min.x, 0.01f);
	ImGui::DragFloat3("Leftaabb.max", &aabbLeft_.max.x, 0.01f);
	ImGui::Text("RightAABB");
	ImGui::DragFloat3("Rightaabb.min", &aabbRight_.min.x, 0.01f);
	ImGui::DragFloat3("Rightaabb.max", &aabbRight_.max.x, 0.01f);
	ImGui::Checkbox("isEmergeHitBox", &isEmergeHitBox_);
	ImGui::End();

#endif // _DEBUG

}


// 描画処理
void PlayerHitBox::Draw() {

	if (isEmergeHitBox_) {
		hitBoxLeft_.model->Draw();
		hitBoxRight_.model->Draw();
	}

}


// もろもろの計算とか
void PlayerHitBox::SetPlayerHitBoxProperty() {

	// 座標
	// Right
	hitBoxLeft_.transform.translate = {
		.x = player_->GetTransform().translate.x - player_->GetSize().x - hitBoxLeft_.size.x,
		.y = player_->GetTransform().translate.y,
		.z = player_->GetTransform().translate.z,
	};
	// Right
	hitBoxRight_.transform.translate = {
		.x = player_->GetTransform().translate.x + player_->GetSize().x + hitBoxRight_.size.x,
		.y = player_->GetTransform().translate.y,
		.z = player_->GetTransform().translate.z,
	};

	// モデル
	// Left
	hitBoxLeft_.model->SetColor(hitBoxLeft_.color);
	hitBoxLeft_.model->SetScale(hitBoxLeft_.transform.scale);
	hitBoxLeft_.model->SetRotate(hitBoxLeft_.transform.rotate);
	hitBoxLeft_.model->SetTranslate(hitBoxLeft_.transform.translate);
	//Right
	hitBoxRight_.model->SetColor(hitBoxRight_.color);
	hitBoxRight_.model->SetScale(hitBoxRight_.transform.scale);
	hitBoxRight_.model->SetRotate(hitBoxRight_.transform.rotate);
	hitBoxRight_.model->SetTranslate(hitBoxRight_.transform.translate);

	// AABBの計算
	CalcAABB();
}


// AABBの計算
void PlayerHitBox::CalcAABB() {

	// Left
	aabbLeft_ = {
		.min = Subtract(hitBoxLeft_.transform.translate, hitBoxLeft_.size),
		.max = Add(hitBoxLeft_.transform.translate, hitBoxLeft_.size),
	};
	//Right
	aabbRight_ = {
		.min = Subtract(hitBoxRight_.transform.translate, hitBoxRight_.size),
		.max = Add(hitBoxRight_.transform.translate, hitBoxRight_.size),
	};
}


// 衝突時コールバック処理
void PlayerHitBox::onCollisionToEnemy() {


}
void PlayerHitBox::EndOverlapToEnemy() {


}