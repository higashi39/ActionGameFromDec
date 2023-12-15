#pragma once

#include "../../../System/Vector3.h"
#include "../CharacterBase.h"

class FenceBase;

//---------------------------------------------------------------------------------
//	���l(�ی�Ώ�)�N���X
//---------------------------------------------------------------------------------
class Villager : public CharacterBase
{
protected:
	// �X�e�[�^�X���
	enum class VillagerStatus
	{
		Idle,				// �ҋ@
		FollowPlayer,		// �v���C���[�ɕt���Ă���
		Damaged,			// �U�����󂯂�
		GoalPoint,			// �ړI�n�ɓ��B
		Reached,			// ���B�ς�
		KnockDown			// �_�E�� 
	};
	VillagerStatus villager_status = VillagerStatus::Idle;		// �X�e�[�^�X���
public:
	int GetterVillagerStatus() const;
	int value = static_cast<int>(villager_status);
private:
	// �X�e�[�^�X��Ԃ�ݒ肷��
	void SetterStatus(VillagerStatus status);

public:
	// �R���X�g���N�^
	// handle	: ���f���n���h��
	// pos		: ���g�̈ʒu
	// id		: ���g�̒ʂ��ԍ�
	Villager(int handle, Vector3 pos, int id);
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
	void SearchPlayer(Vector3 pos);

	// �v���C���[�ɒǏ]���邩�̃t���O
	// flag : true  - �Ǐ]����
	//		: false - �Ǐ]���Ȃ� 
	void IsAlwaysFollow(bool flag);

	// �w�肵���ʒu�܂ňړ�������
	// vec : �w�肷��ʒu
	void FollowObject(Vector3 vec);

	// �S�[���ɓ��B�����Ƃ��̏���
	void GoalAction();

	//void SearchOtherVillagers(const std::vector<Vector3> v_poss);


	void SetFenceInfo(std::vector<FenceBase*> f_objs);

	//---------------------------------
	// �Q�b�^�[�֐�

	// ���g��ID��n��
	int GetterMyID() const;
	// ���g�̓G�Ƃ̐ڐG��Ԃ�n��
	bool GetterIsCollidingWithEnemy() const;
	// ���g���ړI�n�ɓ��B�������ǂ�����n��
	bool GetterIsGoal() const;

	// �P�t���[���O�̈ʒu��n��
	Vector3 GetterMyBeforePosition() const;

	//---------------------------------
	// �Z�b�^�[�֐�

	// ���g�̈ʒu��ݒ肷��
	// set_pos : �ݒ肷��ʒu
	void SetterMyPosition(Vector3 set_pos);
	// �G�Ƃ̐ڐG��Ԃ�ݒ肷��
	void SetterIsHitEnemy(bool ishit);
	// ���l���m�̐ڐG��Ԃ�ݒ肷��
	void SetterIsHitVillager(bool ishit);
	//---------------------------------

	int add_time_ = 0;

private:
	int my_id_;		// ���l(�ی�Ώ�)���g��ID

	Vector3 before_pos_;

	Vector3 player_position_;			// �v���C���[���W�i�[�p
	Vector3 vector_with_player_;		// ���g�ƃv���C���[�̃x�N�g��
	float length_with_player_;			// �v���C���[�Ƃ̋���
	bool is_player_follow_;				// �v���C���[�ɂ��Ă������ǂ���

	// �����蔻��֌W
	// �ڐG���Ă��邩�ǂ���
	bool ishit_enemy_ = false;		// �G
	bool ishit_fence_ = false;		// ��
	bool ishit_villager_ = false;	// ���l

	bool is_search_ = true;				// �v���C���[��T�����邩�ǂ���
	bool is_goal_ = false;				// �S�[���������ǂ���

	bool is_render_ = true;			// �`�悷�邩�ǂ���

	// ���I�u�W�F�N�g���i�[�p�ϐ�
	std::vector<FenceBase*> fences_;		// ��
};
