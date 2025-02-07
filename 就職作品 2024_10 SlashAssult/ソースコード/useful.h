//=============================================
//
//���p�I�ȏ������܂Ƃ߂�����[useful.h]
//Auther Matsuda Towa?
//
//=============================================

//�Q�d�C���N���[�h�h�~
#ifndef _USEFUL_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _USEFUL_H_

#include "main.h"

//�����蔻��n
bool JudgeBallCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float length);	//�~�̓����蔻��(�ʒu�A�ʒu�A���肷�钷��)

//�v�Z�n
float Ratio(float value, float max);	//�������Z�o

//0�������p
#define INT_ZERO (0)
#define FLOAT_ZERO (0.0f)

//�J���[������
#define COLOR_RESET_ZERO (D3DXVECTOR3(0.0f,0.0f,0.0f,0.0f))
#define COLOR_RESET_ONE (D3DXVECTOR3(1.0f,1.0f,1.0f,1.0f))

//���_3D������
#define VEC3_RESET_ZERO (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define VEC3_RESET_ONE (D3DXVECTOR3(1.0f,1.0f,1.0f))

//���_2D������
#define VEC2_RESET_ZERO (D3DXVECTOR2(0.0f,0.0f))
#define VEC2_RESET_ONE (D3DXVECTOR2(1.0f,1.0f))

//���~
#define HALF_PI	(D3DX_PI * 0.5f)
//1/4�~
#define QRTR_PI	(D3DX_PI * 0.25f)

//�����J��
template<class T>
constexpr void SafeDelete(T& p)
{
	if (p == nullptr) { return; }
	delete p;
	p = nullptr;
}

//�ėp�I�ȃL�[����̔���
bool TriggerUp();		//�����������
bool TriggerDown();		//������������
bool TriggerRight();	//�E����������
bool TriggerLeft();		//������������
bool TriggerDecision();	//����{�^������������

//�Q�_�̊p�x�̍����Z�o
float CheckAngleDiff(float angle0, float angle1);

//����l�Ɖ����l�����ꂼ���ׂ�
//template<typename T>
//T Clamp(T x, T low, T high)
//{
//	assert(low <= high);
//	return std::min(std::max(x, low), high);
//}

#endif