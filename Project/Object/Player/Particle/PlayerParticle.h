#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include <stdlib.h>




// Playerの前方宣言
class Player;


struct PlayerParticleProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
	Vector3 velocity{};
	Vector3 size{};
	Vector4 color{};
};
struct PlayerParticleEmitter {
	Transform transform{};
};
enum ColorCalcType {
	Mul,
	Div,
};



/* PlayerParticleクラス */
class PlayerParticle {

public: // メンバ関数

	PlayerParticle() {};
	~PlayerParticle() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


#pragma region Get

	/// <summary>
	/// 描画フラグの取得
	/// </summary>
	bool IsDrawing() const { return isDrawing_; }

#pragma endregion


#pragma region Set



#pragma endregion


private: // メンバ関数

	/// <summary>
	/// いろいろ設定する
	/// </summary>
	void SetPlayerParlicleProperty();

	/// <summary>
	/// 描画時間を計算する
	/// </summary>
	void CalcDrawTimer();

	/// <summary>
	/// アルファの計算
	/// </summary>
	void CalcColor();

	/// <summary>
	/// スケールの計算
	/// </summary>
	void CalcTransform();

	/// <summary>
	/// イージング関数
	/// </summary>
	float EaseInSine(float& x);
	float EaseInQuart(float& x);
	float EaseInCirc(float& x);
	float EaseOutQuart(float& x);
	float EaseOutExpo(float& x);

	/// <summary>
	/// 色の計算
	/// </summary>
	Vector4 CalcRGBA(Vector4 color, ColorCalcType type);

private: // メンバ変数

	// プレイヤーパーティクル
	PlayerParticleProperty particle_;

	// エミッター
	PlayerParticleEmitter emitter_;

	// 描画フラグ
	bool isDrawing_;

	// 描画タイマー
	uint32_t drawTimer_;
	uint32_t endDrawTimer_;
};