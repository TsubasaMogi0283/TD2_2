#pragma once

class GameScene;

//GameSceneの中にさらにStatePatternで分ける
//演出これが一番やりやすいかも
class IGamePlayScene {
public:
	virtual ~IGamePlayScene() {
	
	};
	virtual void Initialize(GameScene* gamaManager)=0;
	virtual void Update(GameScene* gamaManager)=0;
	virtual void Draw(GameScene* gamaManager)=0;


};