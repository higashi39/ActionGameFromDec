#pragma once
#include <vector>
#include "../../../System/Vector3.h"

class RockBase;
class Rock01;
class Rock02;
class Rock03;
class Rock04;
class Rock05;

//---------------------------------------------------------------------------------
// ��Ǘ��N���X
// ���ׂĂ̊�I�u�W�F�N�g���Ǘ�����N���X
//---------------------------------------------------------------------------------
class RockManager
{
public:
	RockManager() {};
	~RockManager() {};

	// �������鏈��
	// type : ���
	// pos  : ���W
	// rot  : �p�x
	void CreateObject(int type, Vector3 pos, Vector3 rot);

	// �X�V
	void Update() {};
	// �`��
	void Render();

protected:
	std::vector<RockBase*> rocks_;
};
