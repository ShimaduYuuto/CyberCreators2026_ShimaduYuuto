//================================
//
//result.cpp�ɕK�v�Ȑ錾[result.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "scene.h"
#include "field.h"

//���U���g�N���X
class CResult : public CScene
{
public:

	//�萔
	static const D3DXVECTOR3 TIME_POS;	//���Ԃ̈ʒu

	//�����o�֐�
	CResult();						//�R���X�g���N�^
	~CResult() override;			//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	CField* GetField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }						//�t�B�[���h�̎擾

private:
	CField* m_pField;					//�t�B�[���h
};

#endif