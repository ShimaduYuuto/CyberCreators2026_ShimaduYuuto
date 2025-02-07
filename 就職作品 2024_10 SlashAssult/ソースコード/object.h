//================================
//
//object.cpp�ɕK�v�Ȑ錾[object.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	//�萔
	static const int MAX_OBJECT = 256;	//�I�u�W�F�N�g�̍ő�
	static const int NUM_PRIORITY = 16;	//�v���C�I���e�B�̐�

	//�I�u�W�F�N�g�̃^�O
	typedef enum
	{
		TAG_NONE = 0,	//���ɖ���
		TAG_PAUSE,		//�|�[�Y���ɍX�V����I�u�W�F�N�g
		TAG_GAME,		//�Q�[�����ɍX�V����I�u�W�F�N�g
		TAG_MAX,		//�񋓂̍ő�
	}TAG;

	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		TYPE_NONE = 0,	//�^�C�v�Ȃ�
		TYPE_ENEMY,		//�G
		TYPE_PLAYER,	//�v���C���[
		TYPE_MAX,		//�ő�
	}TYPE;

	//�֐�
	CObject(int nPriority = 3);			//�R���X�g���N�^
	virtual ~CObject();					//�f�X�g���N�^
	virtual HRESULT Init() = 0;			//������
	virtual void Uninit() = 0;			//�I��
	virtual void Update() = 0;			//�X�V
	virtual void Draw() = 0;			//�`��
	static void ReleaseAll();			//�S�I�u�W�F�N�g�̊J��
	static void UpdateAll();			//�S�I�u�W�F�N�g�̍X�V
	static void DrawAll();				//�S�I�u�W�F�N�g�̕`��
	void SetDeath() { m_bDeath = true; }//�I�u�W�F�N�g�̎��S�t���O�𗧂Ă�
	bool GetDeath() { return m_bDeath; }//�I�u�W�F�N�g�̎��S����̎擾
	static CObject* GetTopObject(int priority);//�I�u�W�F�N�g�̐擪���擾
	static void ChangeUpdateObject(TAG tag);	//�^�O�ɉ������I�u�W�F�N�g�݂̂��X�V����

	//�p�����[�^�[�̐ݒ�Ǝ擾
	virtual void SetPos(D3DXVECTOR3 Pos) { m_Pos = Pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3& GetPos() { return m_Pos; }						//�ʒu�̎擾
	void SetType(TYPE type) {m_Type = type;}					//��ނ̐ݒ�
	TYPE GetType() { return m_Type; }							//��ނ̎擾
	CObject* GetNext() { return m_pNext; }						//���̃|�C���^�̎擾
	void SetUpdateJudge(bool judge) { m_bUpdateJudge = judge; }	//�X�V���邩��ݒ�
	bool GetUpdateJudge() { return m_bUpdateJudge; }			//�X�V���邩���擾
	void SetTag(TAG tag) { m_TagType = tag; }					//�^�O�̎��

//�w��̃N���X�̃I�u�W�F�N�g������
template<class T>
void Search(std::list<T*>& list)
{
	//�v���C�I���e�B�̐���������
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//�擪�擾

		//�ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//���̃|�C���^���擾

			//�L���X�g�����������烊�X�g�ɑ}��
			T* pListObj = dynamic_cast<T*>(pObj);
			if (pListObj != nullptr)
			{
				list.push_back(pListObj);
			}

			pObj = pNext;					//�|�C���^��i�߂�
		}
	}
}

protected:
	void Release();							//�������g�̊J��

private:
	static int m_nNumAll;					//�I�u�W�F�N�g�̑���
	static CObject* m_pTop[NUM_PRIORITY];	//�擪�̃I�u�W�F�N�g�|�C���^
	static CObject* m_pCur[NUM_PRIORITY];	//���݁i�Ō���j�̃|�C���^
	CObject* m_pPrev;						//�O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;						//���̃I�u�W�F�N�g�̃|�C���^
	bool m_bDeath;							//���S�t���O
	int m_nPriority;						//�`��D��x
	D3DXVECTOR3 m_Pos;						//�I�u�W�F�N�g�̈ʒu
	TYPE m_Type;							//�I�u�W�F�N�g�̎��
	bool m_bUpdateJudge;					//�I�u�W�F�N�g���X�V���邩
	TAG m_TagType;							//�^�O�̎��
};

#endif