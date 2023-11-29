#include "EnemyApproachState.h"
#include "Object/Enemy/Enemy.h"


// 接近処理
void EnemyApproachState::Move(Enemy* pEnemy) {

	// プレイヤーとのベクトル
	Vector3 toPlayer = {
		.x = pEnemy->GetPlayerPos().x - pEnemy->GetTransform().translate.x,
		.y = (pEnemy->GetPlayerPos().y + 4.0f) - pEnemy->GetTransform().translate.y,
		.z = pEnemy->GetPlayerPos().z - pEnemy->GetTransform().translate.z,
	};

	// プレイヤーとの距離
	float length = sqrt(
		(toPlayer.x * toPlayer.x) + 
		(toPlayer.y * toPlayer.y) + 
		(toPlayer.z * toPlayer.z));

	// ベクトルとレングスを使った速度設定
	Vector3 vel = {
		.x = toPlayer.x / length * pEnemy->GetMove(),
		.y = toPlayer.y / length * pEnemy->GetMove(),
		.z = toPlayer.z / length * pEnemy->GetMove(),
	};

	// 移動処理
	pEnemy->SetTranslate(Add(pEnemy->GetTransform().translate, vel));

	// プレイヤーの上についたら、ステートチェンジ
	if (length <= 0.0f) {

		// -> 徘徊ステートへ
		pEnemy->ChangeMoveState(new EnemyWanderingState);
	}
}