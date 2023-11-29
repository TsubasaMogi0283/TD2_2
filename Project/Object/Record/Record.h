#pragma once


//倒した敵を記録するためだけだからあまり機能はいらないね
class Record {
private:
	Record();

	~Record();


public:

	static Record* GetInstance();

	//コピーコンストラクタ禁止
	Record(const Record& obj) = delete;

	//代入演算子を無効にする
	Record& operator=(const Record& obj) = delete;

	int SetScore(int score) {
		this->score_ = score;
	}

	

private:
	//5桁
	static const int DIGIT_ = 5;
	int attackdEnemy[DIGIT_] = {};

	int score_ = 0;

};