#include "AllGameScene/GameManager/IGameScene.h"
#include "AllGameScene/Game/GameScene.h"

#include "Input/Input.h"
#include "Polygon/Sprite/Sprite.h"
#include "Audio/Audio.h"

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
	//ロゴ
	std::unique_ptr<Sprite> logo_ = nullptr;
	//スタートのテキスト
	std::unique_ptr<Sprite> startText_ = nullptr;
	//背景
	std::unique_ptr<Sprite> backGround_ = nullptr;

	//BGM
	Audio* bgm_ = nullptr;
	uint32_t titleBGMHandle_ = 0u;
	//SE
	Audio* decideSE_ = nullptr;
	uint32_t decideSEHandle_ = 0u;

	float spriteTransparency_ = 0.0f;
	bool isFadeIn_ = true;

	//フェードアウト
	bool isFadeOut_ = false;

	//点滅
	int flashTime_=0;

	
	int startFlashTime_ = 0;
	//ロード時間
	int32_t loadingTime_ = 0;

	//コントローラー

	//フェードイン
	XINPUT_STATE joyState{};

	int triggerButtonBTime;
};
