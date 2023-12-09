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
	// 各キャラクターで読み込みたいアニメーションを格納する
	anim_data_ = data;

	// 受け取ったアニメーションの数分、各変数の要素を追加する
	// anim_index_, anim_model_にはエラー発生の値-1を入れておく
	// 他変数は0.0fを代入
	for (int i = 0; i < anim_data_.size(); ++i)
	{
		anim_index_.emplace_back(-1);
		anim_model_.emplace_back(-1);
		anim_total_frame_.emplace_back(0.0f);
		anim_frame_.emplace_back(0.0f);
		anim_rate_.emplace_back(0.0f);
	}

	before_anim_name_ = anim_data_[0].anim_name_;

	// アニメーション読み込みを行う
	LoadAnimation();
}

// アニメーションの読み込み
// model : モデルデータ
void Animation::LoadAnimation()
{
	//anim_data[ANIM_IDLE] = MV1LoadModel("data/player/animation/Idle.mv1");

	for (int i = 0; i < anim_data_.size(); i++)
	{
		// string型のanim_path_をconst char*型に変換する
		const char* char_path = anim_data_[i].anim_path_.c_str();
		// アニメーションを読み込む
		anim_model_[i] = MV1LoadModel(char_path);
	}
}

void Animation::AttachAnimation()
{
	for (int i = 0; i < anim_data_.size(); i++)
	{
		// アニメーションのアタッチ
		anim_index_[i] = MV1AttachAnim(model_, anim_data_[i].anim_index_, anim_model_[i], TRUE);
		// アタッチしたモデルが何フレームか(1ループ)
		anim_total_frame_[i] = MV1GetAttachAnimTotalTime(model_, anim_index_[i]);
		// 始めから(0)に初期化
		anim_frame_[i] = anim_data_[i].start_frame_;
		anim_rate_[i] = 0.0f;

		if (anim_data_[i].anim_name_ == "idle")
		{
			// 待機アニメーション割合を最大に
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

		// アニメーションのフレームを進める
		anim_frame_[i] += 1.0f * anim_data_[i].anim_speed_;
		// 1ループ分進んだら0にリセット
		if (anim_frame_[i] >= anim_total_frame_[i])
		{
			anim_frame_[i] = 0.0f;
		}
		// そのフレームのアニメーションにする
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
			// 現在再生中のアニメーションの前に再生していたアニメーションを保持する
			if (anim_rate_[i] > 0.0f)
			{
				SetBeforeAnimation(anim_data_[i].anim_name_);
			}
			anim_rate_[i] -= 1.0f;
			anim_frame_[i] = 0.0f;		// 使用していないアニメーションのフレームを0.0fにしておく
		}

		anim_rate_[i] = max(0.0f, min(anim_rate_[i], 1.0f));

		// アニメーションのフレームを進める
		anim_frame_[i] += 1.0f * anim_data_[i].anim_speed_;
		// 1ループ分進んだら0にリセット
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
		// そのフレームのアニメーションにする
		MV1SetAttachAnimTime(model_, anim_index_[i], anim_frame_[i]);
		MV1SetAttachAnimBlendRate(model_, anim_index_[i], anim_rate_[i]);
	}
}

void Animation::SetBeforeAnimation(std::string before_anim_name)
{
	before_anim_name_ = before_anim_name;
}
