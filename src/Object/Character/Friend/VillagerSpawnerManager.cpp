#include <ctime>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "VillagerSpawner.h"
#include "VillagerSpawnerManager.h"

#include "../../../System/Vector3.h"

VillagerSpawnerManager::VillagerSpawnerManager()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		villager_spawner[i] = NULL;
	}
}

VillagerSpawnerManager::~VillagerSpawnerManager()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		delete villager_spawner[i];
	}
}

void VillagerSpawnerManager::CreateSpawner(Vector3 pos)
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		// �ݒ肳�ꂽ�X�|�i�[�̈ʒu���擾
		//FetchSpawnerPosition();
		// �X�|�i�[�ʒu���X�|�i�[�ʒu�i�[�p�ɒǉ�����
		spawner_positions_.emplace_back(pos);
		// �擾�����ʒu�ɑ��l�X�|�i�[�𐶐�
		villager_spawner[i] = new VillagerSpawner(spawner_positions_[i]);
	}
}

std::vector<Vector3> VillagerSpawnerManager::GetterSpawnerPositions() const
{
	// �i�[�������l(�ی�Ώ�)�̃X�|�i�[��S�ēn��
	return spawner_positions_;
}

Vector3 VillagerSpawnerManager::GetterSpawnerPosition() const
{
	// ���l(�ی�Ώ�)�̃X�|�i�[��0�ԖڂɊi�[���ꂽ�ʒu�̂ݓn��
	// �������A�X�|�i�[�̈ʒu���P���i�[����Ă��Ȃ��ꍇ��(0.0f, 0.0f, 0.0f)��n��
	if (spawner_positions_.size() <= 0)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}
	return spawner_positions_[0];
}

void VillagerSpawnerManager::Update()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		villager_spawner[i]->Update();
	}
}

void VillagerSpawnerManager::Render()
{
	for (int i = 0; i < VILLAGER_SPAWNER_NUM; i++)
	{
		villager_spawner[i]->Render();
	}
}