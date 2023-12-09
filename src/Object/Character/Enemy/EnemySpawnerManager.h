#pragma once
#include <vector>
#include "../../SpawnerManagerBase.h"
class EnemySpawner;
#include "../../../System/Vector3.h"

#define ENEMY_SPAWNER_NUM  2

//---------------------------------------------------------------------------------
//	敵スポナーマネージャクラス
//---------------------------------------------------------------------------------
class EnemySpawnerManager : public SpawnerManagerBase
{
public:
	EnemySpawnerManager();
	~EnemySpawnerManager();

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
	EnemySpawner* enemy_spawner[ENEMY_SPAWNER_NUM];		// 敵のスポナー管理

	//std::vector<Vector3> spawner_positions_;	// 生成された各スポナーの位置の格納用
};
