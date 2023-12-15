#include "../../Main.h"
#include "../../Scene/Game.h"
#include "Ground.h"

Ground::Ground()
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/stage/ground/ground.mv1");

	object_position_.set(0.0f, -0.3f, 0.0f);
	object_scale_.set(1.0f,0.1f,1.0f);
}

void Ground::Render()
{
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	//DrawLine3D(VGet(-40.0f, 0.0f, 0.0f), VGet(40.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
	//DrawLine3D(VGet(0.0f, 0.0f, -40.0f), VGet(0.0f, 0.0f, 40.0f), GetColor(0, 0, 255));
}