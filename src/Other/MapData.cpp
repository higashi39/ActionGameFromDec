#include "../Main.h"
#include "../Scene/Game.h"
#include "MapData.h"

// ���̃T�C�Y
const float BOX_SIZE = 0.02f;
//// �}�b�v�̓񎟌��z��
const int MAP_W = 11;	// ��
const int MAP_H = 15;	// �c
//// �}�b�v�쐬�Ɏg�p����f�[�^(0:�i�߂�(�����Ȃ�) / 1:��)
//int mapdata_pattern[2];
// �}�b�v�f�[�^
int map_data;

//------------------------------------------------------------
// ����������
//------------------------------------------------------------
void MapData::Init(int model)
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();

	m_scale.x = BOX_SIZE;
	m_scale.y = BOX_SIZE;
	m_scale.z = BOX_SIZE;

	// ���f���ǂݍ���([0]�͂Ȃ�)
	mapdata_pattern[0] = NULL;
	mapdata_pattern[1] = MV1LoadModel("data/Item/SetField/obstacle_set.mv1");

	// �����ݒ�
	// �S��0(��)�ɂ���
	map_data = 0;

	// 1��΂��Œ�(-1�Ƃ���)�ɂ���
	if (*wide % 2 == 0 && *height % 2 == 0)
	{
		map_data = -1;
	}

	// ��ԊO����ǂɂ���
	if (*wide == 0)				map_data = 1;
	if (*height == 0)				map_data = 1;
	if (*wide == MAP_W - 1)		map_data = 1;
	if (*height == MAP_H - 1)		map_data = 1;
}

//------------------------------------------------------------
// �X�V����
//------------------------------------------------------------
void MapData::Update()
{
	//for (int h = 0; h < MAP_H; h++)
	//{
	//	for (int w = 0; w < MAP_W; w++)
	//	{
	//		// �S��0(��)�ɂ���
	//		map_data[h][w] = 0;

	//		// 1��΂��Œ�(-1�Ƃ���)�ɂ���
	//		if (w % 2 == 0 && w == 2)
	//		{
	//			map_data[h][w] = -1;
	//		}
	//		// ��ԊO����ǂɂ���
	//		if (w == 0)				map_data[h][w] = 1;
	//		if (h == 0)				map_data[h][w] = 1;
	//		if (w == MAP_W - 1)		map_data[h][w] = 1;
	//		if (h == MAP_H - 1)		map_data[h][w] = 1;
	//	}
	//}

		// ��(-1)���������炻�̒��ƁA�㉺���E�̂ǂ���1�J�����(1�ɂ���)
			// ��(-1)����������
	if (map_data == -1)
	{
		// ���g���(1)�ɂ���
		map_data = 1;
		// �㉺���E�݂̂鐔
		int rand_max;
		// 1�ԏ�̒���4��A����ȊO��3��
		if (*height == 2)
		{
			rand_max = 4;
		}
		else
		{
			rand_max = 3;
		}

		// �ǂɂȂ��Ă���Ƃ���ȊO��������܂Ń����_���ŌJ��Ԃ�
		int rand_start = rand() % rand_max;
		for (int i = rand_start; i < rand_start + rand_max; i++)
		{
			// �����_���ŏ㉺���E�̂ǂ������(1)�ɂ���
			int rand_prace = i % rand_max;

			// ������݂��Ƃ��̏㉺���E�p�ϐ�
			int w1 = *wide;
			int h1 = *height;

			if (rand_prace == 0)		w1++;		// �E
			if (rand_prace == 1)		h1++;		// ��
			if (rand_prace == 2)		w1--;		// ��
			if (rand_prace == 3)		h1--;		// ��

			// �����_���őI�΂ꂽ�ꏊ����(1)����Ȃ�������
			if (map_data[h1][w1] == 0)
			{
				// ���̏ꏊ��ǂƂ���
				map_data[h1][w1] = 1;

				return;
			}
		}
	}


	//for (int h = 0; h < MAP_H; h++)
	//{
	//	for (int w = 0; w < MAP_W; w++)
	//	{
	//		printfDx("%d", map_data[h][w]);
	//		if (w == MAP_W - 1)
	//		{
	//			printfDx("\n");
	//		}
	//	}
	//}
}

//------------------------------------------------------------
// �`�揈��
//------------------------------------------------------------
void MapData::Render()
{
	// �e�}�X�̔ԍ����擾
	int num = map_data;
	// ���̃}�X�̕`����W��ݒ�
	Vector3 pos;
	pos.x = *wide * BOX_SIZE;
	pos.y = m_pos.y;
	pos.z = *height * BOX_SIZE;

	// �`��
	MV1SetPosition(m_model[num], VGet(pos.x, pos.y, pos.z));
	MV1SetScale(m_model[num], VGet(m_scale.x, m_scale.y, m_scale.z));
	MV1DrawModel(m_model[num]);
}
	}
}

//------------------------------------------------------------
// �I������
//------------------------------------------------------------
void MapData::Exit()
{

}