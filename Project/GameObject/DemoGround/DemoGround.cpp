#include "DemoGround.h"



// 初期化処理
void DemoGround::Initialize() {

	// モデル
	dGround_.model = std::make_unique<Model>();
	dGround_.model->CreateObject("Resources/Ground", "Ground.obj");

	// 座標
	dGround_.transform = {
		.scale = {1.0f, 1.0f, 1.0f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 0.0f, 50.0f},
	};

	// サイズ
	dGround_.size = { 10.0f, 1.0f, 10.0f };


}



// 更新処理
void DemoGround::Update() {

	// OBBを求める
	CalcOBB();


#ifdef _DEBUG

	ImGui::Begin("DemoGround");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scele", &dGround_.transform.scale.x, 0.01f);
	ImGui::DragFloat3("Rotate", &dGround_.transform.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &dGround_.transform.translate.x, 0.01f);
	ImGui::Text("OBB");
	ImGui::DragFloat3("OBB.center", &obb_.center.x, 0.01f);
	ImGui::DragFloat3("OBB.rotate", &dGround_.transform.rotate.x, 0.01f);
	ImGui::DragFloat3("OBB.size", &obb_.size.x, 0.01f);
	ImGui::End();

#endif // _DEBUG


}



// 描画処理
void DemoGround::Draw() {

	dGround_.model->Draw(dGround_.transform);
}



// 衝突時コールバック処理
void DemoGround::onCollision() {

}



/// <summary>
/// OBBの計算
/// </summary>
void DemoGround::CalcOBB() {

	obb_.center = dGround_.transform.translate;


	Matrix4x4 rotateMat = MakeRotateXYZMatrix(
		dGround_.transform.rotate.x, dGround_.transform.rotate.y, dGround_.transform.rotate.z);

	obb_.orientations[0].x = rotateMat.m[0][0];
	obb_.orientations[0].y = rotateMat.m[0][1];
	obb_.orientations[0].z = rotateMat.m[0][2];

	obb_.orientations[1].x = rotateMat.m[1][0];
	obb_.orientations[1].y = rotateMat.m[1][1];
	obb_.orientations[1].z = rotateMat.m[1][2];

	obb_.orientations[2].x = rotateMat.m[2][0];
	obb_.orientations[2].y = rotateMat.m[2][1];
	obb_.orientations[2].z = rotateMat.m[2][2];


	obb_.size = dGround_.size;
}



/// <summary>
/// 乗算
/// </summary>
Vector3 DemoGround::Mul(const Vector3& v1, const Vector3& v2) {

	Vector3 result = {
		.x = v1.x * v2.x,
		.y = v1.y * v2.y,
		.z = v1.z * v2.z,
	};

	return result;
}