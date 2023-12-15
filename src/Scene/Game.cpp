#include <vector>
#include <ctime>

#include <fstream>
#include <sstream>

#include "../Main.h"
#include "Game.h"
#include "../System/Random.h"
//#include "../System/Vector3.h"
#include "../System/Hit.h"

#include "../Other/Camera.h"
#include "../Object/Environment/Ground.h"
#include "../Object/Environment/Rock/RockManager.h"
#include "../Object/Environment/FenceManager.h"
//#include "../Object/Environment/Box.h"

#include "../Object/Character/Friend/Player.h"
#include "../Object/Character/Friend/VillagerManager.h"
#include "../Object/Character/Enemy/EnemyManager.h"
#include "../Object/Item/Weapon/Sword01.h"

// マップ作成処理をするかどうか
#define IS_USE_MAP 0

Game::Game(SceneManager* p_manager) : Scene(p_manager), count_gamestart(180), is_gamestart(true),
timelimit_toframe_(10800/*1800*/), score_(0)
{
	stage_ = 0;

	// 各オブジェクトを動的確保
	camera = new Camera();											// カメラ
	ground = new Ground();											// 地面
	rock_manage = new RockManager();								// 岩管理
	fence_manage = new FenceManager();								// 柵
	//box = new Box();												// 箱
	player = new Player();											// プレイヤー
	villager_manage = new VillagerManager();	// 村人(保護対象)キャラクター管理
	enemy_manage = new EnemyManager();								// 敵キャラクター管理
	sword01 = new Sword01();										// 武器１

	// モデルの読み込み
	handle_villager_ = MV1LoadModel("data/villager/model/Mouse.mv1");		// 村人
	handle_enemy1_ = MV1LoadModel("data/enemy01/model/Enemy01.mv1");		// 敵（停止型）
	handle_enemy1_ = MV1LoadModel("data/enemy02/model/Enemy02.mv1");		// 敵（巡回型）
	handle_fence_ = MV1LoadModel("data/stage/fence/fence.mv1");				// 柵

	// ステージ選択で選ばれたステージを取得
	// そのステージのCSVファイルを読み込み
	LoadCSVFile(GetSelectedStagePath(stage_));
	// 各オブジェクトの初期生成関連
	// 村人(保護対象)
	//villager_spawn_manage->CreateSpawner();			// スポナー生成
	//villager_manage->ObjectInitializeSetting();		// キャラクター設定
	//// 敵
	//enemy_spawn_manage->CreateSpawner();			// スポナーの生成
	//enemy_manage->ObjectInitializeSetting();		// キャラクター設定
	// 柵
	//fence_manage->ObjectInitializeSetting();		// オブジェクト設定

	// 描画用にフレームを秒数に変更する
	timelimit_toshow_ = timelimit_toframe_ / 60;

	//enemy_manage->SpawnEnemy({ 0.0f, 0.0f, 0.0f }, EnemyType::TypeStop);
}

Game::~Game()
{
	// 各オブジェクトの解放
	delete camera;								// カメラ
	delete ground;								// 地面
	delete rock_manage;							// 岩
	if (fence_manage != NULL)
	{
		delete fence_manage;								// 柵
	}
	delete player;								// プレイヤー
	delete villager_manage;						// 村人(保護対象)キャラクター管理
	delete enemy_manage;						// 敵キャラクター管理
	delete sword01;								// 武器１
}

void Game::Update()
{
	switch (game_status)
	{
	case GameStatus::GameReady:				// ゲーム開始前
		// ゲーム開始前のカウントダウン処理
		GameStartcountDown();
		break;
	case GameStatus::GamePlay:				// ゲームプレイ
		is_game = true;
		// ゲームタイム処理
		GameTimeUpdate();
		break;
	case GameStatus::GameFinish:			// ゲーム終了
		is_game = false;
		// ゲーム終了処理
		TimeUp();
		break;

	case GameStatus::GamePause:				// ゲームポーズ
		// ゲームを一時中断する
		break;
	}

	//// Escキーでゲームを一時中断できるようにする
	//if (PushHitKey(KEY_INPUT_ESCAPE))
	//{
	//	game_status = GameStatus::GamePause;
	//}

	// 各オブジェクト更新
	camera->Update(player->GetterMyPosition());

	if (is_game)
	{
		fence_manage->Update();
		player->Update();									// プレイヤー
		//villager_spawn_manage->Update();															// 村人(保護対象)スポナー管理
		//enemy_spawn_manage->Update();																// 敵スポナー管理
		villager_manage->Update(player->GetterMyPosition());	// 村人(保護対象)キャラクター管理
		enemy_manage->Update(player->GetterMyPosition(), villager_manage->GetterVillagers());		// 敵キャラクター管理
		//enemy_patrol->EnemyUpdate(player->GetterMyPosition(), villager_manage->GetterVillagers());		// 敵キャラクター管理
		sword01->Update(player->GetterPlayerModelPointer());										// 武器１								

		// 各オブジェクトに必要な情報を渡す
		player->FetchEnemyInfo(enemy_manage->GetterEnemies());		// 敵
		// 柵情報
		if (fence_manage != NULL)
		{
			player->FetchFenceInfo(fence_manage->GetterFenceInfos());	// プレイヤー
			villager_manage->FetchFenceInfo(fence_manage->GetterFenceInfos());	// 村人
		}
	}
}

void Game::Render()
{
#if SHOW_DEBUG
	DrawFormatString(10, 10, GetColor(255, 255, 255), "ゲーム画面");
#endif

	ObjectRender();		// オブジェクト
	UIRender();			// ゲーム本編UI
}

void Game::ObjectRender()
{
	// 各オブジェクト描画
	camera->Render();						// カメラ
	ground->Render();						// 地面
	rock_manage->Render();					// 岩管理
	//box->Render();							// 箱
	if (fence_manage != NULL)
	{
		fence_manage->Render();					// 柵
	}
	player->Render();						// プレイヤー
	villager_manage->Render();				// 村人(保護対象)キャラクター管理
	enemy_manage->Render();					// 敵キャラクター管理
	sword01->Render();						// 武器１
	// ゴールの描画
	DrawLine3D(VGet(-20.0f, 0.1f, 150.0f), VGet(20.0f, 0.1f, 150.0f), GetColor(255, 0, 0));
}

void Game::UIRender()
{
#if SHOW_DEBUG
	//DrawExtendStringToHandle(10, 80,
	//	0.15f,
	//	0.15f,
	//	"テスト表示　オブジェクトよりも前に表示されているかABCabc123",
	//	GetColor(255, 255, 255), font_handle_);
#endif

	// 2D描画
	// HP
	player->RenderFor2D();						// プレイヤー
	enemy_manage->RenderFor2D();				// 敵

	//----------------------------------------
	// ゲームタイム
	// int型 -> string型
	std::string str = std::to_string(timelimit_toshow_);
	// string型 -> const char*型
	const char* str_tochar = str.c_str();
	// 幅の計算
	//int width = GetDrawStringWidthToHandle(str_tochar, -1, font_handle_) * 0.15f;
	//int x = (SCREEN_W - width) / 2;
	//DrawExtendStringToHandle(x, 10,
	//	0.15f,
	//	0.15f,
	//	str_tochar,
	//	GetColor(255, 255, 255), font_handle_);
	make_string.DrawStringCenterX(10, 0.17f, str_tochar, 255, 255, 255, font_handle_);

	//----------------------------------------
	// スコア

	// int型 -> string型
	std::string str_goal_num = std::to_string(villager_manage->GetterGoalVillager());
	// string型 -> const char*型
	const char* str_goal_num_tochar = str_goal_num.c_str();
	make_string.DrawString(10, 10, 0.17f, "とどけた人数：", 255, 255, 255, font_handle_);
	make_string.DrawString(175, 10, 0.17f, str_goal_num_tochar, 255, 255, 255, font_handle_);

	//----------------------------------------
	// ゲーム開始前カウントダウン描画処理
	if (game_status == GameStatus::GameReady)
	{
		RenderGameStartCountDown();
	}
}

//---------------------------------------
// ステージ生成処理関連

void Game::SetUpStageNumber()
{

}

std::string Game::GetSelectedStagePath(int stage)
{
	std::string csvfile_path;		//CSVファイルのパス格納用
	// 選択されたステージのファイルパスを渡す
	switch (stage)
	{
		// 指定したステージのパスを渡す
	case 0:		// ステージ１
		csvfile_path = "data/CSV/stage1.csv";
		//SetupStageSize({ -150.0f, 0.0f, 0.0f }, { 150.0f,0.0f,0.0f }, 300.0f);
		break;
	case 1:		// ステージ２
		csvfile_path = "data/CSV/stage2.csv";
		//SetupStageSize({ -150.0f, 0.0f, 0.0f }, { 150.0f,0.0f,0.0f }, 300.0f);
		break;
	}

	return csvfile_path;
}

void Game::LoadCSVFile(std::string file_path)
{
	// CSVファイルを読み込むためのファイルストリームを開く
	std::ifstream file(file_path);

	// ファイルが正しく開けたか
	if (!file.is_open())
	{
		printfDx("ファイル読み込みが正しく行われませんでした\n");
	}


	// １行ずつ
	std::string line;
	while (std::getline(file, line))
	{
		if (file.eof())
			break;
		if (line.empty())
			continue;

		int start_num = 0;		// 調べ始める位置
		int comma_num = 0;		// カンマの数
		int max_comma_num = 7;

		// スポーンの設定するために各情報を格納する変数を作る
		int counter = 0;
		int type = 0;						// 種類
		Vector3 pos = { 0.0f,0.0f,0.0f };	// 位置
		Vector3 rot = { 0.0f,0.0f,0.0f };	// 向き
		Vector3  patrol_pos1 = { 0.0f,0.0f,0.0f };
		Vector3  patrol_pos2 = { 0.0f,0.0f,0.0f };

		while (comma_num < max_comma_num)
		{
			// start_numの位置からのカンマの位置を調べる
			std::size_t comma_position = line.find(',', start_num);
			// 調べたカンマの位置までの値を求める
			std::string cut_str = line.substr(start_num, comma_position - start_num);

			switch (counter)
			{
			case 0:				// キャラクターの種類
				type = std::stoi(cut_str);
				// 生成するオブジェクトが敵（巡回型）であれば最大読み取りのコンマ数を13にする
				if (type == 4)
				{
					max_comma_num = 13;
				}
				++comma_num;
				break;
			case 1:				// Ｘ座標
				pos.x = std::stoi(cut_str);
				++comma_num;
				break;
			case 2:				// Ｙ座標
				pos.y = std::stoi(cut_str);
				++comma_num;
				break;
			case 3:				// Ｚ座標
				pos.z = std::stoi(cut_str);
				++comma_num;
				break;
			case 4:				// Ⅹ角度
				rot.x = std::stoi(cut_str);
				++comma_num;
				break;
			case 5:				// Ｙ角度
				rot.y = std::stoi(cut_str);
				++comma_num;
				break;
			case 6:				// Ｚ角度
				rot.z = std::stoi(cut_str);
				++comma_num;
				break;
			case 7:				// 巡回折り返し地点１のⅩ座標
				patrol_pos1.x = std::stoi(cut_str);
				++comma_num;
				break;
			case 8:				// 巡回折り返し地点１のＹ座標
				patrol_pos1.y = std::stoi(cut_str);
				++comma_num;
				break;
			case 9:				// 巡回折り返し地点１のＺ座標
				patrol_pos1.z = std::stoi(cut_str);
				++comma_num;
				break;
			case 10:			// 巡回折り返し地点２のⅩ座標
				patrol_pos2.x = std::stoi(cut_str);
				++comma_num;
				break;
			case 11:			// 巡回折り返し地点２のＹ座標
				patrol_pos2.y = std::stoi(cut_str);
				++comma_num;
				break;
			case 12:			// 巡回折り返し地点２のＺ座標
				patrol_pos2.z = std::stoi(cut_str);
				++comma_num;
				break;
			}

			// カウンターを増やす
			++counter;
			// start_numに(調べたカンマの位置＋１)を代入する
			start_num = comma_position + 1;
		}
		CreateStage(type, pos, rot, patrol_pos1, patrol_pos2);
		// データはカンマ区切りなので、これではうまくいかない
		//std::stringstream ss(line);
		//ss >> type >> pos.x >> pos.y >> pos.z;
		//printfDx("type : %d / pos : %f, %f, %f\n", type, pos.x, pos.y, pos.z);
		//CreateStage(type, pos);


		// 取得した行から1文字ずつ表示する
		//int index = 0;
		//for (char ch : line)
		//{
		//	// カンマはスキップする
		//	if (ch == ',')
		//	{
		//		continue;
		//	}
		//	else
		//	{
		//		switch (index)
		//		{
		//		case 0:
		//			type = (int)(ch - '0');
		//			break;
		//		case 1:
		//			//pos.x = (int)(ch - '1');
		//			break;
		//		}
		//		++index;
		//	}
		//}
	}

	// ファイルを閉じる
	file.close();

}

void Game::CalculateMapChip()
{
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			Vector3 pos;
			// 設定するマップサイズで中心座標の取り方を考える
		}
	}
}


void Game::CreateStage(int type, Vector3 pos, Vector3 rot, Vector3 pat_pos1, Vector3 pat_pos2)
{
	switch (type)
	{
	case 0:	// 何もおかない(地面のみ)
		break;
	case 1:	// ゴール
		break;
	case 2:	// 村人
		villager_manage->SpawnVillager(handle_villager_, pos);			// スポナー生成
		//villager_manage->ObjectInitializeSetting(0);		// キャラクター設定
		break;
	case 3:	// 敵(停止型)
		enemy_manage->SpawnEnemy(handle_enemy1_,EnemyType::TypeStop, pos, rot, pat_pos1, pat_pos2);
		break;
	case 4:	// 敵(巡回型)
		enemy_manage->SpawnEnemy(handle_enemy2_,EnemyType::TypePatrol, pos, rot, pat_pos1, pat_pos2);		// キャラクター設定
		break;
	case 5: // 岩１
		rock_manage->CreateObject(1, pos, rot);
		break;
	case 6: // 岩２
		rock_manage->CreateObject(2, pos, rot);
		break;
	case 7: // 岩３
		rock_manage->CreateObject(3, pos, rot);
		break;
	case 8: // 岩４
		rock_manage->CreateObject(4, pos, rot);
		break;
	case 9: // 岩５
		rock_manage->CreateObject(5, pos, rot);
		break;
	case 10: // 柵
		fence_manage->SpawnFence(handle_fence_,1, pos, rot);
		break;
	}
}

void Game::AddGameScore(int point)
{
	score_ += point;
}

void Game::GameStartcountDown()
{
	// カウントダウン用の値を減らす
	count_gamestart--;

	if (count_gamestart < 0)
	{
		count_gamestart = 0;
		// ゲーム状態を「プレイ」にする
		game_status = GameStatus::GamePlay;
	}
}

void Game::RenderGameStartCountDown()
{
	// フレーム数表示を秒単位に変更する
	int counter = count_gamestart / 60;
	// int型 -> string型
	std::string str = std::to_string(counter);
	// string型 -> const char*型
	const char* str_tochar = str.c_str();
	make_string.DrawStringCenterX(SCREEN_H / 2 - 10, 0.23f, str_tochar, 255, 255, 255, font_handle_);
}

void Game::GameTimeUpdate()
{
	timelimit_toframe_ += villager_manage->AddTimeLimit();

	// ゲームタイムを減らす
	timelimit_toframe_--;

	timelimit_toshow_ = timelimit_toframe_ / 60;

	// 0秒になったら
	if (timelimit_toframe_ <= 0)
	{
		// 0秒で止める
		timelimit_toframe_ = 0;
		// ゲーム状態を「ゲーム終了」にする
		game_status = GameStatus::GameFinish;
	}
}

void Game::TimeUp()
{
#if SHOW_DEBUG
	printfDx("ゲーム終了\n");
#endif
}