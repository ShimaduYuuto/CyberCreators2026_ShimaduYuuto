//================================
//
//game.cpp�ɕK�v�Ȑ錾[game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAME_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "scene.h"
#include "player.h"
#include "field.h"
#include "time.h"
#include "enemymanager.h"
#include "gimmickmanager.h"
#include "explosionmanager.h"
#include "enemybulletmanager.h"
#include "barriermanager.h"
#include "lockon.h"
#include "direction.h"
#include "ui_gameguide.h"
#include "pause.h"

class CPlayer;

//�Q�[���N���X
class CGame : public CScene
{
public:

	//�萔
	static const D3DXVECTOR3 TIME_POS;		//���Ԃ̈ʒu
	static const std::string FILEPATH_MODEL;//���f���̃t�@�C���p�X

	//�����o�֐�
	CGame();						//�R���X�g���N�^
	~CGame() override;				//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Load() override;			//�ǂݍ���

	//�|�C���^�̎擾
	CPlayer* GetGamePlayer() { if (m_pPlayer == nullptr) { return nullptr; } return m_pPlayer; }								//�v���C���[�̎擾
	CField* GetGameField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }									//�t�B�[���h�̎擾
	CTime* GetTime() { if (m_pTime == nullptr) { return nullptr; } return m_pTime; }											//���Ԃ̎擾
	CEnemyManager* GetEnemyManager() { if (m_pEnemyManager == nullptr) { return nullptr; } return m_pEnemyManager; }			//�G�l�~�[�}�l�[�W���[�̎擾
	CGimmickManager* GetGimmickManager() { if (m_pGimmickManager == nullptr) { return nullptr; } return m_pGimmickManager; }	//�M�~�b�N�}�l�[�W���[�̎擾
	CExplosionManager* GetExplosionManager() { if (m_pExplosionManager == nullptr) { return nullptr; } return m_pExplosionManager; }	//�����}�l�[�W���[�̎擾
	CEnemyBulletManager* GetEnemyBulletManager() { if (m_pEnemyBulletManager == nullptr)  { return nullptr; } return m_pEnemyBulletManager;}	//�G�l�~�[�e�̎擾
	CBarrierManager* GetBarrierManager() { if (m_pBarrierManager == nullptr) { return nullptr; } return m_pBarrierManager; }			//���E�}�l�[�W���[
	CLockon* GetLockon() { if (m_pLockon == nullptr) { return nullptr; } return m_pLockon; }									//���b�N�I���̎擾
	void SetLockon(bool lockon);																								//���b�N�I���̐ݒ�

	//�N���A����
	void SetClear(bool clear) { m_bClear = clear; }	//�ݒ�

	//�퓬����
	void SetBattle(bool battle) { m_bBattle = battle; }	//�ݒ�

	//�Q�[���I�[�o�[����
	void SetGameOver(bool gameover) { m_bGameOver = gameover; }	//�ݒ�

	//���o
	void SetDirection(CDirection::DIRECTIONTYPE type);	//���o�̎�ނ�ݒ�
	bool GetDirectioning() { return m_bDirectioning; }	//�擾

	//���b�V������
	void SetRushJudge(bool judge) { m_bRush = judge; }	//�ݒ�
	bool GetRushJudge() { return m_bRush; }				//�擾

	//�{�X�풆��
	void SetBossBattleJudge(bool judge) { m_bBossBattle = judge; }	//�ݒ�
	bool GetBossBattleJudge() { return m_bBossBattle; }				//�擾

	//�R���g���[���[�̎��
	CUi_GameGuide::CONTROLLER GetControllerUIType() { return m_ControllerUIType; }

	//�|�[�Y
	void SetPause();						//�|�[�Y�̐؂�ւ�
	bool GetPause() { return m_bPause; }	//�|�[�Y�̏�Ԃ��擾

private:

	//�֐�
	void DirectioningProcess();	//���o���̏���
	bool IsDeleteDirection();	//���o��j�����邩
	void CheckGuideUI();		//�K�C�hUI�̊m�F
	bool IsUsedJoipad();		//�W���C�p�b�h���g���Ă��邩
	bool IsUsedKeyboardMouse();	//�L�[�}�E���g���Ă��邩
	void NextScene();			//���̃V�[���ֈڍs
	bool CanNextScene();		//���̃V�[���ֈڍs�ł��邩
	void ModelLoad();			//���f���̓ǂݍ���
	void GuideUILoad();			//�K�C�hUI���̓ǂݍ���
	void PauseProcess();		//�|�[�Y�̏���

	CPlayer* m_pPlayer;							//�v���C���[
	CField* m_pField;							//�t�B�[���h
	CTime* m_pTime;								//�^�C���N���X
	CEnemyManager* m_pEnemyManager;				//�G�l�~�[�}�l�[�W���[
	CGimmickManager* m_pGimmickManager;			//�M�~�b�N�}�l�[�W���[
	CExplosionManager* m_pExplosionManager;		//�����}�l�[�W���[
	CLockon* m_pLockon;							//���b�N�I��
	CEnemyBulletManager* m_pEnemyBulletManager;	//�G�l�~�[�e�}�l�[�W���[
	CBarrierManager* m_pBarrierManager;			//���E�}�l�[�W���[
	CPause* m_pPause;							//�|�[�Y�̃|�C���^

	//����
	bool m_bClear;				//�N���A����
	bool m_bBattle;				//�퓬����
	bool m_bGameOver;			//�Q�[���I�[�o�[����
	bool m_bRush;				//���b�V������
	bool m_bBossBattle;			//�{�X�풆��
	bool m_bPause;				//�|�[�Y����

	//���o
	bool m_bDirectioning;		//���o����
	CDirection* m_pDirection;	//���o�̃|�C���^

	//�Q�[���ɕ\������K�C�hUI�̎��
	CUi_GameGuide::CONTROLLER m_ControllerUIType;
};

#endif