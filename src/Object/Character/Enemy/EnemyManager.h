#pragma once
#include <vector>
#include "../../../System/Vector3.h"
class EnemySword;
class EnemyPatrol;
class VillagerManager;
class Villager;

//---------------------------------------------------------------------------------
//	�G�}�l�[�W���N���X
//---------------------------------------------------------------------------------
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	// �G�𐶐�����
	// pos    : �X�|�[�������ʒu
	// type   : �G�̎��
	void SpawnEnemy(int type, Vector3 pos);

	// �X�V
	void Update(const Vector3& p_pos, const std::vector<Villager*>& v_objs);
	// �`��
	void Render();
	// �e�G�I�u�W�F�N�g��2D�`�揈��
	void RenderFor2D();

	// ���G�I�u�W�F�N�g�Ƃ̓����蔻��
	void HitOtherEnemies();

	//---------------------------
	// �Q�b�^�[�֐�

	// �S�G�I�u�W�F�N�g����n��
	std::vector<EnemyBase*> GetterEnemies() const;
	//// �S���l(�ی�Ώ�)����n��
	//std::vector<Villager*> GetterVillagers() const;

protected:
	int set_id_num_ = 0;		// �ʂ��ԍ��ݒ�p

	std::vector<EnemyBase*> enemies_;		// �S�G�̊i�[�z��
};
