#pragma once
#include "../../../System/Vector3.h"
class VillagerManager;

//---------------------------------------------------------------------------------
//	村人(保護対象)スポナークラス
//---------------------------------------------------------------------------------
class VillagerSpawner
{

public:
	VillagerSpawner(Vector3& m_pos);
	~VillagerSpawner() {};

	//// 村人(保護対象)マネージャの生成
	//void CreateVillagerManager();

	// のちに削除予定
	// 更新
	void Update();
	// 描画
	void Render();

protected:
	VillagerManager* villager_manage;

	Vector3 villager_spawner_position_;
};