#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	��N���X
//---------------------------------------------------------------------------------
class Fence : public EnvironmentBase
{
public:
	Fence(Vector3 create_pos, Vector3 create_rot);
	~Fence();

	// �X�V
	void Update() {};
	//void FenceUpdate(const Vector3& p_pos);
	// �`��
	void Render();
	
	//-----------------------------
	// �Q�b�^�[�֐�

	// �I�u�W�F�N�g�̈ʒu��n��
	Vector3 GetterFencePosition();
	// �I�u�W�F�N�g�̃T�C�Y��n��
	Vector3 GetterFenceSize();

private:
	Vector3 fence_size_ = { 0.0f,0.0f,0.0f };
};
