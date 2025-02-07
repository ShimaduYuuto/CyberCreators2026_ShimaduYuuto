//================================
//
//explosion.cpp�ɕK�v�Ȑ錾[explosion.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLOSION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EXPLOSION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectdome.h"
#include "collision.h"

//�����N���X
class CExplosion : public CObjectDome
{
public:

	//�萔
	static const std::string FILEPATH;					//�t�@�C���p�X
	static constexpr float SIZE_RADIUS{ 100.0f };		//�T�C�Y�̔��a
	static constexpr float LIFE{ 40.0 };				//��������

	static constexpr float SIZE_STRAT_RATE{ 0.3f };		//�ŏ��̃T�C�Y�{��
	static constexpr float INCREASE_RATE_LIFE{ 20.0f };	//�T�C�Y�{�����������鐶������
	static constexpr float INCREASE_VALUE{ 0.1f };		//��������l
	static constexpr float DECREASE_RATE_LIFE{ 10.0f };	//�T�C�Y�{�����������鐶������
	static constexpr float DECREASE_VALUE{ 0.1f };		//��������l
	static constexpr float MAX_SIZE_VALUE{ 1.0f };		//�ő�T�C�Y�{��
	static constexpr float MIN_SIZE_VALUE{ 0.0f };		//�ŏ��T�C�Y�{��

	//�����o�֐�
	CExplosion(int nPriority = 3);			//�R���X�g���N�^
	~CExplosion() override;					//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��
	static CExplosion* Create(D3DXVECTOR3 pos);		//�����̐���

private:
	float m_fLife;				//����
	float m_fSizeRate;			//�����̃T�C�Y�{��
	CCollision* m_pCollision;	//�����蔻��

};

#endif