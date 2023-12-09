#pragma once
#include <vector>
#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	�I�u�W�F�N�g�}�l�[�W���x�[�X�N���X
//---------------------------------------------------------------------------------
class CharacterManagerBase
{
public:
	CharacterManagerBase();
	~CharacterManagerBase() {};

	// �P�X�|�i�[�ɉ��l�������邩�����ŎZ�o����
	// min : �ŏ��l��
	// max : �ő�l��
	void CalculateObjectNum(int min, int max);
	// �������鑺�l(�ی�Ώ�)�̈ʒu�����ꂼ�ꌈ�߂�
	// pos : �I�u�W�F�N�g�̈ʒu
	Vector3 AssignObjectPosition(const Vector3& pos);
	// �����O�̐ݒ�
	// id : �I�u�W�F�N�gID
	// �ݒ荀�� - 1�X�|�i�[�ɐ�������鐔
	// �@�@�@�@ - �����ʒu
	virtual void ObjectInitializeSetting(int id) = 0;
	// ���l(�ی�Ώ�)�𐶐�����
	// set_id : ���ꂼ������ʂ��邽�߂̒l��ݒ�
	// pos  : �I�u�W�F�N�g�̈ʒu
	virtual void CreateObject(int kindof, int set_id, const Vector3& pos) = 0;

protected:
	int object_create_num_;							// ���������I�u�W�F�N�g��
	std::vector<Vector3> object_create_pos_;		// ���������I�u�W�F�N�g�̈ʒu�i�[�p�z��
};