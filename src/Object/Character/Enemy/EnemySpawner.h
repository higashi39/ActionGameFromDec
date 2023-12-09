#pragma once
#include "../../../System/Vector3.h"
class EnemyManager;

//---------------------------------------------------------------------------------
//	敵スポナークラス
//---------------------------------------------------------------------------------
class EnemySpawner
{

public:
	EnemySpawner(Vector3& m_pos);
	~EnemySpawner() {};

	//// 敵マネージャの生成
	//void CreateEnemyManager();

	// のちに削除予定
	// 更新
	void Update();
	// 描画
	void Render();

protected:
	EnemyManager* enemy_manage;

	Vector3 enemy_spawner_position_;
};