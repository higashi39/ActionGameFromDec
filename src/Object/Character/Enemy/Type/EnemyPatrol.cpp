#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "EnemyPatrol.h"

#include "../../../../System/Hit.h"

EnemyPatrol::EnemyPatrol(Vector3 pos, int id)
{
	// モデルデーター格納
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/enemy02/model/Enemy02.mv1");

	// 各変数の設定(初期化)
	object_position_ = pos;	// 位置
	object_scale_.set(0.05f, 0.05f, 0.05f);	// 大きさ

	patrol_pos1_.set(0.0f, 0.0f, 0.3f);
	patrol_pos2_.set(0.0f, 0.0f, 10.0f);
	object_position_ = patrol_pos1_;	// 位置
	check_patrol_ = 0;
	turn_cool_time_ = 0.0f;

	my_id_ = id;

	//-------------------------------------
	// アニメーション関係
	// 初期設定

	// 自身のモデル情報を渡す
	FetchObjectModel(*object_model_);
	// キャラクターにつけたいアニメーション情報を設定する
	SettingAnimation({ {"idle", "data/enemy01/animation/Idle.mv1", 0, 0.0f, 0.3f},
		});
	// 自身のモデルに各アニメーションをアタッチする
	AttachAnimation();

	// HP情報の初期化
	hp_.Init();
}

EnemyPatrol::~EnemyPatrol()
{
	delete object_model_;
}

//// 最初は索敵状態にしておく
//*enemy_status_ = ENEMYSTATUS::ENEMY_SEARCH;

void EnemyPatrol::Update()
{
	// 生存フラグが立っていなければ、以降の更新処理は行わない
	if (!hp_.IsSurvice())	return;

	// HP情報の更新処理
	hp_.Update(object_position_, 12.0f);

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
		// ステータスを「待機(巡回)」にする
		enemy_status = EnemyStatus::Idle;
		// 巡回する
		PatrolAction();
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

	//---------------------------------------
	// ダメージ処理
	if (is_enable_damage_)
	{
		// ステータスを「攻撃を受ける」にする
		enemy_status = EnemyStatus::Damage;
		// HPを減らす
		hp_.SetterIsDamaged(10.0f);
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
		break;
	case EnemyStatus::Damage:
		break;
	case EnemyStatus::KnockDown:
		break;
	}

	value = static_cast<int>(enemy_status);

#if SHOW_DEBUG
	//printfDx("pos : %f, %f, %f\n", object_position_.x, object_position_.y, object_position_.z);
	//printfDx("turn_cool_time_ : %f\n", turn_cool_time_);
	//printfDx("status : %d\n", value);
#endif
}

void EnemyPatrol::PatrolAction()
{
	Vector3 distance;

	// ベクトルを求める
	// 現在自身がいないほうの位置に向けてベクトルをのばす
	if (check_patrol_ == 0)
	{
		// その折り返し地点に近づいたら、もう１つの地点に折り返す
		if (CheckHitPointToCircle(object_position_, patrol_pos2_, 0.5f))
		{
			object_position_.set(patrol_pos2_);

			check_patrol_ = 1;
		}
		else
		{
			// patrol_pos1_に向けて
			distance = CalculateTwoVector(patrol_pos2_, object_position_);
		}
	}
	else if (check_patrol_ == 1)
	{
		// その折り返し地点に近づいたら、もう１つの地点に折り返す
		if (CheckHitPointToCircle(object_position_, patrol_pos1_, 1.0f))
		{
			object_position_.set(patrol_pos1_);

			check_patrol_ = 0;
		}
		else
		{
			// patrol_pos2_に向けて
			distance = CalculateTwoVector(patrol_pos1_, object_position_);
		}
	}

	// 長さを求める
	float length = CalculateVectorToLength(distance);

	// ベクトルの正規化
	distance.VSet(VNorm(distance.VGet()));

	// 移動する方向に向ける
	object_rotate_.y = atan2f(distance.x, distance.z);
	// 村人に向かう
	object_position_.x += 0.05f * sinf(object_rotate_.y);
	object_position_.z += 0.05f * cosf(object_rotate_.y);
}