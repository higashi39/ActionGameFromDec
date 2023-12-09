#pragma once
#include "../System/Vector2.h"

//---------------------------------------------------------------------------------
// HP情報(2Dスクリーン描画)
// HP情報を2D画面座標に表示する
//---------------------------------------------------------------------------------
class ScreenHPInfo
{
public:
	ScreenHPInfo();

	// 初期化
	void Init();
	// 更新
	void Update();
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
	// is_damaged : ダメージを受けたかどうか
	// damaged_num : 受けたダメージ量
	void SetterIsDamaged(bool is_damaged, float damaged_num);

protected:
	// HP表示用座標
	Vector2 hp_pos_;

	// HPの値
	float hp_num_;
	// 描画時の値
	float hp_value_;
	// 残量HP
	Vector2 hp_min_pos_;			// 最小
	Vector2 hp_max_pos_;			// 最大
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