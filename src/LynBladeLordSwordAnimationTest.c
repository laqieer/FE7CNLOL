// ��������������������
// by laqieer
// 2017/8/13

#include	"FE7JBattleAnimation.h"

#include	"LynBladeLordSwordAnimationData2_bin.h"

const int LynBladeLordSwordAnimationData1[] = {
	0,		// Part 1		��ͨ����		����ǰ��
	4+0x264,	// Part 2		��ͨ����		���˺�
	4+4+0x4CC,	// Part 3		��ɱ����		����ǰ��
	4+4+0x8A4,	// Part 4		��ɱ����		���˺�
	4+4+0xC7C,	// Part 5		��ͨħ������
	4+4+0xCF4,	// Part 6		��ɱħ������
	4+4+0xDE4,	// Part 7		���ӻر�
	4+4+0xE28,	// Part 8		Զ�̻ر�
	4+4+0xE6C,	// Part 9		վ��֡
	4+4+0xE80,	// Part 10	վ��2
	4+4+0xE94,	// Part 11	Զ��վ��
	4+4+0xEA8,	// Part 12	�������ر�
	0,0,0,0,0,0,0,0,0,0,0,0
};

__attribute__((section(".LynBladeLordSwordAnimation")))
const BattleAnimation LynBladeLordSwordAnimation = {
	"bllf_sw1_tst",
//	0x08E47FC8,
	&LynBladeLordSwordAnimationData1,
//	0x08E47AA4,
	LynBladeLordSwordAnimationData2_bin,
	0x08E4661C,
	0x08E45178,
	0x08E45118
};

