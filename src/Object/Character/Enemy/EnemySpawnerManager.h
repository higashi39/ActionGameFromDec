#pragma once
#include <vector>
#include "../../SpawnerManagerBase.h"
class EnemySpawner;
#include "../../../System/Vector3.h"

#define ENEMY_SPAWNER_NUM  2

//---------------------------------------------------------------------------------
//	�G�X�|�i�[�}�l�[�W���N���X
//---------------------------------------------------------------------------------
class EnemySpawnerManager : public SpawnerManagerBase
{
public:
	EnemySpawnerManager();
	~EnemySpawnerManager();

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
	EnemySpawner* enemy_spawner[ENEMY_SPAWNER_NUM];		// �G�̃X�|�i�[�Ǘ�

	//std::vector<Vector3> spawner_positions_;	// �������ꂽ�e�X�|�i�[�̈ʒu�̊i�[�p
};
