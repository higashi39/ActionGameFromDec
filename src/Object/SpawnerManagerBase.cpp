#include "../System/Random.h"

#include "../Main.h"
#include "../Scene/Game.h"
#include "SpawnerManagerBase.h"

SpawnerManagerBase::SpawnerManagerBase()
{
	get_position_.clear();
}

Vector3 SpawnerManagerBase::SetSpawnerPosition()
{
	int max = 10;			// �����ő�l
	int min = -10;			// �����ŏ��l

	// ������X, Z���W��2������
	int rand_x = GetRandomF(max, min);
	int rand_z = GetRandomF(max, min);

	// �ʒu��ݒ肷��	(Y���W��0.0f�Œ�)
	Vector3 set_pos;
	set_pos.x = rand_x;
	set_pos.z = rand_z;
	set_pos.y = 0.0f;

	// �����Őݒ肵���ʒu��Ԃ�
	return set_pos;
}

void SpawnerManagerBase::FetchSpawnerPosition()
{
	// �����_���ɐݒ肳�ꂽ�ʒu���擾
	get_position_.set(SetSpawnerPosition().x, SetSpawnerPosition().y, SetSpawnerPosition().z);

	//// �擾�����ʒu�ɑ��l�X�|�i�[�𐶐�
	//villager_spawner[i] = new VillagerSpawner(rand_pos);
}

//void SpawnerManagerBase::Initialize()
//{
//}