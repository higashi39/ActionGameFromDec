#pragma once
#include <vector>
#include "../../../System/Vector3.h"
class Fence;
class Villager;
class Player;

//---------------------------------------------------------------------------------
//	村人マネージャクラス
//---------------------------------------------------------------------------------
class VillagerManager
{
public:
	VillagerManager();
	~VillagerManager();

	// 村人を生成する
	// pos    : スポーンされる位置
	void SpawnVillager(Vector3 pos);

	// 自分以外の村人(保護対象)の位置を返す
	// my_id : 自分の識別ID
	//std::vector<Villager> FetchOtherVillagers(int my_id);

	// 更新
	// p_pos       : プレイヤーの位置
	void Update(const Vector3& p_pos);
	// 描画
	void Render();

	// 他村人オブジェクトとの当たり判定
	void HitOtherVillagers();

	// 柵の情報をもらう
	void FetchFenceInfo(const std::vector<Fence*>& f_objs);

	//---------------------------------
	// ゲッター関数

	// 全村人(保護対象)の各情報を渡す
	//// ID
	//std::vector<int> GetterVillagersID() const;
	// 全情報を渡す
	std::vector<Villager*> GetterVillagers() const;
	
	// 目的地に到達した村人の総数を渡す
	int GetterGoalVillager() const;

	//---------------------------------

private:
	int set_id_num_ = 0;		// 通し番号設定用

	int villagersgoal_num = 0;	// 目的地に到達した村人の総数

	std::vector<Villager*> villagers_;			// 全村人の格納配列
	// 他オブジェクト情報格納用変数
	std::vector<Fence*> fences_;				// 柵
};
