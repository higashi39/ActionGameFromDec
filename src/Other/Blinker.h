#pragma once

//--------------------------------------------
// �_�ŏ����N���X
// �r�b�g���Z�œ_�ŏ���������
//--------------------------------------------

class Blinker
{
public:
	Blinker();
	~Blinker();

	// �_�ŏ���
	// mask : �_�ŗ�
	// �_�ŗʂɂ��_�ŊԊu�͈ȉ�URL�Q��
	// https://flat-leon.hatenablog.com/entry/blink_with_bit_op
	bool Blink(int mask);

private:
	int count = 0;			// �_�ł��Ǘ����邽�߂̖��t���[���J�E���^�[
};