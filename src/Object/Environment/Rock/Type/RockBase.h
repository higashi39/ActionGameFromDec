#pragma once

#include "../../EnvironmentBase.h"

//---------------------------------------------------------------------------------
// ��x�[�X�N���X
// ���ׂĂ̊�̃I�u�W�F�N�g�̊�{�ƂȂ�N���X
//---------------------------------------------------------------------------------
class RockBase : public EnvironmentBase
{
public:
	RockBase();
	~RockBase() {};

	// �X�V
	void Update() {};
	// �`��
	void Render();
};
