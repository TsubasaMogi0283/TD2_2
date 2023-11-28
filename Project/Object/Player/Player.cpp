#include "Player.h"



// 初期化処理
void Player::Initialize() {

	// インプット
	input = Input::GetInstance();

	// モデル
	pla_.model = std::make_unique<Model>();
	pla_.model.reset(Model::Create("Resources/Player", "Player.obj"));

	// 座標
	init_.transform = {
		.scale = {0.3f, 0.3f, 0.3f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 1.2f, 0.0f},
	};
	pla_.transform = init_.transform;

	// 速度
	pla_.velocity = { 0.1f, 0.1f, 0.1f };

	//サイズ
	pla_.size = {
		.x = 1.0f * pla_.transform.scale.x,
		.y = 1.0f * pla_.transform.scale.y,
		.z = 1.0f * pla_.transform.scale.z,
	};

	// カラー
	pla_.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 重力
	gravity_.enable = false;
	gravity_.velocity = { 0.0f, 0.0f, 0.0f };
	gravity_.accel = 0.1f;
	gravity_.maxVel = -1.0f;



	isHit_ = 0;
}



// 更新処理
void Player::Update() {

	// プレイヤーの各値の設定
	SetPlayerProperty();

	// 移動処理
	Move();

	// 重力の処理
	CalcGravity();


#ifdef _DEBUG

	ImGui::Begin("Player");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Scale", &pla_.transform.scale.x, 0.005f);
	ImGui::DragFloat3("Rotate", &pla_.transform.rotate.x, 0.005f);
	ImGui::DragFloat3("translate", &pla_.transform.translate.x, 0.02f);
	ImGui::Text("size");
	ImGui::DragFloat3("size", &pla_.size.x, 0.01f);
	ImGui::Text("Sphere");
	ImGui::DragFloat3("Sphere.center", &plaSphere_.center.x, 0.01f);
	ImGui::DragFloat("sphere.radius", &plaSphere_.radius, 0.01f);
	ImGui::Text("Gravity");
	ImGui::Checkbox("GravityEnable", &gravity_.enable);
	ImGui::DragFloat("Gravity_accel", &gravity_.accel, 0.001f);
	ImGui::DragFloat3("Gravity_Vel", &gravity_.velocity.x, 0.001f);
	ImGui::Text("isHit = %d", isHit_);
	ImGui::End();

#endif // _DEBUG

}



// 描画処理
void Player::Draw() {

	pla_.model->Draw();
}



// 衝突時コールバック処理
void Player::onCollisionToEnemy() {

	//gravity_.enable = false;
	isHit_ = 1;
}
void Player::EndOverlapToEnemy() {

	//gravity_.enable = true;
	isHit_ = 0;
}



// 移動処理
void Player::Move() {

	if (input->IsPushKey(DIK_A) || input->IsPushKey(DIK_LEFT)) {

		pla_.transform.translate.x -= pla_.velocity.x;
	}
	if (input->IsPushKey(DIK_D) || input->IsPushKey(DIK_RIGHT)) {

		pla_.transform.translate.x += pla_.velocity.x;
	}


#ifdef _DEBUG

	if (input->IsTriggerKey(DIK_R)) {
		pla_.transform = init_.transform;
		isHit_ = 0;
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



/// <summary>
/// スフィアの計算
/// </summary>
void Player::CalcSphere() {

	plaSphere_ = {
		.center = pla_.transform.translate,
		.radius = pla_.size.x,
	};
}



/// <summary>
/// いろいろ設定する
/// </summary>
void Player::SetPlayerProperty() {

	// モデルの設定
	pla_.model->SetColor(pla_.color);
	pla_.model->SetScale(pla_.transform.scale);
	pla_.model->SetRotate(pla_.transform.rotate);
	pla_.model->SetTranslate(pla_.transform.translate);

	// スフィアの計算
	CalcSphere();
}
