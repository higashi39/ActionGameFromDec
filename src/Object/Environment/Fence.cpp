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

	fence_size_.set(5.5f, 5.0f, 3.0f);
	//coll_size.set(26.0f, 0.0f, 2.0f);			// 当たり判定用のサイズ

	//Vector3 coll_size;
	//coll_size.set(10.0f, 10.0f, 5.0f);
	//Vector3 left_up;
	//Vector3 right_bottom;
	//left_up.set(object_position_.x - (coll_size.x / 2), coll_size.y, (object_position_.z - (coll_size.z / 2)));
	//right_bottom.set(object_position_.x + (coll_size.x / 2), coll_size.y, (object_position_.z + (coll_size.z / 2)));
	//Vector3 size;
	//size.x = fabs(left_up.x - right_bottom.x);
	//size.z = fabs(left_up.z - right_bottom.z);
	//size.y = 5.0f;
	//fence_size_ = size;
}

Fence::~Fence()
{
	delete object_model_;
}

//void Fence::FenceUpdate(const Vector3& p_pos)
//{
//}

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
	//float y = coll_size.y;
	//left_up.set(object_position_.x - (coll_size.x / 2), y, (object_position_.z - (coll_size.z / 2)));
	//left_bottom.set(object_position_.x - (coll_size.x / 2), y, (object_position_.z + (coll_size.z / 2)));
	//right_up.set(object_position_.x + (coll_size.x / 2), y, (object_position_.z - (coll_size.z / 2)));
	//right_bottom.set(object_position_.x + (coll_size.x / 2), y, (object_position_.z + (coll_size.z / 2)));

	//DrawLine3D(VGet(left_up.x, left_up.y, left_up.z), VGet(right_up.x, right_up.y, right_up.z), GetColor(255, 0, 0));
	//DrawLine3D(VGet(right_up.x, right_up.y, right_up.z), VGet(right_bottom.x, right_bottom.y, right_bottom.z), GetColor(255, 0, 0));
	//DrawLine3D(VGet(right_bottom.x, right_bottom.y, right_bottom.z), VGet(left_bottom.x, left_bottom.y, left_bottom.z), GetColor(255, 0, 0));
	//DrawLine3D(VGet(left_bottom.x, left_bottom.y, left_bottom.z), VGet(left_up.x, left_up.y, left_up.z), GetColor(255, 0, 0));

	//// HP描画
	//HPRender();
}

Vector3 Fence::GetterFencePosition()
{
	return object_position_;
}

Vector3 Fence::GetterFenceSize()
{
	return fence_size_;
}