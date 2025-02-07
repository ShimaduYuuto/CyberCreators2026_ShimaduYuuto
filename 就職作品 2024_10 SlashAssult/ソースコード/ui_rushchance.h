//================================
//
//ui_rushchance.cpp�ɕK�v�Ȑ錾[ui_rushchance.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _UI_RUSHCHANCE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _UI_RUSHCHANCE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectbillboard.h"
#include "animation.h"

//���b�V���`�����X��UI�N���X
class CUi_RushChance : public CObjectBillboard
{
public:

	//�萔
	static const std::string TEXTURE_PATH;		//�e�N�X�`���p�X
	static constexpr float RADIUS{ 70.0f };	//�T�C�Y���a

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 2 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 1 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 20 };	//�X�V���x
	static constexpr bool LOOP{ true };	//���[�v


	//�����o�֐�
	CUi_RushChance(int nPriority = 4);			//�R���X�g���N�^
	~CUi_RushChance() override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//����
	static CUi_RushChance* Create(D3DXVECTOR3* pos);

private:
	CAnimation m_Anim;			//�A�j���[�V�����p�̏��
	D3DXVECTOR3* m_TargetPos;	//�^�[�Q�b�g�̈ʒu
};

#endif