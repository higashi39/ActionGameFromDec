#include "../Main.h"
#include "../Scene/Game.h"
#include "HPInfoBase.h"

HPInfoBase::HPInfoBase()
{
	hp_num_ = 100.0f;

	hp_value_ = (hp_width_ + hp_width_);
	hp_per_ = hp_value_ / hp_num_;
	hp_width_ = 30;
	hp_height_ = 5;
	hp_red_x_ = 0.0f;
	hp_red_value_ = hp_value_;

	is_damaged_ = false;
	damaged_num_ = 0.0f;
}

void HPInfoBase::Damaged()
{
	// 減る量を設定してHP1あたりにかける
	hp_value_ -= (hp_per_ * damaged_num_);
	// 一度ダメージを受けたらダメージ量は0にリセットする
	damaged_num_ = 0.0f;
}

void HPInfoBase::HPDecrease()
{
	// 減るスピード設定して減らす
	hp_red_value_ -= 0.5f;
	// HPが減った分まで赤いバーを減らす
	if (hp_red_value_ <= hp_value_)
	{
		is_damaged_ = false;
	}
}

void HPInfoBase::Dead()
{
	// キャラクターの生存フラグを落とす
	is_survive_ = false;
}

void HPInfoBase::SetterIsDamaged(bool is_damaged, float damaged_num)
{
	// ダメージ量の設定
	damaged_num_ = damaged_num;
	// ダメージ処理を行う
	is_damaged_ = is_damaged;
}
