#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "EnemyPatrol.h"

#include "../../../../System/Hit.h"

EnemyPatrol::EnemyPatrol(Vector3 pos, int id)
{
	// ���f���f�[�^�[�i�[
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/enemy02/model/Enemy02.mv1");

	// �e�ϐ��̐ݒ�(������)
	object_position_ = pos;	// �ʒu
	object_scale_.set(0.05f, 0.05f, 0.05f);	// �傫��

	patrol_pos1_.set(0.0f, 0.0f, 0.3f);
	patrol_pos2_.set(0.0f, 0.0f, 10.0f);
	object_position_ = patrol_pos1_;	// �ʒu
	check_patrol_ = 0;
	turn_cool_time_ = 0.0f;

	my_id_ = id;

	//-------------------------------------
	// �A�j���[�V�����֌W
	// �����ݒ�

	// ���g�̃��f������n��
	FetchObjectModel(*object_model_);
	// �L�����N�^�[�ɂ������A�j���[�V��������ݒ肷��
	SettingAnimation({ {"idle", "data/enemy01/animation/Idle.mv1", 0, 0.0f, 0.3f},
		});
	// ���g�̃��f���Ɋe�A�j���[�V�������A�^�b�`����
	AttachAnimation();

	// HP���̏�����
	hp_.Init();
}

EnemyPatrol::~EnemyPatrol()
{
	delete object_model_;
}

//// �ŏ��͍��G��Ԃɂ��Ă���
//*enemy_status_ = ENEMYSTATUS::ENEMY_SEARCH;

void EnemyPatrol::Update()
{
	// �����t���O�������Ă��Ȃ���΁A�ȍ~�̍X�V�����͍s��Ȃ�
	if (!hp_.IsSurvice())	return;

	// HP���̍X�V����
	hp_.Update(object_position_, 12.0f);

	// ���l�Ƃ̋��������߂āA��ԋ߂����l�����߂�
	SearchVillagers();

	// ���E���ɑ��l����������
	if (IsViewRange())
	{
		// ���l�ǔ���ԂɂȂ�
		SetterStatus(EnemyStatus::TrackingVillger);
		// ���߂���ԋ߂����l��ǔ�����
		ChaseNearVillager(minimum_vector_);
	}
	else
	{
		// �X�e�[�^�X���u�ҋ@(����)�v�ɂ���
		enemy_status = EnemyStatus::Idle;
		// ���񂷂�
		PatrolAction();
	}

	//------------------------------------
	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	// ��
	// ���ۑ�F�v���C���[�ƍ�Ƃ̓����蔻��̃o�O������������쐬

	// �v���C���[
	// �����ŏ������s���ƁA�v���C���[���G�������Ă��܂��̂ŁA
	// �v���C���[�̕��ŏ������邱�Ƃ���������
	{
		Vector3 vec;
		vec = CalculateTwoVector(fetch_player_position_, object_position_);

		float len = CalculateVectorToLength(vec);

		// �v���C���[�ɐڐG������
		if (len < 5.0f)
		{

			Vector3 dir = vec * -1.0f;
			// object_collision_size_�����������ݒ肷�邱�Ƃœ����蔻����V�r�A�ɂ��Ȃ�
			dir.SetLength(5.0f);

			object_position_ = fetch_player_position_ + dir;
		}
	}

	// �U������ł����
	if (!is_enable_attack_)
	{
		// �N�[���_�E�����Ԃ��J�E���g����
		EnemyCountAttackCoolTime();
	}

	//---------------------------------------
	// �_���[�W����
	if (is_enable_damage_)
	{
		// �X�e�[�^�X���u�U�����󂯂�v�ɂ���
		enemy_status = EnemyStatus::Damage;
		// HP�����炷
		hp_.SetterIsDamaged(10.0f);
	}

	//---------------------------------------------------------
	// �A�j���[�V�����̍X�V
	//---------------------------------------------------------
	// �A�j���[�V�����̍Đ�
	switch (enemy_status)
	{
	case EnemyStatus::Idle:
		break;
	case EnemyStatus::SearchingVillager:
		// �ҋ@��(�����~�܂��Ă���)
		PlayLoopAnimation("idle");
		break;
	case EnemyStatus::TrackingVillger:
		// �ړ���
		PlayLoopAnimation("walk");
		break;
	case EnemyStatus::Attack:
		break;
	case EnemyStatus::Damage:
		break;
	case EnemyStatus::KnockDown:
		break;
	}

	value = static_cast<int>(enemy_status);

#if SHOW_DEBUG
	//printfDx("pos : %f, %f, %f\n", object_position_.x, object_position_.y, object_position_.z);
	//printfDx("turn_cool_time_ : %f\n", turn_cool_time_);
	//printfDx("status : %d\n", value);
#endif
}

void EnemyPatrol::PatrolAction()
{
	Vector3 distance;

	// �x�N�g�������߂�
	// ���ݎ��g�����Ȃ��ق��̈ʒu�Ɍ����ăx�N�g�����̂΂�
	if (check_patrol_ == 0)
	{
		// ���̐܂�Ԃ��n�_�ɋ߂Â�����A�����P�̒n�_�ɐ܂�Ԃ�
		if (CheckHitPointToCircle(object_position_, patrol_pos2_, 0.5f))
		{
			object_position_.set(patrol_pos2_);

			check_patrol_ = 1;
		}
		else
		{
			// patrol_pos1_�Ɍ�����
			distance = CalculateTwoVector(patrol_pos2_, object_position_);
		}
	}
	else if (check_patrol_ == 1)
	{
		// ���̐܂�Ԃ��n�_�ɋ߂Â�����A�����P�̒n�_�ɐ܂�Ԃ�
		if (CheckHitPointToCircle(object_position_, patrol_pos1_, 1.0f))
		{
			object_position_.set(patrol_pos1_);

			check_patrol_ = 0;
		}
		else
		{
			// patrol_pos2_�Ɍ�����
			distance = CalculateTwoVector(patrol_pos1_, object_position_);
		}
	}

	// ���������߂�
	float length = CalculateVectorToLength(distance);

	// �x�N�g���̐��K��
	distance.VSet(VNorm(distance.VGet()));

	// �ړ���������Ɍ�����
	object_rotate_.y = atan2f(distance.x, distance.z);
	// ���l�Ɍ�����
	object_position_.x += 0.05f * sinf(object_rotate_.y);
	object_position_.z += 0.05f * cosf(object_rotate_.y);
}