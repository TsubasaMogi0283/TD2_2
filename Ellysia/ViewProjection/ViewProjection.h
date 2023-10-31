#pragma once
#include "Common/Windows/WinApp.h"

#include <Math/Vector/Vector3.h>
#include <Math/Matrix/Matrix/Matrix4x4.h>

struct ViewProjection {
	//回転
	Vector3 rotate_ = { 0.0f,0.0f,0.0f };
	//座標
	Vector3 translate_ = { 0.0f,0.0f - 50.0f };

	//ビュー行列
	Matrix4x4 matView_{};
	//プロジェクション行列
	Matrix4x4 matProjection_{};

	//視野角
	float fov_ = 0.45f;
	//アスペクト比
	float aspectRatio_ = float(WinApp::GetInstance()->GetClientWidth() / WinApp::GetInstance()->GetClientHeight());

	//Near
	float nearClip_ = 0.1f;
	//Far
	float farClip_ = 1000.0f;

	//行列の計算
	void UpdateMatrix();



};