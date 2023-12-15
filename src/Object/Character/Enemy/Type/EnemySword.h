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
	// handle : モデルハンドル
	// pos    : 自身の位置
	// rot    : 自身の向き
	// id     : 自身の通し番号
	EnemySword(int handle, Vector3 pos, Vector3 rot, int id);
	~EnemySword();

	// 更新
	void Update() override;
};