#pragma once
#include <Polygon/Model/Model.h>

class Corn{
	public:
	//コンストラクタ
	Corn();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~Corn();

private:
	//デバッグテキスト
	void DisplayText();



private:

	//オーブン
	//とうもろこし
	Model* model_ =  nullptr ;
	Vector3 position_ = {};
	Vector3 rotate_ = {};
	Vector4 color_ = {};



	Vector3 lightDirection_ = {};
	float theta_ = 0.0f;
};

