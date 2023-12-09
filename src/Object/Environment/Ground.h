#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	地面クラス
//---------------------------------------------------------------------------------
class Ground : public EnvironmentBase
{
public:
	Ground();
	~Ground() {};

	// 更新
	void Update() {};
	// 描画
	void Render();
};
