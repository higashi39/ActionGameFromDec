#include "../Main.h"
#include "MakeString.h"

MakeString::MakeString()
{

}

MakeString::~MakeString()
{

}

int MakeString::CorrectionString(const char* str, int font_handle, double to_correction_size)
{
	int width = GetDrawStringWidthToHandle(str, -1, font_handle);

	return (int)(width * to_correction_size);
}

void MakeString::DrawString(int pos_x, int pos_y, double to_correction_size, const char* str,
	int color_r, int color_g, int color_b, int font_handle)
{
	DrawExtendStringToHandle(pos_x, pos_y,
		to_correction_size,
		to_correction_size,
		str,
		GetColor(color_r, color_g, color_b), font_handle);
}

// •¶Žš‚ð’†‰›‚É•`‰æ‚·‚é
void MakeString::DrawStringCenterX(int pos_y, double to_correction_size, const char* str,
	int color_r, int color_g, int color_b, int font_handle)
{
	DrawExtendStringToHandle((SCREEN_W - CorrectionString(str, font_handle, to_correction_size)) / 2, pos_y,
		to_correction_size,
		to_correction_size,
		str,
		GetColor(color_r, color_g, color_b), font_handle);
}

// •¶Žš‚ð’†‰›‚É•`‰æ‚·‚é
void MakeString::DrawStringCenterY(int pos_x, double to_correction_size, const char* str,
	int color_r, int color_g, int color_b, int font_handle)
{
	DrawExtendStringToHandle(pos_x, (SCREEN_H - CorrectionString(str, font_handle, to_correction_size)) / 2,
		to_correction_size,
		to_correction_size,
		str,
		GetColor(color_r, color_g, color_b), font_handle);
}