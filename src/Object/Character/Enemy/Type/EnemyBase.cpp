#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <algorithm>

#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "../../Friend/VillagerManager.h"
#include "../../Friend/Villager.h"
#include "../../Friend/Player.h"

#include "../../../../System/Hit.h"
#include "../../../../Other/StatusData.h"

#include "EnemyBase.h"
#include "EnemySword.h"
#include "EnemyPatrol.h"

#define ENEMY_MOV_SPEED	0.1f
#define SEARCH_VILLAGER_RANGE 70.0f

EnemyBase::EnemyBase()
{
	my_id_ = 0;									// 自身の識別番号

	near_villager_ = NULL;						// 一番近い村人の情報格納用
	//minimum_length_.set(0.0f, 0.0f, 0.0f);	// 村人との距離
	minimum_position_.set(0.0f, 0.0f, 0.0f);	// 一番近い村人の位置格納用
	minimum_vector_.set(0.0f, 0.0f, 0.0f);		// 一番近い村人とのベクトル格納用

	//is_colliding_with_player_ = false;			// プレイヤーと接触しているかどうか

	is_enable_attack_ = false;;			// 攻撃処理が有効であるかどうか
	attack_cool_time_ = 0.0f;		// 攻撃のクールダウン時間

	fetch_player_position_.set(0.0f, 0.0f, 0.0f);
	fetch_villagers_.clear();

	// HP情報の初期化
	hp_.Init();
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Render()
{
	if (!hp_.IsSurvice())	return;

	// モデルの描画
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	// 自身の前方向のベクトルを取得
	Vector3 front;
	front.x = object_position_.x + 5.0f * std::sinf(object_rotate_.y);
	front.z = object_position_.z + 5.0f * std::cosf(object_rotate_.y);
	front.y = 0.0f;
	DrawSphere3D(VGet(front.x, 4.0f, front.z), 1.5f, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

	//	視野範囲がどのくらいかをわかりやすくするために線を2本描画
	Vector3 line;
	//	線の先の座標(NPCの向き＋10度の方向に長さ1000.0fだけ先の場所)
	line.x = object_position_.x + 1000.0f * sinf(object_rotate_.y + TO_RADIAN(30.0f));
	line.z = object_position_.z + 1000.0f * cosf(object_rotate_.y + TO_RADIAN(30.0f));
	line.y = 5.0f;
	DrawLine3D(object_position_.VGet(), line.VGet(), GetColor(255, 128, 128));

	line.x = object_position_.x + 1000.0f * sinf(object_rotate_.y - TO_RADIAN(30.0f));
	line.z = object_position_.z + 1000.0f * cosf(object_rotate_.y - TO_RADIAN(30.0f));
	line.y = 5.0f;
	DrawLine3D(object_position_.VGet(), line.VGet(), GetColor(255, 128, 128));

}

void EnemyBase::RenderFor2D()
{
	// HP情報の描画
	hp_.Render();
}

void EnemyBase::SearchVillagers()
{
	// 全村人(保護対象)の中で、最も距離が短い村人を取得する
	float minimum_length = 10000.0f;
	for (auto& v_obj : fetch_villagers_)
	{
		// ２つの座標からベクトルを求める
		Vector3 vector_with_villager_;
		vector_with_villager_ = CalculateTwoVector(v_obj->GetterMyPosition(), object_position_);

		// 長さを求める
		float length = CalculateVectorToLength(vector_with_villager_);

		// 最も近い距離を更新する
		if (minimum_length > length)
		{
			near_villager_ = v_obj;
			minimum_length = length;
			minimum_position_ = v_obj->GetterMyPosition();
			minimum_vector_ = vector_with_villager_;
		}
	}
	
	// おそらくここの処理をSearchVillagerと分けて考えないといけない
	// 当たり判定(村人にめり込まないようにする)
	if (CheckHitPointToCircle(near_villager_->GetterMyPosition(), object_position_, 5.0f))
	{
		//// 村人との接触フラグを立てる
		//near_villager_->SetterIsCollidingWithEnemy(true);
		
		// 敵の前方にいたら
		// 敵ステータスを「村人に攻撃」にする
		enemy_status = EnemyStatus::Attack;

		Vector3 dir = minimum_vector_ * -1.0f;
		dir.SetLength(5.0f);

		object_position_ = minimum_position_ + dir;
	}
	//else
	//{
	//	//// 村人と接触はしていないが。
	//	//// 索敵範囲内に村人がいたら一番近い村人を追尾する
	//	//if (minimum_length < SEARCH_VILLAGER_RANGE)
	//	//{
	//	//	//// ステータスを追尾に
	//	//	//SetterStatus(EnemyStatus::TrackingVillger);
	//	//	// 追尾処理
	//	//	ChaseNearVillager(minimum_vector_);
	//	//}
	//}
	//// 一定以上の距離があいてしまったら、追いかけるのをやめる
	//if (minimum_length > 100.0f)
	//{
	//	// ステータスを「待機」にする
	//	SetterStatus(EnemyStatus::Idle);
	//}
}

void EnemyBase::ChaseNearVillager(Vector3 near_vec)
{
	// ベクトルの正規化
	near_vec.VSet(VNorm(near_vec.VGet()));

	// 移動する方向に向ける
	object_rotate_.y = atan2f(near_vec.x, near_vec.z);
	// 村人に向かう
	object_position_.x += 0.05f * sinf(object_rotate_.y);
	object_position_.z += 0.05f * cosf(object_rotate_.y);
}

void EnemyBase::EnemyAttack(std::vector<Villager*>& v_objs_)
{
	for (auto& v_obj : v_objs_)
	{
		if (v_obj->GetterIsCollidingWithEnemy())
		{
			//// 課題☆ : 後ほどクールダウンを作成して、攻撃の間隔を空ける
			//v_obj->hp_.SetterIsDamaged(true, 20.0f);
			// 攻撃クールダウンのカウントを開始する
			is_enable_attack_ = false;
		}
	}
}

void EnemyBase::EnemyCountAttackCoolTime()
{
	attack_cool_time_++;
	if (attack_cool_time_ > 120.0f)
	{
		is_enable_attack_ = true;
		attack_cool_time_ = 0.0f;
	}
}

bool EnemyBase::IsViewRange()
{
	// 自身の前方向のベクトルを取得
	Vector3 front;
	front.x = 1.0f * sinf(object_rotate_.y);
	front.z = 1.0f * cosf(object_rotate_.y);
	front.y = 0.0f;

	// 村人(一番近い)へのベクトル
	Vector3 target = minimum_vector_;
	target.normalize();

	// 内積を求める
	float front_dot = VDot(front.VGet(), target.VGet());
	// 2つのベクトルのなす角を求める
	// 一定の範囲(今回の場合、-1.0f~1.0f)に収めるためにstd::clampを使用する
	float target_angle = acosf(std::clamp(front_dot, -1.0f, 1.0f));

	// この求めたNPCから見てプレイヤーまでの角度が視野角内かどうか
	// 視野角もある一定範囲のみする
	//printfDx("target_angle : %f\n", target_angle);
	if (target_angle < TO_RADIAN(30.0f)
		&& CalculateVectorToLength(minimum_vector_) <= SEARCH_VILLAGER_RANGE)
	{
		return true;
	}

	return false;
}

void EnemyBase::SetterIsDamageToPlayer(bool is_enable)
{
	is_enable_damage_ = is_enable;
}

int EnemyBase::GetterMyID() const
{
	return my_id_;
}

void EnemyBase::SetterMyPosition(Vector3 set_pos)
{
	object_position_ = set_pos;
}


void EnemyBase::FetchPlayerPosition(const Vector3& pos)
{
	// プレイヤーの位置をもらう
	fetch_player_position_ = pos;
}

void EnemyBase::FetchVillagersPosition(const std::vector<Villager*>& v_objs)
{
	// 村人の情報をもらう
	fetch_villagers_ = v_objs;
}

void EnemyBase::SetterStatus(EnemyStatus status)
{
	enemy_status = status;
}

//void EnemyBase::HitOtherEnemy()
//{
//	//--------------------------------
//	// 他オブジェクトとの当たり判定
//
//	// 他の敵との当たり判定処理
//	for (auto& obj : enemies_)
//	{
//		// 自分自身か自分の識別番号よりも小さい敵は見ない(重複防止)
//		if (e_obj->GetterMyID() <= obj->GetterMyID())
//		{
//			continue;
//		}
//
//		Vector3 vec;
//		vec = CalculateTwoVector(e_obj->GetterMyPosition(), obj->GetterMyPosition());
//		float len = CalculateVectorToLength(vec);
//
//		if (len < 5.0f)
//		{
//			Vector3 dir = vec * -1.0f;
//			dir.SetLength(5.0f);
//
//			obj->SetterMyPosition(e_obj->GetterMyPosition() + dir);
//		}
//	}
//}