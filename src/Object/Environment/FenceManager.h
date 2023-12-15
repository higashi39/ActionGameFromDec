#pragma once
#include <vector>
#include "../../System/Vector3.h"

class FenceBase;
class Fence;

//---------------------------------------------------------------------------------
//	��}�l�[�W���N���X
//---------------------------------------------------------------------------------
class FenceManager
{
public:
	FenceManager() {};
	~FenceManager();

	// �G�𐶐�����
	// handle : ���f���n���h��
	// id	  : ���ʔԍ�
	// pos    : ���������ʒu
	// rot    :	�@�@�@�@�@����
	void SpawnFence(int handle, int id, Vector3 pos, Vector3 rot);

	// �X�V
	void Update();
	// �`��
	void Render();

	//------------------------------
	// �Q�b�^�[�֐�

	//-----------------------------
	// �Q�b�^�[�֐�

	// �I�u�W�F�N�g�̈ʒu��n��
	Vector3 GetterFencePosition();
	// �I�u�W�F�N�g�̃T�C�Y��n��
	Vector3 GetterFenceCollisionSize();

	// ���ׂĂ̍�̏���n��
	std::vector<FenceBase*> GetterFenceInfos() const;

protected:
	std::vector<FenceBase*> fences_;			// ����i�[����p
};