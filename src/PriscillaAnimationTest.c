// Generated by BattleAnimationDumper
// 2017/08/27 19:52:53

// ˫��ɫ�����

#include	"FE7JBattleAnimation.h"

const u16 PriscillaAnimationTest_data5[];

extern const int PriscillaAnimationTest_data1;
extern const int PriscillaAnimationTest_data2;
extern const int PriscillaAnimationTest_data3;
extern const int PriscillaAnimationTest_data4;

// �²�ɫ��
const u16 PriscillaAnimationTest_PalB[] = {
	0x5355, 0x2CF1, 0x599B, 0x72BD, 0x7FBD, 0x66D5, 0x3CE2, 0x30C2,
	0x5585, 0x6E4C, 0x4E0E, 0x3146, 0x27FF, 0x2EBD, 0x35DD, 0x14A5
};

// �ײ�ɫ��������������ɫ���б���
__attribute__((section(".PriscillaTestPal")))
const CharacterBattlePal PriscillaTestPal = {
	"PriscillaTest",
	PriscillaAnimationTest_PalB
};

// ��λְҵ�����ɫ������
__attribute__((section(".PriscillaTestPalNo")))
const u8 PriscillaTestPalNo = 0x79;

__attribute__((section(".PriscillaAnimationTest")))
const BattleAnimation PriscillaAnimationTest = {
	"priscil_tst",	// Identifier
	&PriscillaAnimationTest_data1,	// Mode divider
	&PriscillaAnimationTest_data2,	// Script
	&PriscillaAnimationTest_data3,	// Right X Y Position
	&PriscillaAnimationTest_data4,	// Left X Y Position
	&PriscillaAnimationTest_data5,	// Palette Group
};

const u16 PriscillaAnimationTest_data5[] = {
0x5355,0x7FFF,0x6BFF,0x3EFE,0x1D50,0x41A3,0x0B79,0x0DD5,	// Player
0x6271,0x7EF0,0x79A8,0x3D45,0x431A,0x2E55,0x14EA,0x14A5,
0x5355,0x7FFF,0x6BFF,0x3EFE,0x1D50,0x2973,0x0FBC,0x0DD5,	// Enemy
0x467F,0x3E1F,0x043A,0x0C32,0x431A,0x2E55,0x14EA,0x14A5,
0x5355,0x7FFF,0x6BFF,0x3EFE,0x1D50,0x4164,0x2E1C,0x08F4,	// NPC
0x5F10,0x1BE7,0x1EE5,0x19C5,0x431A,0x2E55,0x14EA,0x14A5,
0x5355,0x7FFF,0x6BFF,0x3EFE,0x1D50,0x4224,0x4CB7,0x30AE,	// 4th(arena)
0x4710,0x5A72,0x45AC,0x3508,0x431A,0x2E55,0x14EA,0x14A5,
};