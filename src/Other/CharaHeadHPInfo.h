#pragma once
#include "../System/Vector3.h"
//#include "HPInfoBase.h"

//---------------------------------------------------------------------------------
//	HP情報
//---------------------------------------------------------------------------------
class CharaHeadHPInfo /*: public HPInfoBase*/
{
public:
	CharaHeadHPInfo();

	// 初期化
	//
	void Init();

	// 更新
	// my_pos   : 自身の位置
	// hp_pos_y : Y座標(キャラクターの頭上に表示されるように)
	void Update(Vector3 my_pos, float hp_pos_y);

	// 生きているかどうか
	bool IsSurvice();

	// 描画
	void Render();

	// ダメージ処理
	// damage_num : ダメージ量
	void Damaged();

	// ダメージ時のHP減少処理
	void HPDecrease();

	// ノックダウン処理
	void Dead();

	//------------------------
	// セッター関数

	// ダメージを受けたかを設定する
	// damaged_num : 受けたダメージ量
	void SetterIsDamaged(float damaged_num);

private:
	// HP表示用座標
	Vector3 hp_pos_;

	// HPの値
	float hp_num_;
	// 描画時の値
	float hp_value_;
	// 残量HP
	Vector3 hp_min_pos_;			// 最小
	Vector3 hp_max_pos_;			// 最大
	// HP1あたりの値
	float hp_per_;

	// HP描画用
	// 幅
	float hp_width_ = 30;	// 横幅
	float hp_height_ = 5;	// 縦幅
	// HPが減った分を赤色で表示
	float hp_red_x_;
	float hp_red_value_;

	// ダメージを受けたかどうか
	bool is_damaged_;
	// 受けたダメージ量
	float damaged_num_;

	// キャラクターの生存フラグ
	// ☆現状はオブジェクトを更新・描画処理するしないで処理する
	bool is_survive_ = true;
};