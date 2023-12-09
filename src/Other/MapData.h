#pragma once
#include "../Object/Object.h"

const int wide = 11;
const int height = 15;

//---------------------------------------------------------------------------------
//	マップデータ
//---------------------------------------------------------------------------------
class MapData : public CharacterBase
{
public:

	void Init(int model);		// 初期化処理
	void Update();				// 更新処理
	void Render();				// 描画処理
	void Exit();				// 終了処理

	// マス数
	int* wide;
	int* height;
};