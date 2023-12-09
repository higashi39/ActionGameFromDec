#include <iostream>
#include "../../Main.h"
#include "EnvironmentBase.h"

EnvironmentBase::EnvironmentBase()
{
	object_model_ = NULL;
	object_position_.clear();
	object_rotate_.clear();
	object_scale_.set(0.02f, 0.02f, 0.02f);

	object_collision_position_.clear();
	object_collision_radius_ = 0.0f;

	object_collision_size_ = 5.0f;
}

Vector3 EnvironmentBase::GetterMyPosition() const
{
	return object_position_;
}

int* EnvironmentBase::GetterModelData() const
{
	return object_model_;
}
