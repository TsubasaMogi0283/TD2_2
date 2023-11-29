#include "PlayerParticle.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerParticle::Initialize(const Vector3& position) {

	// モデル
	particle_.model = std::make_unique<Model>();
	particle_.model.reset(Model::Create("Resources/PlayerParticle", "PlayerParticle.obj"));
	particle_.model->SetLighting(false);

	// トランスフォーム
	particle_.transform = {
		.scale  = { 0.1f, 0.1f, 0.1f },
		.rotate = { 0.0f, 0.0f, 0.0f },
		.translate = position,
	};

	// 速度
	particle_.velocity = { 0.1f, 0.1f, 0.1f };

	// カラー
	particle_.color = { 1.0f, 1.0f, 0.0f, 1.0f };

	// 描画フラグを立てる
	isDrawing_ = true;

	// 描画時間
	drawTimer_ = 0;
	endDrawTimer_ = 90;
}



/// <summary>
/// 更新処理
/// </summary>
void PlayerParticle::Update() {

	// いろいろ設定する
	SetPlayerParlicleProperty();

	// 描画時間の計算
	CalcDrawTimer();

	// カラーの計算
	CalcColor();

	// トランスフォームの計算
	CalcTransform();



#ifdef _DEBUG

	/*ImGui::Begin("PlayerParticle");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scele", &particle_.transform.scale.x, 0.01f);
	ImGui::DragFloat3("Rotate", &particle_.transform.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &particle_.transform.translate.x, 0.01f);
	ImGui::Text("Color");
	ImGui::ColorEdit4("color", &particle_.color.x);
	ImGui::Checkbox("isDrawing", &isDrawing_);
	ImGui::End();*/

#endif // _DEBUG
}



/// <summary>
/// 描画処理
/// </summary>
void PlayerParticle::Draw() {

	if (isDrawing_) {
		particle_.model->Draw();
	}
}



/// <summary>
/// いろいろ設定する
/// </summary>
void PlayerParticle::SetPlayerParlicleProperty() {

	// モデルの設定
	particle_.model->SetColor(particle_.color);
	particle_.model->SetScale(particle_.transform.scale);
	particle_.model->SetRotate(particle_.transform.rotate);
	particle_.model->SetTranslate(particle_.transform.translate);
}



/// <summary>
/// 描画時間を計算する
/// </summary>
void PlayerParticle::CalcDrawTimer() {

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
void PlayerParticle::CalcColor() {

	// フレーム
	float nowFrame = float(drawTimer_);
	float endFrame = float(endDrawTimer_);
	float val = nowFrame / endFrame;

	// 黄色から赤へ
	Vector4 color = CalcRGBA(particle_.color, Mul);

	color = {
		.x = color.x + (50.0f - color.x) * EaseInCirc(val),
		.y = color.y + (0.0f - color.y) * EaseOutQuart(val),
		.z = color.z,
		.w = color.w + (50.0f - color.w) * EaseInCirc(val),
	};

	particle_.color = CalcRGBA(color, Div);
}



/// <summary>
/// スケールの計算
/// </summary>
void PlayerParticle::CalcTransform() {

	// 上へ移動する
	particle_.transform.translate.y += 0.006f;

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
float PlayerParticle::EaseInSine(float& x) {
	return 1.0f - float(std::cos((x * M_PI) / 2.0f));
}
float PlayerParticle::EaseInQuart(float& x) {
	return x * x * x * x;
}
float PlayerParticle::EaseInCirc(float& x) {
	return 1.0f - std::sqrt(1.0f - std::pow(x, 2.0f));
}
float PlayerParticle::EaseOutQuart(float& x) {
	return 1.0f - std::pow(1.0f - x, 4.0f);
}
float PlayerParticle::EaseOutExpo(float& x) {
	return x == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * x);
}



// 色の計算
// RGBを求める
Vector4 PlayerParticle::CalcRGBA(Vector4 color, ColorCalcType type) {

	if (type == Mul) {

		Vector4 result = {
		result.x = color.x * 255.0f,
		result.y = color.y * 255.0f,
		result.z = color.z * 255.0f,
		result.w = color.w * 255.0f,
		};

		return result;
	}
	else if (type == Div) {

		Vector4 result = {
		result.x = color.x / 255.0f,
		result.y = color.y / 255.0f,
		result.z = color.z / 255.0f,
		result.w = color.w / 255.0f,
		};

		return result;
	}

	return color;
}