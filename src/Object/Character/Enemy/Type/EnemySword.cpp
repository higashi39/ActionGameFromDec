#include <cmath>
#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "EnemySword.h"

#include "../../../../System/Hit.h"

EnemySword::EnemySword(int handle, Vector3 pos, Vector3 rot,int id)
{
	// モデルデーター格納
	object_model_ = new int;
	*object_model_ = MV1DuplicateModel(handle);

	// 各変数の設定(初期化)
	object_position_ = pos;	// 位置
	object_rotate_ = rot;	// 向き
	object_scale_.set(0.08f, 0.08f, 0.08f);	// 大きさ

	my_id_ = id;

	//-------------------------------------
	// アニメーション関係
	// 初期設定

	// 自身のモデル情報を渡す
	FetchObjectModel(*object_model_);
	// キャラクターにつけたいアニメーション情報を設定する
	SettingAnimation({ {"idle", "data/enemy02/animation/Idle.mv1", 0, 0.0f, 0.3f},
					   {"walk", "data/enemy02/animation/Walk.mv1", 0, 0.0f, 0.3f},
 					   {"attack", "data/enemy02/animation/Attack.mv1", 0, 0.0f, 0.3f},
		});
	// 自身のモデルに各アニメーションをアタッチする
	AttachAnimation();
}

EnemySword::~EnemySword()
{
	delete object_model_;
}

//// 最初は索敵状態にしておく
//*enemy_status_ = ENEMYSTATUS::ENEMY_SEARCH;

void EnemySword::Update()
{
	//// 生存フラグが立っていなければ、以降の更新処理を行わない
	//if (!hp_.IsSurvice())
	//{
	//	return;
	//}
	//// HP情報の更新処理
	//hp_.Update(object_position_, 10.0f);

	Hit();

	// 村人との距離を求めて、一番近い村人を求める
	SearchVillagers();

	// 視界内に村人が入ったら
	if (IsViewRange())
	{
		// 村人追尾状態になる
		SetterStatus(EnemyStatus::TrackingVillger);
		// 求めた一番近い村人を追尾する
		ChaseNearVillager(minimum_vector_);
	}
	else
	{

	}

	//------------------------------------
	// 他オブジェクトとの当たり判定
	// 柵
	// ☆課題：プレイヤーと柵との当たり判定のバグが解消したら作成

	// プレイヤー
	// ここで処理を行うと、プレイヤーが敵を押せてしまうので、
	// プレイヤーの方で処理することを検討する
	{
		Vector3 vec;
		vec = CalculateTwoVector(fetch_player_position_, object_position_);

		float len = CalculateVectorToLength(vec);

		// プレイヤーに接触したら
		if (len < 5.0f)
		{
			Vector3 dir = vec * -1.0f;
			// object_collision_size_よりも小さく設定することで当たり判定をシビアにしない
			dir.SetLength(5.0f);

			object_position_ = fetch_player_position_ + dir;
		}
	}



	// 攻撃直後であれば
	if (!is_enable_attack_)
	{
		// クールダウン時間をカウントする
		EnemyCountAttackCoolTime();
	}

	//---------------------------------------------------------
	// アニメーションの更新
	//---------------------------------------------------------
	// アニメーションの再生
	switch (enemy_status)
	{
	case EnemyStatus::Idle:
		break;
	case EnemyStatus::SearchingVillager:
		// 待機中(立ち止まっている)
		PlayLoopAnimation("idle");
		break;
	case EnemyStatus::TrackingVillger:
		// 移動中
		PlayLoopAnimation("walk");
		break;
	case EnemyStatus::Attack:
		// 攻撃
		PlayLoopAnimation("attack");
		break;
	case EnemyStatus::Damage:
		break;
	case EnemyStatus::KnockDown:
		break;
	}


#if SHOW_DEBUG
	value = static_cast<int>(enemy_status);
	//printfDx("hp : %d\n", hp_num_);
	printfDx("enemy_status : %d\n,",value);
#endif
}