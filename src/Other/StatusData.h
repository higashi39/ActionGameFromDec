#pragma once
#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
//	ステータスデータ
//---------------------------------------------------------------------------------
// ゲーム状態
enum GameStatus
{
	GameReady,				// ゲーム開始前
	GamePlay,				// プレイ
	//GAME_STATUS_SELECT,	// ステータス選択
	GamePause,				// ポーズ
	GameFinish,				// ゲーム終了
	GAME_CLEAR,				// ゲームクリア
	GAME_OVER,				// ゲームオーバー
};

//// プレイヤー状態
//enum PLAYERSTATUS
//{
//	PLAYER_MOVE,			// 移動
//	PLAYER_TRACK_SELECT,	// 追跡対象選択
//	PLAYER_TRACKING,		// 追跡
//	PLAYER_ATTACK,			// 攻撃中
//	PLAYER_SETCHECK,		// チェックポイント設置
//	PLAYER_SETOBSTACLE,		// 障害物設置
//	PLAYER_STOP,			// 止まる(何もなし)
//};

// プレイヤー追跡対象状態
enum PLAYERTRACKEDSTATUS
{
	ENEMY,					// 敵
	FENCE,					// 柵
	NONE,					// 何も追跡しない
};

//// 敵の構造体
//struct  ENEMTDATA
//{
//	int type;				// 種類
//};

// 敵状態
// ☆課題：敵によって行動が異なるので、あとで違う場所にうつすなりする
enum EnemyType
{
	TypeStop,				// 停止
	TypePatrol,				// 巡回
	ENEMY_WALK,				// 徘徊(のちに処理)
	ENEMY_ATTACK,			// 攻撃
	ENEMY_DESTROY,			// 撃破される
};

//struct StageInfo
//{
//	Vector3 left_pos = {0.0f,0.0f,0.0f};		// 左端
//	Vector3 right_pos = { 0.0f,0.0f,0.0f };		// 右端
//	float side_length = 0.0f;		// 長さ
//};
//StageInfo stage_info;
//
//
//// マップ設定
//void SetupStageSize(Vector3 left_pos, Vector3 right_pos, float side_length);
//
//StageInfo GetterStageSize();