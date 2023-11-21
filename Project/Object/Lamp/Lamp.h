#pragma once
#include <Polygon/Model/Model.h>

class Lamp{
public:
	//コンストラクタ
	Lamp();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~Lamp();

private:
	void DebugText();

private:
	Model* model_ = nullptr;
	Vector3 position_ = {};
	Vector3 scale_ = {};
	Vector3 rotate_ = {};
	Vector4 color_ = {};

	
};

