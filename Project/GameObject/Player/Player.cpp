#include "Player.h"



// 初期化処理
void Player::Initialize() {

	// インプット
	input = Input::GetInstance();


	// モデル
	pla_.model = std::make_unique<Model>();
	pla_.model->CreateObject("Resources/Player", "Player.obj");

	// 座標
	init_.transform = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 10.0f, 50.0f},
	};
	pla_.transform = init_.transform;

	// 速度
	pla_.velocity = { 1.0f, 1.0f, 1.0f };

	//サイズ
	pla_.size = 2.0f;

	// 重力
	gravity_.enable = false;
	gravity_.velocity = { 0.0f, 0.0f, 0.0f };
	gravity_.accel = 0.1f;
	gravity_.maxVel = -1.0f;

}



// 更新処理
void Player::Update() {

	// 移動処理
	Move();


	// 重力の処理
	CalcGravity();


#ifdef _DEBUG

	ImGui::Begin("Player");
	ImGui::DragFloat3("Scale", &pla_.transform.scale.x, 0.005f);
	ImGui::DragFloat3("Rotate", &pla_.transform.rotate.x, 0.005f);
	ImGui::DragFloat3("translate", &pla_.transform.translate.x, 0.02f);
	ImGui::Text("Gravity");
	ImGui::Checkbox("GravityEnable", &gravity_.enable);
	ImGui::DragFloat("Gravity_accel", &gravity_.accel, 0.001f);
	ImGui::DragFloat3("Gravity_Vel", &gravity_.velocity.x, 0.001f);
	ImGui::End();

#endif // _DEBUG

}



// 描画処理
void Player::Draw() {

	pla_.model->Draw(pla_.transform);

}



// 移動処理
void Player::Move() {

	if (input->IsPushKey(DIK_W)) {

		pla_.transform.translate.z += pla_.velocity.z;
	}
	else if (input->IsPushKey(DIK_A)) {

		pla_.transform.translate.x -= pla_.velocity.x;
	}
	else if (input->IsPushKey(DIK_S)) {

		pla_.transform.translate.z -= pla_.velocity.z;
	}
	else if (input->IsPushKey(DIK_D)) {

		pla_.transform.translate.x += pla_.velocity.x;
	}


#ifdef _DEBUG

	if (input->IsTriggerKey(DIK_R)) {
		pla_.transform = init_.transform;
	}

#endif // _DEBUG

}



// 重力の処理
void Player::CalcGravity() {

	// 重力が有効なとき
	if (gravity_.enable) {

		// 速度を座標に加算
		pla_.transform.translate.y += gravity_.velocity.y;


		// 最大速度になったら値を固定して、速度が出すぎるのを防ぐ
		if (gravity_.velocity.y > gravity_.maxVel) {

			// 重力速度に加算
			gravity_.velocity.y -= gravity_.accel;
		}
		else if (gravity_.velocity.y <= gravity_.maxVel) {

			// 加速度が最大速度を超えたら最大速度で固定
			gravity_.velocity.y = gravity_.maxVel;
		}
	}
	else {

		// 重力が無効のときは、速度は０で固定しとく
		gravity_.velocity = { 0.0f, 0.0f, 0.0f };
	}
}