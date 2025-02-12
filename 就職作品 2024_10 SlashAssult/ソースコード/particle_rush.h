//================================
//
//particle_rush.cpp�ɕK�v�Ȑ錾[particle_rush.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_RUSH_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE_RUSH_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "particle.h"

//���b�V���p�[�e�B�N���N���X
class CParticle_Rush : public CParticle
{
public:

	//�萔
	static constexpr int MAX_LIFE{ 30 };		//�̗͂̍ő�l
	static const D3DXVECTOR3 SIZE;				//�T�C�Y
	static const std::string TEXTUREPATH;		//�e�N�X�`���p�X
	static const D3DXCOLOR COLOR;				//�F
	static constexpr float NORMAL_SIZE{ 5.0f };	//�ʏ�̃T�C�Y

	//�����o�֐�
	CParticle_Rush(int nPriority = 3);					//�R���X�g���N�^
	~CParticle_Rush() override;							//�f�X�g���N�^
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw() override;								//�`��
	static CParticle_Rush* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//Particle�̐���

};

#endif