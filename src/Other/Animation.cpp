#include "../Main.h"
#include "../Scene/Game.h"

#include "../System/Random.h"
#include "Animation.h"

Animation::Animation() : model_(NULL), start_frame_(0.0f)
{

}

float Animation::GetRandomStartFrame()
{
	start_frame_ = GetRandomF(0.0f, 1.0f);
	return start_frame_;
}

void Animation::FetchObjectModel(int model)
{
	model_ = model;
}

void Animation::SettingAnimation(const std::vector<Animation::AnimationData> data)
{
	// �e�L�����N�^�[�œǂݍ��݂����A�j���[�V�������i�[����
	anim_data_ = data;

	// �󂯎�����A�j���[�V�����̐����A�e�ϐ��̗v�f��ǉ�����
	// anim_index_, anim_model_�ɂ̓G���[�����̒l-1�����Ă���
	// ���ϐ���0.0f����
	for (int i = 0; i < anim_data_.size(); ++i)
	{
		anim_index_.emplace_back(-1);
		anim_model_.emplace_back(-1);
		anim_total_frame_.emplace_back(0.0f);
		anim_frame_.emplace_back(0.0f);
		anim_rate_.emplace_back(0.0f);
	}

	before_anim_name_ = anim_data_[0].anim_name_;

	// �A�j���[�V�����ǂݍ��݂��s��
	LoadAnimation();
}

// �A�j���[�V�����̓ǂݍ���
// model : ���f���f�[�^
void Animation::LoadAnimation()
{
	//anim_data[ANIM_IDLE] = MV1LoadModel("data/player/animation/Idle.mv1");

	for (int i = 0; i < anim_data_.size(); i++)
	{
		// string�^��anim_path_��const char*�^�ɕϊ�����
		const char* char_path = anim_data_[i].anim_path_.c_str();
		// �A�j���[�V������ǂݍ���
		anim_model_[i] = MV1LoadModel(char_path);
	}
}

void Animation::AttachAnimation()
{
	for (int i = 0; i < anim_data_.size(); i++)
	{
		// �A�j���[�V�����̃A�^�b�`
		anim_index_[i] = MV1AttachAnim(model_, anim_data_[i].anim_index_, anim_model_[i], TRUE);
		// �A�^�b�`�������f�������t���[����(1���[�v)
		anim_total_frame_[i] = MV1GetAttachAnimTotalTime(model_, anim_index_[i]);
		// �n�߂���(0)�ɏ�����
		anim_frame_[i] = anim_data_[i].start_frame_;
		anim_rate_[i] = 0.0f;

		if (anim_data_[i].anim_name_ == "idle")
		{
			// �ҋ@�A�j���[�V�����������ő��
			anim_rate_[0] = 1.0f;
		}
	}
}

void Animation::PlayLoopAnimation(std::string anim_name)
{
	for (int i = 0; i < anim_data_.size(); ++i)
	{
		if (anim_data_[i].anim_name_ == anim_name)
		{
			anim_rate_[i] += 0.1f;
		}
		else
		{
			anim_rate_[i] -= 1.0f;
		}

		anim_rate_[i] = max(0.0f, min(anim_rate_[i], 1.0f));

		// �A�j���[�V�����̃t���[����i�߂�
		anim_frame_[i] += 1.0f * anim_data_[i].anim_speed_;
		// 1���[�v���i�񂾂�0�Ƀ��Z�b�g
		if (anim_frame_[i] >= anim_total_frame_[i])
		{
			anim_frame_[i] = 0.0f;
		}
		// ���̃t���[���̃A�j���[�V�����ɂ���
		MV1SetAttachAnimTime(model_, anim_index_[i], anim_frame_[i]);
		MV1SetAttachAnimBlendRate(model_, anim_index_[i], anim_rate_[i]);
	}
}

void Animation::PlayOnceAnimation(std::string anim_name)
{
	for (int i = 0; i < anim_data_.size(); ++i)
	{
		if (anim_data_[i].anim_name_ == anim_name)
		{
			anim_rate_[i] += 0.1f;
		}
		else
		{
			// ���ݍĐ����̃A�j���[�V�����̑O�ɍĐ����Ă����A�j���[�V������ێ�����
			if (anim_rate_[i] > 0.0f)
			{
				SetBeforeAnimation(anim_data_[i].anim_name_);
			}
			anim_rate_[i] -= 1.0f;
			anim_frame_[i] = 0.0f;		// �g�p���Ă��Ȃ��A�j���[�V�����̃t���[����0.0f�ɂ��Ă���
		}

		anim_rate_[i] = max(0.0f, min(anim_rate_[i], 1.0f));

		// �A�j���[�V�����̃t���[����i�߂�
		anim_frame_[i] += 1.0f * anim_data_[i].anim_speed_;
		// 1���[�v���i�񂾂�0�Ƀ��Z�b�g
		if (anim_frame_[i] >= anim_total_frame_[i])
		{
			anim_frame_[i] = anim_total_frame_[i];
			//if (anim_data_[i].anim_name_ == before_anim_name_)
			//{
			//	anim_rate_[i] += 0.1f;
			//}
			//else
			//{
			//	anim_rate_[i] -= 0.1f;
			//}
		}
		// ���̃t���[���̃A�j���[�V�����ɂ���
		MV1SetAttachAnimTime(model_, anim_index_[i], anim_frame_[i]);
		MV1SetAttachAnimBlendRate(model_, anim_index_[i], anim_rate_[i]);
	}
}

void Animation::SetBeforeAnimation(std::string before_anim_name)
{
	before_anim_name_ = before_anim_name;
}
