#pragma once
#include <Polygon/Model/Model.h>

class Oven{
public:
	//コンストラクタ
	Oven();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~Oven();

private:
	//デバッグテキスト
	void DisplayText();



private:

	//オーブン
	Model* oven_ = nullptr;
	Vector3 ovenPosition_ = {};
	Vector3 ovenRotate_ = {};




};

