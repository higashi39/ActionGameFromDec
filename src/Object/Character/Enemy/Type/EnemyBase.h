#pragma once
#include <vector>
#include "../../CharacterBase.h"
#include "../../../../System/Vector3.h"
#include "../../../../Other/CharaHeadHPInfo.h"

class EnemySword;
class EnemyPatrol;
class VillagerManager;
class Villager;
class Player;

//---------------------------------------------------------------------------------
//	�G�}�l�[�W���N���X
//---------------------------------------------------------------------------------
class EnemyBase : public CharacterBase
{
public:
	// �X�e�[�^�X���
	enum EnemyStatus
	{
		Idle,				// �ҋ@(����)
		SearchingVillager,	// ���l���G��
		TrackingVillger,	// ���l�ǔ�
		Attack,				// �U��
		Damage,				// �U�����󂯂�
		KnockDown			// �_�E��
	};
protected:
	EnemyStatus enemy_status = EnemyStatus::Idle;		// �X�e�[�^�X���

	//�f�o�b�O�p
	int value = static_cast<int>(enemy_status);
	// �G�̃X�e�[�^�X��ݒ肷��
	void SetterStatus(EnemyStatus status);

public:
	EnemyBase();
	~EnemyBase();

	// �X�V
	// ���ꂼ��̓G�ňقȂ鏈���Ȃ̂ŁA�������z�֐��ɂ���
	virtual void Update() = 0;
	// �`��
	void Render();
	// 2D�p�`�揈��
	// ���HP(Render�֐��ŏ�������Ɛ������`�悳��Ȃ�)
	void RenderFor2D();

	// ���l��T��
	void SearchVillagers();

	// ���l��ǐՂ���
	// near_vec : ��ԋ߂������̑��l�Ƃ̃x�N�g��
	void ChaseNearVillager(Vector3 near_vec);

	// �U������(�Α��l(�ی�Ώ�))
	void EnemyAttack(std::vector<Villager*>& v_objs_);
	// �U���̃N�[���_�E�����ԃJ�E���g����
	void EnemyCountAttackCoolTime();

	//// �e�G�I�u�W�F�N�g��HP�`�揈��
	//void EnemyHPRender();
	// 
	// ����͈͂̏���
	bool IsViewRange();


	//---------------------------------
	// �Q�b�^�[�֐�

	// ���g��ID��n��
	int GetterMyID() const;

	//// ���g�ƃv���C���[�Ƃ̐ڐG��Ԃ�n��
	//bool GetterIsCollisionWithPlayer() const;
	//// ���g�Ƒ��l(�ی�Ώ�)�Ƃ̐ڐG��Ԃ�n��
	//bool GetterIsCollisionWithVillager() const;

	//---------------------------------
	// �Z�b�^�[�֐�

	// ���g�̈ʒu��ݒ肷��
	// set_pos : �ݒ肷��ʒu
	void SetterMyPosition(Vector3 set_pos);

	// HP�����炷�t���O�𗧂Ă�
	// is_enable : �_���[�W�������s���Ă�������
	void SetterIsDamageToPlayer(bool is_enable);


	// ���L�����N�^�[�̈ʒu�����炤
	// �v���C���[
	void FetchPlayerPosition(const Vector3& pos);
	// ���l
	void FetchVillagersPosition(const std::vector<Villager*>& v_objs);

protected:
	int my_id_;							// ���g�̎��ʔԍ�

	Villager* near_villager_;			// ��ԋ߂����l�̏��i�[�p
	//float minimum_length_ = 10000.0f;			// ���l�Ƃ̋���
	Vector3 minimum_position_;			// ��ԋ߂����l�̈ʒu�i�[�p
	Vector3 minimum_vector_;			// ��ԋ߂����l�Ƃ̃x�N�g���i�[�p

	//bool is_colliding_with_player_;			// �v���C���[�ƐڐG���Ă��邩�ǂ���

	bool is_enable_attack_;			// �U���������L���ł��邩�ǂ���
	float attack_cool_time_;		// �U���̃N�[���_�E������

	Vector3 fetch_player_position_;
	std::vector<Villager*> fetch_villagers_;

	bool is_enable_damage_ = false;		// �_���[�W���󂯂�ǂ���

protected:
	// HP���
	CharaHeadHPInfo hp_;
};
