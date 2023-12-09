#include <vector>
#include <ctime>

#include <fstream>
#include <sstream>

#include "../Main.h"
#include "Game.h"
#include "../System/Random.h"
//#include "../System/Vector3.h"
#include "../System/Hit.h"

#include "../Other/Camera.h"
#include "../Object/Environment/Ground.h"
#include "../Object/Environment/Rock/RockManager.h"
#include "../Object/Environment/FenceManager.h"
//#include "../Object/Environment/Box.h"

#include "../Object/Character/Friend/Player.h"
#include "../Object/Character/Friend/VillagerManager.h"
#include "../Object/Character/Enemy/EnemyManager.h"
#include "../Object/Item/Weapon/Sword01.h"

// �}�b�v�쐬���������邩�ǂ���
#define IS_USE_MAP 0

Game::Game(SceneManager* p_manager) : Scene(p_manager), count_gamestart(180), is_gamestart(true),
timelimit_toframe_(10800), score_(0)
{
	stage_ = 0;

	// �e�I�u�W�F�N�g�𓮓I�m��
	camera = new Camera();											// �J����
	ground = new Ground();											// �n��
	rock_manage = new RockManager();								// ��Ǘ�
	fence_manage = new FenceManager();								// ��
	//box = new Box();												// ��
	player = new Player();											// �v���C���[
	villager_manage = new VillagerManager();	// ���l(�ی�Ώ�)�L�����N�^�[�Ǘ�
	enemy_manage = new EnemyManager();								// �G�L�����N�^�[�Ǘ�
	sword01 = new Sword01();										// ����P

	// �X�e�[�W�I���őI�΂ꂽ�X�e�[�W���擾
	// ���̃X�e�[�W��CSV�t�@�C����ǂݍ���
	LoadCSVFile(GetSelectedStagePath(stage_));
	// �e�I�u�W�F�N�g�̏��������֘A
	// ���l(�ی�Ώ�)
	//villager_spawn_manage->CreateSpawner();			// �X�|�i�[����
	//villager_manage->ObjectInitializeSetting();		// �L�����N�^�[�ݒ�
	//// �G
	//enemy_spawn_manage->CreateSpawner();			// �X�|�i�[�̐���
	//enemy_manage->ObjectInitializeSetting();		// �L�����N�^�[�ݒ�
	// ��
	//fence_manage->ObjectInitializeSetting();		// �I�u�W�F�N�g�ݒ�

	// �`��p�Ƀt���[����b���ɕύX����
	timelimit_toshow_ = timelimit_toframe_ / 60;

	//enemy_manage->SpawnEnemy({ 0.0f, 0.0f, 0.0f }, EnemyType::TypeStop);
}

Game::~Game()
{
	// �e�I�u�W�F�N�g�̉��
	delete camera;								// �J����
	delete ground;								// �n��
	delete rock_manage;							// ��
	if (fence_manage != NULL)
	{
		delete fence_manage;								// ��
	}
	delete player;								// �v���C���[
	delete villager_manage;						// ���l(�ی�Ώ�)�L�����N�^�[�Ǘ�
	delete enemy_manage;						// �G�L�����N�^�[�Ǘ�
	delete sword01;								// ����P
}

void Game::Update()
{
	switch (game_status)
	{
	case GameStatus::GameReady:				// �Q�[���J�n�O
		// �Q�[���J�n�O�̃J�E���g�_�E������
		is_game = true;
		GameStartcountDown();
		break;
	case GameStatus::GamePlay:				// �Q�[���v���C
		// �Q�[���^�C������
		GameTimeUpdate();
		break;
	case GameStatus::GameFinish:			// �Q�[���I��
		// �Q�[���I������
		TimeUp();
		break;

	case GameStatus::GamePause:				// �Q�[���|�[�Y
		// �Q�[�����ꎞ���f����
		break;
	}

	//// Esc�L�[�ŃQ�[�����ꎞ���f�ł���悤�ɂ���
	//if (PushHitKey(KEY_INPUT_ESCAPE))
	//{
	//	game_status = GameStatus::GamePause;
	//}

	// �e�I�u�W�F�N�g�X�V
	camera->Update(player->GetterMyPosition());

	if (is_game)
	{
		player->Update();									// �v���C���[
		//villager_spawn_manage->Update();															// ���l(�ی�Ώ�)�X�|�i�[�Ǘ�
		//enemy_spawn_manage->Update();																// �G�X�|�i�[�Ǘ�
		villager_manage->Update(player->GetterMyPosition());	// ���l(�ی�Ώ�)�L�����N�^�[�Ǘ�
		enemy_manage->Update(player->GetterMyPosition(), villager_manage->GetterVillagers());		// �G�L�����N�^�[�Ǘ�
		//enemy_patrol->EnemyUpdate(player->GetterMyPosition(), villager_manage->GetterVillagers());		// �G�L�����N�^�[�Ǘ�
		sword01->Update(player->GetterPlayerModelPointer());										// ����P								

		// �e�I�u�W�F�N�g�ɕK�v�ȏ���n��
		player->FetchEnemyInfo(enemy_manage->GetterEnemies());		// �G
		// ����
		if (fence_manage != NULL)
		{
			player->FetchFenceInfo(fence_manage->GetterFenceInfos());	// �v���C���[
			villager_manage->FetchFenceInfo(fence_manage->GetterFenceInfos());	// ���l
		}
	}
}

void Game::Render()
{
#if SHOW_DEBUG
	DrawFormatString(10, 10, GetColor(255, 255, 255), "�Q�[�����");
#endif

	ObjectRender();		// �I�u�W�F�N�g
	UIRender();			// �Q�[���{��UI
}

void Game::ObjectRender()
{
	// �e�I�u�W�F�N�g�`��
	camera->Render();						// �J����
	ground->Render();						// �n��
	rock_manage->Render();					// ��Ǘ�
	//box->Render();							// ��
	if (fence_manage != NULL)
	{
		fence_manage->Render();					// ��
	}
	player->Render();						// �v���C���[
	villager_manage->Render();				// ���l(�ی�Ώ�)�L�����N�^�[�Ǘ�
	enemy_manage->Render();					// �G�L�����N�^�[�Ǘ�
	sword01->Render();						// ����P
	// �S�[���̕`��
	DrawLine3D(VGet(-20.0f, 0.1f, 150.0f), VGet(20.0f, 0.1f, 150.0f), GetColor(255, 0, 0));
}

void Game::UIRender()
{
#if SHOW_DEBUG
	//DrawExtendStringToHandle(10, 80,
	//	0.15f,
	//	0.15f,
	//	"�e�X�g�\���@�I�u�W�F�N�g�����O�ɕ\������Ă��邩ABCabc123",
	//	GetColor(255, 255, 255), font_handle_);
#endif

	// 2D�`��
	// HP
	player->RenderFor2D();						// �v���C���[
	enemy_manage->RenderFor2D();				// �G

	//----------------------------------------
	// �Q�[���^�C��
	// int�^ -> string�^
	std::string str = std::to_string(timelimit_toshow_);
	// string�^ -> const char*�^
	const char* str_tochar = str.c_str();
	// ���̌v�Z
	//int width = GetDrawStringWidthToHandle(str_tochar, -1, font_handle_) * 0.15f;
	//int x = (SCREEN_W - width) / 2;
	//DrawExtendStringToHandle(x, 10,
	//	0.15f,
	//	0.15f,
	//	str_tochar,
	//	GetColor(255, 255, 255), font_handle_);
	make_string.DrawStringCenterX(10, 0.17f, str_tochar, 255, 255, 255, font_handle_);

	//----------------------------------------
	// �X�R�A
	make_string.DrawString(10, 10, 0.17f, "�Ƃǂ����l���F", 255, 255, 255, font_handle_);
	make_string.DrawString(175, 10, 0.17f, "000", 255, 255, 255, font_handle_);

	//----------------------------------------
	// �Q�[���J�n�O�J�E���g�_�E���`�揈��
	if (game_status == GameStatus::GameReady)
	{
		RenderGameStartCountDown();
	}
}

//---------------------------------------
// �X�e�[�W���������֘A

void Game::SetUpStageNumber()
{

}

std::string Game::GetSelectedStagePath(int stage)
{
	std::string csvfile_path;		//CSV�t�@�C���̃p�X�i�[�p
	// �I�����ꂽ�X�e�[�W�̃t�@�C���p�X��n��
	switch (stage)
	{
		// �w�肵���X�e�[�W�̃p�X��n��
	case 0:		// �X�e�[�W�P
		csvfile_path = "data/CSV/stage1.csv";
		//SetupStageSize({ -150.0f, 0.0f, 0.0f }, { 150.0f,0.0f,0.0f }, 300.0f);
		break;
	case 1:		// �X�e�[�W�Q
		csvfile_path = "data/CSV/stage2.csv";
		//SetupStageSize({ -150.0f, 0.0f, 0.0f }, { 150.0f,0.0f,0.0f }, 300.0f);
		break;
	}

	return csvfile_path;
}

void Game::LoadCSVFile(std::string file_path)
{
	// CSV�t�@�C����ǂݍ��ނ��߂̃t�@�C���X�g���[�����J��
	std::ifstream file(file_path);

	// �t�@�C�����������J������
	if (!file.is_open())
	{
		printfDx("�t�@�C���ǂݍ��݂��������s���܂���ł���\n");
	}


	// �P�s����
	std::string line;
	while (std::getline(file, line))
	{
		if (file.eof())
			break;
		if (line.empty())
			continue;

		int start_num = 0;		// ���׎n�߂�ʒu
		int comma_num = 0;		// �J���}�̐�

		// �X�|�[���̐ݒ肷�邽�߂Ɋe�����i�[����ϐ������
		int counter = 0;
		int type = 0;						// ���
		Vector3 pos = { 0.0f,0.0f,0.0f };	// �ʒu
		Vector3 rot = { 0.0f,0.0f,0.0f };	// ����

		while (comma_num < 7)
		{
			// start_num�̈ʒu����̃J���}�̈ʒu�𒲂ׂ�
			std::size_t comma_position = line.find(',', start_num);
			// ���ׂ��J���}�̈ʒu�܂ł̒l�����߂�
			std::string cut_str = line.substr(start_num, comma_position - start_num);

			switch (counter)
			{
			case 0:			// �L�����N�^�[�̎��
				type = std::stoi(cut_str);
				++comma_num;
				break;
			case 1:			// �w���W
				pos.x = std::stoi(cut_str);
				++comma_num;
				break;
			case 2:			// �x���W
				pos.y = std::stoi(cut_str);
				++comma_num;
				break;
			case 3:			// �y���W
				pos.z = std::stoi(cut_str);
				++comma_num;
				break;
			case 4:			// �]�p�x
				rot.x = std::stoi(cut_str);
				++comma_num;
				break;
			case 5:			// �x�p�x
				rot.y = std::stoi(cut_str);
				++comma_num;
				break;
			case 6:			// �y�p�x
				rot.z = std::stoi(cut_str);
				++comma_num;
				break;
			}

			// �J�E���^�[�𑝂₷
			++counter;
			// start_num��(���ׂ��J���}�̈ʒu�{�P)��������
			start_num = comma_position + 1;
		}
		CreateStage(type, pos, rot);
		// �f�[�^�̓J���}��؂�Ȃ̂ŁA����ł͂��܂������Ȃ�
		//std::stringstream ss(line);
		//ss >> type >> pos.x >> pos.y >> pos.z;
		//printfDx("type : %d / pos : %f, %f, %f\n", type, pos.x, pos.y, pos.z);
		//CreateStage(type, pos);


		// �擾�����s����1�������\������
		//int index = 0;
		//for (char ch : line)
		//{
		//	// �J���}�̓X�L�b�v����
		//	if (ch == ',')
		//	{
		//		continue;
		//	}
		//	else
		//	{
		//		switch (index)
		//		{
		//		case 0:
		//			type = (int)(ch - '0');
		//			break;
		//		case 1:
		//			//pos.x = (int)(ch - '1');
		//			break;
		//		}
		//		++index;
		//	}
		//}
	}

	// �t�@�C�������
	file.close();

}

void Game::CalculateMapChip()
{
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			Vector3 pos;
			// �ݒ肷��}�b�v�T�C�Y�Œ��S���W�̎������l����
		}
	}
}


void Game::CreateStage(int type, Vector3 pos, Vector3 rot)
{
	switch (type)
	{
	case 0:	// ���������Ȃ�(�n�ʂ̂�)
		break;
	case 1:	// �S�[��
		break;
	case 2:	// ���l
		villager_manage->SpawnVillager(pos);			// �X�|�i�[����
		//villager_manage->ObjectInitializeSetting(0);		// �L�����N�^�[�ݒ�
		break;
	case 3:	// �G(��~�^)
		enemy_manage->SpawnEnemy(EnemyType::TypeStop, pos);
		break;
	case 4:	// �G(����^)
		enemy_manage->SpawnEnemy(EnemyType::TypePatrol, pos);		// �L�����N�^�[�ݒ�
		break;
	case 5: // ��P
		rock_manage->CreateObject(1, pos, rot);
		break;
	case 6: // ��Q
		rock_manage->CreateObject(2, pos, rot);
		break;
	case 7: // ��R
		rock_manage->CreateObject(3, pos, rot);
		break;
	case 8: // ��S
		rock_manage->CreateObject(4, pos, rot);
		break;
	case 9: // ��T
		rock_manage->CreateObject(5, pos, rot);
		break;

	case 10: // ��
		fence_manage->SpawnFence(pos, rot);
	}
}

void Game::AddGameScore(int point)
{
	score_ += point;
}

void Game::GameStartcountDown()
{
	// �J�E���g�_�E���p�̒l�����炷
	count_gamestart--;

	if (count_gamestart < 0)
	{
		count_gamestart = 0;
		// �Q�[����Ԃ��u�v���C�v�ɂ���
		game_status = GameStatus::GamePlay;
	}
}

void Game::RenderGameStartCountDown()
{
	// �t���[�����\����b�P�ʂɕύX����
	int counter = count_gamestart / 60;
	// int�^ -> string�^
	std::string str = std::to_string(counter);
	// string�^ -> const char*�^
	const char* str_tochar = str.c_str();
	make_string.DrawStringCenterX(SCREEN_H / 2 - 10, 0.23f, str_tochar, 255, 255, 255, font_handle_);
}

void Game::GameTimeUpdate()
{
	// �Q�[���^�C�������炷
	timelimit_toframe_--;

	timelimit_toshow_ = timelimit_toframe_ / 60;

	// 0�b�ɂȂ�����
	if (timelimit_toframe_ <= 0)
	{
		// 0�b�Ŏ~�߂�
		timelimit_toframe_ = 0;
		// �Q�[����Ԃ��u�Q�[���I���v�ɂ���
		game_status = GameStatus::GameFinish;
	}
}

void Game::TimeUp()
{
#if SHOW_DEBUG
	printfDx("�Q�[���I��\n");
#endif
}