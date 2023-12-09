#include "../../Main.h"
#include "../../Scene/Game.h"
#include "Box.h"

#include "../../System/Hit.h"

Box::Box()
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/stage/box/box.mv1");

	object_position_.set(0.0f, 10.0f, 0.0f);					// 位置
	object_scale_.set(0.1f, 0.1f, 0.1f);		// 大きさ

	//coll_size.set(26.0f, 0.0f, 2.0f);			// 当たり判定用のサイズ
}

Box::~Box()
{
	delete object_model_;
}

void Box::Update()
{
}

void Box::Render()
{
	// 柵モデルの描画
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	// 見えないように透明にしておく
	MV1SetOpacityRate(*object_model_, 0.5f);

	Vector3 coll_size;
	coll_size.set(26.0f, 0.0f, 2.0f);
	Vector3 left_up, left_bottom, right_up, right_bottom;
	float y = 0.3f;
	left_up.set(object_position_.x - (coll_size.x / 2), y, (object_position_.z - (coll_size.z / 2)));
	left_bottom.set(object_position_.x - (coll_size.x / 2), y, (object_position_.z + (coll_size.z / 2)));
	right_up.set(object_position_.x + (coll_size.x / 2), y, (object_position_.z - (coll_size.z / 2)));
	right_bottom.set(object_position_.x + (coll_size.x / 2), y, (object_position_.z + (coll_size.z / 2)));
	DrawLine3D(VGet(left_up.x, left_up.y, left_up.z), VGet(right_up.x, right_up.y, right_up.z), GetColor(255, 0, 0));
	DrawLine3D(VGet(right_up.x, right_up.y, right_up.z), VGet(right_bottom.x, right_bottom.y, right_bottom.z), GetColor(255, 0, 0));
	DrawLine3D(VGet(right_bottom.x, right_bottom.y, right_bottom.z), VGet(left_bottom.x, left_bottom.y, left_bottom.z), GetColor(255, 0, 0));
	DrawLine3D(VGet(left_bottom.x, left_bottom.y, left_bottom.z), VGet(left_up.x, left_up.y, left_up.z), GetColor(255, 0, 0));

	//// HP描画
	//HPRender();
}