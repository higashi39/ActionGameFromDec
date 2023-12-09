// �v�Z�p------------------------
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "../../System/Random.h"
//-------------------------------

#include "../../Main.h"
#include "../../Scene/Game.h"
#include "CharacterManagerBase.h"

CharacterManagerBase::CharacterManagerBase()
{
	object_create_num_ = 0;

}	

void CharacterManagerBase::CalculateObjectNum(int min, int max)
{
	int rand_num;
	// ���l�������邩���߂�
	rand_num = GetRandomI(min, max);
	object_create_num_ = rand_num;
	for (int i = 0; i < rand_num; i++)
	{
		// ���ׂẴI�u�W�F�N�g�̏����ʒu��(0.0f, 0.0f, 0.0f)�Ƃ��A
		// �I�u�W�F�N�g�ʒu�i�[�p�z��ɒǉ����Ă���
		Vector3 zero;
		zero.set(0.0f, 0.0f, 0.0f);
		object_create_pos_.emplace_back(zero);
	}
}

Vector3 CharacterManagerBase::AssignObjectPosition(const Vector3& pos)
{
	// �p�x�𗐐��ŋ��߂�
	float rand_angle = GetRandomF(2.0f * M_PI);
	// �X�|�i�[�̒��S�ʒu�����蔼�a���ŗ��������߂�
	float rand_radius = GetRandomF(15.0f);

	// ��������ʒu��ݒ�
	Vector3 create_pos;
	create_pos.x = pos.x + rand_radius * std::sin(rand_angle);
	create_pos.z = pos.z + rand_radius * std::cos(rand_angle);
	create_pos.y = 0.0f;

	return create_pos;
}