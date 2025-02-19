//================================
//
//effect_death.cpp�ɕK�v�Ȑ錾[effect_death.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_DEATH_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_DEATH_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "effect_billboard.h"

//���S�G�t�F�N�g�N���X
class CEffect_Death : public CEffect_Billboard
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X
	static constexpr float RADIUS{ 100.0f };	//�T�C�Y���a

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 10 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 2 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 2 };	//�X�V���x
	static constexpr bool LOOP{ false };	//���[�v

	//�����o�֐�
	CEffect_Death();			//�R���X�g���N�^
	~CEffect_Death() override;	//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

	//����
	static CEffect_Death* Create(D3DXVECTOR3 pos);
};

#endif