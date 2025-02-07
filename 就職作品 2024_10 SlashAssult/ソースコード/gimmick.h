//================================
//
//gimmick.cpp�ɕK�v�Ȑ錾[gimmick.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GIMMICK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GIMMICK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectX.h"
#include "collision.h"

//�M�~�b�N�N���X
class CGimmick : public CObjectX
{
public:

	//�M�~�b�N�̎��
	enum TYPE
	{
		TYPE_EXPLODINGBARREL = 0,
		TYPE_MAX
	};

	//�萔
	static const std::string FILEPATH;
	static constexpr float COLLISION_RADIUS{ 20.0f };	//�R���W�����̔��a
	static const D3DXVECTOR3 COLLISION_POS;				//�R���W�����̈ʒu

	//�����o�֐�
	CGimmick(int nPriority = 3);	//�R���X�g���N�^
	~CGimmick() override;			//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	static CGimmick* Create(D3DXVECTOR3 pos, TYPE type);

	//�R���W�����C���X�^���X
	void SetCollision(CCollision* colision) { m_Collision = colision; }
	CCollision* GetCollision() { return m_Collision; }

	//�q�b�g���̏���
	virtual void GimmickActivation() {}

private:

	//�����o�ϐ�
	CCollision* m_Collision;
};

#endif