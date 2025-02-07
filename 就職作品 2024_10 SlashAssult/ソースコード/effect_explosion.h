//================================
//
//effect_explosion.cpp�ɕK�v�Ȑ錾[effect_explosion.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_EXPLOSION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_EXPLOSION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectdome.h"

//�����G�t�F�N�g�N���X
class CEffect_Explosion : public CObjectDome
{
public:

	//�萔
	static const std::string FILEPATH;

	//�����o�֐�
	CEffect_Explosion(int nPriority = 3);				//�R���X�g���N�^
	~CEffect_Explosion() override;						//�f�X�g���N�^
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw() override;								//�`��
	static CEffect_Explosion* Create(D3DXVECTOR3 pos);	//�����̐���

private:
	float m_fSizeRate;			//�����̃T�C�Y�{��

};

#endif