#pragma once

#include "FenceBase.h"

//---------------------------------------------------------------------------------
//	��N���X
//---------------------------------------------------------------------------------
class Fence : public FenceBase
{
public:
	// �R���X�g���N�^
	// handle		: ���f���n���h��
	// create_pos	: �����ʒu
	// create_rot	: �������ꂽ�Ƃ��̌���	
	Fence(int handle,Vector3 create_pos, Vector3 create_rot);
	~Fence();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;
};
