#include <ctime>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "EnemySpawner.h"
#include "EnemySpawnerManager.h"

#include "../../../System/Vector3.h"

EnemySpawnerManager::EnemySpawnerManager()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		enemy_spawner[i] = NULL;
	}
}

EnemySpawnerManager::~EnemySpawnerManager()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		delete enemy_spawner[i];
	}
}

void EnemySpawnerManager::CreateSpawner(Vector3 pos)
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		//// 設置されたスポナーの位置を取得
		//FetchSpawnerPosition();
		// スポナー位置をスポナー位置格納用に追加する
		spawner_positions_.emplace_back(pos);
		// 取得した位置に敵スポナーを生成
		enemy_spawner[i] = new EnemySpawner(spawner_positions_[i]);
	}
}

std::vector<Vector3> EnemySpawnerManager::GetterSpawnerPositions() const
{
	// 格納した敵のスポナーを全て渡す
	return spawner_positions_;
}

Vector3 EnemySpawnerManager::GetterSpawnerPosition() const
{
	// 敵のスポナーの0番目に格納された位置のみ渡す
	// ただし、スポナーの位置が１つも格納されていない場合は(0.0f, 0.0f, 0.0f)を渡す
	if (spawner_positions_.size() <= 0)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}
	return spawner_positions_[0];
}

void EnemySpawnerManager::Update()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		enemy_spawner[i]->Update();
	}
}

void EnemySpawnerManager::Render()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		enemy_spawner[i]->Render();
	}
}