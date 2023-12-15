#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	柵ベースクラス
//---------------------------------------------------------------------------------
class FenceBase : public EnvironmentBase
{
public:
	FenceBase();
	~FenceBase();

	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;

	//-----------------------------
	// ゲッター関数

	// オブジェクトの位置を渡す
	Vector3 GetterFencePosition();
	// オブジェクトのサイズを渡す
	Vector3 GetterFenceCollisionSize();

protected:
	// 当たり判定用
	Vector3 collision_size_ = { 0.0f,0.0f,0.0f };		// コリジョンサイズ

	Vector3 size_pos[4];		// 回転の補正用サイズ
	Vector3 corner_pos[4];		// ４つの角の座標

	Vector3 test = {0.0f,0.0f,0.0f};
};
