#include "../Main.h"
#include "../Scene/Game.h"
#include "ScreenHPInfo.h"

ScreenHPInfo::ScreenHPInfo()
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

void ScreenHPInfo::Init()
{
	hp_num_ = 100.0f;

	hp_value_ = (hp_width_ + hp_width_);

	hp_min_pos_.x = 40;
	hp_min_pos_.y = 420;
	hp_max_pos_.x = 300;
	hp_max_pos_.y = 440;

	hp_per_ = hp_value_ / hp_num_;
	hp_width_ = 30;
	hp_height_ = 5;
	hp_red_x_ = 0.0f;
	hp_red_value_ = hp_value_;

	is_damaged_ = false;
	damaged_num_ = 0.0f;
}

void ScreenHPInfo::Update()
{
	//VECTOR wpos = my_pos.VGet();
	//// 自身の頭上に表示
	//wpos.y += hp_pos_y;
	//// 2D描画座標を取得
	//VECTOR pos2d = ConvWorldPosToScreenPos(wpos);
	//// 取得した座標を名前表示用座標に設定
	//hp_pos_.VSet(pos2d);
	//hp_pos_.z = 0.0f;
	//// HPの最小値と最大値の設定
	//// 最小値
	//hp_min_pos_.x = hp_pos_.x - hp_width_;
	//hp_min_pos_.y = hp_pos_.y - hp_height_;
	//// 最大値
	//hp_max_pos_.x = hp_min_pos_.x + hp_value_;
	//hp_max_pos_.y = hp_pos_.y + hp_height_;
	//// HPを減った分減らす用の赤いバーの値
	//hp_red_x_ = hp_min_pos_.x + hp_red_value_;

	// HPが0より大きい場合に攻撃を受けたら
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (hp_value_ >= 0.0f)
		{
			if (is_damaged_)
			{
				// ダメージ処理とHPの減少処理を行う
				Damaged();
				HPDecrease();
			}
		}
	}

	if (hp_value_ == 0.0f)
	{
		printfDx("ノックダウン処理に入ります\n");
		Dead();
	}
	printfDx("hp : %f\n", hp_num_);

}

void ScreenHPInfo::Render()
{
	if (!is_survive_)	return;
	//DrawFillBox(hp_min_pos_.x, hp_min_pos_.y, hp_red_x_, hp_max_pos_.y, GetColor(255, 0, 0));					// HPが減った分の赤表示
	DrawFillBox(hp_min_pos_.x, hp_min_pos_.y, hp_max_pos_.x, hp_max_pos_.y, GetColor(0, 255, 0));					// HP残量
	DrawLineBox(hp_min_pos_.x, hp_min_pos_.y, 300, hp_max_pos_.y, GetColor(255, 255, 255));	// HPの枠

	DrawCircle(20, 430, 15, GetColor(255, 255, 255), TRUE);
	//DrawLineBox(40, 420, SCREEN_W / 3, 440, GetColor(255, 255, 255));
}

void ScreenHPInfo::Damaged()
{
	// 減る量を設定してHP1あたりにかける
	hp_value_ -= (hp_per_ * damaged_num_);
	// 一度ダメージを受けたらダメージ量は0にリセットする
	damaged_num_ = 0.0f;
}

void ScreenHPInfo::HPDecrease()
{
	// 減るスピード設定して減らす
	hp_red_value_ -= 0.5f;
	// HPが減った分まで赤いバーを減らす
	if (hp_red_value_ <= hp_value_)
	{
		is_damaged_ = false;
	}
}

void ScreenHPInfo::Dead()
{
	// キャラクターの生存フラグを落とす
	is_survive_ = false;
}

void ScreenHPInfo::SetterIsDamaged(bool is_damaged, float damaged_num)
{
	// ダメージ量の設定
	damaged_num_ = damaged_num;
	// ダメージ処理を行う
	is_damaged_ = is_damaged;
}
