//================================
//
//effect_guard.cpp�ɕK�v�Ȑ錾[effect_guard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_GUARD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_GUARD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "effect_billboard.h"

//�K�[�h�G�t�F�N�g�N���X
class CEffect_Guard : public CEffect_Billboard
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X
	static constexpr float RADIUS{ 80.0f };	//�T�C�Y���a
	static constexpr int TIME_INTERPOLATION_RATIO{ 10 };	//�{�����Ԃ��鎞��

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 13 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 2 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 2 };	//�X�V���x
	static constexpr bool LOOP{ true };	//���[�v

	//�����o�֐�
	CEffect_Guard();			//�R���X�g���N�^
	~CEffect_Guard() override;	//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

	//�I���̐ݒ�
	void SetEnd() { m_bEnd = true; }

	//����
	static CEffect_Guard* Create(D3DXVECTOR3* pos);

private:

	//�֐�
	void UpdateSizeRatio();	//�T�C�Y�{���̍X�V

	//�ϐ�
	int m_nRatioInterpolationCount;	//�{���̕�ԃJ�E���g
	bool m_bEnd;					//�I�����邩
	D3DXVECTOR3* m_pTargetPos;		//�Ώۂ̈ʒu
	
};

#endif