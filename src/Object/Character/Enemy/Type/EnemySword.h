#pragma once
#include <vector>
#include "EnemyBase.h"

//---------------------------------------------------------------------------------
//	敵-剣-クラス
//---------------------------------------------------------------------------------
class EnemySword : public EnemyBase
{
public:
	// コンストラクタ
	// pos   : 自身の位置
	// id    : 自身の通し番号
	EnemySword(Vector3 pos, int id);
	~EnemySword();

	// 更新
	void Update() override;
};