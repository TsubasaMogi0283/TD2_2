#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"

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
	Input* input_ = nullptr;



};
