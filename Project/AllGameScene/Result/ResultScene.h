#include "AllGameScene/GameManager/IGameScene.h"
#include "Input/Input.h"

class ResultScene : public IGameScene{
public:

	ResultScene();

	void Initialize(GameManager* gamaManager) override;
	void Update(GameManager* gamaManager) override;
	void Draw(GameManager* gamaManager) override;

	~ResultScene();

private:
	void ShowImGui();


private:



};