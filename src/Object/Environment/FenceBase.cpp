#include <cmath>

#include "../../Main.h"
#include "../../Scene/Game.h"
#include "FenceBase.h"
#include "Fence.h"

#include "../../System/Hit.h"

FenceBase::FenceBase()
{
	if (object_rotate_.y == 0.0f)
	{
		float tmp_x, tmp_z;
		tmp_x = collision_size_.z;
		tmp_z = collision_size_.x;

		collision_size_.x = tmp_x;
		collision_size_.z = tmp_z;
	}
}

FenceBase::~FenceBase()
{
	delete object_model_;
}

Vector3 FenceBase::GetterFencePosition()
{
	return object_position_;
}

Vector3 FenceBase::GetterFenceCollisionSize()
{
		return collision_size_;
}