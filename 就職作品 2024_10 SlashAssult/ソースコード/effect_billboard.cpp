//======================================
//
//	�r���{�[�h�G�t�F�N�g�̏���[effect_billboard.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_billboard.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CEffect_Billboard::CEffect_Billboard() :
	m_Anim()	//�A�j���[�V�����N���X
{
	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Billboard::~CEffect_Billboard()
{

}

//============================
//�X�V����
//============================
void CEffect_Billboard::Update()
{
	//�e�N�X�`�����W�̍X�V
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	//�I��
	if (m_Anim.GetEnd())
	{
		Uninit();
	}
}