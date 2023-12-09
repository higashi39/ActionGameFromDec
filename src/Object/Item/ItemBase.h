#pragma once

#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	�A�C�e���I�u�W�F�N�g��{�N���X
//---------------------------------------------------------------------------------
class ItemBase
{
public:
	ItemBase();
	~ItemBase() {};

	// �X�V
	// attached_model : ���g���A�^�b�`���������f���f�[�^
	virtual void Update(int* attached_model) = 0;
	// �`��
	virtual void Render() = 0;

	// �Q�b�^�[�֐�
	// ���g�̈ʒu��n��
	virtual Vector3 GetterMyPosition() const;

protected:
	int* object_model_;			// �摜�f�[�^�i�[�p

	Vector3	object_position_;	// �ʒu
	Vector3	object_rotate_;		// ��]
	Vector3 object_scale_;		// �傫��
};


