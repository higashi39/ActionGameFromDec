#pragma once

#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	アイテムオブジェクト基本クラス
//---------------------------------------------------------------------------------
class ItemBase
{
public:
	ItemBase();
	~ItemBase() {};

	// 更新
	// attached_model : 自身をアタッチしたいモデルデータ
	virtual void Update(int* attached_model) = 0;
	// 描画
	virtual void Render() = 0;

	// ゲッター関数
	// 自身の位置を渡す
	virtual Vector3 GetterMyPosition() const;

protected:
	int* object_model_;			// 画像データ格納用

	Vector3	object_position_;	// 位置
	Vector3	object_rotate_;		// 回転
	Vector3 object_scale_;		// 大きさ
};


