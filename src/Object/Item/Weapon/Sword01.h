#pragma once
#include "../ItemBase.h"

//---------------------------------------------------------------------------------
//	武器クラス
//---------------------------------------------------------------------------------
class Sword01 : public ItemBase
{
public:
	Sword01();
	~Sword01() {};

	// 更新
	void Update(int* attached_model) override;
	// 描画
	void Render() override;	
};
