#include <vector>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "Villager.h"

#include "../../Environment/FenceBase.h"

#include "../../../Other/StatusData.h"
#include "../../../System/Vector3.h"
#include "../../../System/Hit.h"

#define VILLAGER_MOV_SPEED	0.4f

#define FOLLOW_PLAYER_RANGE 30.0f
#define LOST_PLAYER_RANGE   40.0f

Villager::Villager(int handle, Vector3 pos, int id)
{

	// ���f���f�[�^�i�[
	object_model_ = new int;
	*object_model_ = MV1DuplicateModel(handle);

	// �e�ϐ��̐ݒ�(������)
	object_position_ = pos;	// �ʒu
	object_scale_.set(0.05f, 0.05f, 0.05f);		// �傫��
	object_box_size_.set(3.0f, 3.0f, 3.0f);

	before_pos_ = pos;

	// �eprivate�ϐ��̐ݒ�
	// ���g��ID���擾
	my_id_ = id;
	player_position_.set(0.0f, 0.0f, 0.0f);
	vector_with_player_.set(0.0f, 0.0f, 0.0f);
	length_with_player_ = 0.0f;
	is_player_follow_ = false;

	//-------------------------------------
	// �A�j���[�V�����֌W
	// �����ݒ�

	float random = GetRandomStartFrame();

	// ���g�̃��f������n��
	FetchObjectModel(*object_model_);
	// �L�����N�^�[�ɂ������A�j���[�V��������ݒ肷��
	SettingAnimation({ {"idle", "data/villager/animation/Idle.mv1", 0, random, 0.5f},
					   {"runaway", "data/villager/animation/Runaway.mv1", 0, 0.0f, 0.5f},
					   {"runforgoal", "data/villager/animation/RunForGoal.mv1", 0, 0.0f, 0.5f},
					   { "death", "data/villager/animation/Death.mv1", 0, 0.0f, 0.5f } });
	// ���g�̃��f���Ɋe�A�j���[�V�������A�^�b�`����
	AttachAnimation();
}

Villager::~Villager()
{
	delete object_model_;
}

void Villager::Update()
{
	if (!is_render_) return;

	// �P�t���[���O�̍��W��ۊǂ��Ă���
	before_pos_ = object_position_;
	before_pos_.y = 0.0f;

	switch (villager_status)
	{
	case VillagerStatus::Idle:			// �ҋ@
		is_search_ = true;

		// �A�j���[�V����(�ҋ@��(�����~�܂��Ă���))
		PlayLoopAnimation("idle");

		break;
	case VillagerStatus::FollowPlayer:	// �v���C���[�ɂ��Ă���
		is_search_ = true;

		// �A�j���[�V����(�v���C���[�ǔ�)
		PlayLoopAnimation("runaway");
		break;
	case VillagerStatus::Damaged:		// �U�����󂯂�
		is_search_ = false;

		break;
	case VillagerStatus::GoalPoint:		// �ړI�n�ɓ��B
		add_time_ = 0;

		is_search_ = false;

		// �A�j���[�V����(�ړI�n�Ɍ�����)
		PlayLoopAnimation("runforgoal");
		// �ړI�n�ɓ����������Ƃ̏����������Ȃ�
		GoalAction();
		//// �X�e�[�^�X���u���B�ς݁v�ɂ���
		//SetterStatus(VillagerStatus::Reached);
		break;
	case VillagerStatus::Reached:

		break;
	case VillagerStatus::KnockDown:		// �_�E��
		is_search_ = false;

		// �A�j���[�V����(�_�E��)
		PlayLoopAnimation("death");
		break;
	}

	if (is_goal_)
	{

	}
	else
	{
		// ���̏��������Ă��Ȃ��Ƃ�
		if (is_search_)
		{
			// ��Ƀv���C���[��T��
			SearchPlayer(player_position_);
		}
		if (is_player_follow_)
		{
			// �X�e�[�^�X���u�v���C���[�ɂ��Ă����v�ɂ���
			SetterStatus(VillagerStatus::FollowPlayer);
		}
	}

	//if (is_player_follow_)
	//{
	//	is_walk_ = true;
	//}
	//else
	//{
	//	is_walk_ = false;
	//}

	//--------------------------------
	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	// �X�e�[�W�T�C�h
	// ����
	if (CheckBoxHit3D(object_position_, object_box_size_, { -175.0f, 0.0f, 0.0f }, { 25.0f, 10.0f, 150.0f }))
	{
		Vector3 set_left = { -175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos_, object_box_size_, set_left, set_size);
		object_position_.y = 0.0f;
	}
	// �E��
	if (CheckBoxHit3D(object_position_, object_box_size_, { 175.0f, 0.0f, 0.0f }, { 25.0f,10.0f,150.0f }))
	{
		Vector3 set_right = { 175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos_, object_box_size_, set_right, set_size);
		object_position_.y = 0.0f;
	}

	// ��
	for (auto& f_obj : fences_)
	{
		if (CheckBoxHit3D({ object_position_.x,object_position_.y + 3.0f,object_position_.z }, object_box_size_, f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize()))
		{
			// �t���O�𗧂Ă�
			//ishit_fence_ = true;
			printfDx("��Ɠ�����܂���\n");

			object_position_ = HitCollision({ object_position_.x,object_position_.y + 3.0f,object_position_.z }, before_pos_, object_box_size_,
				f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize());
			object_position_.y = 0.0f;
		}
		else
		{
			//ishit_fence_ = false;
		}
	}

	// �S�[��
	if (CheckBoxHit3D(object_position_, object_box_size_, { 0.0f, 0.0f, 165.0f }, { 25.0f, 5.0f, 15.0f }))
	{
		// �S�[�������u�Ԃɐ������Ԃ𐔕b���₷
		add_time_ = 5;

		SetterStatus(VillagerStatus::GoalPoint);
	}

#if SHOW_DEBUG
	//value = static_cast<int>(villager_status);
	//printfDx("status : %d\n", value);
	//printfDx("length_with_player_ : %f\n", length_with_player_);
	//printfDx("ishit_fence : %d\n", ishit_fence_);
	//printfDx("ishit_villager : %d\n", ishit_villager_);
#endif
}

void Villager::Render()
{
	if (!is_render_) return;

	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	DrawSphere3D({ object_position_.x,object_position_.y + 6.0f, object_position_.z }, 3.0f,8,
		GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);
}

void Villager::SetPlayerInfomation(const Vector3& p_pos)
{
	player_position_.set(p_pos.x, p_pos.y, p_pos.z);
}

void Villager::SearchPlayer(Vector3 pos)
{
	// �Q�̍��W����x�N�g�������߂�
	vector_with_player_ = CalculateTwoVector(pos, object_position_);

	// ���������߂�
	length_with_player_ = CalculateVectorToLength(vector_with_player_);

	// ��苗�����Ƀv���C���[����������
	if (length_with_player_ < 5.0f)
	{
		Vector3 dir = vector_with_player_ * -1.0f;
		dir.SetLength(5.0f);

		//object_position_ = pos + dir;
		//object_position_.y = 0.0f;
	}
	// �v���C���[�ɐڋ߂�����A�����~�܂�悤�ɂ���
	else if (length_with_player_ < 7.0f)
	{
		// �X�e�[�^�X���u�ҋ@�v�ɂ���
		SetterStatus(VillagerStatus::Idle);
		object_position_.y = 0.0f;

		// �t���O�𗧂Ă�
		IsAlwaysFollow(0);
	}
	else if (length_with_player_ < FOLLOW_PLAYER_RANGE)
	{
		// �v���C���[�����킹��
		FollowObject(vector_with_player_);
		object_position_.y = 0.0f;

		// �t���O�𗧂Ă�
		IsAlwaysFollow(1);
	}
	// ���ꂷ���Ă��܂�����(���E�����炢�Ȃ��Ȃ�������)
	else if (length_with_player_ > LOST_PLAYER_RANGE)
	{
		// �X�e�[�^�X���u�ҋ@�v�ɂ���
		SetterStatus(VillagerStatus::Idle);
		object_position_.y = 0.0f;

		IsAlwaysFollow(0);
	}
}

void Villager::IsAlwaysFollow(bool flag)
{
	is_player_follow_ = flag;
}

void Villager::FollowObject(Vector3 vec)
{
	//// �X�e�[�^�X���u�v���C���[�ɂ��Ă����v�ɂ���
	//SetterStatus(VillagerStatus::FollowPlayer);

	// �x�N�g���̐��K��
	vec.VSet(VNorm(vec.VGet()));

	// �ړ���������Ɍ�����
	object_rotate_.y = atan2f(vec.x, vec.z);
	// �v���C���[�Ɍ�����
	object_position_.x += VILLAGER_MOV_SPEED * sinf(object_rotate_.y);
	object_position_.z += VILLAGER_MOV_SPEED * cosf(object_rotate_.y);
	object_position_.y = 0.0f;
}

void Villager::GoalAction()
{
	// �S�[���t���O�𗧂Ă�
	is_goal_ = true;
	// �X�e�[�W���Ɍ����킹��
	FollowObject({ 0.0f,0.0f,250.0f });
	if (object_position_.z >= 230.0f)
	{
		// �`�悵�Ȃ��悤�ɂ���
		is_render_ = false;
	}
}

void Villager::SetFenceInfo(std::vector<FenceBase*> f_objs)
{
	fences_ = f_objs;
}

int Villager::GetterMyID() const
{
	// ���g�̎���ID��n��
	return my_id_;
}

bool Villager::GetterIsCollidingWithEnemy() const
{
	return ishit_enemy_;
}

bool Villager::GetterIsGoal() const
{
	return is_goal_;
}

Vector3 Villager::GetterMyBeforePosition() const
{
	return before_pos_;
}

int Villager::GetterVillagerStatus() const
{
	return value;
}

void Villager::SetterMyPosition(Vector3 set_pos)
{
	object_position_ = set_pos;
}

void Villager::SetterIsHitEnemy(bool ishit)
{
	ishit_enemy_ = ishit;
}

void Villager::SetterIsHitVillager(bool ishit)
{
	ishit_villager_ = ishit;
}

void Villager::SetterStatus(VillagerStatus status)
{
	villager_status = status;
}