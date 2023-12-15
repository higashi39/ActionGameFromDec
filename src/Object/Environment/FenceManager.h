#pragma once
#include <vector>
#include "../../System/Vector3.h"

class FenceBase;
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
	// handle : モデルハンドル
	// id	  : 識別番号
	// pos    : 生成される位置
	// rot    :	　　　　　向き
	void SpawnFence(int handle, int id, Vector3 pos, Vector3 rot);

	// 更新
	void Update();
	// 描画
	void Render();

	//------------------------------
	// ゲッター関数

	//-----------------------------
	// ゲッター関数

	// オブジェクトの位置を渡す
	Vector3 GetterFencePosition();
	// オブジェクトのサイズを渡す
	Vector3 GetterFenceCollisionSize();

	// すべての柵の情報を渡す
	std::vector<FenceBase*> GetterFenceInfos() const;

protected:
	std::vector<FenceBase*> fences_;			// 柵を格納する用
};