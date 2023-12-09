#include "../Main.h"
#include "SceneManager.h"

#include "StageSelect.h"
#include "Game.h"

StageSelect::StageSelect(SceneManager* p_manager) :Scene(p_manager), stage_(-1)
{
};

void StageSelect::Update()
{
	// ステージ選択処理
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
		// スペースキーでゲーム画面に移行
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			manager->scene = new Game(manager);
			delete this;
		}
		break;
	case 2:
		// 未実装
		break;
	}
}

void StageSelect::Render()
{
	// タイトル(ステージ選択)
	make_string.DrawStringCenterX(10, 0.25f, "ステージ選択", 255, 255, 255, font_handle_);

	// 選択している方を拡大する
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

	// ステージ１
	DrawCircle(SCREEN_W / 4, SCREEN_H / 2, 120 * extexd_1, GetColor(255, 255, 255), FALSE);
	make_string.DrawString(SCREEN_W / 4 - 70, SCREEN_H / 2 - 10, 0.25f, "ステージ１", 255, 255, 255, font_handle_);
	make_string.DrawString(SCREEN_W / 4 - 70, SCREEN_H / 2 + 30, 0.15f, "＋チュートリアル", 255, 255, 255, font_handle_);
	// ステージ２
	DrawCircle(SCREEN_W / 4 * 3, SCREEN_H / 2, 120 * extexd_2, GetColor(255, 255, 255), FALSE);
	make_string.DrawString(SCREEN_W / 4 * 3 - 80, SCREEN_H / 2 - 10, 0.25f, "ステージ２", 255, 255, 255, font_handle_);
	make_string.DrawString(SCREEN_W / 4 * 3 - 80, SCREEN_H / 2 + 30, 0.15f, "未実装", 255, 255, 255, font_handle_);
}

void StageSelect::SetupStage(int num)
{
	stage_ = num;
}