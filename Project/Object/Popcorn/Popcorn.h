#pragma once
#include <Polygon/Model/Model.h>

class Popcorn{
	
public:
	//コンストラクタ
	Popcorn();

	//初期化
	void Initialize(Vector3 position,Vector3 move);

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~Popcorn();


	bool IsDead() {
		return isDead_;
	}

private:
	//デバッグテキスト
	void DisplayText();





private:


	//オーブン
	//とうもろこし
	Model* model_ =  nullptr ;
	Vector3 scale_ = {0.5f,0.5f,0.5f,};
	Vector3 position_ = {};
	Vector3 move_ = {};
	Vector3 rotate_ = {};
	Vector4 color_ = {};

	Vector3 velocity = {};

	Vector3 lightDirection_ = {};
	float theta_ = 0.0f;

	int deleteTime_ = 60;
	bool isDead_ = false;
};

