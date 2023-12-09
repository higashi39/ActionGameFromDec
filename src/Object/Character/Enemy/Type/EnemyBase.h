#pragma once
#include <vector>
#include "../../CharacterBase.h"
#include "../../../../System/Vector3.h"
#include "../../../../Other/CharaHeadHPInfo.h"

class EnemySword;
class EnemyPatrol;
class VillagerManager;
class Villager;
class Player;

//---------------------------------------------------------------------------------
//	敵マネージャクラス
//---------------------------------------------------------------------------------
class EnemyBase : public CharacterBase
{
public:
	// ステータス情報
	enum EnemyStatus
	{
		Idle,				// 待機(巡回)
		SearchingVillager,	// 村人索敵中
		TrackingVillger,	// 村人追尾
		Attack,				// 攻撃
		Damage,				// 攻撃を受ける
		KnockDown			// ダウン
	};
protected:
	EnemyStatus enemy_status = EnemyStatus::Idle;		// ステータス情報

	//デバッグ用
	int value = static_cast<int>(enemy_status);
	// 敵のステータスを設定する
	void SetterStatus(EnemyStatus status);

public:
	EnemyBase();
	~EnemyBase();

	// 更新
	// それぞれの敵で異なる処理なので、純粋仮想関数にする
	virtual void Update() = 0;
	// 描画
	void Render();
	// 2D用描画処理
	// 主にHP(Render関数で処理すると正しく描画されない)
	void RenderFor2D();

	// 村人を探す
	void SearchVillagers();

	// 村人を追跡する
	// near_vec : 一番近い距離の村人とのベクトル
	void ChaseNearVillager(Vector3 near_vec);

	// 攻撃処理(対村人(保護対象))
	void EnemyAttack(std::vector<Villager*>& v_objs_);
	// 攻撃のクールダウン時間カウント処理
	void EnemyCountAttackCoolTime();

	//// 各敵オブジェクトのHP描画処理
	//void EnemyHPRender();
	// 
	// 視野範囲の処理
	bool IsViewRange();


	//---------------------------------
	// ゲッター関数

	// 自身のIDを渡す
	int GetterMyID() const;

	//// 自身とプレイヤーとの接触状態を渡す
	//bool GetterIsCollisionWithPlayer() const;
	//// 自身と村人(保護対象)との接触状態を渡す
	//bool GetterIsCollisionWithVillager() const;

	//---------------------------------
	// セッター関数

	// 自身の位置を設定する
	// set_pos : 設定する位置
	void SetterMyPosition(Vector3 set_pos);

	// HPを減らすフラグを立てる
	// is_enable : ダメージ処理を行ってもいいか
	void SetterIsDamageToPlayer(bool is_enable);


	// 他キャラクターの位置をもらう
	// プレイヤー
	void FetchPlayerPosition(const Vector3& pos);
	// 村人
	void FetchVillagersPosition(const std::vector<Villager*>& v_objs);

protected:
	int my_id_;							// 自身の識別番号

	Villager* near_villager_;			// 一番近い村人の情報格納用
	//float minimum_length_ = 10000.0f;			// 村人との距離
	Vector3 minimum_position_;			// 一番近い村人の位置格納用
	Vector3 minimum_vector_;			// 一番近い村人とのベクトル格納用

	//bool is_colliding_with_player_;			// プレイヤーと接触しているかどうか

	bool is_enable_attack_;			// 攻撃処理が有効であるかどうか
	float attack_cool_time_;		// 攻撃のクールダウン時間

	Vector3 fetch_player_position_;
	std::vector<Villager*> fetch_villagers_;

	bool is_enable_damage_ = false;		// ダメージを受けるどうか

protected:
	// HP情報
	CharaHeadHPInfo hp_;
};
