#include "PlayerParticle.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerParlicle::Initialize(const Vector3& position) {

	// モデル
	particle_.model = std::make_unique<Model>();
	particle_.model.reset(Model::Create("Resources/PlayerParticle", "PlayerParticle.obj"));
	particle_.model->SetLighting(false);

	// 座標
	particle_.transform = {
		.scale  = { 0.1f, 0.1f, 0.1f },
		.rotate = { 0.0f, 0.0f, 0.0f },
		.translate = position,
	};

	// 速度
	particle_.velocity = { 0.1f, 0.1f, 0.1f };

	// カラー
	particle_.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 描画フラグを立てる
	isDrawing_ = true;
}



/// <summary>
/// 更新処理
/// </summary>
void PlayerParlicle::Update() {

	// いろいろ設定する
	SetPlayerParlicleProperty();

	// アルファの計算
	CalcAlpha();

	// スケールの計算
	CalcTranslate();



#ifdef _DEBUG

	ImGui::Begin("PlayerParticle");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scele", &particle_.transform.scale.x, 0.01f);
	ImGui::DragFloat3("Rotate", &particle_.transform.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &particle_.transform.translate.x, 0.01f);
	ImGui::Text("Color");
	ImGui::ColorEdit4("color", &particle_.color.x);
	ImGui::Checkbox("isDrawing", &isDrawing_);
	ImGui::End();

#endif // _DEBUG

}



/// <summary>
/// 描画処理
/// </summary>
void PlayerParlicle::Draw() {

	if (isDrawing_) {
		particle_.model->Draw();
	}
}



/// <summary>
/// いろいろ設定する
/// </summary>
void PlayerParlicle::SetPlayerParlicleProperty() {

	// モデルの設定
	particle_.model->SetColor(particle_.color);
	particle_.model->SetScale(particle_.transform.scale);
	particle_.model->SetRotate(particle_.transform.rotate);
	particle_.model->SetTranslate(particle_.transform.translate);
}



/// <summary>
/// アルファの計算
/// </summary>
void PlayerParlicle::CalcAlpha() {

	particle_.color.w -= 0.01f;

	// アルファが０以下になったら描画フラグを折る
	if (particle_.color.w <= 0.0f) {
		isDrawing_ = false;
	}
}



/// <summary>
/// スケールの計算
/// </summary>
void PlayerParlicle::CalcTranslate() {

	particle_.transform.translate.y += 0.007f;

}