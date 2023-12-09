#pragma once
#include <string>
#include <vector>

//---------------------------------------------------------------------------------
//	アニメーション関連
//---------------------------------------------------------------------------------
class Animation
{
public:
	// 各アニメーション定義構造体
	struct AnimationData
	{
		std::string anim_name_{};		// アニメーション名格納用
		std::string anim_path_{};		// アニメーションパス格納用
		int anim_index_ = 0;			// アニメーション番号
		float start_frame_ = 0.0f;		// フレーム開始時点
		float anim_speed_ = 1.0f;		// アニメーションの再生速度		
	};

public:
	Animation();
	~Animation() {};

	// アニメーション開始時点をランダム設定
	float GetRandomStartFrame();

	// モデルのアニメーション初期設定
	void FetchObjectModel(int model);

	// アニメーションの設定
	// data : アニメーションデータ
	void SettingAnimation(const std::vector<Animation::AnimationData> data);

	// アニメーションの読み込み
	// data : 
	void LoadAnimation();

	// オブジェクトのモデルにアニメーションのアタッチ
	// model : オブジェクトのモデルデータ
	// data  : アニメーションデータの先頭アドレス
	void AttachAnimation();

	// アニメーションの再生
	// ループ再生
	void PlayLoopAnimation(std::string anim_name);
	// １フレーム再生
	void PlayOnceAnimation(std::string anim_name);

	// 現在再生中のアニメーションの前に再生していたアニメーションを保持する
	void SetBeforeAnimation(std::string before_anim_name);

	std::string before_anim_name_;

protected:
	int model_;												// アタッチするモデル
	float start_frame_;										// フレーム開始時点
	std::vector < Animation::AnimationData > anim_data_;	// 各アニメーションデータ

	std::vector<int> anim_index_;				// アニメーションアタッチ番号格納
	std::vector<int> anim_model_;				// アニメーションモデル格納
	std::vector<float> anim_total_frame_;		// アニメーション１ループ何フレームか
	std::vector<float> anim_frame_;				// アニメーションの現在のフレーム数
	std::vector<float> anim_rate_;				// アニメーションの割合
};