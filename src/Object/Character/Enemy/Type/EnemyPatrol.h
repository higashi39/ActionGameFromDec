#pragma once
#include <vector>
#include "EnemyBase.h"

//---------------------------------------------------------------------------------
//	敵-巡回-クラス
//---------------------------------------------------------------------------------
class EnemyPatrol : public EnemyBase
{
public:
	// コンストラクタ
	// pos   : 自身の位置 
	// id    : 自身の通し番号
	EnemyPatrol(Vector3 pos, int id);
	~EnemyPatrol();

	// 更新
	void Update() override;

	// 巡回アクション
	void PatrolAction();

private:
	//-------------------------------
	// 巡回アクション用変数
	Vector3 patrol_pos1_;			// 巡回折り返し位置1
	Vector3 patrol_pos2_;			// 巡回折り返し位置2
	bool check_patrol_;				// もう１つの巡回位置に行くためフラグ
	float turn_cool_time_;			// 折り返すまでのクールタイム
};