//======================================
//
//	���b�V���`�����X��UI�̕`��[ui_gameguide.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "ui_gameguide.h"
#include "manager.h"
#include "game.h"

//�萔
const std::string CUi_GameGuide::TEXTURE_PATH[CONTROLLER_MAX][GUIDE_MAX] =
{
	{//�L�[�{�[�h�}�E�X
		{"data\\TEXTURE\\gameguide000.png"},
		{"data\\TEXTURE\\gameguide001.png"},
		{"data\\TEXTURE\\gameguide002.png"},
	},
	{//�W���C�p�b�h
		{"data\\TEXTURE\\gameguide003.png"},
		{"data\\TEXTURE\\gameguide006.png"},
		{"data\\TEXTURE\\gameguide005.png"},
	}
};

//============================
//�R���X�g���N�^
//============================
CUi_GameGuide::CUi_GameGuide(int nPriority) : CObject2D(nPriority),
	m_GuideType()
{
	
}

//============================
//�f�X�g���N�^
//============================
CUi_GameGuide::~CUi_GameGuide()
{

}

//============================
//������
//============================
HRESULT CUi_GameGuide::Init()
{
	CObject2D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CUi_GameGuide::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�X�V����
//============================
void CUi_GameGuide::Update()
{
	
}

//============================
//�`�揈��
//============================
void CUi_GameGuide::Draw()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���o���Ȃ�`�悵�Ȃ�
	if (pGame->GetDirectioning())
	{
		return;
	}

	//�e�N�X�`���`��
	CObject2D::Draw(TEXTURE_PATH[pGame->GetControllerUIType()][m_GuideType].c_str());
}

//============================
//��������
//============================
CUi_GameGuide* CUi_GameGuide::Create(D3DXVECTOR3 pos, GUIDE type, D3DXVECTOR3 size)
{
	//�|�C���^�p�̕ϐ�
	CUi_GameGuide* pObject;

	//�������̊m��
	pObject = new CUi_GameGuide();

	//������
	pObject->Init();									//������
	pObject->SetPos(pos);								//�ʒu
	pObject->SetSize(size);	//�T�C�Y
	pObject->m_GuideType = type;

	return pObject;
}