#pragma once
#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
//	�X�e�[�^�X�f�[�^
//---------------------------------------------------------------------------------
// �Q�[�����
enum GameStatus
{
	GameReady,				// �Q�[���J�n�O
	GamePlay,				// �v���C
	//GAME_STATUS_SELECT,	// �X�e�[�^�X�I��
	GamePause,				// �|�[�Y
	GameFinish,				// �Q�[���I��
	GAME_CLEAR,				// �Q�[���N���A
	GAME_OVER,				// �Q�[���I�[�o�[
};

//// �v���C���[���
//enum PLAYERSTATUS
//{
//	PLAYER_MOVE,			// �ړ�
//	PLAYER_TRACK_SELECT,	// �ǐՑΏۑI��
//	PLAYER_TRACKING,		// �ǐ�
//	PLAYER_ATTACK,			// �U����
//	PLAYER_SETCHECK,		// �`�F�b�N�|�C���g�ݒu
//	PLAYER_SETOBSTACLE,		// ��Q���ݒu
//	PLAYER_STOP,			// �~�܂�(�����Ȃ�)
//};

// �v���C���[�ǐՑΏۏ��
enum PLAYERTRACKEDSTATUS
{
	ENEMY,					// �G
	FENCE,					// ��
	NONE,					// �����ǐՂ��Ȃ�
};

//// �G�̍\����
//struct  ENEMTDATA
//{
//	int type;				// ���
//};

// �G���
// ���ۑ�F�G�ɂ���čs�����قȂ�̂ŁA���ƂňႤ�ꏊ�ɂ����Ȃ肷��
enum EnemyType
{
	TypeStop,				// ��~
	TypePatrol,				// ����
	ENEMY_WALK,				// �p�j(�̂��ɏ���)
	ENEMY_ATTACK,			// �U��
	ENEMY_DESTROY,			// ���j�����
};

//struct StageInfo
//{
//	Vector3 left_pos = {0.0f,0.0f,0.0f};		// ���[
//	Vector3 right_pos = { 0.0f,0.0f,0.0f };		// �E�[
//	float side_length = 0.0f;		// ����
//};
//StageInfo stage_info;
//
//
//// �}�b�v�ݒ�
//void SetupStageSize(Vector3 left_pos, Vector3 right_pos, float side_length);
//
//StageInfo GetterStageSize();