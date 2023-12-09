#pragma once
#include <vector>
#include "../../SpawnerManagerBase.h"
class VillagerSpawner;
#include "../../../System/Vector3.h"

#define VILLAGER_SPAWNER_NUM  1

//---------------------------------------------------------------------------------
//	村人(保護対象)スポナーマネージャクラス
//---------------------------------------------------------------------------------
class VillagerSpawnerManager : public SpawnerManagerBase
{

public:
	VillagerSpawnerManager();
	~VillagerSpawnerManager();

	// スポナーを生成する
	void CreateSpawner(Vector3 pos) override;
	// スポナーの生成位置を渡す
	Vector3 GetterSpawnerPosition() const override;
	// 全スポナーの位置を格納した変数を渡す
	std::vector<Vector3> GetterSpawnerPositions() const override;

	// のちに削除
	// 更新
	void Update() override;
	// 描画
	void Render() override;

private:
	// ポインタで情報を取得
	VillagerSpawner* villager_spawner[VILLAGER_SPAWNER_NUM];	// 村人(保護対象)のスポナー管理

	//std::vector<Vector3> spawner_positions_;	// 生成された各スポナーの位置の格納用
};
