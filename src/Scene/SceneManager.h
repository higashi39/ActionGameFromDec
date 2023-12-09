#pragma once

class SceneManager;

//---------------------------------------------------------------------------------
// シーン基底クラス
//---------------------------------------------------------------------------------
class Scene
{
protected:
	SceneManager* manager;

public:
	Scene(SceneManager* p_manager) :manager(p_manager), font_handle_(0)
	{
		// フォントの読み込み
		font_handle_ = LoadFontDataToHandle("data/font/GN-KillGothic-U-KanaNA.dft");
	}
	~Scene() 
	{
		DeleteFontToHandle(font_handle_);
	};

	// 初期化
	void Init(){};

	// 更新
	virtual void Update() {};
	// 描画
	virtual void Render() {};
	// 終了
	virtual void Exit() {};

protected:
	int font_handle_;
};

//---------------------------------------------------------------------------------
// シーン管理クラス
// memo : 各シーンの切り替えの際に解放と動的確保をする為のクラス 
//---------------------------------------------------------------------------------
class SceneManager
{
public:
	// 現在のシーンのポインタ
	Scene* scene;

	SceneManager() {};
	~SceneManager() { delete scene; };

	// 読み込み
	void Init() { scene->Init(); };
	// 更新
	void Update() { scene->Update(); };
	// 描画
	void Render() { scene->Render(); };
};