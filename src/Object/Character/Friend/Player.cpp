#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include <cmath>

#include "Player.h"
#include "../Enemy/Type/EnemyBase.h"
#include "../../Environment/FenceBase.h"

#include "../../../Other/StatusData.h"
#include "../../../System/Hit.h"

#define PLAYER_MOV_SPEED	0.5f
#define PLAYER_ROT_SPEED	3.0f

Player::Player()
{
	// ���f���f�[�^�i�[
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/player/model/Human.mv1");

	// �e�ϐ��̐ݒ�(������)
	object_position_.set(0.0f, 0.0f, -250.0f);		// �ʒu
	object_rotate_.y = TO_RADIAN(0.0f);			// ��]
	object_scale_.set(0.05f, 0.05f, 0.05f);		// �傫��

	object_box_size_.set(3.0f, 3.0f, 3.0f);

	is_enable_attack_ = true;
	attack_cool_time_ = 0.0f;

	//is_enable_spacekey_ = false;

	//-------------------------------------
	// �A�j���[�V�����֌W
	// �����ݒ�

	// ���g�̃��f������n��
	FetchObjectModel(*object_model_);
	// �L�����N�^�[�ɂ������A�j���[�V��������ݒ肷��
	SettingAnimation({ {"idle",   "data/player/animation/Idle.mv1",			0, 0.0f, 1.0f},
					   {"run",   "data/player/animation/Run.mv1",			0, 0.0f, 1.0f},
					   {"attack", "data/player/animation/AttackSword.mv1",  0, 0.0f, 1.0f} });
	// ���g�̃��f���Ɋe�A�j���[�V�������A�^�b�`����
	AttachAnimation();

	//// HP���̏�����
	//hp_.Init();
}

void Player::Update()
{
	// �v���C���[�̂P�t���[���O�̍��W��ۊǂ��Ă���
	Vector3 before_pos;
	before_pos = object_position_;

	//// HP���̍X�V
	//hp_.Update();

	//----------------------------------
	// �L�[����

	// ��]
	if (CheckHitKey(KEY_INPUT_D))
	{
		// ���W�A���p��3�x���₷
		object_rotate_.y += TO_RADIAN(PLAYER_ROT_SPEED);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		object_rotate_.y -= TO_RADIAN(PLAYER_ROT_SPEED);
	}

	if (CheckHitKey(KEY_INPUT_W))					// �ړ�
	{
		SetterStatus(PlayerStatus::Run);

		// m_rot �̓��W�A���p�Ōv�Z���Ă��邩��֐��͂��̂܂ܓn��
		object_position_.x += PLAYER_MOV_SPEED * sinf(object_rotate_.y);
		object_position_.z += PLAYER_MOV_SPEED * cosf(object_rotate_.y);
	}
	else if (PushHitKey(KEY_INPUT_SPACE))		// �X�y�[�X�L�[����������
	{
		// �X�y�[�X�L�[���������t���O�𗧂Ă�
		is_enable_spacekey_ = true;

		//// �v���C���[�̑O���ɓG��������
		//if(CheckHitPointToCircle())
		//// �v���C���[��Ԃ��u�U���v�ɕύX
		//SetterStatus(PlayerStatus::Attack);
	}
	else
	{
		SetterStatus(PlayerStatus::Idle);
	}

	// �X�y�[�X�L�[�������ꂽ�t���O�������Ă�����
	if (is_enable_spacekey_)
	{
		// �S�G�̏����擾����
		if (CheckHitEnemy())
		{

		}
		else
		{
			is_enable_spacekey_ = false;
		}
	}

	//--------------------------------
	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	// �X�e�[�W�T�C�h
	// ����
	if (CheckBoxHit3D(object_position_, object_box_size_, { -175.0f, 0.0f, 0.0f }, { 25.0f, 10.0f, 150.0f }))
	{
		Vector3 set_left = { -175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos, object_box_size_, set_left, set_size);
	}
	// �E��
	if (CheckBoxHit3D(object_position_, object_box_size_, { 175.0f, 0.0f, 0.0f }, { 25.0f,10.0f,150.0f }))
	{
		Vector3 set_right = { 175.0f, 0.0f, 0.0f };
		Vector3 set_size = { 25.0f, 10.0f, 150.0f };
		object_position_ = HitCollision(object_position_, before_pos, object_box_size_, set_right, set_size);
	}

	// ��
	for (auto& f_obj : fence_objs_)
	{
		if (CheckBoxHit3D(object_position_, object_box_size_, f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize()))
		{
			object_position_ = HitCollision(object_position_, before_pos, object_box_size_,
				f_obj->GetterFencePosition(), f_obj->GetterFenceCollisionSize());
		}
	}

	// �U������ł����
	if (!is_enable_attack_)
	{
		// �N�[���_�E�����Ԃ��J�E���g����
		PlayerCountAttackCoolTime();

	}

	//---------------------------------------------------------
	// �A�j���[�V�����̍X�V
	//---------------------------------------------------------
	// �A�j���[�V�����̍Đ�
	switch (player_status)
	{
	case PlayerStatus::Idle:			// �ҋ@��(�����~�܂��Ă���)
		PlayLoopAnimation("idle");
		break;
	case PlayerStatus::Run:			// �ړ���
		PlayLoopAnimation("run");
		break;
	case PlayerStatus::Attack:			// �U��
		PlayOnceAnimation("attack");
		break;
	}

#if SHOW_DEBUG
	printfDx("player_pos : %f, %f\n", object_position_.x, object_position_.z);
#endif
}

void Player::Render()
{
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	// ���g�̃J�v�Z��
	DrawCapsule3D(VGet(object_position_.x, 5.0f, object_position_.z),
		VGet(object_position_.x, 3.0f, object_position_.z), 3.0f, 8,
		GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);

	// ���g�̑O�����̃x�N�g�����擾
	Vector3 front;
	front.x = object_position_.x + 5.0f * std::sinf(object_rotate_.y);
	front.z = object_position_.z + 5.0f * std::cosf(object_rotate_.y);
	front.y = 0.0f;
	DrawSphere3D(VGet(front.x, 4.0f, front.z), 1.5f, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

void Player::RenderFor2D()
{
	//hp_.Render();
}

void Player::PlayerAttack(EnemyBase* e_obj)
{
	// �v���C���[��Ԃ��u�U���v�ɂ���
	player_status = PlayerStatus::Attack;

	// �v���C���[���N�[���_�E�����łȂ�������
	if (is_enable_attack_)
	{
		e_obj->SetterIsDamageToPlayer(true);
		is_enable_spacekey_ = false;
	}
}

void Player::PlayerCountAttackCoolTime()
{
	attack_cool_time_++;
	if (attack_cool_time_ > 120.0f)
	{
		is_enable_attack_ = true;
		attack_cool_time_ = 0.0f;
	}
}

void Player::FetchEnemyInfo(const std::vector<EnemyBase*>& e_objs)
{
	enemy_objs_ = e_objs;
}

void Player::FetchFenceInfo(const std::vector<FenceBase*>& f_objs)
{
	fence_objs_ = f_objs;
}

bool Player::CheckHitEnemy()
{
	// ���g�̑O�����̃x�N�g�����擾
	Vector3 front;
	front.x = object_position_.x + 5.0f * std::sinf(object_rotate_.y);
	front.z = object_position_.z + 5.0f * std::cosf(object_rotate_.y);
	front.y = 0.0f;

	// �v���C���[�̑O���Ɗe�G�̓����蔻�������
	for (auto& obj : enemy_objs_)
	{
		if (CheckHitPointToCircle(obj->GetterMyPosition(), front, 1.5f))
		{
			// �v���C���[�̍U������(�_���[�W��^����G��ݒ肷��)
			PlayerAttack(obj);

			return true;
		}
	}
	return false;
}

int* Player::GetterPlayerModelPointer()
{
	return object_model_;
}

Player::PlayerStatus Player::GetterPlayerStatus()
{
	return player_status;
}

void Player::SetterStatus(PlayerStatus status)
{
	player_status = status;
}

void Player::SetterIsHitEnemy(bool is_hit)
{

}