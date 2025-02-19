//================================
//
//effect_death_boss.cpp�ɕK�v�Ȑ錾[effect_death_boss.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_DEATH_BOSS_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_DEATH_BOSS_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "effect_billboard.h"

//���S�G�t�F�N�g�N���X
class CEffect_Death_Boss : public CEffect_Billboard
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X
	static constexpr float RADIUS{ 200.0f };	//�T�C�Y���a

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 10 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 7 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 3 };	//�X�V���x
	static constexpr bool LOOP{ false };	//���[�v

	//�����o�֐�
	CEffect_Death_Boss();			//�R���X�g���N�^
	~CEffect_Death_Boss() override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//����
	static CEffect_Death_Boss* Create(D3DXVECTOR3* pos);

private:

	//�ϐ�
	D3DXVECTOR3* m_TargetPos;		//�Ώۂ̈ʒu
};

#endif