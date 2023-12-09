#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "Rock05.h"

Rock05::Rock05(Vector3 create_pos, Vector3 create_rot)
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/stage/rock/rock05.mv1");
	object_position_= create_pos;
	object_rotate_ = create_rot;
	object_scale_.set(15.0f, 15.0f, 15.0f);
}