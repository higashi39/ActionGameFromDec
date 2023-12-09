#pragma once
#include "../System/Vector2.h"

//---------------------------------------------------------------------------------
// HP���(2D�X�N���[���`��)
// HP����2D��ʍ��W�ɕ\������
//---------------------------------------------------------------------------------
class ScreenHPInfo
{
public:
	ScreenHPInfo();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Render();

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
	Vector2 hp_pos_;

	// HP�̒l
	float hp_num_;
	// �`�掞�̒l
	float hp_value_;
	// �c��HP
	Vector2 hp_min_pos_;			// �ŏ�
	Vector2 hp_max_pos_;			// �ő�
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