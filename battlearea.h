//================================
//
//battlearea.cpp�ɕK�v�Ȑ錾[battlearea.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREA_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "collision_wall.h"
#include "enemy.h"

//�o�g���G���A�̃N���X
class CBattleArea
{
public:

	//�o�g���X�e�[�W���
	struct BattleInfo
	{
		D3DXVECTOR3 StagePos;			//�X�e�[�W�ʒu
		float fRadius;					//�X�e�[�W�̔��a
		CCollision_Wall* pWall;			//�X�e�[�W�̕�
		std::list<CEnemy*> EnemyList;	//�G�̃��X�g
	};

	//�����o�֐�
	CBattleArea();		//�R���X�g���N�^
	~CBattleArea();		//�f�X�g���N�^
	HRESULT Init();		//������
	void Uninit();		//�I��

private:

	//�����o�ϐ�
	std::list<BattleInfo*> m_apArea;	//�G���A���Ǘ�
};

#endif