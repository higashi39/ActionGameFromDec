#pragma once

#include "../System/Vector3.h"

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
public:
	Camera();
	~Camera() {};

	// �X�V
	// p_pos : �v���C���[�ʒu
	void Update(const Vector3& p_pos);
	// �`��
	void Render();

private:
	Vector3	camera_position_;			// �J�����̈ʒu
	Vector3 camera_default_position_;	// �J�����̃f�t�H���g�ʒu

	Vector3	camera_look_;				// �J����������ʒu
	Vector3 camera_rotation_;			// �J������]��
	float camera_radius_;				// �J�����̔��a

	float distance_toplayer_;			// �v���C���[�Ƃ̋���
};
