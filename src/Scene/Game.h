#pragma once
#include "SceneManager.h"
#include <string>

#include "../System/Vector3.h"
#include "../Other/MakeString.h"
#include "../Other/StatusData.h"

// �V�X�e��
class Camera;

// �X�e�[�W�\��
class Ground;
class RockManager;
class FenceManager;
class Box;

// �L�����N�^�[�E�A�C�e��
class Player;
class VillagerManager;
class EnemyManager;
class Sword01;

//---------------------------------------------------------------------------------
// �Q�[���V�[���N���X
//---------------------------------------------------------------------------------
class Game : public Scene
{
public:
	// �|�C���^�ϐ�
	Camera* camera;									// �J����
	Ground* ground;									// �n��
	RockManager* rock_manage;						// ��Ǘ�
	FenceManager* fence_manage;						// ��
	Box* box;										// ��
		
	Player* player;									// �v���C���[
	VillagerManager* villager_manage;				// ���l(�ی�Ώ�)�L�����N�^�[�Ǘ�
	EnemyManager* enemy_manage;						// �G�L�����N�^�[�Ǘ�
	Sword01* sword01;								// ����P

public:
	Game(SceneManager* p_manager);
	~Game();

	// �X�V
	void Update();

	// �`��
	void Render();

	// �`��q�֐�
	// �I�u�W�F�N�g�֘A
	void ObjectRender();
	// �Q�[���{��UI�֘A
	void UIRender();

	//-------------------------------------
	// �X�e�[�W���������֘A

	// �X�e�[�W�I�𔽉f����
	// �X�e�[�W�I���V�[���őI�����ꂽ�X�e�[�W��ݒ�
	void SetUpStageNumber();

	// �I�����ꂽ�X�e�[�W�̃p�X���擾
	std::string GetSelectedStagePath(int stage);

	// �X�e�[�W�p�̃t�@�C���ǂݍ���
	void LoadCSVFile(std::string file_path);

	// �X�e�[�W�̊e�}�X�̍��W�ݒ�
	void CalculateMapChip();

	// �X�e�[�W��������
	// type : �n�����I�u�W�F�N�g�pID
	// pos  : ���̃I�u�W�F�N�g���ݒu�������W
	// rot  :							�p�x
	void CreateStage(int type, Vector3 pos, Vector3 rot);



	// �Q�[���X�R�A�����_����
	// point : ����X�R�A�Ɋ܂ޓ_��
	void AddGameScore(int point);

	//-----------------------------------
	// �^�C���֘A
	// �Q�[���J�n�O�J�E���g�_�E������
	void GameStartcountDown();			// �J�E���g�_�E��
	void RenderGameStartCountDown();	// �`��p

	// �Q�[���^�C������
	void GameTimeUpdate();
	// �Q�[���I������
	void TimeUp();

private:
	// �X�e�[�W�ԍ�
	int stage_;

	// �Q�[���X�R�A�֘A
	int score_ = 0;					// �g�[�^���X�R�A

	// �Q�[���X�e�[�^�X
	int game_status = GameStatus::GameReady;

	// �Q�[���^�C���֘A
	int count_gamestart = 0;		// �Q�[���J�n�O�J�E���g�_�E��
	bool is_gamestart = false;		// �Q�[���J�n�O�J�E���g�_�E���̕`��t���O

	int timelimit_toframe_ = 0;		// ��������
	int timelimit_toshow_ = 0;		// �`��p

	bool is_game = false;

	// has�֌W
	MakeString make_string;
};