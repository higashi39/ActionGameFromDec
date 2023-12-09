#pragma once
#include <vector>
#include "../../../System/Vector3.h"

class RockBase;
class Rock01;
class Rock02;
class Rock03;
class Rock04;
class Rock05;

//---------------------------------------------------------------------------------
// 岩管理クラス
// すべての岩オブジェクトを管理するクラス
//---------------------------------------------------------------------------------
class RockManager
{
public:
	RockManager() {};
	~RockManager() {};

	// 生成する処理
	// type : 種類
	// pos  : 座標
	// rot  : 角度
	void CreateObject(int type, Vector3 pos, Vector3 rot);

	// 更新
	void Update() {};
	// 描画
	void Render();

protected:
	std::vector<RockBase*> rocks_;
};
