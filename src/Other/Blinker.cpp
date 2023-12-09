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
	// 毎フレームカウントする
	++count;
	// 値が大きくなりすぎないように一定の値まで大きくなったらリセットする
	if (count >= 180)
	{
		count = 0;
	}

	// 点滅の際の描画を処理
	if (count & mask)
	{
		return true;
	}

	return false;
}