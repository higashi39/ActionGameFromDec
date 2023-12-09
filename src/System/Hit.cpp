#include <cmath>

#include "../Main.h"
#include "../Scene/Game.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	�����m�̓����蔻��
//---------------------------------------------------------------------------------
bool CheckBallHit(Vector3 center1, float radius1, Vector3 center2, float radius2)
{
	float length = GetVector3Distance(center1, center2);
	float radius = radius1 + radius2;
	if (length <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�{�b�N�X���m�̓����蔻��
//	�i���W pos �𒆐S�ɃT�C�Y size ���v���X�}�C�i�X�����{�b�N�X�F�Q�c�̂悤�ȍ��ォ��̑傫���ł̔���ł͂Ȃ��̂Œ��Ӂj
//---------------------------------------------------------------------------------
bool CheckBoxHit3D(Vector3 box_pos1, Vector3 box_size1, Vector3 box_pos2, Vector3 box_size2)
{
	float right1 = box_pos1.x + box_size1.x;
	float left1 = box_pos1.x - box_size1.x;
	float up1 = box_pos1.y + box_size1.y;
	float down1 = box_pos1.y - box_size1.y;
	float front1 = box_pos1.z + box_size1.z;
	float back1 = box_pos1.z - box_size1.z;

	float right2 = box_pos2.x + box_size2.x;
	float left2 = box_pos2.x - box_size2.x;
	float up2 = box_pos2.y + box_size2.y;
	float down2 = box_pos2.y - box_size2.y;
	float front2 = box_pos2.z + box_size2.z;
	float back2 = box_pos2.z - box_size2.z;

	if (right1 >= left2 && left1 <= right2) {
		if (up1 >= down2 && down1 <= up2) {
			if (front1 >= back2 && back1 <= front2) {
				return true;
			}
		}
	}
	return false;
}

//==================================================================================
// ���吧��֐�
//==================================================================================
//---------------------------------------------------------------------------------
//	�l�p�Ɖ~�̓����蔻��(�ǂ����瓖���������𐮐��ŕԂ�)
//---------------------------------------------------------------------------------
void CheckBoxSphereHit(int* box_model_data, Vector3 sphere_center, float sphere_radius)
{
	//printfDx("��Ɠ������Ă��܂�\n");

	//MV1_COLL_RESULT_POLY_DIM hit_dim = MV1CollCheck_Sphere(*box_model_data, -1, sphere_center.VGet(), sphere_radius);
	//// ���������|���S�����̎擾
	//int hit_num = hit_dim.HitNum;
	//// ���������|���S�������ԂɌ��Ă���
	//for (int i = 0; i < hit_num; ++i)
	//{
	//	// �ǂ̃|���S���ɓ������������擾����
	//	VECTOR hit_pos = hit_dim.Dim[i].HitPosition;

	//	// ���g�̍��W����l�p�����蔻�胂�f���ɓ����������W�܂ł̒��������߂�
	//	VECTOR vec;
	//	vec.x = sphere_center.x - hit_pos.x;
	//	vec.z = sphere_center.z - hit_pos.z;
	//	vec.y = 0.0f;
	//	float length = VSize(vec);

	//	// �ǂꂾ���l�p�����蔻�胂�f���ɂ߂荞�񂾂��[�������߂�
	//	float depth = sphere_radius - length;
	//	// ���������|���S���@�������߂�
	//	VECTOR hit_normal = hit_dim.Dim[i].Normal;
	//	// �߂荞�񂾗ʂ����߂�ifloat�̌덷���l���AY���W�͂��̂܂܂Łj
	//	Vector3 q;
	//	q.x = hit_normal.x * (depth + FLT_EPSILON);
	//	q.z = hit_normal.z * (depth + FLT_EPSILON);
	//	q.y = 0.0f;

	//	// �߂荞�񂾕������@�������ɉ����o��
	//	sphere_center += q;
	//}
}

//---------------------------------------------------------------------------------
//	�Q�̃I�u�W�F�N�g�̃x�N�g���������Z�o
//---------------------------------------------------------------------------------
Vector3 CalculateTwoVector(Vector3 vec1, Vector3 vec2)
{
	Vector3 vec;
	vec.x = vec1.x - vec2.x;
	vec.z = vec1.z - vec2.z;
	// Y���W��0�ɂ��Ă���
	vec.y = 0.0f;

	return vec;
}
//---------------------------------------------------------------------------------
//	�x�N�g�������̒��������߂�
//---------------------------------------------------------------------------------
float CalculateVectorToLength(Vector3 vec)
{
	float len;
	len = VSize(vec.VGet());
	return len;
}

//---------------------------------------------------------------------------------
//	�P�_�̈ʒu�i���W�j�ƂP�̉~�̓����蔻��
//---------------------------------------------------------------------------------
bool CheckHitPointToCircle(Vector3 point, Vector3 circle_center, float circle_radius)
{
	Vector3 distance;
	distance = CalculateTwoVector(circle_center, point);

	float length = CalculateVectorToLength(distance);

	if (length <= circle_radius)
	{
		return true;
	}

	return false;
}

Vector3 HitCollision(Vector3 obj_pos, Vector3 obj_before_pos, Vector3 obj_size,
	Vector3 box_pos, Vector3 box_size)
{
	if (obj_before_pos.z + obj_size.z >= box_pos.z - box_size.z &&
		obj_before_pos.z - obj_size.z <= box_pos.z + box_size.z)
	{
		// X���������P�t���[���O�̍��W�ɖ߂�
		obj_pos.x = obj_before_pos.x;
	}
	// �c�ɓ������Ă�����X���������߂�
	// ���ړ��O�̎l�p�Ǝl�p�p�l���������������������Ă�����
	if (obj_before_pos.x + obj_size.x >= box_pos.x - box_size.x &&
		obj_before_pos.x - obj_size.x <= box_pos.x + box_size.x)
	{
		// Z���������P�t���[���O�̍��W�ɖ߂�
		obj_pos.z = obj_before_pos.z;
	}

	return obj_pos;
}