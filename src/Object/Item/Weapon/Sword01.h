#pragma once
#include "../ItemBase.h"

//---------------------------------------------------------------------------------
//	����N���X
//---------------------------------------------------------------------------------
class Sword01 : public ItemBase
{
public:
	Sword01();
	~Sword01() {};

	// �X�V
	void Update(int* attached_model) override;
	// �`��
	void Render() override;	
};
