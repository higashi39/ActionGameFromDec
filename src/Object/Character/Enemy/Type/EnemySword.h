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
	// pos   : ���g�̈ʒu
	// id    : ���g�̒ʂ��ԍ�
	EnemySword(Vector3 pos, int id);
	~EnemySword();

	// �X�V
	void Update() override;
};