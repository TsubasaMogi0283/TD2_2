#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include "CollisionManager/CollisionManager.h"


class DemoPlayer {

public:

	DemoPlayer() {};
	~DemoPlayer() {};

	void Init();
	void Update();
	void Draw();


	void onCollisionToEnemy();
	void EndOverlapToEnemy();

	Segment GetSegment() { return segment_; }

private:

	void Move();

	void SetPlayerProperty();

private:

	std::unique_ptr<Model> model_ = nullptr;
	Transform transform_{};
	Vector3 velocity_{};
	Vector3 size_{};
	Vector4 color_{};
	Vector3 moveRotate_{};
	bool isHit_ = false;

	Segment segment_{};
};