#include "../Main.h"
#include "Blinker.h"

Blinker::Blinker()
{
	count = 0;
}

Blinker::~Blinker()
{

}

bool Blinker::Blink(int mask)
{
	// ���t���[���J�E���g����
	++count;
	// �l���傫���Ȃ肷���Ȃ��悤�Ɉ��̒l�܂ő傫���Ȃ����烊�Z�b�g����
	if (count >= 180)
	{
		count = 0;
	}

	// �_�ł̍ۂ̕`�������
	if (count & mask)
	{
		return true;
	}

	return false;
}