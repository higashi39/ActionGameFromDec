#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	柵クラス
//---------------------------------------------------------------------------------
class Fence : public EnvironmentBase
{
public:
	Fence(Vector3 create_pos, Vector3 create_rot);
	~Fence();

	// 更新
	void Update() {};
	//void FenceUpdate(const Vector3& p_pos);
	// 描画
	void Render();
	
	//-----------------------------
	// ゲッター関数

	// オブジェクトの位置を渡す
	Vector3 GetterFencePosition();
	// オブジェクトのサイズを渡す
	Vector3 GetterFenceSize();

private:
	Vector3 fence_size_ = { 0.0f,0.0f,0.0f };
};
