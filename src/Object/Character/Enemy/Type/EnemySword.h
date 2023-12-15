#pragma once
#include <vector>
#include "EnemyBase.h"

//---------------------------------------------------------------------------------
//	�G-��-�N���X
//---------------------------------------------------------------------------------
class EnemySword : public EnemyBase
{
public:
	// �R���X�g���N�^
	// handle : ���f���n���h��
	// pos    : ���g�̈ʒu
	// rot    : ���g�̌���
	// id     : ���g�̒ʂ��ԍ�
	EnemySword(int handle, Vector3 pos, Vector3 rot, int id);
	~EnemySword();

	// �X�V
	void Update() override;
};