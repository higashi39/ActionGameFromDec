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
	//// ���g�̓���ɕ\��
	//wpos.y += hp_pos_y;
	//// 2D�`����W���擾
	//VECTOR pos2d = ConvWorldPosToScreenPos(wpos);
	//// �擾�������W�𖼑O�\���p���W�ɐݒ�
	//hp_pos_.VSet(pos2d);
	//hp_pos_.z = 0.0f;
	//// HP�̍ŏ��l�ƍő�l�̐ݒ�
	//// �ŏ��l
	//hp_min_pos_.x = hp_pos_.x - hp_width_;
	//hp_min_pos_.y = hp_pos_.y - hp_height_;
	//// �ő�l
	//hp_max_pos_.x = hp_min_pos_.x + hp_value_;
	//hp_max_pos_.y = hp_pos_.y + hp_height_;
	//// HP�������������炷�p�̐Ԃ��o�[�̒l
	//hp_red_x_ = hp_min_pos_.x + hp_red_value_;

	// HP��0���傫���ꍇ�ɍU�����󂯂���
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (hp_value_ >= 0.0f)
		{
			if (is_damaged_)
			{
				// �_���[�W������HP�̌����������s��
				Damaged();
				HPDecrease();
			}
		}
	}

	if (hp_value_ == 0.0f)
	{
		printfDx("�m�b�N�_�E�������ɓ���܂�\n");
		Dead();
	}
	printfDx("hp : %f\n", hp_num_);

}

void ScreenHPInfo::Render()
{
	if (!is_survive_)	return;
	//DrawFillBox(hp_min_pos_.x, hp_min_pos_.y, hp_red_x_, hp_max_pos_.y, GetColor(255, 0, 0));					// HP�����������̐ԕ\��
	DrawFillBox(hp_min_pos_.x, hp_min_pos_.y, hp_max_pos_.x, hp_max_pos_.y, GetColor(0, 255, 0));					// HP�c��
	DrawLineBox(hp_min_pos_.x, hp_min_pos_.y, 300, hp_max_pos_.y, GetColor(255, 255, 255));	// HP�̘g

	DrawCircle(20, 430, 15, GetColor(255, 255, 255), TRUE);
	//DrawLineBox(40, 420, SCREEN_W / 3, 440, GetColor(255, 255, 255));
}

void ScreenHPInfo::Damaged()
{
	// ����ʂ�ݒ肵��HP1������ɂ�����
	hp_value_ -= (hp_per_ * damaged_num_);
	// ��x�_���[�W���󂯂���_���[�W�ʂ�0�Ƀ��Z�b�g����
	damaged_num_ = 0.0f;
}

void ScreenHPInfo::HPDecrease()
{
	// ����X�s�[�h�ݒ肵�Č��炷
	hp_red_value_ -= 0.5f;
	// HP�����������܂ŐԂ��o�[�����炷
	if (hp_red_value_ <= hp_value_)
	{
		is_damaged_ = false;
	}
}

void ScreenHPInfo::Dead()
{
	// �L�����N�^�[�̐����t���O�𗎂Ƃ�
	is_survive_ = false;
}

void ScreenHPInfo::SetterIsDamaged(bool is_damaged, float damaged_num)
{
	// �_���[�W�ʂ̐ݒ�
	damaged_num_ = damaged_num;
	// �_���[�W�������s��
	is_damaged_ = is_damaged;
}
