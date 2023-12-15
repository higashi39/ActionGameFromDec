#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	��x�[�X�N���X
//---------------------------------------------------------------------------------
class FenceBase : public EnvironmentBase
{
public:
	FenceBase();
	~FenceBase();

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;

	//-----------------------------
	// �Q�b�^�[�֐�

	// �I�u�W�F�N�g�̈ʒu��n��
	Vector3 GetterFencePosition();
	// �I�u�W�F�N�g�̃T�C�Y��n��
	Vector3 GetterFenceCollisionSize();

protected:
	// �����蔻��p
	Vector3 collision_size_ = { 0.0f,0.0f,0.0f };		// �R���W�����T�C�Y

	Vector3 size_pos[4];		// ��]�̕␳�p�T�C�Y
	Vector3 corner_pos[4];		// �S�̊p�̍��W

	Vector3 test = {0.0f,0.0f,0.0f};
};
