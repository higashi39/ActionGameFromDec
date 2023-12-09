#pragma once

class SceneManager;

//---------------------------------------------------------------------------------
// �V�[�����N���X
//---------------------------------------------------------------------------------
class Scene
{
protected:
	SceneManager* manager;

public:
	Scene(SceneManager* p_manager) :manager(p_manager), font_handle_(0)
	{
		// �t�H���g�̓ǂݍ���
		font_handle_ = LoadFontDataToHandle("data/font/GN-KillGothic-U-KanaNA.dft");
	}
	~Scene() 
	{
		DeleteFontToHandle(font_handle_);
	};

	// ������
	void Init(){};

	// �X�V
	virtual void Update() {};
	// �`��
	virtual void Render() {};
	// �I��
	virtual void Exit() {};

protected:
	int font_handle_;
};

//---------------------------------------------------------------------------------
// �V�[���Ǘ��N���X
// memo : �e�V�[���̐؂�ւ��̍ۂɉ���Ɠ��I�m�ۂ�����ׂ̃N���X 
//---------------------------------------------------------------------------------
class SceneManager
{
public:
	// ���݂̃V�[���̃|�C���^
	Scene* scene;

	SceneManager() {};
	~SceneManager() { delete scene; };

	// �ǂݍ���
	void Init() { scene->Init(); };
	// �X�V
	void Update() { scene->Update(); };
	// �`��
	void Render() { scene->Render(); };
};