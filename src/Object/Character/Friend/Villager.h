#pragma once

#include "../../../System/Vector3.h"
#include "../CharacterBase.h"

class Fence;

//---------------------------------------------------------------------------------
//	村人(保護対象)クラス
//---------------------------------------------------------------------------------
class Villager : public CharacterBase
{
private:
	// ステータス情報
	enum class VillagerStatus
	{
		Idle,				// 待機
		FollowPlayer,		// プレイヤーに付いていく
		Damaged,			// 攻撃を受ける
		GoalPoint,			// 目的地に到達
		KnockDown			// ダウン 
	};
private:
	VillagerStatus villager_status = VillagerStatus::Idle;		// ステータス情報
	int value = static_cast<int>(villager_status);
	// ステータス状態を設定する
	void SetterStatus(VillagerStatus status);

public:
	// コンストラクタ
	// pos : 自身の位置
	// id  : 自身の通し番号
	Villager(Vector3 pos, int id);
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
	void SearchFollowObject(Vector3 pos);

	// プレイヤーに追従するかのフラグ
	// flag : true  - 追従する
	//		: false - 追従しない 
	void IsAlwaysFollow(bool flag);

	// プレイヤーに追従する
	// vec : プレイヤーとのベクトル
	void Follow(Vector3 vec);

	// ゴールに到達したときの処理
	void GoalAction();

	//void SearchOtherVillagers(const std::vector<Vector3> v_poss);


	void SetFenceInfo(std::vector<Fence*> f_objs);

	//---------------------------------
	// ゲッター関数

	// 自身のIDを渡す
	int GetterMyID() const;
	// 自身の敵との接触状態を渡す
	bool GetterIsCollidingWithEnemy() const;

	//---------------------------------
	// セッター関数

	// 自身の位置を設定する
	// set_pos : 設定する位置
	void SetterMyPosition(Vector3 set_pos);
	// 敵との接触状態を設定する
	void SetterIsCollidingWithEnemy(bool is_colliding);
	//---------------------------------

private:
	int my_id_;		// 村人(保護対象)自身のID

	Vector3 player_position_;			// プレイヤー座標格納用
	Vector3 vector_with_player_;		// 自身とプレイヤーのベクトル
	bool is_player_follow_;				// プレイヤーについていくかどうか

	bool is_colliding_with_enemy_;		// 敵と接触しているかどうか

	bool is_search_ = true;				// プレイヤーを探索するかどうか

	// 他オブジェクト情報格納用変数
	std::vector<Fence*> fences_;		// 柵
};
