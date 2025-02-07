//================================
//
//effect_repel.cpp�ɕK�v�Ȑ錾[effect_repel.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_REPEL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_REPEL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectbillboard.h"
#include "animation.h"

//�e���G�t�F�N�g�N���X
class CEffect_Repel : public CObjectBillboard
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X
	static constexpr float RADIUS = 70.0f;	//�T�C�Y���a

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 10 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 1 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 1 };	//�X�V���x
	static constexpr bool LOOP{ false };	//���[�v


	//�����o�֐�
	CEffect_Repel();			//�R���X�g���N�^
	~CEffect_Repel() override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//����
	static CEffect_Repel* Create(D3DXVECTOR3 pos);

private:
	CAnimation m_Anim;	//�A�j���[�V�����p�̏��
};

#endif