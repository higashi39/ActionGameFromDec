#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	箱クラス
//---------------------------------------------------------------------------------
class Box : public EnvironmentBase
{
public:
	Box();
	~Box();

	// 更新
	void Update();
	// 描画
	void Render();
};
