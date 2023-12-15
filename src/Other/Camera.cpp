#include "../Main.h"
#include "../Scene/Game.h"

#include "Camera.h"

#define BIRDS_EYE 1

Camera::Camera()
{
	camera_position_.set(0.0f, 0.0f, 0.0f);
	camera_default_position_.set(0.0f, 50.0f, -30.0f);
	camera_look_.set(0.0f, 0.0f, 0.0f);
	camera_rotation_.set(0.0f, 180.0f, 0.0f);
	camera_radius_ = 1.0f;

#if BIRDS_EYE
	// �J�����܂ł̏����̒���
	distance_toplayer_ = 20.0f;
#endif
}

void Camera::Update(const Vector3& p_pos)
{
#if BIRDS_EYE
	// ������W�̓v���C���[�ʒu
	camera_look_ = p_pos;

	// �J�����̈ʒu���X�V����
	camera_position_.x = camera_default_position_.x + camera_look_.x + distance_toplayer_ * sinf(TO_RADIAN(camera_rotation_.y));
	camera_position_.z = camera_default_position_.z + camera_look_.z + distance_toplayer_ * cosf(TO_RADIAN(camera_rotation_.y));
	camera_position_.y = camera_default_position_.y;
#endif
}

void Camera::Render()
{
	SetCameraPositionAndTarget_UpVecY(VGet(camera_position_.x, camera_position_.y, camera_position_.z),
		VGet(camera_look_.x, camera_look_.y, camera_look_.z));

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}