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
	// ����ʂ�ݒ肵��HP1������ɂ�����
	hp_value_ -= (hp_per_ * damaged_num_);
	// ��x�_���[�W���󂯂���_���[�W�ʂ�0�Ƀ��Z�b�g����
	damaged_num_ = 0.0f;
}

void HPInfoBase::HPDecrease()
{
	// ����X�s�[�h�ݒ肵�Č��炷
	hp_red_value_ -= 0.5f;
	// HP�����������܂ŐԂ��o�[�����炷
	if (hp_red_value_ <= hp_value_)
	{
		is_damaged_ = false;
	}
}

void HPInfoBase::Dead()
{
	// �L�����N�^�[�̐����t���O�𗎂Ƃ�
	is_survive_ = false;
}

void HPInfoBase::SetterIsDamaged(bool is_damaged, float damaged_num)
{
	// �_���[�W�ʂ̐ݒ�
	damaged_num_ = damaged_num;
	// �_���[�W�������s��
	is_damaged_ = is_damaged;
}
