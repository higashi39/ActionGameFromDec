#pragma once
#include <vector>
#include "../../../System/Vector3.h"
class Fence;
class Villager;
class Player;

//---------------------------------------------------------------------------------
//	���l�}�l�[�W���N���X
//---------------------------------------------------------------------------------
class VillagerManager
{
public:
	VillagerManager();
	~VillagerManager();

	// ���l�𐶐�����
	// pos    : �X�|�[�������ʒu
	void SpawnVillager(Vector3 pos);

	// �����ȊO�̑��l(�ی�Ώ�)�̈ʒu��Ԃ�
	// my_id : �����̎���ID
	//std::vector<Villager> FetchOtherVillagers(int my_id);

	// �X�V
	// p_pos       : �v���C���[�̈ʒu
	void Update(const Vector3& p_pos);
	// �`��
	void Render();

	// �����l�I�u�W�F�N�g�Ƃ̓����蔻��
	void HitOtherVillagers();

	// ��̏������炤
	void FetchFenceInfo(const std::vector<Fence*>& f_objs);

	//---------------------------------
	// �Q�b�^�[�֐�

	// �S���l(�ی�Ώ�)�̊e����n��
	//// ID
	//std::vector<int> GetterVillagersID() const;
	// �S����n��
	std::vector<Villager*> GetterVillagers() const;
	//---------------------------------

private:
	int set_id_num_ = 0;		// �ʂ��ԍ��ݒ�p

	std::vector<Villager*> villagers_;			// �S���l�̊i�[�z��
	// ���I�u�W�F�N�g���i�[�p�ϐ�
	std::vector<Fence*> fences_;				// ��
};
