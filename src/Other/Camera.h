#pragma once

#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	Camera();
	~Camera() {};

	// 更新
	// p_pos : プレイヤー位置
	void Update(const Vector3& p_pos);
	// 描画
	void Render();

private:
	Vector3	camera_position_;			// カメラの位置
	Vector3 camera_default_position_;	// カメラのデフォルト位置

	Vector3	camera_look_;				// カメラが見る位置
	Vector3 camera_rotation_;			// カメラ回転量
	float camera_radius_;				// カメラの半径

	float distance_toplayer_;			// プレイヤーとの距離
};
