//================================
//
//enemy002_alterego.cpp�ɕK�v�Ȑ錾[enemy002_alterego.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY002_ALTEREGO_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY002_ALTEREGO_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemy002.h"
#include "state_enemy002.h"

//�U���̃G�l�~�[�N���X
class CEnemy002_AlterEgo : public CEnemy002
{
public:

	//�萔
	static const std::string FILEPATH;		//�ǂݍ��ރt�@�C��
	static constexpr int LIFE{ 1 };			//�̗�

	//�����o�֐�
	CEnemy002_AlterEgo();				//�R���X�g���N�^
	~CEnemy002_AlterEgo() override;		//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��

	//����
	static CEnemy002_AlterEgo* Create(D3DXVECTOR3 pos);

	//��Ԃ̃��Z�b�g
	void StateReset() override;


private:

};

#endif