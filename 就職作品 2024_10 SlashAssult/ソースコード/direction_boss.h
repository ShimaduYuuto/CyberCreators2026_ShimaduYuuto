//================================
//
//direction_boss.cpp�ɕK�v�Ȑ錾[direction_boss.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DIRECTION_BOSS_H_ //���̃}�N����`������Ă��Ȃ�������
#define _DIRECTION_BOSS_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "direction.h"

//���o�N���X
class CDirection_Boss : public CDirection
{
public:

	//���o
	static constexpr int END_TIME{ 300 };	//�I������

	//�J����
	static const D3DXVECTOR3 CAMERA_POSV;				//�J���������_�̈ʒu
	static const D3DXVECTOR3 CAMERA_POSR;				//�J�������_�̈ʒu
	static constexpr int START_SHAKE_FRAME{ 250 };		//�h�炵�n�߂鎞��
	static constexpr int SHAKE_FRAME{ 55 };				//�h�炷����
	static constexpr float SHAKE_MAGNITUDE{ 20.0f };	//�h�炷�l

	//�����o�֐�
	CDirection_Boss();	//�R���X�g���N�^
	~CDirection_Boss();	//�f�X�g���N�^

	//��{����
	HRESULT Init() override;	//������
	bool TimeUpdate() override;	//�X�V

private:

};

#endif