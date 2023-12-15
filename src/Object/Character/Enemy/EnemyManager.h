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
	// handle		: モデルハンドル
	// pos			: スポーンされる位置
	// rot			: スポーンされたときの向き
	// type			: 敵の種類
	// patrol_pos1　: 巡回折り返し地点１（敵（巡回型）のみ）
	// patrol_pos2　: 巡回折り返し地点２（敵（巡回型）のみ）
	void SpawnEnemy(int handle, int type, Vector3 pos, Vector3 rot, Vector3 patrol_pos1, Vector3 patrol_pos2);

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
