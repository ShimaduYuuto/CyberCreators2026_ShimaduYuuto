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

	static constexpr float RADIUS_ENTEREDAREA{ 400.0f };	//�G���A�ɓ������������m���锼�a

	//�����o�֐�
	CBattleArea();		//�R���X�g���N�^
	virtual ~CBattleArea();		//�f�X�g���N�^
	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V

	//����
	static CBattleArea* Create(D3DXVECTOR3 pos, const char* path);

	//�X�e�[�W�̕�
	CCollision_Wall* GetWall() { return m_pWall; }	//�擾

	//�I������
	bool GetEnd() { return m_bEnd; }	//�擾

	//���������鏈��
	void SpawnLoad(const char* path);			//�X�|�[�����̓ǂݍ���
	void SpawnEnemy(std::ifstream& File);		//�G�l�~�[
	void SpawnGimmick(std::ifstream& File);		//�M�~�b�N
	void InfoLoad(std::ifstream& File, const char* end, D3DXVECTOR3& pos, int& type);//�I���̕�����܂œǂݎ��

	//�ʒu
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	//�ݒ�
	D3DXVECTOR3& GetPos() { return m_Pos; }			//�擾

	//�G�̐�
	void AddEnemyNum() { m_nEnemyNum++; }//�G�̐��𑝂₷
	void DecrementEnemyNum() { if (m_nEnemyNum > 0) { m_nEnemyNum--; } }//�G�̐������炷

	//�t�@�C���p�X�̐ݒ�
	void SetPath(const char* path) { m_Path = path; }

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_Pos;				//�ʒu
	float m_fRadius;				//�X�e�[�W�̔��a
	CCollision_Wall* m_pWall;		//�X�e�[�W�̕�
	std::list<CEnemy*> m_EnemyList;	//�G�̃��X�g
	bool m_bEnteredArea;			//�G���A�ɓ�������
	int m_nEnemyNum;				//�G�̐�
	bool m_bEnd;					//�I��������
	std::string m_Path;				//�ǂݍ��ރp�X
};

#endif