#pragma once

//--------------------------------------------
// 点滅処理クラス
// ビット演算で点滅処理をする
//--------------------------------------------

class Blinker
{
public:
	Blinker();
	~Blinker();

	// 点滅処理
	// mask : 点滅量
	// 点滅量による点滅間隔は以下URL参照
	// https://flat-leon.hatenablog.com/entry/blink_with_bit_op
	bool Blink(int mask);

private:
	int count = 0;			// 点滅を管理するための毎フレームカウンター
};