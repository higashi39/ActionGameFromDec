#pragma once
#include <vector>
#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
//	�X�|�i�[�}�l�[�W���x�[�X�N���X
//---------------------------------------------------------------------------------
class SpawnerManagerBase
{
public:
	SpawnerManagerBase();
	~SpawnerManagerBase() {};

	// �X�|�i�[�𐶐�����
	// pos : �X�|�i�[�ݒu�ʒu
	virtual void CreateSpawner(Vector3 pos) = 0;
	// �X�|�i�[�̐����ʒu��n��
	virtual Vector3 GetterSpawnerPosition() const = 0;
	// �S�X�|�i�[�̈ʒu���i�[�����ϐ���n��
	virtual std::vector<Vector3> GetterSpawnerPositions() const = 0;

	// �ʒu�������_���ŎZ�o����
	Vector3 SetSpawnerPosition();
	// �X�|�i�[�̈ʒu���擾����
	void FetchSpawnerPosition();

	// �̂��ɍ폜�\��
	//void Initialize();
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;

protected:
	Vector3 get_position_;

	std::vector<Vector3> spawner_positions_;	// �������ꂽ�e�X�|�i�[�̈ʒu���i�[
};