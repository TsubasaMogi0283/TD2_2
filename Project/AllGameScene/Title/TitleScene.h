#include "AllGameScene/GameManager/IGameScene.h"
#include "AllGameScene/Game/GameScene.h"

#include "Input/Input.h"
#include "Polygon/Sprite/Sprite.h"

class TitleScene : public IGameScene{
public:

	TitleScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~TitleScene();

private:
	void ShowImGui();


private:
	
	std::unique_ptr<Sprite> logo_ = nullptr;
	std::unique_ptr<Sprite> startText_ = nullptr;
	std::unique_ptr<Sprite> backGround_ = nullptr;

	float spriteTransparency_ = 0.0f;

	//フェードイン
	bool isFadeIn_ = true;

	//フェードアウト
	bool isFadeOut_ = false;

	//点滅
	int flashTime_=0;

	
	int startFlashTime_ = 0;
	//ロード時間
	int32_t loadingTime_ = 0;

	//コントローラー
	XINPUT_STATE joyState{};

	int triggerButtonBTime;
};
