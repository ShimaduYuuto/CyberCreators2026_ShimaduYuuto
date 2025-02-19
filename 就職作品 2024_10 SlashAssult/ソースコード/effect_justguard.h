//================================
//
//effect_justguard.cpp�ɕK�v�Ȑ錾[effect_justguard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_JUSTGUARD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_JUSTGUARD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "effect_billboard.h"

//�W���X�g�K�[�h�G�t�F�N�g�N���X
class CEffect_JustGuard : public CEffect_Billboard
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X
	static constexpr float RADIUS = 100.0f;	//�T�C�Y���a

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 10 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 2 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 1 };	//�X�V���x
	static constexpr bool LOOP{ false };	//���[�v


	//�����o�֐�
	CEffect_JustGuard();			//�R���X�g���N�^
	~CEffect_JustGuard() override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//����
	static CEffect_JustGuard* Create(D3DXVECTOR3 pos);
};

#endif