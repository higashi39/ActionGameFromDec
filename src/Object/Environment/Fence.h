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
	void Update();
	// 描画
	void Render();

	//-----------------------------
	// ゲッター関数

	// オブジェクトの位置を渡す
	Vector3 GetterFencePosition();
	// オブジェクトのサイズを渡す
	Vector3 GetterFenceCollisionSize();

private:
	// 当たり判定用
	Vector3 collision_size_ = { 0.0f,0.0f,0.0f };		// コリジョンサイズ

	Vector3 size_pos[4];		// 回転の補正用サイズ
	Vector3 corner_pos[4];		// ４つの角の座標

	Vector3 test = {0.0f,0.0f,0.0f};
};
