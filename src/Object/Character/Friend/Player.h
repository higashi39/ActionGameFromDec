#pragma once
#include <vector>
#include "../CharacterBase.h"
//#include "../../../Other/ScreenHPInfo.h"
class EnemyBase;
class FenceBase;

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public CharacterBase
{
private:
	// ステータス情報
	enum class PlayerStatus
	{
		Idle,					// 待機
		Run,					// 移動(走る)
		Attack,					// 攻撃
		Damage,					// 攻撃を受ける
		KnockDown,				// ダウン
	};
private:
	PlayerStatus player_status = PlayerStatus::Idle;	// ステータス情報
	//int value = static_cast<int>(player_status);
	//// ステータス状態を設定する
	void SetterStatus(PlayerStatus status);

public:
	Player();
	~Player() {};

	// プレイヤー専用更新
	void Update() override;
	// 描画
	void Render() override;
	// 2D用描画処理
	void RenderFor2D();

	// 攻撃処理(対敵)
	void PlayerAttack(EnemyBase* e_obj);

	// クールタイム時間カウント処理
	void PlayerCountAttackCoolTime();

	// 全敵の情報を取得
	void FetchEnemyInfo(const std::vector<EnemyBase*>& e_objs);
	// 柵の情報を取得する
	void FetchFenceInfo(const std::vector<FenceBase*>& f_objs);

	//--------------------------
	// ゲッター関数

	// モデルデータのポインタを渡す
	int* GetterPlayerModelPointer();
	// ステータス状態を渡す
	PlayerStatus GetterPlayerStatus();

	// セッター関数

	// 敵と接触したかどうかを設定する
	// is_hit : 接触したかどうかのフラグ
	void SetterIsHitEnemy(bool is_hit);

	// 全敵の情報を確認する
	bool CheckHitEnemy();

private:

	std::vector<EnemyBase*> enemy_objs_;			// 敵の情報を格納する配列
	std::vector<FenceBase*> fence_objs_;				// 柵の情報を格納する配列

	bool is_enable_attack_;			// 攻撃処理が有効であるかどうか
	float attack_cool_time_;		// 攻撃のクールダウン時間

	bool is_enable_spacekey_ = false;		// スペースキーを押したかどうか

//protected:
//	// HP情報
//	ScreenHPInfo hp_;
};
