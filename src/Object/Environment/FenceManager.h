#pragma once
#include <vector>
#include "../../System/Vector3.h"

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
	// pos    : ���������ʒu
	// rot    :	�@�@�@�@�@����
	void SpawnFence(Vector3 pos, Vector3 rot);

	// �X�V
	void Update();
	// �`��
	void Render();

	//------------------------------
	// �Q�b�^�[�֐�

	// ���ׂĂ̍�̏���n��
	std::vector<Fence*> GetterFenceInfos() const;

private:
	std::vector<Fence*> fences_;			// ����i�[����p
};