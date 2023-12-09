#include <vector>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "Villager.h"

#include "../../Environment/Fence.h"

#include "../../../Other/StatusData.h"
#include "../../../System/Vector3.h"
#include "../../../System/Hit.h"

#define VILLAGER_MOV_SPEED	0.4f

#define FOLLOW_PLAYER_RANGE 30.0f
#define LOST_PLAYER_RANGE   40.0f

Villager::Villager(Vector3 pos, int id)
{

	// モデルデータ格納
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/villager/model/Mouse.mv1");

	// 各変数の設定(初期化)
	object_position_ = pos;	// 位置
	object_scale_.set(0.05f, 0.05f, 0.05f);		// 大きさ
	object_box_size_.set(3.0f, 0.0f, 3.0f);

	// 各private変数の設定
	// 自身のIDを取得
	my_id_ = id;
	player_position_.set(0.0f, 0.0f, 0.0f);
	vector_with_player_.set(0.0f, 0.0f, 0.0f);
	is_player_follow_ = false;

	is_colliding_with_enemy_ = false;

	//-------------------------------------
	// アニメーション関係
	// 初期設定

	float random = GetRandomStartFrame();

	// 自身のモデル情報を渡す
	FetchObjectModel(*object_model_);
	// キャラクターにつけたいアニメーション情報を設定する
	SettingAnimation({ {"idle", "data/villager/animation/Idle.mv1", 0, random, 0.5f},
					   {"runaway", "data/villager/animation/Runaway.mv1", 0, 0.0f, 0.5f},
					   {"runforgoal", "data/villager/animation/RunForGoal.mv1", 0, 0.0f, 0.5f},
					   { "death", "data/villager/animation/Death.mv1", 0, 0.0f, 0.5f } });
	// 自身のモデルに各アニメーションをアタッチする
	AttachAnimation();
}

Villager::~Villager()
{
	delete object_model_;
}

void Villager::Update()
{
	if (!is_render_) return;

	// １フレーム前の座標を保管しておく
	Vector3 before_pos;
	before_pos = object_position_;
	before_pos.y = 0.0f;

	switch (villager_status)
	{
	case VillagerStatus::Idle:			// 待機
		is_search_ = true;

		// アニメーション(待機中(立ち止まっている))
		PlayLoopAnimation("idle");

		break;
	case VillagerStatus::FollowPlayer:	// プレイヤーについていく
		is_search_ = true;

		// アニメーション(プレイヤー追尾)
		PlayLoopAnimation("runaway");
		break;
	case VillagerStatus::Damaged:		// 攻撃を受ける
		is_search_ = false;

		break;
	case VillagerStatus::GoalPoint:		// 目的地に到達
		is_search_ = false;

		// アニメーション(目的地に向かう)
		PlayLoopAnimation("runforgoal");
		// 目的地に到着したあとの処理をおこなう
		GoalAction();
		break;
	case VillagerStatus::KnockDown:		// ダウン
		is_search_ = false;

		// アニメーション(ダウン)
		PlayLoopAnimation("death");
		break;
	}

	if (is_goal_)
	{

	}
	else
	{
		// 一定の処理をしていないとき
		if (is_search_)
		{
			// 常にプレイヤーを探す
			SearchPlayer(player_position_);
		}
		if (is_player_follow_)
		{
			// ステータスを「プレイヤーについていく」にする
			SetterStatus(VillagerStatus::FollowPlayer);
		}
	}

	//if (is_player_follow_)
	//{
	//	is_walk_ = true;
	//}
	//else
	//{
	//	is_walk_ = false;
	//}

	//--------------------------------
	// 他オブジェクトとの当たり判定
	// ステージサイド
	// 左側
	if (CheckBoxHit3D(object_position_, object_box_size_, { -175.0f, 0.0f, 0.0f }, { 25.0f, 10.0f, 150.0f }))
	{
		Vector3 set_left = { -175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos, object_box_size_, set_left, set_size);
		object_position_.y = 0.0f;
	}
	// 右側
	if (CheckBoxHit3D(object_position_, object_box_size_, { 175.0f, 0.0f, 0.0f }, { 25.0f,10.0f,150.0f }))
	{
		Vector3 set_right = { 175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos, object_box_size_, set_right, set_size);
		object_position_.y = 0.0f;
	}

	// 柵
	for (auto& f_obj : fences_)
	{
		if (CheckBoxHit3D(object_position_, object_box_size_, f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize()))
		{
			object_position_ = HitCollision(object_position_, before_pos, object_box_size_,
				f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize());
			object_position_.y = 0.0f;
		}
	}

	// ゴール
	if (CheckBoxHit3D(object_position_, object_box_size_, { 0.0f, 0.0f, 165.0f }, { 25.0f, 5.0f, 15.0f }))
	{
		SetterStatus(VillagerStatus::GoalPoint);
	}

#if SHOW_DEBUG
	value = static_cast<int>(villager_status);
	printfDx("villager_status : %d\n", value);
#endif
}

void Villager::Render()
{
	if (!is_render_) return;

	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);
}

void Villager::SetPlayerInfomation(const Vector3& p_pos)
{
	player_position_.set(p_pos.x, p_pos.y, p_pos.z);
}

void Villager::SearchPlayer(Vector3 pos)
{
	// ２つの座標からベクトルを求める
	vector_with_player_ = CalculateTwoVector(pos, object_position_);

	// 長さを求める
	float length = CalculateVectorToLength(vector_with_player_);

	// 一定距離内にプレイヤーを見つけたら
	if (length < 5.0f)
	{
		Vector3 dir = vector_with_player_ * -1.0f;
		dir.SetLength(5.0f);

		object_position_ = pos + dir;
		object_position_.y = 0.0f;
	}
	// プレイヤーに接近したら、立ち止まるようにする
	else if (length < 7.0f)
	{
		// ステータスを「待機」にする
		SetterStatus(VillagerStatus::Idle);

		// フラグを立てる
		IsAlwaysFollow(0);
	}
	else if (length < FOLLOW_PLAYER_RANGE)
	{
		// プレイヤー向かわせる
		FollowObject(vector_with_player_);

		// フラグを立てる
		IsAlwaysFollow(1);
	}
	// 離れすぎてしまったら(視界内からいなくなった判定)
	else if (length > LOST_PLAYER_RANGE)
	{
		// ステータスを「待機」にする
		SetterStatus(VillagerStatus::Idle);

		IsAlwaysFollow(0);
	}
}

void Villager::IsAlwaysFollow(bool flag)
{
	is_player_follow_ = flag;
}

void Villager::FollowObject(Vector3 vec)
{
	//// ステータスを「プレイヤーについていく」にする
	//SetterStatus(VillagerStatus::FollowPlayer);

	// ベクトルの正規化
	vec.VSet(VNorm(vec.VGet()));

	// 移動する方向に向ける
	object_rotate_.y = atan2f(vec.x, vec.z);
	// プレイヤーに向かう
	object_position_.x += VILLAGER_MOV_SPEED * sinf(object_rotate_.y);
	object_position_.z += VILLAGER_MOV_SPEED * cosf(object_rotate_.y);
	object_position_.y = 0.0f;
}

void Villager::GoalAction()
{
	// ゴールフラグを立てる
	is_goal_ = true;
	// ステージ奥に向かわせる
	FollowObject({ 0.0f,0.0f,250.0f });
	if (object_position_.z >= 230.0f)
	{
		// 描画しないようにする
		is_render_ = false;
	}
}

void Villager::SetFenceInfo(std::vector<Fence*> f_objs)
{
	fences_ = f_objs;
}

int Villager::GetterMyID() const
{
	// 自身の識別IDを渡す
	return my_id_;
}

bool Villager::GetterIsCollidingWithEnemy() const
{
	return is_colliding_with_enemy_;
}

bool Villager::GetterIsGoal() const
{
	return is_goal_;
}

void Villager::SetterMyPosition(Vector3 set_pos)
{
	object_position_ = set_pos;
}

void Villager::SetterIsCollidingWithEnemy(bool is_colliding)
{
	is_colliding_with_enemy_ = is_colliding;
}

void Villager::SetterStatus(VillagerStatus status)
{
	villager_status = status;
}