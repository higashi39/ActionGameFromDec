#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "Sword01.h"

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
Sword01::Sword01()
{
	object_model_ = new int;
	*object_model_ = MV1LoadModel("data/weapon/model/Sword1.mv1");

	object_scale_.set(0.02f, 0.02f, 0.02f);
}

void Sword01::Update(int* attached_model)
{
	// ���̃��f����t�������t���[��(�v���C���[�̉E��)���擾
	int attach_frame = MV1SearchFrame(*attached_model, "mixamorig6:RightHand");
	// ���f���̃t���[���̃��[�J�����W���烏�[���h���W�ɕϊ�����s����擾����
	MATRIX mat_frame = MV1GetFrameLocalWorldMatrix(*attached_model, attach_frame);

	// �t����t���[���ɍ��킹�邽�߂Ƀ��f���̒���
	// ���[���h���W�̍s��ϐ�
	MATRIX mat_world;
	mat_world = MGetScale(VGet(0.5f, 0.5f, 0.5f));									// �T�C�Y����(�g��k���s��)
	mat_world = MMult(mat_world, MGetRotX(DX_PI_F * 1.8f));						// ����(Y��)����
	mat_world = MMult(mat_world, MGetRotY(DX_PI_F * 1.0f));						// ����(Y��)����
	mat_world = MMult(mat_world, MGetRotZ(DX_PI_F * 1.5f));						// ����(Z��)����
	mat_world = MMult(mat_world, MGetTranslate(VGet(-10.0f, 10.0f, -10.0f)));	// �ʒu����

	mat_world = MMult(mat_world, mat_frame);
	MV1SetMatrix(*object_model_, mat_world);
}

void Sword01::Render()
{
	MV1SetPosition(*object_model_, VGet(object_position_.x, object_position_.y, object_position_.z));
	MV1SetScale(*object_model_, VGet(object_scale_.x, object_scale_.y, object_scale_.z));
	MV1SetRotationXYZ(*object_model_, VGet(object_rotate_.x, object_rotate_.y + TO_RADIAN(180.0f), object_rotate_.z));
	MV1DrawModel(*object_model_);
}