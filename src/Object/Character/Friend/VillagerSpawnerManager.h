#pragma once
#include <vector>
#include "../../SpawnerManagerBase.h"
class VillagerSpawner;
#include "../../../System/Vector3.h"

#define VILLAGER_SPAWNER_NUM  1

//---------------------------------------------------------------------------------
//	���l(�ی�Ώ�)�X�|�i�[�}�l�[�W���N���X
//---------------------------------------------------------------------------------
class VillagerSpawnerManager : public SpawnerManagerBase
{

public:
	VillagerSpawnerManager();
	~VillagerSpawnerManager();

	// �X�|�i�[�𐶐�����
	void CreateSpawner(Vector3 pos) override;
	// �X�|�i�[�̐����ʒu��n��
	Vector3 GetterSpawnerPosition() const override;
	// �S�X�|�i�[�̈ʒu���i�[�����ϐ���n��
	std::vector<Vector3> GetterSpawnerPositions() const override;

	// �̂��ɍ폜
	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	// �|�C���^�ŏ����擾
	VillagerSpawner* villager_spawner[VILLAGER_SPAWNER_NUM];	// ���l(�ی�Ώ�)�̃X�|�i�[�Ǘ�

	//std::vector<Vector3> spawner_positions_;	// �������ꂽ�e�X�|�i�[�̈ʒu�̊i�[�p
};
