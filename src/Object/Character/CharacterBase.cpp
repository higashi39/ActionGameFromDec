#include "../../Main.h"
#include "CharacterBase.h"

#include <iostream>

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CharacterBase::CharacterBase()
{
	object_model_ = NULL;
	object_position_.clear();
	object_rotate_.clear();
	object_scale_.set(0.02f, 0.02f, 0.02f);

	//object_collision_position_.clear();
	//object_collision_radius_ = 0.0f;

	object_box_size_.set(3.0f, 3.0f, 3.0f);
}

Vector3 CharacterBase::GetterMyPosition() const
{
	return object_position_;
}