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
	// handle		: モデルハンドル
	// pos			: 自身の位置 
	// rot			: 自身の向き
	// id			: 自身の通し番号
	// patrol_pos1	: 巡回折り返し位置１ 
	// patrol_pos2	: 巡回折り返し位置２ 
	EnemyPatrol(int handle, Vector3 pos,Vector3 rot, int id, Vector3 patrol_pos1, Vector3 patrol_pos2);
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