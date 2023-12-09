#pragma once
#include <string>
#include <vector>

//---------------------------------------------------------------------------------
//	�A�j���[�V�����֘A
//---------------------------------------------------------------------------------
class Animation
{
public:
	// �e�A�j���[�V������`�\����
	struct AnimationData
	{
		std::string anim_name_{};		// �A�j���[�V�������i�[�p
		std::string anim_path_{};		// �A�j���[�V�����p�X�i�[�p
		int anim_index_ = 0;			// �A�j���[�V�����ԍ�
		float start_frame_ = 0.0f;		// �t���[���J�n���_
		float anim_speed_ = 1.0f;		// �A�j���[�V�����̍Đ����x		
	};

public:
	Animation();
	~Animation() {};

	// �A�j���[�V�����J�n���_�������_���ݒ�
	float GetRandomStartFrame();

	// ���f���̃A�j���[�V���������ݒ�
	void FetchObjectModel(int model);

	// �A�j���[�V�����̐ݒ�
	// data : �A�j���[�V�����f�[�^
	void SettingAnimation(const std::vector<Animation::AnimationData> data);

	// �A�j���[�V�����̓ǂݍ���
	// data : 
	void LoadAnimation();

	// �I�u�W�F�N�g�̃��f���ɃA�j���[�V�����̃A�^�b�`
	// model : �I�u�W�F�N�g�̃��f���f�[�^
	// data  : �A�j���[�V�����f�[�^�̐擪�A�h���X
	void AttachAnimation();

	// �A�j���[�V�����̍Đ�
	// ���[�v�Đ�
	void PlayLoopAnimation(std::string anim_name);
	// �P�t���[���Đ�
	void PlayOnceAnimation(std::string anim_name);

	// ���ݍĐ����̃A�j���[�V�����̑O�ɍĐ����Ă����A�j���[�V������ێ�����
	void SetBeforeAnimation(std::string before_anim_name);

	std::string before_anim_name_;

protected:
	int model_;												// �A�^�b�`���郂�f��
	float start_frame_;										// �t���[���J�n���_
	std::vector < Animation::AnimationData > anim_data_;	// �e�A�j���[�V�����f�[�^

	std::vector<int> anim_index_;				// �A�j���[�V�����A�^�b�`�ԍ��i�[
	std::vector<int> anim_model_;				// �A�j���[�V�������f���i�[
	std::vector<float> anim_total_frame_;		// �A�j���[�V�����P���[�v���t���[����
	std::vector<float> anim_frame_;				// �A�j���[�V�����̌��݂̃t���[����
	std::vector<float> anim_rate_;				// �A�j���[�V�����̊���
};