#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "Rock04.h"

Rock04::Rock04(Vector3 create_pos, Vector3 create_rot)
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/stage/rock/rock04.mv1");
	object_position_= create_pos;
	object_rotate_ = create_rot;
	object_scale_.set(13.0f, 13.0f, 13.0f);
}