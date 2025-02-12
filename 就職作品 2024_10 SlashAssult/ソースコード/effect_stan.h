//================================
//
//effect_stan.cpp�ɕK�v�Ȑ錾[effect_stan.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_STAN_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_STAN_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectcylinder.h"

//�X�^���G�t�F�N�g�N���X
class CEffect_Stan : public CObjectCylinder
{
public:

	//�萔
	static const std::string TEXTURE_PATH;			//�e�N�X�`���p�X
	static constexpr float RADIUS{ 20.0f };			//�T�C�Y���a
	static constexpr float HEIGHT{ 30.0f };			//����
	static constexpr float ROTATE_SPEED{ 0.05f };	//��]���x

	//�����o�֐�
	CEffect_Stan();			//�R���X�g���N�^
	~CEffect_Stan() override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//����
	static CEffect_Stan* Create(D3DXVECTOR3 pos, D3DXMATRIX* mtx);

private:

	//�֐�
	void MtxCalculation() override;		//�}�g���b�N�X�̌v�Z
	
	//�ϐ�
	D3DXMATRIX* m_pmtxParent;
};

#endif