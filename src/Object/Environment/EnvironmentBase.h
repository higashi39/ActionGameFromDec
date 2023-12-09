#pragma once

#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	環境オブジェクト基本クラス
//---------------------------------------------------------------------------------
class EnvironmentBase
{
public:
	EnvironmentBase();
	~EnvironmentBase() {};


	// 円の当たり判定
	Vector3 object_collision_position_; // 中心
	float object_collision_radius_;		// 半径

	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;

	//-----------------------------
	// ゲッター関数
	
	// 自身の位置を渡す
	virtual Vector3 GetterMyPosition() const;

	// 自身の使用しているモデルデータを渡す
	int* GetterModelData() const;

protected:
	int* object_model_;			// 画像データ格納用

	Vector3	object_position_;	// 位置
	Vector3	object_rotate_;		// 回転
	Vector3 object_scale_;		// 大きさ

	float object_collision_size_;		// 当たり判定のコリジョンの大きさ

	bool is_walk_ = false;			// 歩いているかどうか
};


