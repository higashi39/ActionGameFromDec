#pragma once

#include "FenceBase.h"

//---------------------------------------------------------------------------------
//	柵クラス
//---------------------------------------------------------------------------------
class Fence : public FenceBase
{
public:
	// コンストラクタ
	// handle		: モデルハンドル
	// create_pos	: 生成位置
	// create_rot	: 生成されたときの向き	
	Fence(int handle,Vector3 create_pos, Vector3 create_rot);
	~Fence();

	// 更新
	void Update() override;
	// 描画
	void Render() override;
};
