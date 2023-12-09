#pragma once
#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
// HP���x�[�X�N���X
// HP�����X�V�A�`�悷�鏈���̃x�[�X�N���X  
//---------------------------------------------------------------------------------
class HPInfoBase
{
public:
	HPInfoBase();

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;

	// �_���[�W����
	// damage_num : �_���[�W��
	void Damaged();

	// �_���[�W����HP��������
	void HPDecrease();

	// �m�b�N�_�E������
	void Dead();

	//------------------------
	// �Z�b�^�[�֐�

	// �_���[�W���󂯂�����ݒ肷��
	// is_damaged : �_���[�W���󂯂����ǂ���
	// damaged_num : �󂯂��_���[�W��
	void SetterIsDamaged(bool is_damaged, float damaged_num);

protected:
	// HP�\���p���W
	Vector3 hp_pos_;

	// HP�̒l
	float hp_num_;
	// �`�掞�̒l
	float hp_value_;
	// �c��HP
	Vector3 hp_min_pos_;			// �ŏ�
	Vector3 hp_max_pos_;			// �ő�
	// HP1������̒l
	float hp_per_;

	// HP�`��p
	// ��
	float hp_width_ = 30;	// ����
	float hp_height_ = 5;	// �c��
	// HP������������ԐF�ŕ\��
	float hp_red_x_;
	float hp_red_value_;

	// �_���[�W���󂯂����ǂ���
	bool is_damaged_;
	// �󂯂��_���[�W��
	float damaged_num_;

	// �L�����N�^�[�̐����t���O
	// ������̓I�u�W�F�N�g���X�V�E�`�揈�����邵�Ȃ��ŏ�������
	bool is_survive_ = true;
};