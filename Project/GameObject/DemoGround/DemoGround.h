#pragma once

#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"




/* DemoGroundクラス */
class DemoGround {

public:

	DemoGround() {};
	~DemoGround() {};

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


private:

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// トランスフォーム
	Transform transform_{};


};