#include <cmath>

#include "../Main.h"
#include "../Scene/Game.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	球同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckBallHit(Vector3 center1, float radius1, Vector3 center2, float radius2)
{
	float length = GetVector3Distance(center1, center2);
	float radius = radius1 + radius2;
	if (length <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	ボックス同士の当たり判定
//	（座標 pos を中心にサイズ size 分プラスマイナスしたボックス：２Ｄのような左上からの大きさでの判定ではないので注意）
//---------------------------------------------------------------------------------
bool CheckBoxHit3D(Vector3 box_pos1, Vector3 box_size1, Vector3 box_pos2, Vector3 box_size2)
{
	float right1 = box_pos1.x + box_size1.x;
	float left1 = box_pos1.x - box_size1.x;
	float up1 = box_pos1.y + box_size1.y;
	float down1 = box_pos1.y - box_size1.y;
	float front1 = box_pos1.z + box_size1.z;
	float back1 = box_pos1.z - box_size1.z;

	float right2 = box_pos2.x + box_size2.x;
	float left2 = box_pos2.x - box_size2.x;
	float up2 = box_pos2.y + box_size2.y;
	float down2 = box_pos2.y - box_size2.y;
	float front2 = box_pos2.z + box_size2.z;
	float back2 = box_pos2.z - box_size2.z;

	if (right1 >= left2 && left1 <= right2) {
		if (up1 >= down2 && down1 <= up2) {
			if (front1 >= back2 && back1 <= front2) {
				return true;
			}
		}
	}
	return false;
}

//==================================================================================
// 自主制作関数
//==================================================================================
//---------------------------------------------------------------------------------
//	四角と円の当たり判定(どこから当たったかを整数で返す)
//---------------------------------------------------------------------------------
void CheckBoxSphereHit(int* box_model_data, Vector3 sphere_center, float sphere_radius)
{
	//printfDx("柵と当たっています\n");

	//MV1_COLL_RESULT_POLY_DIM hit_dim = MV1CollCheck_Sphere(*box_model_data, -1, sphere_center.VGet(), sphere_radius);
	//// あたったポリゴン数の取得
	//int hit_num = hit_dim.HitNum;
	//// 当たったポリゴンを順番に見ていく
	//for (int i = 0; i < hit_num; ++i)
	//{
	//	// どのポリゴンに当たったかを取得する
	//	VECTOR hit_pos = hit_dim.Dim[i].HitPosition;

	//	// 自身の座標から四角当たり判定モデルに当たった座標までの長さを求める
	//	VECTOR vec;
	//	vec.x = sphere_center.x - hit_pos.x;
	//	vec.z = sphere_center.z - hit_pos.z;
	//	vec.y = 0.0f;
	//	float length = VSize(vec);

	//	// どれだけ四角当たり判定モデルにめり込んだか深さを求める
	//	float depth = sphere_radius - length;
	//	// 当たったポリゴン法線を求める
	//	VECTOR hit_normal = hit_dim.Dim[i].Normal;
	//	// めり込んだ量を求める（floatの誤差も考慮、Y座標はそのままで）
	//	Vector3 q;
	//	q.x = hit_normal.x * (depth + FLT_EPSILON);
	//	q.z = hit_normal.z * (depth + FLT_EPSILON);
	//	q.y = 0.0f;

	//	// めり込んだ分だけ法線方向に押し出す
	//	sphere_center += q;
	//}
}

//---------------------------------------------------------------------------------
//	２つのオブジェクトのベクトル方向を算出
//---------------------------------------------------------------------------------
Vector3 CalculateTwoVector(Vector3 vec1, Vector3 vec2)
{
	Vector3 vec;
	vec.x = vec1.x - vec2.x;
	vec.z = vec1.z - vec2.z;
	// Y座標は0にしておく
	vec.y = 0.0f;

	return vec;
}
//---------------------------------------------------------------------------------
//	ベクトル方向の長さを求める
//---------------------------------------------------------------------------------
float CalculateVectorToLength(Vector3 vec)
{
	float len;
	len = VSize(vec.VGet());
	return len;
}

//---------------------------------------------------------------------------------
//	１点の位置（座標）と１つの円の当たり判定
//---------------------------------------------------------------------------------
bool CheckHitPointToCircle(Vector3 point, Vector3 circle_center, float circle_radius)
{
	Vector3 distance;
	distance = CalculateTwoVector(circle_center, point);

	float length = CalculateVectorToLength(distance);

	if (length <= circle_radius)
	{
		return true;
	}

	return false;
}

Vector3 HitCollision(Vector3 obj_pos, Vector3 obj_before_pos, Vector3 obj_size,
	Vector3 box_pos, Vector3 box_size)
{
	if (obj_before_pos.z + obj_size.z >= box_pos.z - box_size.z &&
		obj_before_pos.z - obj_size.z <= box_pos.z + box_size.z)
	{
		// X方向だけ１フレーム前の座標に戻す
		obj_pos.x = obj_before_pos.x;
	}
	// 縦に当たっていたらX方向だけ戻す
	// →移動前の四角と四角パネルが横方向だけ当たっていたら
	if (obj_before_pos.x + obj_size.x >= box_pos.x - box_size.x &&
		obj_before_pos.x - obj_size.x <= box_pos.x + box_size.x)
	{
		// Z方向だけ１フレーム前の座標に戻す
		obj_pos.z = obj_before_pos.z;
	}

	return obj_pos;
}