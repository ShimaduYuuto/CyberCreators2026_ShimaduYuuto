//================================
//
//direction_boss_destroy.cpp�ɕK�v�Ȑ錾[direction_boss_destroy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DIRECTION_BOSS_DESTROY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _DIRECTION_BOSS_DESTROY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "direction.h"
#include "object2D.h"

//���o�N���X
class CDirection_Boss_Destroy : public CDirection
{
public:

	//���o
	static constexpr int END_TIME{ 700 };	//�I������

	//�J����
	static const D3DXVECTOR3 CAMERA_POSV;				//�J���������_�̈ʒu
	static const D3DXVECTOR3 CAMERA_POSR;				//�J�������_�̈ʒu
	static constexpr int START_SHAKE_FRAME{ 250 };		//�h�炵�n�߂鎞��
	static constexpr int SHAKE_FRAME{ END_TIME - START_SHAKE_FRAME };	//�h�炷����
	static constexpr float SHAKE_MAGNITUDE{ 40.0f };	//�h�炷�l
	static constexpr float PARTICLE_SPEED{ 10.0f };		//�p�[�e�B�N���̑��x
	static constexpr float PARTICLE_SIZE{ 100.0f };		//�p�[�e�B�N���T�C�Y

	//�Q�[�����I��
	static constexpr int TIME_ENDGAME_FRAME{ 660 };		//�Q�[�����I���鎞��

	//���o�t�F�[�h
	static constexpr int TIME_ENDFADE_FRAME{ START_SHAKE_FRAME + 200 };		//�t�F�[�h�A�E�g���I���鎞��

	//�����o�֐�
	CDirection_Boss_Destroy();	//�R���X�g���N�^
	~CDirection_Boss_Destroy();	//�f�X�g���N�^

	//��{����
	HRESULT Init() override;	//������
	bool TimeUpdate() override;	//�X�V

private:

	//�֐�
	void CreateParticle();	//�p�[�e�B�N���̐���

	CObject2D* m_pDirectionFade;	//���o�p�̃t�F�[�h
	float m_fFadeAlpfa;				//�t�F�[�h�̃��l
};

#endif