#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <algorithm>

#include "../../../../Main.h"
#include "../../../../Scene/Game.h"
#include "../../Friend/VillagerManager.h"
#include "../../Friend/Villager.h"
#include "../../Friend/Player.h"

#include "../../../../System/Hit.h"
#include "../../../../Other/StatusData.h"

#include "EnemyBase.h"
#include "EnemySword.h"
#include "EnemyPatrol.h"

#define ENEMY_MOV_SPEED	0.1f
#define SEARCH_VILLAGER_RANGE 70.0f

EnemyBase::EnemyBase()
{
	my_id_ = 0;									// ���g�̎��ʔԍ�

	near_villager_ = NULL;						// ��ԋ߂����l�̏��i�[�p
	//minimum_length_.set(0.0f, 0.0f, 0.0f);	// ���l�Ƃ̋���
	minimum_position_.set(0.0f, 0.0f, 0.0f);	// ��ԋ߂����l�̈ʒu�i�[�p
	minimum_vector_.set(0.0f, 0.0f, 0.0f);		// ��ԋ߂����l�Ƃ̃x�N�g���i�[�p

	//is_colliding_with_player_ = false;			// �v���C���[�ƐڐG���Ă��邩�ǂ���

	is_enable_attack_ = false;;			// �U���������L���ł��邩�ǂ���
	attack_cool_time_ = 0.0f;		// �U���̃N�[���_�E������

	fetch_player_position_.set(0.0f, 0.0f, 0.0f);
	fetch_villagers_.clear();

	// HP���̏�����
	hp_.Init();
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Render()
{
	if (!hp_.IsSurvice())	return;

	// ���f���̕`��
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);

	// ���g�̑O�����̃x�N�g�����擾
	Vector3 front;
	front.x = object_position_.x + 5.0f * std::sinf(object_rotate_.y);
	front.z = object_position_.z + 5.0f * std::cosf(object_rotate_.y);
	front.y = 0.0f;
	DrawSphere3D(VGet(front.x, 4.0f, front.z), 1.5f, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

	//	����͈͂��ǂ̂��炢�����킩��₷�����邽�߂ɐ���2�{�`��
	Vector3 line;
	//	���̐�̍��W(NPC�̌����{10�x�̕����ɒ���1000.0f������̏ꏊ)
	line.x = object_position_.x + 1000.0f * sinf(object_rotate_.y + TO_RADIAN(30.0f));
	line.z = object_position_.z + 1000.0f * cosf(object_rotate_.y + TO_RADIAN(30.0f));
	line.y = 5.0f;
	DrawLine3D(object_position_.VGet(), line.VGet(), GetColor(255, 128, 128));

	line.x = object_position_.x + 1000.0f * sinf(object_rotate_.y - TO_RADIAN(30.0f));
	line.z = object_position_.z + 1000.0f * cosf(object_rotate_.y - TO_RADIAN(30.0f));
	line.y = 5.0f;
	DrawLine3D(object_position_.VGet(), line.VGet(), GetColor(255, 128, 128));

}

void EnemyBase::RenderFor2D()
{
	// HP���̕`��
	hp_.Render();
}

void EnemyBase::SearchVillagers()
{
	// �S���l(�ی�Ώ�)�̒��ŁA�ł��������Z�����l���擾����
	float minimum_length = 10000.0f;
	for (auto& v_obj : fetch_villagers_)
	{
		// �Q�̍��W����x�N�g�������߂�
		Vector3 vector_with_villager_;
		vector_with_villager_ = CalculateTwoVector(v_obj->GetterMyPosition(), object_position_);

		// ���������߂�
		float length = CalculateVectorToLength(vector_with_villager_);

		// �ł��߂��������X�V����
		if (minimum_length > length)
		{
			near_villager_ = v_obj;
			minimum_length = length;
			minimum_position_ = v_obj->GetterMyPosition();
			minimum_vector_ = vector_with_villager_;
		}
	}
	
	// �����炭�����̏�����SearchVillager�ƕ����čl���Ȃ��Ƃ����Ȃ�
	// �����蔻��(���l�ɂ߂荞�܂Ȃ��悤�ɂ���)
	if (CheckHitPointToCircle(near_villager_->GetterMyPosition(), object_position_, 5.0f))
	{
		//// ���l�Ƃ̐ڐG�t���O�𗧂Ă�
		//near_villager_->SetterIsCollidingWithEnemy(true);
		
		// �G�̑O���ɂ�����
		// �G�X�e�[�^�X���u���l�ɍU���v�ɂ���
		enemy_status = EnemyStatus::Attack;

		Vector3 dir = minimum_vector_ * -1.0f;
		dir.SetLength(5.0f);

		object_position_ = minimum_position_ + dir;
	}
	//else
	//{
	//	//// ���l�ƐڐG�͂��Ă��Ȃ����B
	//	//// ���G�͈͓��ɑ��l���������ԋ߂����l��ǔ�����
	//	//if (minimum_length < SEARCH_VILLAGER_RANGE)
	//	//{
	//	//	//// �X�e�[�^�X��ǔ���
	//	//	//SetterStatus(EnemyStatus::TrackingVillger);
	//	//	// �ǔ�����
	//	//	ChaseNearVillager(minimum_vector_);
	//	//}
	//}
	//// ���ȏ�̋����������Ă��܂�����A�ǂ�������̂���߂�
	//if (minimum_length > 100.0f)
	//{
	//	// �X�e�[�^�X���u�ҋ@�v�ɂ���
	//	SetterStatus(EnemyStatus::Idle);
	//}
}

void EnemyBase::ChaseNearVillager(Vector3 near_vec)
{
	// �x�N�g���̐��K��
	near_vec.VSet(VNorm(near_vec.VGet()));

	// �ړ���������Ɍ�����
	object_rotate_.y = atan2f(near_vec.x, near_vec.z);
	// ���l�Ɍ�����
	object_position_.x += 0.05f * sinf(object_rotate_.y);
	object_position_.z += 0.05f * cosf(object_rotate_.y);
}

void EnemyBase::EnemyAttack(std::vector<Villager*>& v_objs_)
{
	for (auto& v_obj : v_objs_)
	{
		if (v_obj->GetterIsCollidingWithEnemy())
		{
			//// �ۑ聙 : ��قǃN�[���_�E�����쐬���āA�U���̊Ԋu���󂯂�
			//v_obj->hp_.SetterIsDamaged(true, 20.0f);
			// �U���N�[���_�E���̃J�E���g���J�n����
			is_enable_attack_ = false;
		}
	}
}

void EnemyBase::EnemyCountAttackCoolTime()
{
	attack_cool_time_++;
	if (attack_cool_time_ > 120.0f)
	{
		is_enable_attack_ = true;
		attack_cool_time_ = 0.0f;
	}
}

bool EnemyBase::IsViewRange()
{
	// ���g�̑O�����̃x�N�g�����擾
	Vector3 front;
	front.x = 1.0f * sinf(object_rotate_.y);
	front.z = 1.0f * cosf(object_rotate_.y);
	front.y = 0.0f;

	// ���l(��ԋ߂�)�ւ̃x�N�g��
	Vector3 target = minimum_vector_;
	target.normalize();

	// ���ς����߂�
	float front_dot = VDot(front.VGet(), target.VGet());
	// 2�̃x�N�g���̂Ȃ��p�����߂�
	// ���͈̔�(����̏ꍇ�A-1.0f~1.0f)�Ɏ��߂邽�߂�std::clamp���g�p����
	float target_angle = acosf(std::clamp(front_dot, -1.0f, 1.0f));

	// ���̋��߂�NPC���猩�ăv���C���[�܂ł̊p�x������p�����ǂ���
	// ����p��������͈݂͂̂���
	//printfDx("target_angle : %f\n", target_angle);
	if (target_angle < TO_RADIAN(30.0f)
		&& CalculateVectorToLength(minimum_vector_) <= SEARCH_VILLAGER_RANGE)
	{
		return true;
	}

	return false;
}

void EnemyBase::SetterIsDamageToPlayer(bool is_enable)
{
	is_enable_damage_ = is_enable;
}

int EnemyBase::GetterMyID() const
{
	return my_id_;
}

void EnemyBase::SetterMyPosition(Vector3 set_pos)
{
	object_position_ = set_pos;
}


void EnemyBase::FetchPlayerPosition(const Vector3& pos)
{
	// �v���C���[�̈ʒu�����炤
	fetch_player_position_ = pos;
}

void EnemyBase::FetchVillagersPosition(const std::vector<Villager*>& v_objs)
{
	// ���l�̏������炤
	fetch_villagers_ = v_objs;
}

void EnemyBase::SetterStatus(EnemyStatus status)
{
	enemy_status = status;
}

//void EnemyBase::HitOtherEnemy()
//{
//	//--------------------------------
//	// ���I�u�W�F�N�g�Ƃ̓����蔻��
//
//	// ���̓G�Ƃ̓����蔻�菈��
//	for (auto& obj : enemies_)
//	{
//		// �������g�������̎��ʔԍ������������G�͌��Ȃ�(�d���h�~)
//		if (e_obj->GetterMyID() <= obj->GetterMyID())
//		{
//			continue;
//		}
//
//		Vector3 vec;
//		vec = CalculateTwoVector(e_obj->GetterMyPosition(), obj->GetterMyPosition());
//		float len = CalculateVectorToLength(vec);
//
//		if (len < 5.0f)
//		{
//			Vector3 dir = vec * -1.0f;
//			dir.SetLength(5.0f);
//
//			obj->SetterMyPosition(e_obj->GetterMyPosition() + dir);
//		}
//	}
//}