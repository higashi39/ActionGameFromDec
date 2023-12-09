#include "../../Main.h"
#include "../../Scene/Game.h"
#include "RockBase.h"

RockBase::RockBase()
{
	object_position_.set(0.0f, 0.0f, 0.0f);
	object_scale_.set(0.0f, 0.0f, 0.0f);
}

void RockBase::Render()
{
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);
}