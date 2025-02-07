//================================
//
//explodingbarrel.cpp�ɕK�v�Ȑ錾[explodingbarrel.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLODINGBARREL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EXPLODINGBARREL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "gimmick.h"

//�����M�N���X
class CExplodingBarrel : public CGimmick
{
public:

	//�萔
	static const std::string FILEPATH;				//�t�@�C���p�X
	static constexpr float SIZE_RADIUS{ 40.0f };	//�T�C�Y�̔��a

	//�����o�֐�
	CExplodingBarrel(int nPriority = 3);	//�R���X�g���N�^
	~CExplodingBarrel() override;			//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��
	static CExplodingBarrel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�����M�̐���

	//�M�~�b�N�쓮�̏���
	void GimmickActivation() override;

private:

	void SetDetonation();	//�N���ݒ�

	bool m_bDetonation;	//�N��������

};

#endif