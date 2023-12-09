#include "Main.h"
#include "Scene/SceneManager.h"
#include "Scene/Title.h"
#include "Scene/StageSelect.h"
#include "Scene/Game.h"

#include "Other/StatusData.h"

char KeyBuffer[256];
int KeyFrame[256];
int MouseLeftFrame;
int MouseRightFrame;

int NowMouseX;
int NowMouseY;
int BeforeMouseX;
int BeforeMouseY;

//---------------------------------------------------------------------------------
//	WinMain
//---------------------------------------------------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	int Time;

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetMainWindowText("MyBaseProject");
	SetBackgroundColor(100, 100, 100);

	SetDoubleStartValidFlag(TRUE);
	SetAlwaysRunFlag(TRUE);

	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	if (DxLib_Init() == -1)	return -1;

	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 0, 255);
	srand(GetNowCount() % RAND_MAX);

	for (int i = 0; i < 256; i++) {
		KeyFrame[i] = 0;
	}
	MouseLeftFrame = 0;
	MouseRightFrame = 0;

	SetCameraNearFar(0.1f, 3000.0f);
	SetupCamera_Perspective(TO_RADIAN(45.0f));

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// �V�[���Ǘ��V�X�e���𓮓I�m��
	SceneManager* manager;
	manager = new SceneManager();
	// �ŏ��̓^�C�g���V�[���𓮓I�m��
	manager->scene = new Game(manager);

	manager->Init();

	while (TRUE)
	{
		Time = GetNowCount();

		clsDx();
		ClearDrawScreen();

		GetHitKeyStateAll(KeyBuffer);

		for (int i = 0; i < 256; i++) {
			if (KeyBuffer[i])	KeyFrame[i]++;
			else				KeyFrame[i] = 0;
		}

		if (CheckMouseInput(MOUSE_INPUT_LEFT))	MouseLeftFrame++;
		else										MouseLeftFrame = 0;

		if (CheckMouseInput(MOUSE_INPUT_RIGHT))	MouseRightFrame++;
		else										MouseRightFrame = 0;

		NowMouseX = GetMouseX();
		NowMouseY = GetMouseY();

		// �Q�[�����[�v
		manager->Update();
		manager->Render();

		BeforeMouseX = NowMouseX;
		BeforeMouseY = NowMouseY;

		ScreenFlip();
		while (GetNowCount() - Time < 17) {}
		if (ProcessMessage())	break;
		if (CheckHitKey(KEY_INPUT_P))	break;
	}

	// �I��
	delete manager;

	DxLib_End();
	return 0;
}

//---------------------------------------------------------------------------------
//	�L�[�������ꂽ�u�Ԃ��擾����
//---------------------------------------------------------------------------------
bool PushHitKey(int key)
{
	if (KeyFrame[key] == 1) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�}�E�X��������Ă��邩���擾����
//---------------------------------------------------------------------------------
bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�}�E�X�������ꂽ�u�Ԃ��擾����
//---------------------------------------------------------------------------------
bool PushMouseInput(int button)
{
	if (button & MOUSE_INPUT_LEFT) {
		if (MouseLeftFrame == 1) {
			return true;
		}
	}
	if (button & MOUSE_INPUT_RIGHT) {
		if (MouseRightFrame == 1) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�}�E�X�̍��W���擾����
//---------------------------------------------------------------------------------
int GetMouseX()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_x;
}
int GetMouseY()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_y;
}
//---------------------------------------------------------------------------------
//	�}�E�X�̈ړ��ʂ��擾����
//---------------------------------------------------------------------------------
int GetMouseMoveX()
{
	return NowMouseX - BeforeMouseX;
}
int GetMouseMoveY()
{
	return NowMouseY - BeforeMouseY;
}
//---------------------------------------------------------------------------------
//	�x�����W�A���ɕϊ�����֐�
//---------------------------------------------------------------------------------
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}
//---------------------------------------------------------------------------------
//	���W�A����x�ɕϊ�����֐�
//---------------------------------------------------------------------------------
float TO_DEGREE(float radian)
{
	return radian * 180.0f / 3.14159265f;
}
