#pragma once
#include "../Other/MakeString.h"
#include "../Other/Blinker.h"

//---------------------------------------------------------------------------------
// �^�C�g���V�[���N���X
//---------------------------------------------------------------------------------
class Title : public Scene
{
public:
	Title(SceneManager* p_manager);
	~Title();

	// �X�V
	void Update();
	// �`��
	void Render();

private:
	MakeString make_string;
	Blinker blinker;
};