#pragma once
#include <Polygon/Model/Model.h>
#include <Object/Popcorn/Popcorn.h>
#include <list>

class SamplePlayer{

public:
	//コンストラクタ
	SamplePlayer();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~SamplePlayer();

private:
	//デバッグテキスト
	void DisplayText();

	void Move();

	void Attack();


private:


	//オーブン
	//とうもろこし
	Model* model_ =  nullptr ;
	Vector3 scale_ = {};
	Vector3 position_ = {};
	Vector3 move_ = {};
	Vector3 rotate_ = {};
	Vector4 color_ = {};



	Vector3 lightDirection_ = {};
	float theta_ = 0.0f;


	std::list<Popcorn*> popcornRight_;
	std::list<Popcorn*> popcornLeft_;

};

