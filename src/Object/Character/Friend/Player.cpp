#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include <cmath>

#include "Player.h"
#include "../Enemy/Type/EnemyBase.h"
#include "../../Environment/FenceBase.h"

#include "../../../Other/StatusData.h"
#include "../../../System/Hit.h"

#define PLAYER_MOV_SPEED	0.5f
#define PLAYER_ROT_SPEED	3.0f

Player::Player()
{
	// モデルデータ格納
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/player/model/Human.mv1");

	// 各変数の設定(初期化)
	object_position_.set(0.0f, 0.0f, -250.0f);		// 位置
	object_rotate_.y = TO_RADIAN(0.0f);			// 回転
	object_scale_.set(0.05f, 0.05f, 0.05f);		// 大きさ

	object_box_size_.set(3.0f, 3.0f, 3.0f);

	is_enable_attack_ = true;
	attack_cool_time_ = 0.0f;

	//is_enable_spacekey_ = false;

	//-------------------------------------
	// アニメーション関係
	// 初期設定

	// 自身のモデル情報を渡す
	FetchObjectModel(*object_model_);
	// キャラクターにつけたいアニメーション情報を設定する
	SettingAnimation({ {"idle",   "data/player/animation/Idle.mv1",			0, 0.0f, 1.0f},
					   {"run",   "data/player/animation/Run.mv1",			0, 0.0f, 1.0f},
					   {"attack", "data/player/animation/AttackSword.mv1",  0, 0.0f, 1.0f} });
	// 自身のモデルに各アニメーションをアタッチする
	AttachAnimation();

	//// HP情報の初期化
	//hp_.Init();
}

void Player::Update()
{
	// プレイヤーの１フレーム前の座標を保管しておく
	Vector3 before_pos;
	before_pos = object_position_;

	//// HP情報の更新
	//hp_.Update();

	//----------------------------------
	// キー操作

	// 回転
	if (CheckHitKey(KEY_INPUT_D))
	{
		// ラジアン角の3度増やす
		object_rotate_.y += TO_RADIAN(PLAYER_ROT_SPEED);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		object_rotate_.y -= TO_RADIAN(PLAYER_ROT_SPEED);
	}

	if (CheckHitKey(KEY_INPUT_W))					// 移動
	{
		SetterStatus(PlayerStatus::Run);

		// m_rot はラジアン角で計算しているから関数はそのまま渡す
		object_position_.x += PLAYER_MOV_SPEED * sinf(object_rotate_.y);
		object_position_.z += PLAYER_MOV_SPEED * cosf(object_rotate_.y);
	}
	else if (PushHitKey(KEY_INPUT_SPACE))		// スペースキーを押したら
	{
		// スペースキーを押したフラグを立てる
		is_enable_spacekey_ = true;

		//// プレイヤーの前方に敵がいたら
		//if(CheckHitPointToCircle())
		//// プレイヤー状態を「攻撃」に変更
		//SetterStatus(PlayerStatus::Attack);
	}
	else
	{
		SetterStatus(PlayerStatus::Idle);
	}

	// スペースキーが押されたフラグが立っていたら
	if (is_enable_spacekey_)
	{
		// 全敵の情報を取得する
		if (CheckHitEnemy())
		{

		}
		else
		{
			is_enable_spacekey_ = false;
		}
	}

	//--------------------------------
	// 他オブジェクトとの当たり判定
	// ステージサイド
	// 左側
	if (CheckBoxHit3D(object_position_, object_box_size_, { -175.0f, 0.0f, 0.0f }, { 25.0f, 10.0f, 150.0f }))
	{
		Vector3 set_left = { -175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos, object_box_size_, set_left, set_size);
	}
	// 右側
	if (CheckBoxHit3D(object_position_, object_box_size_, { 175.0f, 0.0f, 0.0f }, { 25.0f,10.0f,150.0f }))
	{
		Vector3 set_right = { 175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos, object_box_size_, set_right, set_size);
	}

	// 柵
	for (auto& f_obj : fence_objs_)
	{
		if (CheckBoxHit3D(object_position_, object_box_size_, f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize()))
		{
			object_position_ = HitCollision(object_position_, before_pos, object_box_size_,
				f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize());
		}
	}

	// 攻撃直後であれば
	if (!is_enable_attack_)
	{
		// クールダウン時間をカウントする
		PlayerCountAttackCoolTime();

	}

	//---------------------------------------------------------
	// アニメーションの更新
	//---------------------------------------------------------
	// アニメーションの再生
	switch (player_status)
	{
	case PlayerStatus::Idle:			// 待機中(立ち止まっている)
		PlayLoopAnimation("idle");
		break;
	case PlayerStatus::Run:			// 移動中
		PlayLoopAnimation("run");
		break;
	case PlayerStatus::Attack:			// 攻撃
		PlayOnceAnimation("attack");
		break;
	}

#if SHOW_DEBUG
	printfDx("player_pos : %f, %f\n", object_position_.x, object_position_.z);
#endif
}

void Player::Render()
{
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	// 自身のカプセル
	DrawCapsule3D(VGet(object_position_.x, 5.0f, object_position_.z),
		VGet(object_position_.x, 3.0f, object_position_.z), 3.0f, 8,
		GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);

	// 自身の前方向のベクトルを取得
	Vector3 front;
	front.x = object_position_.x + 5.0f * std::sinf(object_rotate_.y);
	front.z = object_position_.z + 5.0f * std::cosf(object_rotate_.y);
	front.y = 0.0f;
	DrawSphere3D(VGet(front.x, 4.0f, front.z), 1.5f, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

void Player::RenderFor2D()
{
	//hp_.Render();
}

void Player::PlayerAttack(EnemyBase* e_obj)
{
	// プレイヤー状態を「攻撃」にする
	player_status = PlayerStatus::Attack;

	// プレイヤーがクールダウン中でなかったら
	if (is_enable_attack_)
	{
		e_obj->SetterIsDamageToPlayer(true);
		is_enable_spacekey_ = false;
	}
}

void Player::PlayerCountAttackCoolTime()
{
	attack_cool_time_++;
	if (attack_cool_time_ > 120.0f)
	{
		is_enable_attack_ = true;
		attack_cool_time_ = 0.0f;
	}
}

void Player::FetchEnemyInfo(const std::vector<EnemyBase*>& e_objs)
{
	enemy_objs_ = e_objs;
}

void Player::FetchFenceInfo(const std::vector<FenceBase*>& f_objs)
{
	fence_objs_ = f_objs;
}

bool Player::CheckHitEnemy()
{
	// 自身の前方向のベクトルを取得
	Vector3 front;
	front.x = object_position_.x + 5.0f * std::sinf(object_rotate_.y);
	front.z = object_position_.z + 5.0f * std::cosf(object_rotate_.y);
	front.y = 0.0f;

	// プレイヤーの前方と各敵の当たり判定を見る
	for (auto& obj : enemy_objs_)
	{
		if (CheckHitPointToCircle(obj->GetterMyPosition(), front, 1.5f))
		{
			// プレイヤーの攻撃処理(ダメージを与える敵を設定する)
			PlayerAttack(obj);

			return true;
		}
	}
	return false;
}

int* Player::GetterPlayerModelPointer()
{
	return object_model_;
}

Player::PlayerStatus Player::GetterPlayerStatus()
{
	return player_status;
}

void Player::SetterStatus(PlayerStatus status)
{
	player_status = status;
}

void Player::SetterIsHitEnemy(bool is_hit)
{

}