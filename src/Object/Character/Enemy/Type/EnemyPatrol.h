#pragma once
#include <vector>
#include "EnemyBase.h"

//---------------------------------------------------------------------------------
//	�G-����-�N���X
//---------------------------------------------------------------------------------
class EnemyPatrol : public EnemyBase
{
public:
	// �R���X�g���N�^
	// handle		: ���f���n���h��
	// pos			: ���g�̈ʒu 
	// rot			: ���g�̌���
	// id			: ���g�̒ʂ��ԍ�
	// patrol_pos1	: ����܂�Ԃ��ʒu�P 
	// patrol_pos2	: ����܂�Ԃ��ʒu�Q 
	EnemyPatrol(int handle, Vector3 pos,Vector3 rot, int id, Vector3 patrol_pos1, Vector3 patrol_pos2);
	~EnemyPatrol();

	// �X�V
	void Update() override;

	// ����A�N�V����
	void PatrolAction();

private:
	//-------------------------------
	// ����A�N�V�����p�ϐ�
	Vector3 patrol_pos1_;			// ����܂�Ԃ��ʒu1
	Vector3 patrol_pos2_;			// ����܂�Ԃ��ʒu2
	bool check_patrol_;				// �����P�̏���ʒu�ɍs�����߃t���O
	float turn_cool_time_;			// �܂�Ԃ��܂ł̃N�[���^�C��
};