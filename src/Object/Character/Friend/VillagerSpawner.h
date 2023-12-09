#pragma once
#include "../../../System/Vector3.h"
class VillagerManager;

//---------------------------------------------------------------------------------
//	���l(�ی�Ώ�)�X�|�i�[�N���X
//---------------------------------------------------------------------------------
class VillagerSpawner
{

public:
	VillagerSpawner(Vector3& m_pos);
	~VillagerSpawner() {};

	//// ���l(�ی�Ώ�)�}�l�[�W���̐���
	//void CreateVillagerManager();

	// �̂��ɍ폜�\��
	// �X�V
	void Update();
	// �`��
	void Render();

protected:
	VillagerManager* villager_manage;

	Vector3 villager_spawner_position_;
};