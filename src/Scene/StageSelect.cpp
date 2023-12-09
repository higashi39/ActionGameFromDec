#include "../Main.h"
#include "SceneManager.h"

#include "StageSelect.h"
#include "Game.h"

StageSelect::StageSelect(SceneManager* p_manager) :Scene(p_manager), stage_(-1)
{
};

void StageSelect::Update()
{
	// �X�e�[�W�I������
	if (PushHitKey(KEY_INPUT_LEFT))
	{
		select_stage_--;
		if (select_stage_ <= 0)
		{
			select_stage_ = 2;
		}
	}
	else if (PushHitKey(KEY_INPUT_RIGHT))
	{
		select_stage_++;
		if (select_stage_ >= 3)
		{
			select_stage_ = 1;
		}
	}
	printfDx("select_stage_ : %d\n", select_stage_);

	switch (select_stage_)
	{
	case 1:
		// �X�y�[�X�L�[�ŃQ�[����ʂɈڍs
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			manager->scene = new Game(manager);
			delete this;
		}
		break;
	case 2:
		// ������
		break;
	}
}

void StageSelect::Render()
{
	// �^�C�g��(�X�e�[�W�I��)
	make_string.DrawStringCenterX(10, 0.25f, "�X�e�[�W�I��", 255, 255, 255, font_handle_);

	// �I�����Ă�������g�傷��
	float extexd_1 = 1;
	float extexd_2 = 2;
	switch (select_stage_)
	{
	case 1:
		extexd_1 = 1.2f;
		extexd_2 = 1;
		break;
	case 2:
		extexd_1 = 1;
		extexd_2 = 1.2f;
		break;
	}

	// �X�e�[�W�P
	DrawCircle(SCREEN_W / 4, SCREEN_H / 2, 120 * extexd_1, GetColor(255, 255, 255), FALSE);
	make_string.DrawString(SCREEN_W / 4 - 70, SCREEN_H / 2 - 10, 0.25f, "�X�e�[�W�P", 255, 255, 255, font_handle_);
	make_string.DrawString(SCREEN_W / 4 - 70, SCREEN_H / 2 + 30, 0.15f, "�{�`���[�g���A��", 255, 255, 255, font_handle_);
	// �X�e�[�W�Q
	DrawCircle(SCREEN_W / 4 * 3, SCREEN_H / 2, 120 * extexd_2, GetColor(255, 255, 255), FALSE);
	make_string.DrawString(SCREEN_W / 4 * 3 - 80, SCREEN_H / 2 - 10, 0.25f, "�X�e�[�W�Q", 255, 255, 255, font_handle_);
	make_string.DrawString(SCREEN_W / 4 * 3 - 80, SCREEN_H / 2 + 30, 0.15f, "������", 255, 255, 255, font_handle_);
}

void StageSelect::SetupStage(int num)
{
	stage_ = num;
}