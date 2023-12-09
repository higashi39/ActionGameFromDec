#pragma once

#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	���I�u�W�F�N�g��{�N���X
//---------------------------------------------------------------------------------
class EnvironmentBase
{
public:
	EnvironmentBase();
	~EnvironmentBase() {};


	// �~�̓����蔻��
	Vector3 object_collision_position_; // ���S
	float object_collision_radius_;		// ���a

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;

	//-----------------------------
	// �Q�b�^�[�֐�
	
	// ���g�̈ʒu��n��
	virtual Vector3 GetterMyPosition() const;

	// ���g�̎g�p���Ă��郂�f���f�[�^��n��
	int* GetterModelData() const;

protected:
	int* object_model_;			// �摜�f�[�^�i�[�p

	Vector3	object_position_;	// �ʒu
	Vector3	object_rotate_;		// ��]
	Vector3 object_scale_;		// �傫��

	float object_collision_size_;		// �����蔻��̃R���W�����̑傫��

	bool is_walk_ = false;			// �����Ă��邩�ǂ���
};


