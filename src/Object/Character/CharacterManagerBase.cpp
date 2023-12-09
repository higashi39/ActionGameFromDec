// 計算用------------------------
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "../../System/Random.h"
//-------------------------------

#include "../../Main.h"
#include "../../Scene/Game.h"
#include "CharacterManagerBase.h"

CharacterManagerBase::CharacterManagerBase()
{
	object_create_num_ = 0;

}	

void CharacterManagerBase::CalculateObjectNum(int min, int max)
{
	int rand_num;
	// 何人生成するか決める
	rand_num = GetRandomI(min, max);
	object_create_num_ = rand_num;
	for (int i = 0; i < rand_num; i++)
	{
		// すべてのオブジェクトの初期位置を(0.0f, 0.0f, 0.0f)とし、
		// オブジェクト位置格納用配列に追加していく
		Vector3 zero;
		zero.set(0.0f, 0.0f, 0.0f);
		object_create_pos_.emplace_back(zero);
	}
}

Vector3 CharacterManagerBase::AssignObjectPosition(const Vector3& pos)
{
	// 角度を乱数で求める
	float rand_angle = GetRandomF(2.0f * M_PI);
	// スポナーの中心位置から一定半径内で乱数を求める
	float rand_radius = GetRandomF(15.0f);

	// 生成する位置を設定
	Vector3 create_pos;
	create_pos.x = pos.x + rand_radius * std::sin(rand_angle);
	create_pos.z = pos.z + rand_radius * std::cos(rand_angle);
	create_pos.y = 0.0f;

	return create_pos;
}