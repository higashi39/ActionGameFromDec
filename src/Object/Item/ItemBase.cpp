#include <iostream>
#include "../../Main.h"
#include "ItemBase.h"

ItemBase::ItemBase()
{
	object_model_ = NULL;
	object_position_.clear();
	object_rotate_.clear();
	object_scale_.set(0.02f, 0.02f, 0.02f);
}

Vector3 ItemBase::GetterMyPosition() const
{
	return object_position_;
}