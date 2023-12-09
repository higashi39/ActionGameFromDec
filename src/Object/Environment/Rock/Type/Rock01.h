#pragma once

#include "RockBase.h"

//---------------------------------------------------------------------------------
//	地面クラス
//---------------------------------------------------------------------------------
class Rock01 : public RockBase
{
public:
	Rock01(Vector3 create_pos, Vector3 create_rot);
	~Rock01() {};

	//// 更新
	//void Update() {};
	//// 描画
	//void Render() {};
};
