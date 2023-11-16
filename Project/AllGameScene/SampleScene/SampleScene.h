#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include "Polygon/Sprite/Sprite.h"
#include "Math/Vector/Transform.h"

#include "Polygon/Model/Model.h"

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
	static const int MODEL_AMOUNT_ = 10;

	Model* model_[MODEL_AMOUNT_] = { nullptr };
	Vector3 modelTranslate_ = {};

	Vector2 position_ = { 0.0f,0.0f };
	Vector2 scale_ = { 1.0f,1.0f };
	float rotate = 0.0f;

	Vector2 anchorPoint = { 0.0f,0.0f };
	Sprite* sprite = nullptr;
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	Vector4 modelColor_ = { 1.0f,1.0f,1.0f,1.0f };

	bool flipX_ = false;
	bool flipY_ = false;

	bool isInvisible_ = false;


	Vector2 leftTop_ = { 0.0f,0.0f };
	Vector2 size_ = { 100.0f,100.0f };


};

