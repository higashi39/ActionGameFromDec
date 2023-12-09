#pragma once
#include "../Other/MakeString.h"

//---------------------------------------------------------------------------------
// �^�C�g���V�[���N���X
//---------------------------------------------------------------------------------
class StageSelect : public Scene
{
public:
	StageSelect(SceneManager* p_manager);
	~StageSelect() {};

	// �X�V
	void Update();
	// �`��
	void Render();

	// �I�����ꂽ�X�e�[�W��ݒ肷��
	void SetupStage(int num);

private:
	int stage_;

	int select_stage_ = 1;

	MakeString make_string;
};