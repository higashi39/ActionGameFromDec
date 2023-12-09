#pragma once
#include "../Other/MakeString.h"
#include "../Other/Blinker.h"

//---------------------------------------------------------------------------------
// タイトルシーンクラス
//---------------------------------------------------------------------------------
class Title : public Scene
{
public:
	Title(SceneManager* p_manager);
	~Title();

	// 更新
	void Update();
	// 描画
	void Render();

private:
	MakeString make_string;
	Blinker blinker;
};