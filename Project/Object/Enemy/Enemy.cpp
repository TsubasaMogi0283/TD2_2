#include "Enemy.h"
#include "Object/Player/Player.h"



// 初期化処理
void Enemy::Initialize(const Vector3& position) {

	// インプット
	input = Input::GetInstance();

	// モデル
	ene_.model = std::make_unique<Model>();
	ene_.model.reset(Model::Create("Resources/Enemy", "Enemy.obj"));

	// 座標
	init_.transform = {
		.scale = {0.18f, 0.18f, 0.18f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = position,
	};
	ene_.transform = init_.transform;

	// 速度
	ene_.velocity = { 0.0f, 0.0f, 0.0f };

	// 移動量
	move_ = 0.028f;

	//サイズ
	ene_.size = {
		.x = 1.0f * ene_.transform.scale.x,
		.y = 1.0f * ene_.transform.scale.y,
		.z = 1.0f * ene_.transform.scale.z,
	};

	// カラー
	ene_.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	isHit_ = 0;
	isApproach_ = true;

	// 挙動ステート
	moveState_ = new EnemyWanderingState();

	// モデルの設定
	ene_.model->SetColor(ene_.color);
	ene_.model->SetScale(ene_.transform.scale);
	ene_.model->SetRotate(ene_.transform.rotate);
	ene_.model->SetTranslate(ene_.transform.translate);
}



// 更新処理
void Enemy::Update() {

	// プレイヤーの各値の設定
	SetEnemyProperty();

	// 移動処理
	if (isApproach_) {
		Move();
	}
	// 挙動
	//moveState_->Move(this);

#ifdef _DEBUG

	ImGui::Begin("Enemy");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scale", &ene_.transform.scale.x, 0.005f);
	ImGui::DragFloat3("Rotate", &ene_.transform.rotate.x, 0.005f);
	ImGui::DragFloat3("translate", &ene_.transform.translate.x, 0.02f);
	ImGui::Text("size");
	ImGui::DragFloat3("size", &ene_.size.x, 0.01f);
	ImGui::Text("Velocity");
	ImGui::DragFloat3("velocity", &ene_.velocity.x, 0.01f);
	ImGui::Text("Sphere");
	ImGui::DragFloat3("Sphere.center", &eneSphere_.center.x, 0.01f);
	ImGui::DragFloat("sphere.radius", &eneSphere_.radius, 0.01f);
	ImGui::Text("isHit = %d", isHit_);
	ImGui::Checkbox("isApproach", &isApproach_);
	ImGui::Checkbox("isDead", &isDead_);
	ImGui::End();


	if (input->IsTriggerKey(DIK_R)) {
		ene_.transform = init_.transform;
		isApproach_ = false;
	}

#endif // _DEBUG
}



// 描画処理
void Enemy::Draw() {

	ene_.model->Draw();
}



// 衝突時コールバック処理
void Enemy::onCollisionToPlayer() {

	isHit_ = 1;
	isApproach_ = false;
	isDead_ = true;
}
void Enemy::EndOverlapToPlayer() {

	isHit_ = 0;
}


// 挙動ステートパターン変更
void Enemy::ChangeMoveState(IEnemyMoveState* newState) {

	delete moveState_;
	moveState_ = newState;
}


// 移動処理
void Enemy::Move() {

	// プレイヤーとのベクトル
	Vector3 toPlayer = {
		.x = player_->GetTransform().translate.x - ene_.transform.translate.x,
		.y = player_->GetTransform().translate.y - ene_.transform.translate.y,
		.z = player_->GetTransform().translate.z - ene_.transform.translate.z,
	};

	// プレイヤー間との距離
	float lenght = sqrt((toPlayer.x * toPlayer.x) + (toPlayer.y * toPlayer.y) + (toPlayer.z * toPlayer.z));

	// ベクトルとレングスを使った速度設定
	ene_.velocity = {
		.x = toPlayer.x / lenght * move_,
		.y = toPlayer.y / lenght * move_,
		.z = toPlayer.z / lenght * move_,
	};

	// 移動処理
	ene_.transform.translate = Add(ene_.transform.translate, ene_.velocity);
}



/// <summary>
/// スフィアの計算
/// </summary>
void Enemy::CalcSphere() {

	eneSphere_ = {
		.center = ene_.transform.translate,
		.radius = ene_.size.x,
	};
}



/// <summary>
/// いろいろ設定する
/// </summary>
void Enemy::SetEnemyProperty() {

	// モデルの設定
	ene_.model->SetColor(ene_.color);
	ene_.model->SetScale(ene_.transform.scale);
	ene_.model->SetRotate(ene_.transform.rotate);
	ene_.model->SetTranslate(ene_.transform.translate);

	// スフィアの計算
	CalcSphere();

	// マットワールドの計算
	UpdateMat();
}



/// <summary>
/// マットワールド作る
/// </summary>
void Enemy::UpdateMat() {

	ene_.matWorld = MakeAffineMatrix(ene_.transform.scale, ene_.transform.rotate, ene_.transform.translate);
}



/// <summary>
/// プレイヤーのTransformの取得
/// </summary>
Vector3 Enemy::GetPlayerPos() {
	return player_->GetTransform().translate;
}