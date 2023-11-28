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

	// 描画時間
	drawTimer_ = 0;
	endDrawTimer_ = 90;
}



/// <summary>
/// 更新処理
/// </summary>
void PlayerParlicle::Update() {

	// いろいろ設定する
	SetPlayerParlicleProperty();

	// 描画時間の計算
	CalcDrawTimer();

	// アルファの計算
	CalcAlpha();

	// スケールの計算
	CalcTransform();



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
/// 描画時間を計算する
/// </summary>
void PlayerParlicle::CalcDrawTimer() {

	// 毎フレームー１
	drawTimer_ = drawTimer_ + 1;

	// ９０フレームで描画を切る
	if (drawTimer_ >= endDrawTimer_) {
		isDrawing_ = false;
	}
}



/// <summary>
/// アルファの計算
/// </summary>
void PlayerParlicle::CalcAlpha() {

	particle_.color.w -= 0.01f;

}



/// <summary>
/// スケールの計算
/// </summary>
void PlayerParlicle::CalcTransform() {

	// 上へ移動する
	particle_.transform.translate.y += 0.007f;

	// スケールが小さくなっていく
	float nowFrame = float(drawTimer_);
	float endFrame = float(endDrawTimer_);
	float val = nowFrame / endFrame;

	particle_.transform.scale = {
		.x = particle_.transform.scale.x + (0.04f - particle_.transform.scale.x) * EaseInQuart(val),
		.y = particle_.transform.scale.y + (0.04f - particle_.transform.scale.y) * EaseInQuart(val),
		.z = particle_.transform.scale.z + (0.04f - particle_.transform.scale.z) * EaseInQuart(val),
	};

}



/// <summary>
/// イージング関数
/// </summary>
float PlayerParlicle::EaseInQuart(float& x) {
	return x * x * x * x;
}