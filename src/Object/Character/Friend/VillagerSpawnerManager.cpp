#include <ctime>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "VillagerSpawner.h"
#include "VillagerSpawnerManager.h"

#include "../../../System/Vector3.h"

VillagerSpawnerManager::VillagerSpawnerManager()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		villager_spawner[i] = NULL;
	}
}

VillagerSpawnerManager::~VillagerSpawnerManager()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		delete villager_spawner[i];
	}
}

void VillagerSpawnerManager::CreateSpawner(Vector3 pos)
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		// 設定されたスポナーの位置を取得
		//FetchSpawnerPosition();
		// スポナー位置をスポナー位置格納用に追加する
		spawner_positions_.emplace_back(pos);
		// 取得した位置に村人スポナーを生成
		villager_spawner[i] = new VillagerSpawner(spawner_positions_[i]);
	}
}

std::vector<Vector3> VillagerSpawnerManager::GetterSpawnerPositions() const
{
	// 格納した村人(保護対象)のスポナーを全て渡す
	return spawner_positions_;
}

Vector3 VillagerSpawnerManager::GetterSpawnerPosition() const
{
	// 村人(保護対象)のスポナーの0番目に格納された位置のみ渡す
	// ただし、スポナーの位置が１つも格納されていない場合は(0.0f, 0.0f, 0.0f)を渡す
	if (spawner_positions_.size() <= 0)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}
	return spawner_positions_[0];
}

void VillagerSpawnerManager::Update()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		villager_spawner[i]->Update();
	}
}

void VillagerSpawnerManager::Render()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		villager_spawner[i]->Render();
	}
}