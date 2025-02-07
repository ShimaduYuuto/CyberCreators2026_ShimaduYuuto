//=============================================
//
//���p�I�ȏ������܂Ƃ߂�����[useful.cpp]
//Auther Matsuda Towa?
//
//=============================================

//�w�b�_�[�̃C���N���[�h
#include "useful.h"
#include "manager.h"

//=============================================
//�~�̓����蔻��
//=============================================
bool JudgeBallCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float length)
{
    D3DXVECTOR3 Vector = { 0.0f, 0.0f, 0.0f };     //�x�N�g��
    float fDistance = 0.0f; //����
    bool bHit = false;      //�������Ă��邩

    //�Q�_�Ԃ̋������v�Z
    D3DXVec3Subtract(&Vector, &pos2, &pos1);

    // �����x�N�g���̒����i�����j���v�Z
    fDistance = static_cast<float>(D3DXVec3Length(&Vector));

    //�����͈͈̔ȉ��Ȃ瓖�����Ă���
    if (fDistance <= length)
    {
        bHit = true;
    }

    return bHit;
}

//==================================================================
//�v�Z�n
//==================================================================

//=============================================
//�������Z�o
//=============================================
float Ratio(float value, float max)
{
    return value / max;
}

//=============================================
//�p�x�����Z�o
//=============================================
float CheckAngleDiff(float angle0, float angle1)
{
    float InterpolationAngle = angle0 - angle1;

    if (InterpolationAngle > D3DX_PI)
    {
        InterpolationAngle = (-D3DX_PI - angle1) + -(D3DX_PI - InterpolationAngle);
    }
    else if (InterpolationAngle < -D3DX_PI)
    {
        InterpolationAngle = (D3DX_PI - angle1) + (D3DX_PI + InterpolationAngle);
    }

    //��Βl��Ԃ�
    return std::abs(InterpolationAngle);
}

//==================================================================
//����n
//==================================================================

//============================
//�����������
//============================
bool TriggerUp()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_UP)) return true;					//�L�[�{�[�h
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_UP)) return true;		//�W���C�p�b�h

    return false;
}

//============================
//������������
//============================
bool TriggerDown()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_DOWN)) return true;					//�L�[�{�[�h
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_DOWN)) return true;	//�W���C�p�b�h

    return false;
}

//============================
//�E����������
//============================
bool TriggerRight()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RIGHT)) return true;					//�L�[�{�[�h
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RIGHT)) return true;		//�W���C�p�b�h

    return false;
}

//============================
//������������
//============================
bool TriggerLeft()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LEFT)) return true;					//�L�[�{�[�h
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_LEFT)) return true;	//�W���C�p�b�h

    return false;
}

//============================
//����{�^������������
//============================
bool TriggerDecision()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN)) return true;				//�L�[�{�[�h
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) return true;		//�W���C�p�b�h

    return false;
}