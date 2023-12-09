#pragma once

#include "Vector3.h"

bool CheckBallHit(Vector3 center1, float radius1, Vector3 center2, float radius2);
bool CheckBoxHit3D(Vector3 box_pos1, Vector3 box_size1, Vector3 box_pos2, Vector3 box_size2);

//=========================================================
// é©éÂêßçÏä÷êî
//=========================================================
void CheckBoxSphereHit(int* box_model_data, Vector3 sphere_center, float sphere_radius);

Vector3 CalculateTwoVector(Vector3 vec1, Vector3 vec2);
float CalculateVectorToLength(Vector3 vec);

bool CheckHitPointToCircle(Vector3 point, Vector3 circle_center, float circle_radius);

Vector3 HitCollision(Vector3 obj_pos, Vector3 obj_before_pos, Vector3 obj_size,
	Vector3 box_pos, Vector3 box_size);