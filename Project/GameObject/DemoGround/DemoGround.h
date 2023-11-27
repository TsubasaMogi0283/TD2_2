#pragma once

#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"
#include "Math/Vector/Calculation/VectorCalculation.h"
#include "Math/Matrix/Calculation/Matrix4x4Calculation.h"

#include "Collider/CollisionManager/CollisionManager.h"


struct DemoGroundProperty {
	std::unique_ptr<Model> model = nullptr;
	Transform transform{};
	Vector3 size{};
};



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

	/// <summary>
	/// 衝突時コールバック処理
	/// </summary>
	void onCollision();


#pragma region Get

	/// <summary>
	/// OBBの取得
	/// </summary>
	OBB GetOBB() { return obb_; }


#pragma endregion


private:


	/// <summary>
	/// OBBの計算
	/// </summary>
	void CalcOBB();

private:

	// デモ床
	DemoGroundProperty dGround_;

	
	// OBB
	OBB obb_{};

};