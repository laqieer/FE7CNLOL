// 琳利刃领主剑动画测试
// by laqieer
// 2017/8/13

#include	"FE7JBattleAnimation.h"

#include	"LynBladeLordSwordAnimationData2_bin.h"

const int LynBladeLordSwordAnimationData1[] = {
	0,		// Part 1		普通攻击		敌人前方
	4+0x264,	// Part 2		普通攻击		敌人后方
	4+4+0x4CC,	// Part 3		必杀攻击		敌人前方
	4+4+0x8A4,	// Part 4		必杀攻击		敌人后方
	4+4+0xC7C,	// Part 5		普通魔法攻击
	4+4+0xCF4,	// Part 6		必杀魔法攻击
	4+4+0xDE4,	// Part 7		近接回避
	4+4+0xE28,	// Part 8		远程回避
	4+4+0xE6C,	// Part 9		站立帧
	4+4+0xE80,	// Part 10	站立2
	4+4+0xE94,	// Part 11	远程站立
	4+4+0xEA8,	// Part 12	攻击被回避
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

