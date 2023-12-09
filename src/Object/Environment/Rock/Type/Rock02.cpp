#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "Rock02.h"

Rock02::Rock02(Vector3 create_pos, Vector3 create_rot)
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/stage/rock/rock02.mv1");
	object_position_= create_pos;
	object_rotate_ = create_rot;
	object_scale_.set(13.0f, 13.0f, 13.0f);
}