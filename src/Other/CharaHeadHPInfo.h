#pragma once
#include "../System/Vector3.h"
//#include "HPInfoBase.h"

//---------------------------------------------------------------------------------
//	HP���
//---------------------------------------------------------------------------------
class CharaHeadHPInfo /*: public HPInfoBase*/
{
public:
	CharaHeadHPInfo();

	// ������
	//
	void Init();

	// �X�V
	// my_pos   : ���g�̈ʒu
	// hp_pos_y : Y���W(�L�����N�^�[�̓���ɕ\�������悤��)
	void Update(Vector3 my_pos, float hp_pos_y);

	// �����Ă��邩�ǂ���
	bool IsSurvice();

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
	// damaged_num : �󂯂��_���[�W��
	void SetterIsDamaged(float damaged_num);

private:
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