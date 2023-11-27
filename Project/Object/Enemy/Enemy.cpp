#include "Enemy.h"



// 初期化処理
void Enemy::Initialize() {

	// インプット
	input = Input::GetInstance();

	// モデル
	ene_.model = std::make_unique<Model>();
	ene_.model.reset(Model::Create("Resources/Player", "Player.obj"));

	// 座標
	init_.transform = {
		.scale = {0.3f, 0.3f, 0.3f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 1.2f, 0.0f},
	};
	ene_.transform = init_.transform;

	// 速度
	ene_.velocity = { 0.1f, 0.1f, 0.1f };

	//サイズ
	ene_.size = {
		.x = 1.0f * ene_.transform.scale.x,
		.y = 1.0f * ene_.transform.scale.y,
		.z = 1.0f * ene_.transform.scale.z,
	};

	// カラー
	ene_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}



// 更新処理
void Enemy::Update() {

	// プレイヤーの各値の設定
	SetEnemyProperty();

	// 移動処理
	Move();


#ifdef _DEBUG

	ImGui::Begin("Player");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scale", &ene_.transform.scale.x, 0.005f);
	ImGui::DragFloat3("Rotate", &ene_.transform.rotate.x, 0.005f);
	ImGui::DragFloat3("translate", &ene_.transform.translate.x, 0.02f);
	ImGui::Text("size");
	ImGui::DragFloat3("size", &ene_.size.x, 0.01f);
	ImGui::Text("Sphere");
	ImGui::DragFloat3("Sphere.center", &eneSphere_.center.x, 0.01f);
	ImGui::DragFloat("sphere.radius", &eneSphere_.radius, 0.01f);
	ImGui::End();

#endif // _DEBUG
}



// 描画処理
void Enemy::Draw() {

	ene_.model->Draw();
}



// 衝突時コールバック処理




// 移動処理
void Enemy::Move() {

	


#ifdef _DEBUG

	if (input->IsTriggerKey(DIK_R)) {
		ene_.transform = init_.transform;
	}

#endif // _DEBUG
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
}
