#pragma once
#include "../Other/MakeString.h"

//---------------------------------------------------------------------------------
// タイトルシーンクラス
//---------------------------------------------------------------------------------
class StageSelect : public Scene
{
public:
	StageSelect(SceneManager* p_manager);
	~StageSelect() {};

	// 更新
	void Update();
	// 描画
	void Render();

	// 選択されたステージを設定する
	void SetupStage(int num);

private:
	int stage_;

	int select_stage_ = 1;

	MakeString make_string;
};