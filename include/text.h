// by laqieer
// 2017/4/19
// ������ı�

#pragma once
#include "portraitID.h"

// ���ַ����鸳ֵ�ķ�ʽҪ��:
// 1) �궨�����ַ�('')��Ҳ����ֱ�Ӷ������ֵ(���Զ�ǿ������ת��)
// 2) ������˫�ֽڱ��룬Ҫ�ߵ�λ�ֿ���ֵ
// ��ƪ�����տ����Ի�
//const char text0835[] = {openRight,loadFace,'\x20',endl,'��'>>8,'��','��'>>8,'��','��'>>8,'��',endl,'��'>>8,'��','��'>>8,'��','��'>>8,'��','��'>>8,'��','��'>>8,'��',pushA,clearFace};

const char* const text[]=
{
	// ���ַ�����ֵ
	// �ַ����п�����ת���ַ�
	// �궨����ַ���(""),C�����ж���ַ�����������һ��д��ʾƴ��
/*	[0x0835] =	openRight loadFace "\x20" endl
				"��ã�" endl
				"����������" pushA
				clearFace	*/
/*	[0x0835] = talk(\x20,Right,	"��ã�" endl
								"��������" pushA)	*/
	[0x0835] = sbsaysth(pTikiF,Right,"��ã�" endl
									"����������" pushA)
};

