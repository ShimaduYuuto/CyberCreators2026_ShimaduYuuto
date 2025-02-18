//======================================
//
//	�̗̓Q�[�W�̏���[lifegauge.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "lifegauge.h"
#include "manager.h"
#include "game.h"

const std::string CLifeGauge::TEXTUREPATH = "data\\TEXTURE\\LifeGauge.png";

//============================
//�Q�[�W�̃R���X�g���N�^
//============================
CLifeGauge::CLifeGauge(int nPriority) : CGauge(nPriority)
{

}

//============================
//�Q�[�W�̃f�X�g���N�^
//============================
CLifeGauge::~CLifeGauge()
{

}

//============================
//�Q�[�W�̕`��
//============================
void CLifeGauge::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTUREPATH.c_str());
}

//============================
//�Q�[�W�̃N���G�C�g
//============================
CLifeGauge* CLifeGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max)
{
	//�|�C���^�p�̕ϐ�
	CLifeGauge* pLifeGauge;

	//�������̊m��
	pLifeGauge = new CLifeGauge;

	//������
	pLifeGauge->Init();
	pLifeGauge->SetPos(pos);	//�ʒu
	pLifeGauge->SetSize(size);	//�T�C�Y
	pLifeGauge->SetMaxGauge(max);	//�Q�[�W�̍ő�l��ݒ�
	pLifeGauge->SetNowGauge(max);	//�Q�[�W�̌��ݒl��ݒ�

	return pLifeGauge;
}