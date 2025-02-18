//================================
//
//random.cpp�ɕK�v�Ȑ錾[random.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RANDOM_H_ //���̃}�N����`������Ă��Ȃ�������
#define _RANDOM_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�����_���N���X
class CRandom
{
private:

	//�֐�
	CRandom() : m_Engine(m_Seed_gen()) {}	//�R���X�g���N�^�ŏ�����

public:

	//�C���X�^���X�̐���
	static CRandom* GetInstance()
	{
		static CRandom instance;	//�ÓI�C���X�^���X
		return &instance;
	}

	//�͈͓��ŗ����l��Ԃ�
	template<typename T>
	static T GetRandom(T min, T max)
	{
		//���l�^�łȂ��ꍇ�̓R���p�C���G���[�ɂ���
		static_assert(std::is_arithmetic<T>::value, "���l�^�ȊO�̌^�͈����܂���");

		// �V���O���g������G���W�����擾
		std::mt19937& engine = GetInstance()->m_Engine;

		//�n���ꂽ�^�ɉ����ė����𐶐��̎d���𔻒f
		using Distribution = typename std::conditional<
			std::is_integral<T>::value,						//�����^���𔻒f
			std::uniform_int_distribution<T>,				//�����̗���
			std::uniform_real_distribution<T>				//���������_�̗���
		>::type;

		//�擾�����^�ŗ����𐶐�
		Distribution Random(min, max);	//�ŏ��ƍő�͈̔͂ŗ��������߂�
		T Value = (Random(engine));

		return Value;
	}

	//�����l��Ԃ�
	template<typename T>
	static T GetRandom()
	{
		//���l�^�łȂ��ꍇ�̓R���p�C���G���[�ɂ���
		static_assert(std::is_arithmetic<T>::value, "���l�^�ȊO�̌^�͈����܂���");

		//�}�N�����������Ă���
		#undef max  

		// �ŏ��l�ƍő�l�𕂓������_�^�̍ŏ��ő�l�ɐݒ�
		T min = std::numeric_limits<T>::lowest();  // �ŏ��l
		T max = std::numeric_limits<T>::max();     // �ő�l

		return CRandom::GetRandom(min, max);
	}

private:

	//�ϐ�
	std::mt19937 m_Engine;
	std::random_device m_Seed_gen;

};

#endif