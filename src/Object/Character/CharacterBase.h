#pragma once
#include "../../Other/Animation.h"
#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	�I�u�W�F�N�g��{�N���X
//---------------------------------------------------------------------------------
class CharacterBase : public Animation
{
public:
	CharacterBase();
	~CharacterBase() {};


	//// �~�̓����蔻��
	//Vector3 object_collision_position_; // ���S
	//float object_collision_radius_;		// ���a

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;

	// �Q�b�^�[�֐�
	// ���g�̈ʒu��n��
	virtual Vector3 GetterMyPosition() const;

	//// �o��(�\��)�����邩�ǂ����̐ݒ�/�擾
	//void SetIsActive(bool a);
	//bool GetIsActive();

	//// �����蔻��ɂ�鉟���o������
	//// hitcoll_pos : ���������L�����N�^�[���W
	//// hit_power : ���������ۂ̉����o����
	//void PushColl(Vector3 hitcoll_pos, float hit_power);

	//// ���g�̃J�v�Z���R���W�����̐ݒ�
	//void SetCapsuleColl(float up_y, float bottom_y, float rot);

	// �ǂƂ̓����蔻��
	// top_cap_pos : �J�v�Z���̋���(�㑤)�̍��W
	// bottom_cap_pos : �J�v�Z���̋���(����)�̍��W
	// cap_rot : �����̃R���W�������a
	//void HitStageModel(/*VECTOR top_cap_pos, VECTOR bottom_cap_pos, */float cap_rot);

	//void HitModelToModel(Base* other);
protected:
	int* object_model_;			// ���f���f�[�^�i�[�p

	Vector3	object_position_;	// �ʒu
	Vector3	object_rotate_;		// ��]
	Vector3 object_scale_;		// �傫��

	Vector3 object_box_size_;		// �����蔻��̃R���W�����̑傫��

	bool is_walk_ = false;			// �����Ă��邩�ǂ���

};


