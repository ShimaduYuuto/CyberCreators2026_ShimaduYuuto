//================================
//
//character.cpp�ɕK�v�Ȑ錾[character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CHARACTER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CHARACTER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "object.h"
#include "modelparts.h"
#include "shadow.h"

//�L�����N�^�[�N���X
class CCharacter : public CObject
{
public:

	//�萔
	static constexpr float ROTATE_SPEED{0.2f};		//��]�̑��x
	static constexpr int DAMAGE_TIME{5};			//�_���[�W��Ԃ̎���
	static constexpr int INTERPOLATION_FRAME{6};	//���[�V�����̕�ԃJ�E���g
	static constexpr float GRAVITY{0.6f};			//�d�͂̋���
	static constexpr float SIZE_RADIUS{30.0f};		//�T�C�Y�̔��a
	static constexpr int MAX_MODEL{ 16 };			//�ǂݍ��ރ��f���p�[�c�̍ő吔
	static constexpr int MAX_STRING{ 256 };			//�ǂݍ��ޕ����̍ő吔

	//�L�����N�^�[�̎��
	typedef enum
	{
		CHARACTER_TYPE_NONE = 0,//����
		CHARACTER_TYPE_PLAYER,	//�v���C���[
		CHARACTER_TYPE_ENEMY,	//�G
		CHARACTER_TYPE_MAX,		//�񋓂̍ő�
	}CHARACTER_TYPE;

	//�L�[�̍\����
	struct Key
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
		Key() : pos(), rot()
		{

		}
	};

	//�L�[�Z�b�g�̍\����
	struct KeySet
	{
		int nFrame;				//���[�V�����̃t���[����
		std::vector<Key> Key;	//�e�L�[�̏��
		KeySet() : nFrame(0), Key()
		{

		}
	};
	
	//���[�V�������̍\����
	struct Motion
	{
		bool bLoop;					//���[�V���������[�v���邩
		int nNumKey;				//�L�[�̎��
		std::vector<KeySet> KeySet;	//�e�L�[�̐ݒ�
		Motion() : bLoop(false), nNumKey(0), KeySet()
		{

		}
	};

	//�p�[�c���̍\����
	struct PartsInfo
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
		PartsInfo() : pos(), rot()
		{

		}
	};

	//�����o�֐�
	CCharacter(int nPriority = 3);						//�R���X�g���N�^
	virtual ~CCharacter() override;						//�f�X�g���N�^
	virtual HRESULT Init() override;					//������
	virtual void Uninit() override;						//�I��
	virtual void Update() override;						//�X�V
	void Draw() override;								//�`��

	virtual void UpdatePos();							//�ʒu�̍X�V
	void UpdateRot();									//�����̍X�V
	virtual D3DXVECTOR3 GravityMove(D3DXVECTOR3 move);	//�d�͂̏���
	
	//�p�����[�^�֘A�̊֐�
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }								//�����̐ݒ�
	D3DXVECTOR3& GetRot() {return m_Rot;}										//�����̎擾

	//�ړ���
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }							//�ݒ�
	void AddMove(D3DXVECTOR3 move) { m_Move += move; }							//�ǉ�
	D3DXVECTOR3& GetMove() { return m_Move; }									//�擾

	//�ړI�̌���
	void SetGoalRot(D3DXVECTOR3 goalrot);										//�ݒ�
	D3DXVECTOR3& GetGoalRot() { return m_GoalRot; }								//�擾

	//�O��̈ʒu
	void SetOldPos(D3DXVECTOR3 oldpos) { m_OldPos = oldpos; }					//�ݒ�
	D3DXVECTOR3& GetOldPos() { return m_OldPos; }								//�擾

	//�e
	CShadow*& GetShadow() { return m_pShadow; }	//�擾

	//���[�V����
	void SetMotionInfo(const char* motionfilename);								//���[�V�������̐ݒ�
	void SetMotion(int motion);													//���[�V�����̐ݒ�
	int GetMotionState() { return m_MotionState; }								//���[�V������Ԃ̎擾
	void UpdateMotion();														//���[�V�����̍X�V������֐�
	CModelparts* GetModelParts(int index) { return m_apModel[index]; }			//���f���p�[�c�̎擾
	std::vector<CModelparts*> GetModelPartsVector() { return m_apModel; }		//���f���p�[�c�̃x�N�^�[���擾

	//�ʒu�̐ݒ�
	void SetPos(D3DXVECTOR3 pos) override
	{
		CObject::SetPos(pos);
		m_OldPos = pos;
	}

private:

	//�����o�֐�
	float AddRot(float addrot);										//�����̉��Z������֐�
	D3DXVECTOR3 RotCalculation(D3DXVECTOR3 goal, D3DXVECTOR3 current);	//���[�V�����̌����̒l���Z�o

	//�����o�ϐ�
	D3DXVECTOR3 m_OldPos;					//�O��̈ʒu
	D3DXVECTOR3 m_Move;						//�ړ���
	D3DXVECTOR3 m_Rot;						//����
	D3DXVECTOR3 m_GoalRot;					//�ړI�̌���
	D3DXMATRIX m_mtxWorld;					//�}�g���b�N�X
	CShadow* m_pShadow;						//�e�̃|�C���^

	//���[�V�����̕ϐ�
	int m_MotionState;						//���݂̃��[�V�����̏��
	int m_nMotionCount;						//���[�V�����L�[�̃J�E���g
	float m_fFrameCount;					//���[�V�����t���[���̃J�E���g
	bool m_bChangeMotion;					//���[�V������؂�ւ��邩�̕ϐ�
	float m_fInterpolationCount;			//���`��Ԃ̃J�E���g
	bool m_bInterpolationEnd;				//���`�ۊǂ��I����Ă��邩
	std::vector<PartsInfo> m_InterpolationInfo;		//�p�[�c�̏��
	std::vector<Motion> m_Motion;			//���[�V�������
	std::vector<CModelparts*> m_apModel;	//�v���C���[�̃p�[�c[�p�[�c��]
	std::vector<PartsInfo> m_PartsInfo;		//�p�[�c�̏��
};

#endif