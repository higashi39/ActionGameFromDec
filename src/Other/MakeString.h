#pragma once
#include <string>

//--------------------------------------------
// ������`��N���X
// ��������w�肵���t�H���g/�T�C�Y/�ʒu�ɕ`�悷��
//--------------------------------------------

class MakeString
{
public:
	MakeString();
	~MakeString();

	// �����̕���␳����
	// str                : �`�悷�镶����
	// font_handle        : �t�H���g�n���h��
	// to_correction_size : �␳�������T�C�Y
	int CorrectionString(const char* str, int font_handle, double to_correction_size);

	//------------------------------------
	// �`��p�֐�
	// pos_x / pos_y      : X / Y���W
	// to_correction_size : �␳�������T�C�Y
	// str                : �`�悵����������
	// color_ r / g / b   : �`�悷�镶����̐F
	// font_handle        : �t�H���g�n���h��
	
	// ������`�悷��
	void DrawString(int pos_x, int pos_y, double to_correction_size, const char* str,
		int color_r, int color_g, int color_b, int font_handle);

	// ������X���W�̒����ɕ`�悷��
	void DrawStringCenterX(int pos_y, double to_correction_size, const char* str,
		int color_r, int color_g, int color_b, int font_handle);

	// ������Y���W�̒����ɕ`�悷��
	void DrawStringCenterY(int pos_x, double to_correction_size, const char* str,
		int color_r, int color_g, int color_b, int font_handle);
	//------------------------------------

private:
};