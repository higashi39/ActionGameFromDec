#pragma once
#include <string>

//--------------------------------------------
// 文字列描画クラス
// 文字列を指定したフォント/サイズ/位置に描画する
//--------------------------------------------

class MakeString
{
public:
	MakeString();
	~MakeString();

	// 文字の幅を補正する
	// str                : 描画する文字列
	// font_handle        : フォントハンドル
	// to_correction_size : 補正したいサイズ
	int CorrectionString(const char* str, int font_handle, double to_correction_size);

	//------------------------------------
	// 描画用関数
	// pos_x / pos_y      : X / Y座標
	// to_correction_size : 補正したいサイズ
	// str                : 描画したい文字列
	// color_ r / g / b   : 描画する文字列の色
	// font_handle        : フォントハンドル
	
	// 文字を描画する
	void DrawString(int pos_x, int pos_y, double to_correction_size, const char* str,
		int color_r, int color_g, int color_b, int font_handle);

	// 文字をX座標の中央に描画する
	void DrawStringCenterX(int pos_y, double to_correction_size, const char* str,
		int color_r, int color_g, int color_b, int font_handle);

	// 文字をY座標の中央に描画する
	void DrawStringCenterY(int pos_x, double to_correction_size, const char* str,
		int color_r, int color_g, int color_b, int font_handle);
	//------------------------------------

private:
};