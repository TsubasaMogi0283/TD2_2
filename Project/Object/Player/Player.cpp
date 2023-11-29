#include "Player.h"



// デストラクタ
Player::~Player() {

	// パーティクルリストの削除
	for (PlayerParlicle* particle : particles_) {
		delete particle;
	}
}



// 初期化処理
void Player::Initialize() {

	// インプット
	input = Input::GetInstance();

	// モデル
	pla_.model = std::make_unique<Model>();
	pla_.model.reset(Model::Create("Resources/Player", "Player.obj"));
	pla_.model->SetLighting(false);

	// 座標
	init_.transform = {
		.scale = {0.2f, 0.2f, 0.2f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 1.2f, 0.0f},
	};
	pla_.transform = init_.transform;

	// 速度
	pla_.velocity = { 0.1f, 0.1f, 0.1f };

	// 回転量
	moveRotate_ = { 0.3f, 0.2f, 0.1f };

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

	// パーティクルのプッシュバックタイマー
	particlePushBackTimer_ = 0;
}



// 更新処理
void Player::Update() {

	// プレイヤーの各値の設定
	SetPlayerProperty();

	// 移動処理
	Move();

	// 重力の処理
	CalcGravity();

	// パーティクルの更新処理
	UpdateParticle();



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
	ImGui::End();

#endif // _DEBUG
}



// 描画処理
void Player::Draw() {

	pla_.model->Draw();
	for (PlayerParlicle* particle : particles_) {
		particle->Draw();
	}
}



// 衝突時コールバック処理
void Player::onCollisionToEnemy() {

	//gravity_.enable = false;
}
void Player::EndOverlapToEnemy() {

	//gravity_.enable = true;
}



// 移動処理
void Player::Move() {
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		//右
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			pla_.transform.translate.x += pla_.velocity.x;
		}
		//左
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			pla_.transform.translate.x -= pla_.velocity.x;
		}
	}

	// 左右移動処理
	if (input->IsPushKey(DIK_A) || input->IsPushKey(DIK_LEFT)) {

		pla_.transform.translate.x -= pla_.velocity.x;
	}
	if (input->IsPushKey(DIK_D) || input->IsPushKey(DIK_RIGHT)) {

		pla_.transform.translate.x += pla_.velocity.x;
	}

	// 無駄な回転処理
	pla_.transform.rotate = Add(pla_.transform.rotate, moveRotate_);


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



// スフィアの計算
void Player::CalcSphere() {

	plaSphere_ = {
		.center = pla_.transform.translate,
		.radius = pla_.size.x,
	};
}



// いろいろ設定する
void Player::SetPlayerProperty() {

	// モデルの設定
	pla_.model->SetColor(pla_.color);
	pla_.model->SetScale(pla_.transform.scale);
	pla_.model->SetRotate(pla_.transform.rotate);
	pla_.model->SetTranslate(pla_.transform.translate);

	// スフィアの計算
	CalcSphere();
}



// パーティクルの更新処理
void Player::UpdateParticle() {

	particlePushBackTimer_++;

	if (particlePushBackTimer_ >= 3) {

		// 0に戻す
		particlePushBackTimer_ = 0;

		// パーティクルの登録
		PushBackParticles();
	}

	// 更新処理
	for (PlayerParlicle* particle : particles_) {
		particle->Update();
	}

	// 描画フラグが切れたら削除
	particles_.remove_if([](PlayerParlicle* particle) {
		if (!particle->IsDrawing()) {
			delete particle;
			return true;
		}
		return false;
		}
	);
}



// プレイヤーパーティクルのプッシュバク処理
void Player::PushBackParticles() {

	// パーティクルを生成
	PlayerParlicle* newParticle = new PlayerParlicle();

	Vector3 min = Subtract(pla_.transform.translate, pla_.size);
	Vector3 max = Add(pla_.transform.translate, pla_.size);
	float val = 0.35f;

	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	std::uniform_real_distribution<float> distributionX(min.x, max.x);
	std::uniform_real_distribution<float> distributionY(min.y, max.y);
	std::uniform_real_distribution<float> distributionZ(min.z, max.z - val);
	Vector3 particlePos = {
		.x = distributionX(randomEngine),
		.y = distributionY(randomEngine),
		.z = distributionZ(randomEngine),
	};
	newParticle->Initialize(particlePos);

	// パーティクルを登録する
	particles_.push_back(newParticle);

}


