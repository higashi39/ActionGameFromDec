#pragma once
#include "../../Other/Animation.h"
#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	オブジェクト基本クラス
//---------------------------------------------------------------------------------
class CharacterBase : public Animation
{
public:
	CharacterBase();
	~CharacterBase() {};


	//// 円の当たり判定
	//Vector3 object_collision_position_; // 中心
	//float object_collision_radius_;		// 半径

	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render() = 0;

	// ゲッター関数
	// 自身の位置を渡す
	virtual Vector3 GetterMyPosition() const;

	//// 出現(表示)させるかどうかの設定/取得
	//void SetIsActive(bool a);
	//bool GetIsActive();

	//// 当たり判定による押し出し処理
	//// hitcoll_pos : 当たったキャラクター座標
	//// hit_power : 当たった際の押し出す力
	//void PushColl(Vector3 hitcoll_pos, float hit_power);

	//// 自身のカプセルコリジョンの設定
	//void SetCapsuleColl(float up_y, float bottom_y, float rot);

	// 壁との当たり判定
	// top_cap_pos : カプセルの球体(上側)の座標
	// bottom_cap_pos : カプセルの球体(下側)の座標
	// cap_rot : 自分のコリジョン半径
	//void HitStageModel(/*VECTOR top_cap_pos, VECTOR bottom_cap_pos, */float cap_rot);

	//void HitModelToModel(Base* other);
protected:
	int* object_model_;			// モデルデータ格納用

	Vector3	object_position_;	// 位置
	Vector3	object_rotate_;		// 回転
	Vector3 object_scale_;		// 大きさ

	Vector3 object_box_size_;		// 当たり判定のコリジョンの大きさ

	bool is_walk_ = false;			// 歩いているかどうか

};


