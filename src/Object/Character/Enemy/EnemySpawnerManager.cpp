#include <ctime>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "EnemySpawner.h"
#include "EnemySpawnerManager.h"

#include "../../../System/Vector3.h"

EnemySpawnerManager::EnemySpawnerManager()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		enemy_spawner[i] = NULL;
	}
}

EnemySpawnerManager::~EnemySpawnerManager()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		delete enemy_spawner[i];
	}
}

void EnemySpawnerManager::CreateSpawner(Vector3 pos)
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		//// �ݒu���ꂽ�X�|�i�[�̈ʒu���擾
		//FetchSpawnerPosition();
		// �X�|�i�[�ʒu���X�|�i�[�ʒu�i�[�p�ɒǉ�����
		spawner_positions_.emplace_back(pos);
		// �擾�����ʒu�ɓG�X�|�i�[�𐶐�
		enemy_spawner[i] = new EnemySpawner(spawner_positions_[i]);
	}
}

std::vector<Vector3> EnemySpawnerManager::GetterSpawnerPositions() const
{
	// �i�[�����G�̃X�|�i�[��S�ēn��
	return spawner_positions_;
}

Vector3 EnemySpawnerManager::GetterSpawnerPosition() const
{
	// �G�̃X�|�i�[��0�ԖڂɊi�[���ꂽ�ʒu�̂ݓn��
	// �������A�X�|�i�[�̈ʒu���P���i�[����Ă��Ȃ��ꍇ��(0.0f, 0.0f, 0.0f)��n��
	if (spawner_positions_.size() <= 0)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}
	return spawner_positions_[0];
}

void EnemySpawnerManager::Update()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		enemy_spawner[i]->Update();
	}
}

void EnemySpawnerManager::Render()
{
	for (int i = 0; i < ENEMY_SPAWNER_NUM; i++)
	{
		enemy_spawner[i]->Render();
	}
}