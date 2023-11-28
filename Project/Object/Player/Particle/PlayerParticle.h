#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"




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



/* PlayerParticleクラス */
class PlayerPerlicle {

public: // メンバ関数

	PlayerPerlicle() {};
	~PlayerPerlicle() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


#pragma region Get



#pragma endregion


#pragma region Set



#pragma endregion


private: // メンバ関数


private: // メンバ変数

	// プレイヤーパーティクル
	PlayerParticleProperty particle_;

	// エミッター
	PlayerParticleEmitter emitter_;

};