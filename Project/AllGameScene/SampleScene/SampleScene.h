#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include <memory>

#include "Polygon/Sprite/Sprite.h"
#include "Polygon/Model/Model.h"

#include "Object/Oven/Oven.h"

//StatePatternを使う時は必ず前方宣言をするように
class Gamemanager;

class SampleScene : public IGameScene {
public:

	//コンストラクタ
	SampleScene();

	/// デストラクタ
	~SampleScene();

	/// 初期化
	void Initialize(GameManager* gameManager)override;

	/// 更新
	void Update(GameManager* gameManager)override;

	/// 描画
	void Draw(GameManager* gameManager)override;

private:

	//とうもろこし
	Model* corn_ =  nullptr ;
	Vector3 cornPosition_ = {};
	Vector3 cornRotate_ = {};

	


	//オーブン
	std::unique_ptr<Oven> oven_ = nullptr;
	
	
	Model* lamp_ = nullptr;
	Vector3 lampPosition_ = {};
	Vector3 lampScale_ = {};
	Vector3 lampRotate_ = {};
	Vector4 lampColor_ = {};

	Vector4 cornColor_ = {};




	//カメラ
	Vector3 cameraPosition_ = {};
	Vector3 cameraRotate_ = {};

};

