#pragma once
#include <vector>
#include "../../System/Vector3.h"

class Fence;

//---------------------------------------------------------------------------------
//	柵マネージャクラス
//---------------------------------------------------------------------------------
class FenceManager
{
public:
	FenceManager() {};
	~FenceManager();

	// 敵を生成する
	// pos    : 生成される位置
	// rot    :	　　　　　向き
	void SpawnFence(Vector3 pos, Vector3 rot);

	// 更新
	void Update();
	// 描画
	void Render();

	//------------------------------
	// ゲッター関数

	// すべての柵の情報を渡す
	std::vector<Fence*> GetterFenceInfos() const;

private:
	std::vector<Fence*> fences_;			// 柵を格納する用
};