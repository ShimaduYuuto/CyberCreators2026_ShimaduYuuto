//======================================
//
//	���^�[�{�b�N�X�̏���[letterbox.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "letterbox.h"
#include "manager.h"

//============================
//���^�[�{�b�N�X�̃R���X�g���N�^
//============================
CLetterBox::CLetterBox() :
	m_pLetterBox(),
	m_nTime(0),
	m_nCurrentTime(0)
{
	//���^�[�{�b�N�X�̏�����
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		m_pLetterBox[i] = nullptr;
	}
}

//============================
//���^�[�{�b�N�X�̃f�X�g���N�^
//============================
CLetterBox::~CLetterBox()
{
	//���^�[�{�b�N�X�̏I������
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		//nullptr�`�F�b�N
		if (m_pLetterBox[i] == nullptr)
		{
			continue;
		}

		m_pLetterBox[i]->Uninit();
		m_pLetterBox[i] = nullptr;
	}
}

//============================
//���^�[�{�b�N�X�̏�����
//============================
HRESULT CLetterBox::Init()
{
	//���^�[�{�b�N�X�̏�����
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		//���^�[�{�b�N�X
		if (m_pLetterBox[i] != nullptr)
		{
			continue;
		}

		m_pLetterBox[i] = CObject2D::Create();													//����
		m_pLetterBox[i]->SetPos({(float)SCREEN_WIDTH * 0.5f, i * (float)SCREEN_HEIGHT, 0.0f});	//�ʒu
		m_pLetterBox[i]->SetSize({ (float)SCREEN_WIDTH, 0.0f, 0.0f });							//�T�C�Y
		m_pLetterBox[i]->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });									//�F
	}

	return S_OK;
}

//============================
//���^�[�{�b�N�X�̏I������
//============================
void CLetterBox::Uninit()
{
	//���^�[�{�b�N�X�̏I������
	for (int i = 0; i < NUM_LETTERBOX; i++)
	{
		//nullptr�`�F�b�N
		if (m_pLetterBox[i] == nullptr)
		{
			continue;
		}

		m_pLetterBox[i]->Uninit();
	}

	//���^�[�{�b�N�X�N���X(���g)�̔j��
	CObject::Uninit();
}

//============================
//���^�[�{�b�N�X�̍X�V����
//============================
void CLetterBox::Update()
{
	//���Ԃ̃J�E���g
	m_nCurrentTime++;

	//�ŏ��̈�莞�Ԃ����T�C�Y�����Z
	if (m_nCurrentTime <= TIME_INTERPOLATION)
	{
		//���^�[�̐���������
		for (int i = 0; i < NUM_LETTERBOX; i++)
		{
			//���������Z���Đݒ�
			D3DXVECTOR3 Size = m_pLetterBox[i]->GetSize();
			Size.y += HEIGHT_LETTERBOX / TIME_INTERPOLATION;

			//�T�C�Y�̕␳
			if (Size.y > HEIGHT_LETTERBOX)
			{
				Size.y = HEIGHT_LETTERBOX;
			}

			//�T�C�Y�̐ݒ�
			m_pLetterBox[i]->SetSize(Size);
		}
	}

	//�I���O�̈�莞�Ԃ����T�C�Y�����Z
	else if (m_nCurrentTime >= m_nTime - TIME_INTERPOLATION)
	{
		//���^�[�̐���������
		for (int i = 0; i < NUM_LETTERBOX; i++)
		{
			//���������Z���Đݒ�
			D3DXVECTOR3 Size = m_pLetterBox[i]->GetSize();
			Size.y -= HEIGHT_LETTERBOX / TIME_INTERPOLATION;

			//�T�C�Y�̕␳
			if (Size.y < 0.0f)
			{
				Size.y = 0.0f;
			}

			//�T�C�Y�̐ݒ�
			m_pLetterBox[i]->SetSize(Size);
		}
	}

	//�������}���������
	if (m_nCurrentTime > m_nTime)
	{
		Uninit();
	}
}

//============================
//���^�[�{�b�N�X�̕`�揈��
//============================
void CLetterBox::Draw()
{

}

//============================
//���^�[�{�b�N�X�̐�������
//============================
CLetterBox* CLetterBox::Create(int time)
{
	//���^�[�{�b�N�X�̐���
	CLetterBox* pLetterBox = nullptr;
	pLetterBox = new CLetterBox;

	//������
	pLetterBox->Init();

	//����
	pLetterBox->m_nTime = time + static_cast<float>((TIME_INTERPOLATION * 2.0f));	//��Ԃ̎��Ԃ�ǉ�

	return nullptr;
}