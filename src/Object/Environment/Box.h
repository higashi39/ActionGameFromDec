#pragma once

#include "EnvironmentBase.h"

//---------------------------------------------------------------------------------
//	���N���X
//---------------------------------------------------------------------------------
class Box : public EnvironmentBase
{
public:
	Box();
	~Box();

	// �X�V
	void Update();
	// �`��
	void Render();
};
