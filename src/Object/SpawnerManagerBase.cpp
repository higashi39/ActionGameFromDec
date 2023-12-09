#include "../System/Random.h"

#include "../Main.h"
#include "../Scene/Game.h"
#include "SpawnerManagerBase.h"

SpawnerManagerBase::SpawnerManagerBase()
{
	get_position_.clear();
}

Vector3 SpawnerManagerBase::SetSpawnerPosition()
{
	int max = 10;			// 乱数最大値
	int min = -10;			// 乱数最小値

	// 乱数をX, Z座標の2つ分生成
	int rand_x = GetRandomF(max, min);
	int rand_z = GetRandomF(max, min);

	// 位置を設定する	(Y座標は0.0f固定)
	Vector3 set_pos;
	set_pos.x = rand_x;
	set_pos.z = rand_z;
	set_pos.y = 0.0f;

	// 乱数で設定した位置を返す
	return set_pos;
}

void SpawnerManagerBase::FetchSpawnerPosition()
{
	// ランダムに設定された位置を取得
	get_position_.set(SetSpawnerPosition().x, SetSpawnerPosition().y, SetSpawnerPosition().z);

	//// 取得した位置に村人スポナーを生成
	//villager_spawner[i] = new VillagerSpawner(rand_pos);
}

//void SpawnerManagerBase::Initialize()
//{
//}