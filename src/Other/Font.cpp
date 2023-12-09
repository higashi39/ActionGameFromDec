#include "../Main.h"
#include "../Scene/Game.h"

#include "Font.h"

Font::Font() : font_handle_(0)
{

}

Font::~Font()
{
	DeleteFontToHandle(font_handle_);
}

void Font::LoadFont()
{
	font_handle_ = LoadFontDataToHandle("data/font/851letrogo_font.dft");
}

int Font::GetterFontHandle()
{
	return font_handle_;
}