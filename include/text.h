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
/*	[0x0835] = sbsaysth(pSharon,Right,"��ã�" endl
									"�������ء�" pushA)	*/
/*	[0x0835] = openFarLeft loadFace pOswin openLeft loadFace pHector openFarRight loadFace pSurtrR openRight loadFace pSurtrL
				"��������С���" endl
				"Ҳ���ؼ�?" pushA
				clearFace openFarRight clearFace,	*/
	[0x0835] = openFarLeft loadFace pOswin
				"ǰ������ɽ" pushA
				openLeft loadFace pHectorNoble
				"�����Ǹ���" pushA
				openFarRight loadFace pSurtrR
				openRight loadFace pSurtrL
				"һȺս����" pushA
				clearFace openLeft clearFace openFarLeft clearFace
				openFarRight clearFace loadFace pBlackKnightR
				openRight loadFace pBlackKnightL
				"�̲�������" pushA,
	[0x0836] = openFarLeft loadFace pZelgius
				openLeft loadFace pZelgius
				openRight loadFace pZelgius
				openFarRight loadFace pZelgius
				//"�̲�ʲôʱ��" endl
				//"�۾�����Ķ���" pushA,
				toggleMouthMove
				"�첿��������" endl pushA
				toggleMouthMove
				toggleSmile
				"΢Ц����" endl pushA
				toggleMouthMove
				"΢Ц�첿��������" endl pushA
				toggleMouthMove
				toggleSmile
				closeEyes "���۲���" endl pushA
				openEyes halfCloseEyes "����۲���" endl pushA
				openEyes wink "ʹ��ɫ����" endl pushA
				openEyes "����" endl pushA,
	[0x837] = openLeft loadFace pFenrir
				openFarLeft loadFace pFenrir
				openRight loadFace pFenrir
				openFarRight loadFace pFenrir
				"���޷�����ͷ�����" pushA
				clearFace,
};
