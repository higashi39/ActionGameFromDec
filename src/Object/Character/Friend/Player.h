#pragma once
#include <vector>
#include "../CharacterBase.h"
//#include "../../../Other/ScreenHPInfo.h"
class EnemyBase;
class FenceBase;

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public CharacterBase
{
private:
	// �X�e�[�^�X���
	enum class PlayerStatus
	{
		Idle,					// �ҋ@
		Run,					// �ړ�(����)
		Attack,					// �U��
		Damage,					// �U�����󂯂�
		KnockDown,				// �_�E��
	};
private:
	PlayerStatus player_status = PlayerStatus::Idle;	// �X�e�[�^�X���
	//int value = static_cast<int>(player_status);
	//// �X�e�[�^�X��Ԃ�ݒ肷��
	void SetterStatus(PlayerStatus status);

public:
	Player();
	~Player() {};

	// �v���C���[��p�X�V
	void Update() override;
	// �`��
	void Render() override;
	// 2D�p�`�揈��
	void RenderFor2D();

	// �U������(�ΓG)
	void PlayerAttack(EnemyBase* e_obj);

	// �N�[���^�C�����ԃJ�E���g����
	void PlayerCountAttackCoolTime();

	// �S�G�̏����擾
	void FetchEnemyInfo(const std::vector<EnemyBase*>& e_objs);
	// ��̏����擾����
	void FetchFenceInfo(const std::vector<FenceBase*>& f_objs);

	//--------------------------
	// �Q�b�^�[�֐�

	// ���f���f�[�^�̃|�C���^��n��
	int* GetterPlayerModelPointer();
	// �X�e�[�^�X��Ԃ�n��
	PlayerStatus GetterPlayerStatus();

	// �Z�b�^�[�֐�

	// �G�ƐڐG�������ǂ�����ݒ肷��
	// is_hit : �ڐG�������ǂ����̃t���O
	void SetterIsHitEnemy(bool is_hit);

	// �S�G�̏����m�F����
	bool CheckHitEnemy();

private:

	std::vector<EnemyBase*> enemy_objs_;			// �G�̏����i�[����z��
	std::vector<FenceBase*> fence_objs_;				// ��̏����i�[����z��

	bool is_enable_attack_;			// �U���������L���ł��邩�ǂ���
	float attack_cool_time_;		// �U���̃N�[���_�E������

	bool is_enable_spacekey_ = false;		// �X�y�[�X�L�[�����������ǂ���

//protected:
//	// HP���
//	ScreenHPInfo hp_;
};
