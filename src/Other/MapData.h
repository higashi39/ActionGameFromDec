#pragma once
#include "../Object/Object.h"

const int wide = 11;
const int height = 15;

//---------------------------------------------------------------------------------
//	�}�b�v�f�[�^
//---------------------------------------------------------------------------------
class MapData : public CharacterBase
{
public:

	void Init(int model);		// ����������
	void Update();				// �X�V����
	void Render();				// �`�揈��
	void Exit();				// �I������

	// �}�X��
	int* wide;
	int* height;
};