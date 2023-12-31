#pragma once

#include "Input/Input.h"
#include "Polygon/Model/Model.h"
#include "WorldTransform/WorldTransform.h"

#include "CollisionManager/CollisionManager.h"


class DemoGround {

public:

	DemoGround() {};
	~DemoGround() {};

	void Init();
	void Update();
	void Draw();


	void onCollisionToEnemy();
	void EndOverlapToEnemy();

	OBB GetOBB() { return obb_; }

private:

	void Move();

	void SetGroundProperty();

private:

	std::unique_ptr<Model> model_ = nullptr;
	Transform transform_{};
	Vector3 velocity_{};
	Vector3 size_{};
	Vector4 color_{};
	Vector3 moveRotate_{};

	OBB obb_{};

};