#pragma once

#include "../../../System/Vector3.h"
#include "../CharacterBase.h"

class Fence;

//---------------------------------------------------------------------------------
//	���l(�ی�Ώ�)�N���X
//---------------------------------------------------------------------------------
class Villager : public CharacterBase
{
private:
	// �X�e�[�^�X���
	enum class VillagerStatus
	{
		Idle,				// �ҋ@
		FollowPlayer,		// �v���C���[�ɕt���Ă���
		Damaged,			// �U�����󂯂�
		GoalPoint,			// �ړI�n�ɓ��B
		KnockDown			// �_�E�� 
	};
private:
	VillagerStatus villager_status = VillagerStatus::Idle;		// �X�e�[�^�X���
	int value = static_cast<int>(villager_status);
	// �X�e�[�^�X��Ԃ�ݒ肷��
	void SetterStatus(VillagerStatus status);

public:
	// �R���X�g���N�^
	// pos : ���g�̈ʒu
	// id  : ���g�̒ʂ��ԍ�
	Villager(Vector3 pos, int id);
	~Villager();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

	// �}�l�[�W���ł�������v���C���[�̈ʒu���擾����
	// p_pos : �v���C���[�̈ʒu
	void SetPlayerInfomation(const Vector3& p_pos);

	// �ǂ�������I�u�W�F�N�g��T��
	// pos : �ǂ�������Ώۂ̈ʒu
	void SearchFollowObject(Vector3 pos);

	// �v���C���[�ɒǏ]���邩�̃t���O
	// flag : true  - �Ǐ]����
	//		: false - �Ǐ]���Ȃ� 
	void IsAlwaysFollow(bool flag);

	// �v���C���[�ɒǏ]����
	// vec : �v���C���[�Ƃ̃x�N�g��
	void Follow(Vector3 vec);

	// �S�[���ɓ��B�����Ƃ��̏���
	void GoalAction();

	//void SearchOtherVillagers(const std::vector<Vector3> v_poss);


	void SetFenceInfo(std::vector<Fence*> f_objs);

	//---------------------------------
	// �Q�b�^�[�֐�

	// ���g��ID��n��
	int GetterMyID() const;
	// ���g�̓G�Ƃ̐ڐG��Ԃ�n��
	bool GetterIsCollidingWithEnemy() const;

	//---------------------------------
	// �Z�b�^�[�֐�

	// ���g�̈ʒu��ݒ肷��
	// set_pos : �ݒ肷��ʒu
	void SetterMyPosition(Vector3 set_pos);
	// �G�Ƃ̐ڐG��Ԃ�ݒ肷��
	void SetterIsCollidingWithEnemy(bool is_colliding);
	//---------------------------------

private:
	int my_id_;		// ���l(�ی�Ώ�)���g��ID

	Vector3 player_position_;			// �v���C���[���W�i�[�p
	Vector3 vector_with_player_;		// ���g�ƃv���C���[�̃x�N�g��
	bool is_player_follow_;				// �v���C���[�ɂ��Ă������ǂ���

	bool is_colliding_with_enemy_;		// �G�ƐڐG���Ă��邩�ǂ���

	bool is_search_ = true;				// �v���C���[��T�����邩�ǂ���

	// ���I�u�W�F�N�g���i�[�p�ϐ�
	std::vector<Fence*> fences_;		// ��
};
