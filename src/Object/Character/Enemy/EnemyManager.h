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
	// handle		: ���f���n���h��
	// pos			: �X�|�[�������ʒu
	// rot			: �X�|�[�����ꂽ�Ƃ��̌���
	// type			: �G�̎��
	// patrol_pos1�@: ����܂�Ԃ��n�_�P�i�G�i����^�j�̂݁j
	// patrol_pos2�@: ����܂�Ԃ��n�_�Q�i�G�i����^�j�̂݁j
	void SpawnEnemy(int handle, int type, Vector3 pos, Vector3 rot, Vector3 patrol_pos1, Vector3 patrol_pos2);

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
