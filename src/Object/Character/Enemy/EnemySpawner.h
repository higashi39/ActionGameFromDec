#pragma once
#include "../../../System/Vector3.h"
class EnemyManager;

//---------------------------------------------------------------------------------
//	�G�X�|�i�[�N���X
//---------------------------------------------------------------------------------
class EnemySpawner
{

public:
	EnemySpawner(Vector3& m_pos);
	~EnemySpawner() {};

	//// �G�}�l�[�W���̐���
	//void CreateEnemyManager();

	// �̂��ɍ폜�\��
	// �X�V
	void Update();
	// �`��
	void Render();

protected:
	EnemyManager* enemy_manage;

	Vector3 enemy_spawner_position_;
};