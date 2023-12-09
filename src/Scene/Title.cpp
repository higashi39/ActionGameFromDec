#include "../Main.h"
#include "SceneManager.h"

#include "Title.h"
#include "StageSelect.h"

Title::Title(SceneManager* p_manager) : Scene(p_manager)
{
}

Title::~Title()
{
}

void Title::Update()
{
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		// �X�y�[�X�L�[�ŃX�e�[�W�I����ʂɈڍs
		manager->scene = new StageSelect(manager);
		delete this;
	}
}

void Title::Render()
{
#if SHOW_DEBUG
#endif

	make_string.DrawStringCenterX(80, 0.7f, "�����ڂ�����", 255, 255, 255, font_handle_);
	make_string.DrawStringCenterX(230, 0.3f, "�Q�[���X�^�[�g", 255, 255, 255, font_handle_);

	
	if (blinker.Blink(32))
	{
		DrawBox(SCREEN_W / 6 * 2, 220, SCREEN_W / 6 * 4, 275, GetColor(255, 255, 255), FALSE);
	}
}