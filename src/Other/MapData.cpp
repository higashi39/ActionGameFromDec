#include "../Main.h"
#include "../Scene/Game.h"
#include "MapData.h"

// 箱のサイズ
const float BOX_SIZE = 0.02f;
//// マップの二次元配列
const int MAP_W = 11;	// 横
const int MAP_H = 15;	// 縦
//// マップ作成に使用するデータ(0:進める(何もなし) / 1:壁)
//int mapdata_pattern[2];
// マップデータ
int map_data;

//------------------------------------------------------------
// 初期化処理
//------------------------------------------------------------
void MapData::Init(int model)
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();

	m_scale.x = BOX_SIZE;
	m_scale.y = BOX_SIZE;
	m_scale.z = BOX_SIZE;

	// モデル読み込み([0]はなし)
	mapdata_pattern[0] = NULL;
	mapdata_pattern[1] = MV1LoadModel("data/Item/SetField/obstacle_set.mv1");

	// 初期設定
	// 全て0(壁)にする
	map_data = 0;

	// 1つ飛ばしで柱(-1とする)にする
	if (*wide % 2 == 0 && *height % 2 == 0)
	{
		map_data = -1;
	}

	// 一番外側を壁にする
	if (*wide == 0)				map_data = 1;
	if (*height == 0)				map_data = 1;
	if (*wide == MAP_W - 1)		map_data = 1;
	if (*height == MAP_H - 1)		map_data = 1;
}

//------------------------------------------------------------
// 更新処理
//------------------------------------------------------------
void MapData::Update()
{
	//for (int h = 0; h < MAP_H; h++)
	//{
	//	for (int w = 0; w < MAP_W; w++)
	//	{
	//		// 全て0(壁)にする
	//		map_data[h][w] = 0;

	//		// 1つ飛ばしで柱(-1とする)にする
	//		if (w % 2 == 0 && w == 2)
	//		{
	//			map_data[h][w] = -1;
	//		}
	//		// 一番外側を壁にする
	//		if (w == 0)				map_data[h][w] = 1;
	//		if (h == 0)				map_data[h][w] = 1;
	//		if (w == MAP_W - 1)		map_data[h][w] = 1;
	//		if (h == MAP_H - 1)		map_data[h][w] = 1;
	//	}
	//}

		// 柱(-1)があったらその柱と、上下左右のどこか1カ所を壁(1にする)
			// 柱(-1)があったら
	if (map_data == -1)
	{
		// 自身を壁(1)にする
		map_data = 1;
		// 上下左右のみる数
		int rand_max;
		// 1番上の柱は4回、それ以外は3回
		if (*height == 2)
		{
			rand_max = 4;
		}
		else
		{
			rand_max = 3;
		}

		// 壁になっているところ以外を見つけるまでランダムで繰り返す
		int rand_start = rand() % rand_max;
		for (int i = rand_start; i < rand_start + rand_max; i++)
		{
			// ランダムで上下左右のどこかを壁(1)にする
			int rand_prace = i % rand_max;

			// 柱からみたときの上下左右用変数
			int w1 = *wide;
			int h1 = *height;

			if (rand_prace == 0)		w1++;		// 右
			if (rand_prace == 1)		h1++;		// 下
			if (rand_prace == 2)		w1--;		// 左
			if (rand_prace == 3)		h1--;		// 上

			// ランダムで選ばれた場所が壁(1)じゃなかったら
			if (map_data[h1][w1] == 0)
			{
				// その場所を壁とする
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
// 描画処理
//------------------------------------------------------------
void MapData::Render()
{
	// 各マスの番号を取得
	int num = map_data;
	// そのマスの描画座標を設定
	Vector3 pos;
	pos.x = *wide * BOX_SIZE;
	pos.y = m_pos.y;
	pos.z = *height * BOX_SIZE;

	// 描画
	MV1SetPosition(m_model[num], VGet(pos.x, pos.y, pos.z));
	MV1SetScale(m_model[num], VGet(m_scale.x, m_scale.y, m_scale.z));
	MV1DrawModel(m_model[num]);
}
	}
}

//------------------------------------------------------------
// 終了処理
//------------------------------------------------------------
void MapData::Exit()
{

}