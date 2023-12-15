#pragma once
#include "SceneManager.h"
#include <string>

#include "../System/Vector3.h"
#include "../Other/MakeString.h"
#include "../Other/StatusData.h"

// システム
class Camera;

// ステージ構成
class Ground;
class RockManager;
class FenceManager;
class Box;

// キャラクター・アイテム
class Player;
class VillagerManager;
class EnemyManager;
class Sword01;

//---------------------------------------------------------------------------------
// ゲームシーンクラス
//---------------------------------------------------------------------------------
class Game : public Scene
{
public:
	// ポインタ変数
	Camera* camera;									// カメラ
	Ground* ground;									// 地面
	RockManager* rock_manage;						// 岩管理
	FenceManager* fence_manage;						// 柵
	Box* box;										// 箱
		
	Player* player;									// プレイヤー
	VillagerManager* villager_manage;				// 村人(保護対象)キャラクター管理
	EnemyManager* enemy_manage;						// 敵キャラクター管理
	Sword01* sword01;								// 武器１

public:
	Game(SceneManager* p_manager);
	~Game();

	// 更新
	void Update();

	// 描画
	void Render();

	// 描画子関数
	// オブジェクト関連
	void ObjectRender();
	// ゲーム本編UI関連
	void UIRender();

	//-------------------------------------
	// ステージ生成処理関連

	// ステージ選択反映処理
	// ステージ選択シーンで選択されたステージを設定
	void SetUpStageNumber();

	// 選択されたステージのパスを取得
	std::string GetSelectedStagePath(int stage);

	// ステージ用のファイル読み込み
	void LoadCSVFile(std::string file_path);

	// ステージの各マスの座標設定
	void CalculateMapChip();

	// ステージ生成処理
	// type			: 渡されるオブジェクト用ID
	// pos			: そのオブジェクトが設置される座標
	// rot			:							角度
	// pat_pos1		: 巡回折り返し地点１（敵（巡回型）のみ） 
	// pat_pos2		: 巡回折り返し地点２（敵（巡回型）のみ） 
	void CreateStage(int type, Vector3 pos, Vector3 rot, Vector3 pat_pos1, Vector3 pat_pos2);



	// ゲームスコア加減点処理
	// point : 今回スコアに含む点数
	void AddGameScore(int point);

	//-----------------------------------
	// タイム関連
	// ゲーム開始前カウントダウン処理
	void GameStartcountDown();			// カウントダウン
	void RenderGameStartCountDown();	// 描画用

	// ゲームタイム処理
	void GameTimeUpdate();
	// ゲーム終了処理
	void TimeUp();

private:
	// ステージ番号
	int stage_;

	// ゲームスコア関連
	int score_ = 0;					// トータルスコア

	// ゲームステータス
	int game_status = GameStatus::GameReady;

	// ゲームタイム関連
	int count_gamestart = 0;		// ゲーム開始前カウントダウン
	bool is_gamestart = false;		// ゲーム開始前カウントダウンの描画フラグ

	int timelimit_toframe_ = 0;		// 制限時間
	int timelimit_toshow_ = 0;		// 描画用

	bool is_game = false;

	// has関係
	MakeString make_string;

	// モデル関係
	int handle_villager_ = 0;		// 村人
	int handle_enemy1_ = 0;	// 敵（停止型）
	int handle_enemy2_ = 0;	// 敵（巡回型）
	int handle_fence_ = 0;			// 柵
};