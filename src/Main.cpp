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
	//SetBackgroundColor(100, 100, 100);
	SetBackgroundColor(135, 206, 250);

	SetDoubleStartValidFlag(TRUE);
	SetAlwaysRunFlag(TRUE);

	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)	return -1;

	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

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

	// シーン管理システムを動的確保
	SceneManager* manager;
	manager = new SceneManager();
	// 最初はタイトルシーンを動的確保
	manager->scene = new Game(manager);

	manager->Init();

	// エフェクトリソースを読み込む。
	// 読み込む時に大きさを指定する。
	int effectResourceHandle = LoadEffekseerEffect("Laser01.efkefc", 1.0f);
	// エフェクトを再生する。
	int playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
	// 再生中のエフェクトを移動する。
	float position_x = 0.0f;
	float position_y = 0.0f;
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position_x, position_y, 0);
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, TO_RADIAN(90), 0);

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

		// ゲームループ
		manager->Update();
		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer3D();

		manager->Render();
		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer3D();

		BeforeMouseX = NowMouseX;
		BeforeMouseY = NowMouseY;

		ScreenFlip();
		while (GetNowCount() - Time < 17) {}
		if (ProcessMessage())	break;
		if (CheckHitKey(KEY_INPUT_P))	break;
	}

	// 終了
	delete manager;

	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(effectResourceHandle);

	// Effekseerを終了する。
	Effkseer_End();

	DxLib_End();
	return 0;
}

//---------------------------------------------------------------------------------
//	キーが押された瞬間を取得する
//---------------------------------------------------------------------------------
bool PushHitKey(int key)
{
	if (KeyFrame[key] == 1) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスが押されているかを取得する
//---------------------------------------------------------------------------------
bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスが押された瞬間を取得する
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
//	マウスの座標を取得する
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
//	マウスの移動量を取得する
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
//	度をラジアンに変換する関数
//---------------------------------------------------------------------------------
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}
//---------------------------------------------------------------------------------
//	ラジアンを度に変換する関数
//---------------------------------------------------------------------------------
float TO_DEGREE(float radian)
{
	return radian * 180.0f / 3.14159265f;
}
