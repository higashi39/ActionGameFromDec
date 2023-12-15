#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define SCREEN_W	800
#define SCREEN_H	450

// デバッグ表示をするかどうか
#define SHOW_DEBUG 1

#include <windows.h>
#include <time.h>
#include <math.h>
#include <memory>

#pragma warning (disable : 4819)

#include <d3d9.h>
//#include <d3dx9.h>

#include <DxLib.h>
#include "EffekseerForDXLib.h"

bool PushHitKey(int key);
bool CheckMouseInput(int button = MOUSE_INPUT_LEFT | MOUSE_INPUT_RIGHT);
bool PushMouseInput(int button = MOUSE_INPUT_LEFT | MOUSE_INPUT_RIGHT);
int GetMouseX();
int GetMouseY();
int GetMouseMoveX();
int GetMouseMoveY();
float TO_RADIAN(float degree);
float TO_DEGREE(float radian);