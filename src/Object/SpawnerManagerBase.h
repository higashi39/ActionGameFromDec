#pragma once
#include <vector>
#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
//	スポナーマネージャベースクラス
//---------------------------------------------------------------------------------
class SpawnerManagerBase
{
public:
	SpawnerManagerBase();
	~SpawnerManagerBase() {};

	// スポナーを生成する
	// pos : スポナー設置位置
	virtual void CreateSpawner(Vector3 pos) = 0;
	// スポナーの生成位置を渡す
	virtual Vector3 GetterSpawnerPosition() const = 0;
	// 全スポナーの位置を格納した変数を渡す
	virtual std::vector<Vector3> GetterSpawnerPositions() const = 0;

	// 位置をランダムで算出する
	Vector3 SetSpawnerPosition();
	// スポナーの位置を取得する
	void FetchSpawnerPosition();

	// のちに削除予定
	//void Initialize();
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;

protected:
	Vector3 get_position_;

	std::vector<Vector3> spawner_positions_;	// 生成された各スポナーの位置を格納
};