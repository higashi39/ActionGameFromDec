#pragma once

#include "../../../System/Vector3.h"
#include "../CharacterBase.h"

class FenceBase;

//---------------------------------------------------------------------------------
//	村人(保護対象)クラス
//---------------------------------------------------------------------------------
class Villager : public CharacterBase
{
protected:
	// ステータス情報
	enum class VillagerStatus
	{
		Idle,				// 待機
		FollowPlayer,		// プレイヤーに付いていく
		Damaged,			// 攻撃を受ける
		GoalPoint,			// 目的地に到達
		Reached,			// 到達済み
		KnockDown			// ダウン 
	};
	VillagerStatus villager_status = VillagerStatus::Idle;		// ステータス情報
public:
	int GetterVillagerStatus() const;
	int value = static_cast<int>(villager_status);
private:
	// ステータス状態を設定する
	void SetterStatus(VillagerStatus status);

public:
	// コンストラクタ
	// handle	: モデルハンドル
	// pos		: 自身の位置
	// id		: 自身の通し番号
	Villager(int handle, Vector3 pos, int id);
	~Villager();

	// 更新
	void Update() override;
	// 描画
	void Render() override;

	// マネージャでもらったプレイヤーの位置を取得する
	// p_pos : プレイヤーの位置
	void SetPlayerInfomation(const Vector3& p_pos);

	// 追いかけるオブジェクトを探す
	// pos : 追いかける対象の位置
	void SearchPlayer(Vector3 pos);

	// プレイヤーに追従するかのフラグ
	// flag : true  - 追従する
	//		: false - 追従しない 
	void IsAlwaysFollow(bool flag);

	// 指定した位置まで移動させる
	// vec : 指定する位置
	void FollowObject(Vector3 vec);

	// ゴールに到達したときの処理
	void GoalAction();

	//void SearchOtherVillagers(const std::vector<Vector3> v_poss);


	void SetFenceInfo(std::vector<FenceBase*> f_objs);

	//---------------------------------
	// ゲッター関数

	// 自身のIDを渡す
	int GetterMyID() const;
	// 自身の敵との接触状態を渡す
	bool GetterIsCollidingWithEnemy() const;
	// 自身が目的地に到達したかどうかを渡す
	bool GetterIsGoal() const;

	// １フレーム前の位置を渡す
	Vector3 GetterMyBeforePosition() const;

	//---------------------------------
	// セッター関数

	// 自身の位置を設定する
	// set_pos : 設定する位置
	void SetterMyPosition(Vector3 set_pos);
	// 敵との接触状態を設定する
	void SetterIsHitEnemy(bool ishit);
	// 村人同士の接触状態を設定する
	void SetterIsHitVillager(bool ishit);
	//---------------------------------

	int add_time_ = 0;

private:
	int my_id_;		// 村人(保護対象)自身のID

	Vector3 before_pos_;

	Vector3 player_position_;			// プレイヤー座標格納用
	Vector3 vector_with_player_;		// 自身とプレイヤーのベクトル
	float length_with_player_;			// プレイヤーとの距離
	bool is_player_follow_;				// プレイヤーについていくかどうか

	// 当たり判定関係
	// 接触しているかどうか
	bool ishit_enemy_ = false;		// 敵
	bool ishit_fence_ = false;		// 柵
	bool ishit_villager_ = false;	// 村人

	bool is_search_ = true;				// プレイヤーを探索するかどうか
	bool is_goal_ = false;				// ゴールしたかどうか

	bool is_render_ = true;			// 描画するかどうか

	// 他オブジェクト情報格納用変数
	std::vector<FenceBase*> fences_;		// 柵
};
