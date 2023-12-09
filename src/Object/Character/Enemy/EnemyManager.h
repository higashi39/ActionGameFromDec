#pragma once
#include <vector>
#include "../../../System/Vector3.h"
class EnemySword;
class EnemyPatrol;
class VillagerManager;
class Villager;

//---------------------------------------------------------------------------------
//	敵マネージャクラス
//---------------------------------------------------------------------------------
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	// 敵を生成する
	// pos    : スポーンされる位置
	// type   : 敵の種類
	void SpawnEnemy(int type, Vector3 pos);

	// 更新
	void Update(const Vector3& p_pos, const std::vector<Villager*>& v_objs);
	// 描画
	void Render();
	// 各敵オブジェクトの2D描画処理
	void RenderFor2D();

	// 他敵オブジェクトとの当たり判定
	void HitOtherEnemies();

	//---------------------------
	// ゲッター関数

	// 全敵オブジェクト情報を渡す
	std::vector<EnemyBase*> GetterEnemies() const;
	//// 全村人(保護対象)情報を渡す
	//std::vector<Villager*> GetterVillagers() const;

protected:
	int set_id_num_ = 0;		// 通し番号設定用

	std::vector<EnemyBase*> enemies_;		// 全敵の格納配列
};
