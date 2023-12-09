#pragma once

#include "../../EnvironmentBase.h"

//---------------------------------------------------------------------------------
// 岩ベースクラス
// すべての岩のオブジェクトの基本となるクラス
//---------------------------------------------------------------------------------
class RockBase : public EnvironmentBase
{
public:
	RockBase();
	~RockBase() {};

	// 更新
	void Update() {};
	// 描画
	void Render();
};
