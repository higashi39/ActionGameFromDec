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
	// pos   : ���g�̈ʒu 
	// id    : ���g�̒ʂ��ԍ�
	EnemyPatrol(Vector3 pos, int id);
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