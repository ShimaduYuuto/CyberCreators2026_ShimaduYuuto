//======================================
//
//	�L�����N�^�[�̏���[character.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "character.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"

//============================
//�L�����N�^�[�̃R���X�g���N�^
//============================
CCharacter::CCharacter(int nPriority) : CObject(nPriority),
	m_OldPos { 0.0f, 0.0, 0.0f },		//�O��̈ʒu
	m_Move { 0.0f, 0.0, 0.0f },			//�ړ���
	m_GoalRot { 0.0f, 0.0, 0.0f },		//�ړI�̌���
	m_MotionState(0),					//���[�V�����̏�����
	m_bChangeMotion(true),				//���[�V������؂�ւ����邩
	m_fInterpolationCount(0.0f),		//���`��Ԃ̃J�E���g
	m_bInterpolationEnd(true),			//���`��Ԃ��I����Ă��邩
	m_Rot { 0.0f, 0.0, 0.0f },			//����
	m_pShadow(nullptr)					//�e�̃|�C���^
{
	
}

//============================
//�L�����N�^�[�̃f�X�g���N�^
//============================
CCharacter::~CCharacter()
{
	//vector�̓��I�z����폜
	m_apModel.clear();		//���f���̍폜
	m_Motion.clear();		//���[�V�������̍폜
	m_PartsInfo.clear();	//�p�[�c���̍폜
	m_InterpolationInfo.clear();

	//�e�̔j��
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//============================
//�L�����N�^�[�̏�����
//============================
HRESULT CCharacter::Init()
{
	//������
	CObject::Init();

	//�L�����N�^�[�N���X�̃����o�ϐ��̏�����
	m_bChangeMotion = true;
	m_fFrameCount = 0.0f;
	m_nMotionCount = 0;

	//�e�̐���
	m_pShadow = CShadow::Create(&GetPos(), SIZE_RADIUS);

	return S_OK;
}

//============================
//���[�V�����̐ݒ�
//============================
void CCharacter::SetMotionInfo(const char* motionfilename)
{
	int nCnt = 0;								// ���݂̃f�[�^��
	char aDataSearch[MAX_STRING];				// �f�[�^�����p
	int nMotionCount = 0;						//���[�V�����̃J�E���g
	int nKeyCount = 0;							//�L�[�̃J�E���g
	int nKeySetCount = 0;						//�L�[�Z�b�g�̃J�E���g
	int nPartsNum = 0;							//�p�[�c�̐�
	char aModelFileName[MAX_MODEL][MAX_STRING];	//���f���̃t�@�C���l�[��

	//�p�[�c����ǂݍ��ޕϐ�
	D3DXVECTOR3 Pos[MAX_MODEL];		//�ʒu
	D3DXVECTOR3 Rot[MAX_MODEL];		//����
	int nIndex[MAX_MODEL];			//���g�̔ԍ�
	int nParentIndex[MAX_MODEL];	//�e�̔ԍ�

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen(motionfilename, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "SCRIPT"))
		{
			// END��������܂œǂݍ��݂��J��Ԃ�
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);	// ����

				if (!strcmp(aDataSearch, "MODEL_FILENAME"))
				{
					fscanf(pFile, "%s", aDataSearch);
					fscanf(pFile, "%s", &aModelFileName[nPartsNum][0]);

					//X�t�@�C���̓o�^
					CManager::GetInstance()->GetXfile()->Regist(&aModelFileName[nPartsNum][0]);

					//�p�[�c���̉��Z
					nPartsNum++;
				}

				if (!strcmp(aDataSearch, "END_SCRIPT"))
				{// �ǂݍ��݂��I��
					break;
				}

				if (!strcmp(aDataSearch, "CHARACTERSET"))
				{
					// END��������܂œǂݍ��݂��J��Ԃ�
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch);	// ����

						if (!strcmp(aDataSearch, "END_CHARACTERSET"))
						{// �ǂݍ��݂��I��
							break;
						}
						if (aDataSearch[0] == '#')
						{// �܂�Ԃ�
							continue;
						}
						if (!strcmp(aDataSearch, "NUM_PARTS"))
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &nPartsNum);
						}


						if (!strcmp(aDataSearch, "PARTSSET"))
						{
							// ���ڂ��ƂɃf�[�^����
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch); // ����

								if (!strcmp(aDataSearch, "END_PARTSSET"))
								{
									break;
								}		// �ǂݍ��݂��I��
								else if (!strcmp(aDataSearch, "INDEX"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &nIndex[nCnt]);
								}		// ���
								else if (!strcmp(aDataSearch, "PARENT"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &nParentIndex[nCnt]);
								}		// ��
								else if (!strcmp(aDataSearch, "POS"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%f", &Pos[nCnt].x);
									fscanf(pFile, "%f", &Pos[nCnt].y);
									fscanf(pFile, "%f", &Pos[nCnt].z);
								}		// ����
								else if (!strcmp(aDataSearch, "ROT"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%f", &Rot[nCnt].x);
									fscanf(pFile, "%f", &Rot[nCnt].y);
									fscanf(pFile, "%f", &Rot[nCnt].z);
								}		// ���s��

							}

							nCnt++;	// �f�[�^�����Z
						}
					}
				}

				//============���[�V�����̓ǂݍ���==============================================
				if (!strcmp(aDataSearch, "MOTIONSET"))
				{
					//���[�V��������ǂݍ��ޕϐ�
					Motion aMotion;
					
					int LoopType = 0;
					// ���ڂ��ƂɃf�[�^����
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // ����

						if (aDataSearch[0] == '#')
						{// �܂�Ԃ�
							continue;
						}
						if (!strcmp(aDataSearch, "END_MOTIONSET"))
						{
							break;
						}			// �ǂݍ��݂��I��
						else if (!strcmp(aDataSearch, "LOOP")) //���[�v�̓ǂݍ���
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &aMotion.bLoop);
							if (aMotion.bLoop == 0)
							{
								aMotion.bLoop = false;
							}
							else
							{
								aMotion.bLoop = true;
							}
						}		// ���
						else if (!strcmp(aDataSearch, "NUM_KEY")) //�L�[���̓ǂݍ���
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &aMotion.nNumKey);
						}		// ��

						if (!strcmp(aDataSearch, "KEYSET")) //�L�[�Z�b�g�̓ǂݍ���
						{
							//�L�[����ǂݍ��ޕϐ�
							KeySet aKeySet;

							// ���ڂ��ƂɃf�[�^����
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch); // ����

								if (aDataSearch[0] == '#')
								{// �܂�Ԃ�
									fgets(aDataSearch, 30, pFile);
									continue;
								}
								if (!strcmp(aDataSearch, "END_KEYSET"))
								{
									break;
								}			// �ǂݍ��݂��I��
								//�t���[�����̓ǂݍ���
								if (!strcmp(aDataSearch, "FRAME"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &aKeySet.nFrame);
								}

								if (!strcmp(aDataSearch, "KEY")) //�L�[�̓ǂݍ���
								{
									//�L�[����ǂݍ��ޕϐ�
									D3DXVECTOR3 KeyPos;	//�ʒu
									D3DXVECTOR3 Keyrot;	//����
									Key aKey;

									// ���ڂ��ƂɃf�[�^����
									while (1)
									{
										fscanf(pFile, "%s", aDataSearch); // ����

										if (aDataSearch[0] == '#')
										{// �܂�Ԃ�
											continue;
										}
										if (!strcmp(aDataSearch, "POS"))
										{
											fscanf(pFile, "%s", aDataSearch);
											fscanf(pFile, "%f", &aKey.pos.x);
											fscanf(pFile, "%f", &aKey.pos.y);
											fscanf(pFile, "%f", &aKey.pos.z);
										}
										else if (!strcmp(aDataSearch, "ROT"))
										{
											fscanf(pFile, "%s", aDataSearch);
											fscanf(pFile, "%f", &aKey.rot.x);
											fscanf(pFile, "%f", &aKey.rot.y);
											fscanf(pFile, "%f", &aKey.rot.z);
										}

										if (!strcmp(aDataSearch, "END_KEY"))
										{
											break;
										}			// �ǂݍ��݂��I��

									}

									aKeySet.Key.push_back(aKey);	//�L�[���̕ۑ�
									nKeyCount++; //�f�[�^�̉��Z
								}
							}
							aMotion.KeySet.push_back(aKeySet);	//�L�[���̕ۑ�
							nKeyCount = 0;
							nKeySetCount++; //�f�[�^�̉��Z
						}
					}
					m_Motion.push_back(aMotion);	//���[�V�������̕ۑ�
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++; //�f�[�^�̉��Z
				}
			}
			fclose(pFile);
			break;
		}
	}

	//�p�[�c�̐���������
	for (int nInfoCount = 0; nInfoCount < nPartsNum; nInfoCount++)
	{
		//���f���p�[�c�̐����Ɛݒ�
		m_apModel.push_back(CModelparts::Create(&aModelFileName[nInfoCount][0], Pos[nInfoCount], Rot[nInfoCount]));

		//�p�[�c�̏���ۑ�
		PartsInfo aPartsInfo;
		aPartsInfo.pos = Pos[nInfoCount];
		aPartsInfo.rot = Rot[nInfoCount];
		m_PartsInfo.push_back(aPartsInfo);
		m_InterpolationInfo.push_back(aPartsInfo);
	}

	//�p�[�c�̐���������
	for (int i = 0; i < nPartsNum; i++)
	{
		if (nParentIndex[i] == -1)
		{
			//�e�̃}�g���b�N�X�̐ݒ�
			m_apModel[i]->SetParent(nullptr);
		}
		else
		{
			//�e�̃}�g���b�N�X�̐ݒ�
			m_apModel[i]->SetParent(m_apModel[nParentIndex[i]]);
		}
		
		//�p�����[�^�̐ݒ�
		m_apModel[i]->SetPos(m_Motion[0].KeySet[0].Key[i].pos + m_PartsInfo[i].pos);	//�ʒu
		m_apModel[i]->SetRot(m_Motion[0].KeySet[0].Key[i].rot + m_PartsInfo[i].rot);	//�p�x
	}
}

//============================
//�L�����N�^�[�̏I������
//============================
void CCharacter::Uninit()
{
	//���łɎ��S�t���O�������Ă����甲����
	if (GetDeath())
	{
		return;
	}
	
	//�I������
	CObject::Uninit();

	//���g�̃p�[�c���J��
	for (auto& iter : m_apModel)
	{
		iter->Uninit();
	}

	//�e�̔j��
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//============================
//�L�����N�^�[�̍X�V
//============================
void CCharacter::Update()
{
	//�ʒu�̍X�V
	UpdatePos();

	//�����̍X�V
	UpdateRot();

	//���[�V�����̍X�V
	UpdateMotion();
}

//============================
//�ʒu�̍X�V
//============================
void CCharacter::UpdatePos()
{
	//�p�����[�^�̎擾
	D3DXVECTOR3 pos = CObject::GetPos();	//�ʒu

	//�O��̈ʒu��ۑ�
	m_OldPos = pos;

	//�ړ��ʂ�����
	m_Move.x += (0.0f - m_Move.x) * 0.5f;
	m_Move.z += (0.0f - m_Move.z) * 0.5f;

	//�p�����[�^�̐ݒ�
	CObject::SetPos(pos);	//�ʒu
}

//============================
//�����̍X�V
//============================
void CCharacter::UpdateRot()
{
	//�ړI�̌����Ɍ������鏈��
	if (m_Rot.y == m_GoalRot.y)
	{//�ړI�̌����������Ă����甲����
		return;
	}

	if (m_Rot.y >= D3DX_PI * 0.5f && m_GoalRot.y <= D3DX_PI * -0.5f)
	{
		m_Rot.y += AddRot(ROTATE_SPEED);
		if (m_Rot.y > D3DX_PI)
		{
			m_Rot.y -= D3DX_PI * 2;
		}
	}
	else if (m_GoalRot.y >= D3DX_PI * 0.5f && m_Rot.y <= D3DX_PI * -0.5f)
	{
		m_Rot.y -= AddRot(ROTATE_SPEED);
		if (m_Rot.y < D3DX_PI)
		{
			m_Rot.y += D3DX_PI * 2;
		}
	}
	else if (m_GoalRot.y - m_Rot.y > 0)
	{
		m_Rot.y += AddRot(ROTATE_SPEED);
	}
	else
	{
		m_Rot.y -= AddRot(ROTATE_SPEED);
	}

	//�ړI�̌����Ƌ߂��Ȃ�����␳
	if (m_GoalRot.y - m_Rot.y < ROTATE_SPEED && m_GoalRot.y - m_Rot.y > -ROTATE_SPEED)
	{
		m_Rot.y = m_GoalRot.y;
	}
}

//============================
//�����̉��Z
//============================
float CCharacter::AddRot(float addrot)
{
	//�Ԃ��p�̕ϐ�
	float fAdd = addrot;

	return fAdd;
}

//============================
//�d�͂̏���
//============================
D3DXVECTOR3 CCharacter::GravityMove(D3DXVECTOR3 move)
{
	return { 0.0f, 0.0f, 0.0f };
}

//===================================
//���[�V�����̐ݒ�
//===================================
void CCharacter::SetMotion(int motion)
{
	//�؂�ւ����Ȃ����[�V�����̓r���Ȃ�֐��𔲂���
	if (!m_bChangeMotion)
	{
		return;
	}

	//���[�V�������̏�����
	m_MotionState = motion;			 //���[�V������ݒ�
	m_nMotionCount = 0;				//���[�V�����̃L�[��������
	m_fFrameCount = 0;				//���[�V�����t���[����������
	m_fInterpolationCount = 0.0f;	//���`��Ԃ̃J�E���g�̏�����
	m_bInterpolationEnd = false;	//���`�ۊǂ̃t���O�𗧂Ă�

	//���[�J���ϐ�
	int nCount = 0;	//�������̃J�E���g

	//�p�[�c������
	for (auto& iter : m_InterpolationInfo)
	{
		//�ړ��ʂ̕ϐ�
		D3DXVECTOR3 GoalPos = m_Motion[m_MotionState].KeySet[0].Key[nCount].pos + m_PartsInfo[nCount].pos;
		D3DXVECTOR3 GoalRot = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot + m_PartsInfo[nCount].rot;
		D3DXVECTOR3 Movepos = GoalPos - m_apModel[nCount]->GetPos();
		D3DXVECTOR3 Moverot = GoalRot - m_apModel[nCount]->GetRot();
		Moverot = RotCalculation(GoalRot, m_apModel[nCount]->GetRot());

		//���[�V�����̈ړ��ʂ̕ۑ�
		iter.pos = Movepos / INTERPOLATION_FRAME;
		iter.rot = Moverot / INTERPOLATION_FRAME;
		nCount++;
	}
}

//===================================
//���[�V�����̍X�V
//===================================
void CCharacter::UpdateMotion()
{
	//���[�v���Ȃ����[�V�����Ȃ�֐��𔲂���
	if (!m_Motion[m_MotionState].bLoop && m_nMotionCount == m_Motion[m_MotionState].nNumKey - 1)
	{
		return;
	}

	//���[�J���ϐ�
	int nCount = 0;	//�������̃J�E���g

	//���g�̃p�[�c�̈ʒu�ƌ�����ݒ�3
	for (auto& iter : m_apModel)
	{
		//���݂̈ʒu�ƌ������擾
		D3DXVECTOR3 pos = iter->GetPos();
		D3DXVECTOR3 rot = iter->GetRot();

		//�ړ��ʂ̕ϐ�
		D3DXVECTOR3 Movepos = m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos;
		D3DXVECTOR3 Moverot = m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot;

		//�ړI�̃L�[���ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
		if (m_nMotionCount != m_Motion[m_MotionState].nNumKey - 1)
		{
			Movepos = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].pos - m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos;
			Moverot = RotCalculation(m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot, m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot);
		}
		else
		{
			Movepos = m_Motion[m_MotionState].KeySet[0].Key[nCount].pos - m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].pos;
			Moverot = RotCalculation(m_Motion[m_MotionState].KeySet[0].Key[nCount].rot, m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot);
		}

		//�����̕����t���[���Ŋ������l�ŉ��Z
		Movepos /= (float)m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;
		Moverot /= (float)m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;

		//�����̕��������Z
		pos += Movepos;
		rot += Moverot;

		//��Ԃ��I����Ă��Ȃ��Ȃ�
		if (!m_bInterpolationEnd)
		{
			pos += m_InterpolationInfo[nCount].pos;
			rot += m_InterpolationInfo[nCount].rot;
		}

		//�ʒu�ƌ����̐ݒ�
		iter->SetPos(pos);
		iter->SetRot(rot);

		//�J�E���g�̍X�V
		nCount++;
	}

	//���`��Ԃ��I����Ă��Ȃ��Ȃ�J�E���g��i�߂�
	if (!m_bInterpolationEnd)
	{
		//�t���[���̉��Z
		m_fInterpolationCount++;

		//�J�E���g���w��l�ɂȂ�����
		if (m_fInterpolationCount >= INTERPOLATION_FRAME)
		{
			//�t���O���I���
			m_bInterpolationEnd = true;
		}
	}

	//�t���[���̉��Z
	m_fFrameCount++;

	//�t���[���̃J�E���g����������C��
	if (m_fFrameCount > m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame)
	{
		m_fFrameCount = static_cast<float>(m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame);
	}

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_fFrameCount == m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame)
	{
		m_fFrameCount = 0; //�J�E���g��������
		m_nMotionCount++; //���[�V�����̃J�E���g�𑝉�

		//���̃L�[������Ȃ�
		if (m_nMotionCount < m_Motion[m_MotionState].nNumKey)
		{
			int nCount = 0;
			//�X���[�ō����o�Ȃ��悤�ɕ␳�o�O�ł�
			for (auto& iter : m_apModel)
			{
				//�p�[�c�̉��Z
				iter->SetPos(m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos + m_PartsInfo[nCount].pos);
				iter->SetRot(m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot + m_PartsInfo[nCount].rot);
				nCount++;
			}
		}

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (m_nMotionCount == m_Motion[m_MotionState].nNumKey && m_Motion[m_MotionState].bLoop)
		{
			m_nMotionCount = 0; //�J�E���g��0�ɂ���
		}
		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (m_nMotionCount == m_Motion[m_MotionState].nNumKey - 1 && !m_Motion[m_MotionState].bLoop)
		{
			//����ȍs���̏I���
			m_bChangeMotion = true; //���[�V�����̔����off�ɂ���
		}
	}

}

//============================
//���[�V�����̌����̎Z�o
//============================
D3DXVECTOR3 CCharacter::RotCalculation(D3DXVECTOR3 goal, D3DXVECTOR3 current)
{
	D3DXVECTOR3 InterpolationRot = goal - current;

	//X�̊p�x�̕␳
	if (InterpolationRot.x > D3DX_PI)
	{
		InterpolationRot.x = (-D3DX_PI - current.x) + -(D3DX_PI - goal.x);
	}
	else if (InterpolationRot.x < -D3DX_PI)
	{
		InterpolationRot.x = (D3DX_PI - current.x) + (D3DX_PI + goal.x);
	}

	//Y�̊p�x�̕␳
	if (InterpolationRot.y > D3DX_PI)
	{
		InterpolationRot.y = (-D3DX_PI - current.y) + -(D3DX_PI - goal.y);
	}
	else if (InterpolationRot.y < -D3DX_PI)
	{
		InterpolationRot.y = (D3DX_PI - current.y) + (D3DX_PI + goal.y);
	}

	//Z�̊p�x�̕␳
	if (InterpolationRot.z > D3DX_PI)
	{
		InterpolationRot.z = (-D3DX_PI - current.z) + -(D3DX_PI - goal.z);
	}
	else if (InterpolationRot.z < -D3DX_PI)
	{
		InterpolationRot.z = (D3DX_PI - current.z) + (D3DX_PI + goal.z);
	}

	return InterpolationRot;
}

//============================
//�L�����N�^�[�̕`�揈��
//============================
void CCharacter::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;														//�v�Z�p�}�g���b�N�X
	D3DXVECTOR3 pos = GetPos();															//�ʒu�̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�p�[�c������
	for (auto iter : m_apModel)
	{
		iter->Draw(0,0);
	}
}

//============================
//�ړI�̌����̐ݒ�
//============================
void CCharacter::SetGoalRot(D3DXVECTOR3 goalrot)
{
	//�ړI�̌����̐ݒ�
	m_GoalRot = goalrot;

	//x��
	if (m_GoalRot.x > D3DX_PI)
	{
		m_GoalRot.x -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.x < -D3DX_PI)
	{
		m_GoalRot.x += D3DX_PI * 2.0f;
	}

	//y��
	if (m_GoalRot.y > D3DX_PI)
	{
		m_GoalRot.y -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.y < -D3DX_PI)
	{
		m_GoalRot.y += D3DX_PI * 2.0f;
	}

	//z��
	if (m_GoalRot.z > D3DX_PI)
	{
		m_GoalRot.z -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.z < -D3DX_PI)
	{
		m_GoalRot.z += D3DX_PI * 2.0f;
	}
}