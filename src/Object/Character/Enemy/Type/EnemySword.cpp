#include <cmath>
#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "EnemySword.h"

#include "../../../../System/Hit.h"

EnemySword::EnemySword(int handle, Vector3 pos, Vector3 rot,int id)
{
	// ���f���f�[�^�[�i�[
	object_model_ = new int;
	*object_model_ = MV1DuplicateModel(handle);

	// �e�ϐ��̐ݒ�(������)
	object_position_ = pos;	// �ʒu
	object_rotate_ = rot;	// ����
	object_scale_.set(0.08f, 0.08f, 0.08f);	// �傫��

	my_id_ = id;

	//-------------------------------------
	// �A�j���[�V�����֌W
	// �����ݒ�

	// ���g�̃��f������n��
	FetchObjectModel(*object_model_);
	// �L�����N�^�[�ɂ������A�j���[�V��������ݒ肷��
	SettingAnimation({ {"idle", "data/enemy02/animation/Idle.mv1", 0, 0.0f, 0.3f},
					   {"walk", "data/enemy02/animation/Walk.mv1", 0, 0.0f, 0.3f},
 					   {"attack", "data/enemy02/animation/Attack.mv1", 0, 0.0f, 0.3f},
		});
	// ���g�̃��f���Ɋe�A�j���[�V�������A�^�b�`����
	AttachAnimation();
}

EnemySword::~EnemySword()
{
	delete object_model_;
}

//// �ŏ��͍��G��Ԃɂ��Ă���
//*enemy_status_ = ENEMYSTATUS::ENEMY_SEARCH;

void EnemySword::Update()
{
	//// �����t���O�������Ă��Ȃ���΁A�ȍ~�̍X�V�������s��Ȃ�
	//if (!hp_.IsSurvice())
	//{
	//	return;
	//}
	//// HP���̍X�V����
	//hp_.Update(object_position_, 10.0f);

	Hit();

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
		// �U��
		PlayLoopAnimation("attack");
		break;
	case EnemyStatus::Damage:
		break;
	case EnemyStatus::KnockDown:
		break;
	}


#if SHOW_DEBUG
	value = static_cast<int>(enemy_status);
	//printfDx("hp : %d\n", hp_num_);
	printfDx("enemy_status : %d\n,",value);
#endif
}