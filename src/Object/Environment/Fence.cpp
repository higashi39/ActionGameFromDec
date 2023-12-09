#include <cmath>

#include "../../Main.h"
#include "../../Scene/Game.h"
#include "Fence.h"

#include "../../System/Hit.h"

Fence::Fence(Vector3 create_pos, Vector3 create_rot)
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/stage/fence/fence.mv1");

	object_position_ = create_pos;				// 位置
	object_rotate_.y = TO_RADIAN(create_rot.y);	// 向き
	object_scale_.set(0.01f, 0.01f, 0.01f);		// 大きさ

	collision_size_.set(11.0f, 0.0f, 5.0f);		// 当たり判定用モデルサイズ

	size_pos[0].set(-collision_size_.x / 2, collision_size_.y, -collision_size_.z / 2);		// 左上
	size_pos[1].set(+collision_size_.x / 2, collision_size_.y, -collision_size_.z / 2);		// 右上
	size_pos[2].set(+collision_size_.x / 2, collision_size_.y, +collision_size_.z / 2);		// 右下
	size_pos[3].set(-collision_size_.x / 2, collision_size_.y, +collision_size_.z / 2);		// 左下

	corner_pos[0].set(0.0f, 5.0f, 0.0f);
	corner_pos[1].set(0.0f, 5.0f, 0.0f);
	corner_pos[2].set(0.0f, 5.0f, 0.0f);
	corner_pos[3].set(0.0f, 5.0f, 0.0f);
}

Fence::~Fence()
{
	delete object_model_;
}

void Fence::Update()
{
	corner_pos[0].x = size_pos[0].x * sinf(object_rotate_.y) + size_pos[0].z * -cosf(object_rotate_.y) + object_position_.x;
	corner_pos[0].z = size_pos[0].x * cosf(object_rotate_.y) + size_pos[0].z * sinf(object_rotate_.y) + object_position_.z;

	corner_pos[1].x = size_pos[1].x * sinf(object_rotate_.y) + size_pos[1].z * -cosf(object_rotate_.y) + object_position_.x;
	corner_pos[1].z = size_pos[1].x * cosf(object_rotate_.y) + size_pos[1].z * sinf(object_rotate_.y) + object_position_.z;

	corner_pos[2].x = size_pos[2].x * sinf(object_rotate_.y) + size_pos[2].z * -cosf(object_rotate_.y) + object_position_.x;
	corner_pos[2].z = size_pos[2].x * cosf(object_rotate_.y) + size_pos[2].z * sinf(object_rotate_.y) + object_position_.z;

	corner_pos[3].x = size_pos[3].x * sinf(object_rotate_.y) + size_pos[3].z * -cosf(object_rotate_.y) + object_position_.x;
	corner_pos[3].z = size_pos[3].x * cosf(object_rotate_.y) + size_pos[3].z * sinf(object_rotate_.y) + object_position_.z;

	//Vector3 vec;
	//Vector3 vec2;
	//vec.x = std::fabs(corner_pos[1].x - corner_pos[0].x);
	//vec.z = std::fabs(corner_pos[3].z - corner_pos[0].z);
	//test.x = CalculateVectorToLength(vec);
	//test.z = CalculateVectorToLength(vec2);
	//test.y = 0.0f;

	printfDx("corner[%d] : {%f, %f, %f}\n", 0, corner_pos[0].x, corner_pos[0].y, corner_pos[0].z);
	printfDx("corner[%d] : {%f, %f, %f}\n", 1, corner_pos[1].x, corner_pos[1].y, corner_pos[1].z);
	printfDx("corner[%d] : {%f, %f, %f}\n", 2, corner_pos[2].x, corner_pos[2].y, corner_pos[2].z);
	printfDx("corner[%d] : {%f, %f, %f}\n", 3, corner_pos[3].x, corner_pos[3].y, corner_pos[3].z);
}

void Fence::Render()
{
	// 柵モデルの描画
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	//Vector3 coll_size;
	//coll_size.set(10.0f, 10.0f, 5.0f);
	//Vector3 left_up, left_bottom, right_up, right_bottom;
	//float y = collision_size_.y;
	//left_up.set(object_position_.x - (coll_size.x / 2), y, (object_position_.z - (coll_size.z / 2)));
	//left_bottom.set(object_position_.x - (coll_size.x / 2), y, (object_position_.z + (coll_size.z / 2)));
	//right_up.set(object_position_.x + (coll_size.x / 2), y, (object_position_.z - (coll_size.z / 2)));
	//right_bottom.set(object_position_.x + (coll_size.x / 2), y, (object_position_.z + (coll_size.z / 2)));

	DrawLine3D(VGet(corner_pos[0].x, corner_pos[0].y, corner_pos[0].z), VGet(corner_pos[1].x, corner_pos[1].y, corner_pos[1].z), GetColor(255, 0, 0));
	DrawLine3D(VGet(corner_pos[1].x, corner_pos[1].y, corner_pos[1].z), VGet(corner_pos[2].x, corner_pos[2].y, corner_pos[2].z), GetColor(255, 0, 0));
	DrawLine3D(VGet(corner_pos[2].x, corner_pos[2].y, corner_pos[2].z), VGet(corner_pos[3].x, corner_pos[3].y, corner_pos[3].z), GetColor(255, 0, 0));
	DrawLine3D(VGet(corner_pos[3].x, corner_pos[3].y, corner_pos[3].z), VGet(corner_pos[0].x, corner_pos[0].y, corner_pos[0].z), GetColor(255, 0, 0));

	//// HP描画
	//HPRender();
}

Vector3 Fence::GetterFencePosition()
{
	return object_position_;
}

Vector3 Fence::GetterFenceCollisionSize()
{
	return collision_size_;
}