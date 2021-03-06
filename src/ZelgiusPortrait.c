// 塞尔基乌斯头像
// by laqieer
// 2019-03-06

#include "ZelgiusPortrait.h"

// 用人造人乌海的头像位置做测试
__attribute__((section(".UhaiMorphPortraitID")))
const PortraitID UhaiMorphPortraitID = 0x108;

const u16 portraitMaskZelgius[9][10] = {
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1}
};

// 塞尔基乌斯对话头像模板(在右边)
const u16 ZelgiusPortraitTemplateLeft[1 + 3 * 8] =
{
	8,
	getObjectAttribute1(1,48),getObjectAttribute2(3,0,-136/2),getObjectAttribute3(0),	// 64x32
	getObjectAttribute1(1,48),getObjectAttribute2(3,0,-136/2 + 64),getObjectAttribute3(8),	// 64x32
	getObjectAttribute1(2,48),getObjectAttribute2(1,0,-136/2 + 64 + 64),getObjectAttribute3(16),	// 8x32
	getObjectAttribute1(0,0),getObjectAttribute2(2,0,-136/2 + 32),getObjectAttribute3(17),	// 32x32
	getObjectAttribute1(2,0),getObjectAttribute2(2,0,-136/2 + 32 + 32),getObjectAttribute3(21),	// 16x32
	getObjectAttribute1(2,0),getObjectAttribute2(1,0,-136/2 + 32 + 32 +16),getObjectAttribute3(23),	// 8x32
	getObjectAttribute1(1,32),getObjectAttribute2(2,0,-136/2 + 32),getObjectAttribute3(24 + 32 * 2),	// 32x16
	getObjectAttribute1(1,32),getObjectAttribute2(2,0,-136/2 + 32 + 32),getObjectAttribute3(28 + 32 * 2)	// 32x16
};

// 塞尔基乌斯头像模板(在左边)
const u16 ZelgiusPortraitTemplateRight[1 + 3 * 8] =
{
	8,
	getObjectAttribute1(1,48),getObjectAttribute2(3,1,-(-136/2 + 64)),getObjectAttribute3(0),	// 64x32
	getObjectAttribute1(1,48),getObjectAttribute2(3,1,-(-136/2 + 64 + 64)),getObjectAttribute3(8),	// 64x32
	getObjectAttribute1(2,48),getObjectAttribute2(1,1,-(-136/2 + 64 + 64 + 8)),getObjectAttribute3(16),	// 8x32
	getObjectAttribute1(0,0),getObjectAttribute2(2,1,-(-136/2 + 32 + 32)),getObjectAttribute3(17),	// 32x32
	getObjectAttribute1(2,0),getObjectAttribute2(2,1,-(-136/2 + 32 + 32 + 16)),getObjectAttribute3(21),	// 16x32
	getObjectAttribute1(2,0),getObjectAttribute2(1,1,-(-136/2 + 32 + 32 + 16 + 8)),getObjectAttribute3(23),	// 8x32
	getObjectAttribute1(1,32),getObjectAttribute2(2,1,-(-136/2 + 32 + 32)),getObjectAttribute3(24 + 32 * 2),	// 32x16
	getObjectAttribute1(1,32),getObjectAttribute2(2,1,-(-136/2 + 32 + 32 + 32)),getObjectAttribute3(28 + 32 * 2)	// 32x16
};

// 塞尔基乌斯头像框模板
const u16 ZelgiusPortraitInBoxTemplate[1 + 10 * 9 + 1] =
{
	0x809,
	getTileNo(3,2),getTileNo(4,2),getTileNo(5,2),getTileNo(6,2),getTileNo(7,2),getTileNo(8,2),getTileNo(9,2),getTileNo(10,2),getTileNo(11,2),getTileNo(12,2),
	getTileNo(3,1),getTileNo(4,1),getTileNo(5,1),getTileNo(6,1),getTileNo(7,1),getTileNo(8,1),getTileNo(9,1),getTileNo(10,1),getTileNo(11,1),getTileNo(12,1),
	getTileNo(3,0),getTileNo(4,0),getTileNo(5,0),getTileNo(6,0),getTileNo(7,0),getTileNo(8,0),getTileNo(9,0),getTileNo(10,0),getTileNo(11,0),getTileNo(12,0),
	getTileNo(0,0),getTileNo(24,3),getTileNo(25,3),getTileNo(26,3),getTileNo(27,3),getTileNo(28,3),getTileNo(29,3),getTileNo(30,3),getTileNo(31,3),getTileNo(0,0),
	getTileNo(0,0),getTileNo(24,2),getTileNo(25,2),getTileNo(26,2),getTileNo(27,2),getTileNo(28,2),getTileNo(29,2),getTileNo(30,2),getTileNo(31,2),getTileNo(0,0),
	getTileNo(0,0),getTileNo(17,3),getTileNo(18,3),getTileNo(19,3),getTileNo(20,3),getTileNo(21,3),getTileNo(22,3),getTileNo(23,3),getTileNo(0,0),getTileNo(0,0),
	getTileNo(0,0),getTileNo(17,2),getTileNo(18,2),getTileNo(19,2),getTileNo(20,2),getTileNo(21,2),getTileNo(22,2),getTileNo(23,2),getTileNo(0,0),getTileNo(0,0),
	getTileNo(0,0),getTileNo(17,1),getTileNo(18,1),getTileNo(19,1),getTileNo(20,1),getTileNo(21,1),getTileNo(22,1),getTileNo(23,1),getTileNo(0,0),getTileNo(0,0),
	getTileNo(0,0),getTileNo(17,0),getTileNo(18,0),getTileNo(19,0),getTileNo(20,0),getTileNo(21,0),getTileNo(22,0),getTileNo(23,0),getTileNo(0,0),getTileNo(0,0),
	0
};

const unsigned short ZelgiusPortraitMain[2 + 2048] __attribute__((aligned(4)))=
{
	0x400, 0x10,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0060,0x0000,0x06E6,0x0000,0x6EE6,0x6000,0xEEE6,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x6000,0x0006,0x6660,0x666C,0xEC66,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6000,
	0x6600,0x6666,0xC666,0xDDEE,0xDDEC,0xDDDD,0xDDDD,0xDDDD,
	0x0000,0x6660,0x0000,0x8886,0x0000,0x8886,0x6666,0xB886,
	0x6CEC,0xB8A6,0xCEDD,0xA8A6,0xEDDD,0x88BC,0xEDDD,0x886C,

	0x88AB,0x886A,0xBA88,0x88B6,0xCCBA,0x88B6,0xCCCC,0xA8A6,
	0xCCCC,0xA886,0xCCCC,0xB886,0xCCC6,0xB886,0x6CCB,0x688B,
	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x7999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,

	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,
	0xECC6,0xEDDD,0xDECC,0xCEDD,0xDDCC,0xBCDD,0xDDEC,0x86ED,
	0xDDEC,0x8BCD,0xDDEC,0x886E,0xEEEC,0x88BC,0xEEEC,0xA886,
	0x66CC,0xAABB,0x8AB6,0x8888,0x8888,0xBAA8,0xBA88,0x6666,
	0xC6A8,0xCCEE,0xECBA,0xCCEE,0xEECB,0xDCEE,0xEEE6,0xDCCE,
	0x88AA,0x8888,0x8888,0xBBAA,0x666B,0xE666,0xEEC6,0xDDDD,
	0xDEDD,0xDDDD,0xDEDD,0xDDDD,0xDEDD,0xCEED,0xCEDD,0xECCC,

	0x8888,0x006A,0xBBBB,0x06AA,0x6EEE,0x06B6,0xDDDD,0x066E,
	0xDDDD,0x066D,0xCCED,0x6666,0xECCC,0xEDDE,0xDDDE,0xDDDD,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x6666,0x0066,0x6CCE,0x6666,0xDDDD,0xEDDD,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0066,0x0000,0x66CC,0x0006,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x6000,0x0000,0x1600,
	0x0000,0x2160,0x0000,0x2260,0x0000,0x1216,0x0000,0x1216,
	0x6600,0x6666,0x2166,0x3332,0x3321,0x3333,0x2332,0x2111,
	0x1122,0x3332,0x3211,0x3333,0x3332,0x3333,0x1111,0x3211,

	0x6666,0x6666,0x3333,0x1223,0x3333,0x3333,0x3332,0x3333,
	0x2233,0x3332,0x3333,0x3322,0x3333,0x3223,0x3333,0x2233,
	0x0006,0x0000,0x6661,0x0006,0x2233,0x6661,0x3333,0x1233,
	0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,
	0x0000,0x0000,0x0000,0x0000,0x0006,0x0000,0x0661,0x0000,
	0x6212,0x0006,0x2133,0x0061,0x2333,0x0613,0x3333,0x6232,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xB996,0x99AF,0x99A6,0x7799,
	0x99BF,0x7999,0x9A6F,0xABB9,0x9B66,0x9999,0x9F66,0x9999,
	0x7777,0x7777,0x7777,0x7777,0xAFBA,0x7779,0x9977,0x7779,
	0x7777,0x7777,0x7779,0x7777,0x7779,0x7777,0x7777,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0x6000,0xCCE6,0x6000,0x6CC6,0x6600,0xCCC6,0xC600,0xCCC6,
	0xE600,0xCCCC,0xE600,0xCCCC,0xE600,0xCCCE,0xEC60,0xC6EE,
	0xC66C,0xDDDE,0xEEC6,0xDDDD,0xEECC,0xDDDD,0xEEEC,0xDDDE,
	0xEEEC,0xDDDE,0xEEEC,0xDDEE,0xEEEC,0xEEEE,0xEEEC,0xEEEE,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xEEDD,0xEEEE,0xEEEE,
	0xEDDD,0x8A6E,0xEDDD,0x8BCE,0xEDDD,0x86CE,0xEDDD,0xA6CC,
	0xEEDD,0xBCCC,0xEEED,0x6CCC,0xCEEE,0x6CCC,0x6CEE,0x6C66,

	0x6C6A,0x688B,0x6C68,0x688A,0x6CB8,0x6A8A,0x6CA8,0x6A88,
	0x6688,0x6B88,0x6688,0x6B8A,0x36AA,0x6623,0x746B,0x6234,
	0xE66C,0x86EC,0xEC6C,0x6EEE,0xEE66,0xDEEC,0xEDC6,0xEDCB,
	0x6DE6,0xCCBA,0xCEDC,0xC88B,0xEEEE,0xBB6C,0xCEEE,0xCEEE,
	0xDECB,0x8BCD,0xBBAA,0xBAAB,0xA896,0xCC66,0xB986,0x6DEE,
	0x6A8B,0xBEDE,0xB68A,0xABC6,0x6CB8,0xCA8B,0xEE6B,0xEC6C,
	0xECB8,0xDDDD,0xDDC6,0xDDDD,0xDDEC,0xDDDD,0xDDDC,0xDDDD,
	0xDDD6,0xDDDD,0xDDDC,0xDDDD,0xDDDE,0xDDDD,0xDDDD,0xEDDD,

	0xCEED,0xA8A6,0xEEED,0x88A6,0xEEED,0x88B6,0xEEED,0x88BC,
	0xEEED,0xA86C,0xEEEE,0xAA6C,0xEEEE,0xBA66,0xCEEE,0x3666,
	0xCEE6,0xB88B,0x6EE6,0x6B88,0xBCE6,0xC688,0xA6C6,0xE6B8,
	0x8A66,0x6C6A,0x8AB6,0xC66B,0xAAB6,0xEC66,0x6674,0xECC6,
	0xEEEC,0xDCCE,0xEEEE,0x66CC,0x6CEE,0xEC66,0xC66C,0xEECC,
	0xCEC6,0xEEEC,0xCEEE,0xEEEC,0xCCEE,0xEEEC,0xCCEE,0xEEEC,
	0x666C,0xDDEC,0xEEC6,0xDDDE,0xEEEE,0xDDDD,0xEEEE,0xDDDD,
	0xDEEE,0xDDDD,0xDEEE,0xDDDD,0xDEEE,0xDDDD,0xEEEE,0xDDDD,

	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xCDDD,0x066C,0xDDDD,0x6CDD,0xDDDD,0xEDDD,0xDDDD,0xDDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0x0000,0x0000,0x0006,0x0000,0x066C,0x0000,0x6CED,0x0006,
	0xEDDD,0x006C,0xDDDD,0x06CE,0xDDDD,0x6CEE,0xDDDD,0x6CEE,

	0x0000,0x0000,0x6660,0x0000,0xD660,0x0006,0xD660,0x0006,
	0xDE66,0x006D,0xDD66,0x006D,0xDDE6,0x006D,0xDDDE,0x06DD,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6000,
	0x0000,0x1600,0x0000,0x2600,0x0000,0x3260,0x0000,0x3360,
	0x0000,0x1116,0x6600,0x3211,0x2166,0x3322,0x3321,0x1122,
	0x1232,0x1111,0x3333,0x1113,0x1223,0x1221,0x1112,0x1111,
	0x3332,0x1123,0x3333,0x2333,0x2223,0x3333,0x2333,0x3232,
	0x3321,0x2322,0x3211,0x3212,0x3111,0x2113,0x2111,0x1113,

	0x3332,0x2333,0x3322,0x3333,0x3222,0x3333,0x2223,0x3333,
	0x2133,0x3332,0x1232,0x3322,0x1322,0x3221,0x2322,0x2211,
	0x3332,0x3333,0x3322,0x3333,0x3213,0x3233,0x2133,0x2333,
	0x1333,0x3332,0x3332,0x3321,0x3323,0x3213,0x3132,0x2133,
	0x3333,0x2333,0x3323,0x3233,0x3233,0x2333,0x2333,0x2333,
	0x2332,0x3332,0x3322,0x3331,0x3223,0x3312,0x3123,0x3213,
	0x0006,0x0000,0x0062,0x0000,0x0623,0x0000,0x6122,0x0000,
	0x6221,0x0000,0x1212,0x0006,0x2213,0x0006,0x2123,0x0061,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x7999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,

	0xEC60,0xCECE,0xEE60,0xECEE,0xEE60,0xCCEE,0xEE60,0xCCEE,
	0xEE60,0xCCEE,0xEE60,0xCEEE,0xEE60,0xCEEE,0xEE60,0xCEEE,
	0xEEC6,0xEEEE,0x666E,0xECCC,0xEEEE,0x66CE,0xDEEC,0xEDDD,
	0xDDDE,0xDDDD,0xDDDE,0xDDEE,0xEDDE,0xDDCB,0xBEDE,0xDDDC,
	0xEEEE,0xCEEE,0xEEEE,0xB6CC,0x6666,0x8A66,0xCCCE,0x88A6,
	0x6CEE,0x888A,0xA6ED,0xA888,0x8BED,0x6A88,0x8ACD,0xE6B8,
	0x666C,0x6666,0x888A,0xFA88,0x8888,0xF888,0x8888,0xB888,
	0x6A88,0xA8AB,0x666B,0xB886,0x66CC,0x6A8A,0xB6CE,0x6B88,

	0x2236,0x6374,0x7434,0x3242,0x4433,0x4373,0x3347,0x4637,
	0x4743,0x3463,0x3326,0xB336,0x6666,0xBF6C,0x6666,0x6CCC,
	0xCEEC,0xCEEE,0xBAAB,0xCECF,0xBBFF,0xBAAA,0xFFFB,0xBBBF,
	0xFBAB,0xEFFF,0xABFF,0xCFBA,0xBBAA,0xFFFF,0xBFF6,0xBAAA,
	0xEECB,0xDDEE,0xEEEA,0xDDDE,0xFFFF,0xFFFF,0xAAAB,0xAAAA,
	0xEEEE,0xEEEE,0xCCCC,0xCCCC,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
	0xDDDD,0xEEDD,0xDDDD,0xCCEE,0xFFFF,0xAABB,0xBAAA,0xFFFB,
	0xFCEE,0xBFFF,0xABFC,0xBBBA,0xFFFF,0xFFFF,0xAABF,0xAAAA,

	0x6CEE,0x7366,0xB666,0x3326,0x3BAA,0x3742,0x4FFF,0x4322,
	0x4FBA,0x7423,0xFFFF,0x3224,0xAABF,0x223B,0x6FBB,0xFBFF,
	0x2734,0xCCC6,0x3431,0x6666,0x7417,0x8AA6,0x4334,0x8886,
	0x3733,0x888B,0x6437,0x888A,0xA222,0xBBA8,0xA8AF,0x666A,
	0xCCEE,0xEECC,0x6666,0xECCC,0x8888,0xC6BA,0x8888,0xB888,
	0x8888,0x8888,0x8888,0x8888,0xABBB,0x8888,0x6666,0x8AB6,
	0xEEEE,0xDDDD,0xEEEE,0xDDDE,0xEEEE,0xDDEE,0xEEC6,0xDEEE,
	0xC6B8,0xEEEC,0x6A88,0x6666,0xA888,0xCCCC,0x8888,0xECCA,

	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xDDDE,0xDDDD,0xC666,0xCCCC,0xEEEE,0xCCCC,0xEEEE,0xCEEE,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0xDDDD,0xDDDD,0xCCCC,0x6CC6,0xCCCC,0xCCCC,0xCCCC,0xCCCC,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xCCED,
	0xCCEE,0xC666,0xC666,0xEEEC,0xEEEC,0xDDEE,0xEEEE,0xDDEE,
	0xDDDD,0xE6CE,0xEDDD,0xDECE,0x6CED,0xDDE6,0xCC66,0xDDDE,
	0xDEEC,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,

	0xDDDD,0x06DD,0xDDDD,0x06DD,0xDDDD,0x06DD,0xDDDD,0x06DD,
	0xDDDD,0x06DD,0xDDDD,0x06DD,0xDDDD,0x06DD,0xDDDD,0x06DD,
	0x0000,0x2360,0x0000,0x1236,0x0000,0x1136,0x0000,0x1126,
	0x0000,0x2116,0x0000,0x3666,0x0000,0x3666,0x0000,0x3606,
	0x2311,0x1111,0x1231,0xAB11,0x1132,0x77B1,0x1123,0x77A1,
	0x1113,0x7791,0x1113,0x7791,0x1112,0x7791,0x1111,0x79B1,
	0x1111,0x1123,0x1BA9,0xB132,0xB977,0xA131,0xA777,0xA231,
	0x9777,0x932B,0x7777,0x931A,0x7777,0x7319,0x7777,0x72B7,

	0x3221,0x1121,0x3211,0x1212,0x2219,0x3113,0x2197,0x2A13,
	0x1A77,0x1913,0x1977,0xB722,0xB777,0xA721,0xA777,0xBA21,
	0x1222,0x1333,0x2211,0x3321,0x1112,0x3212,0x1213,0x2111,
	0x2222,0x1121,0x3231,0x1222,0x213B,0x3313,0x2F6F,0x3213,
	0x2132,0x3123,0x1222,0x2133,0x1223,0x1232,0x2133,0x1331,
	0x1321,0x1321,0x2111,0x2311,0x1112,0x3211,0x1123,0x3111,
	0x1133,0x0062,0x1233,0x0062,0x1233,0x0611,0x1332,0x0621,
	0x1331,0x0621,0x1331,0x0611,0x1321,0x0661,0x1322,0x0606,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0600,0x77B6,0x0600,0x7760,0x0000,0x7960,0x0000,0x9A60,
	0x0000,0x9B60,0x0000,0x9F00,0x0000,0xA600,0x0000,0xB600,
	0x9B77,0x7777,0x7B77,0x7777,0x7A97,0x7777,0x79A9,0x7777,
	0x79B9,0x7777,0x77F9,0x7777,0xBBA9,0x79AA,0xAA99,0x779A,
	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,

	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x7777,0x9777,0x7777,0xA777,0x7777,0xB977,0x7777,0xFA77,
	0xBFAA,0x2B9A,0xAFB9,0x21B9,0x9AB9,0x121B,0xFBBA,0x6121,
	0xFFFB,0x0611,0xAABF,0x0611,0xA9AF,0x061B,0x979B,0x006B,
	0x0062,0x0000,0x0006,0x0000,0x0006,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0xEE60,0xCEEE,0xEE60,0xCEEE,0xEC60,0xCEEE,0xEC60,0xCEEE,
	0xE600,0xCEEE,0xC600,0xCEEE,0x6600,0xCEEE,0xA600,0xCEC6,
	0xBBEE,0xDDDE,0xCACE,0xDDDD,0xEABE,0xDDDD,0xEABE,0xDDDD,
	0xEAAE,0xEDDE,0xEAAE,0xCEEE,0xC8AC,0xCEEE,0xA8AC,0xBCEC,
	0x886D,0xEE6B,0xA86E,0xEEE6,0xB8BC,0xEEEC,0x6AA6,0xEEEE,
	0x6B86,0xEEEE,0xCB8B,0xCEEE,0xC6AA,0x6EEE,0xCCB8,0xBCEE,
	0xA6CC,0x66A8,0x8BCC,0x6B68,0x8A6C,0x6AAB,0xA8BC,0x6A8B,
	0xA8A6,0xBA8B,0x688B,0xB88B,0x6A8A,0xA886,0x6B88,0x88A6,

	0xC666,0xEECC,0xCCC6,0xEEEE,0xECCC,0xEEEE,0xECCC,0xEEEE,
	0xEECC,0xEEEE,0xEEC6,0xEEEE,0xEECB,0xEEEE,0xEE6A,0xEEEE,
	0x6CEE,0xABF6,0xEEEE,0x66EE,0xEEEE,0xEEDE,0xEEEE,0xDDDD,
	0xDEEE,0xDDDD,0xDEEE,0xDDDD,0xDDEE,0xDDDD,0xDDDE,0xDDDD,
	0xAAAA,0xFBBA,0x6666,0xCC66,0xEEEE,0xCEEE,0xDDDD,0xEDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,
	0x66CC,0x6666,0xCCCC,0x6CCC,0xCCCC,0xCCCC,0xCCCC,0xCCCC,
	0xCCCE,0xCCCC,0xCEED,0xCCCC,0xEEED,0x6CEE,0xCEED,0xAB66,

	0x6666,0xFAF6,0x6666,0xFAF6,0x6666,0xFAF6,0x6666,0xFABF,
	0x666C,0xFBAF,0xB66C,0xFFAF,0xFABB,0xFFAB,0xF88A,0xFFBA,
	0x88AF,0xCCC6,0x88BF,0xECC6,0x88FF,0xEECB,0x88FB,0xEECB,
	0x88FA,0xEECA,0x8AFA,0xEE6A,0x8AFA,0xEE68,0x8BFA,0xEE68,
	0xEEEC,0xB6CC,0xEEEE,0xCEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,
	0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,
	0x888A,0xECB8,0x88B6,0xE6A8,0xA6CE,0xCB88,0xCEEE,0x6A8A,
	0xEEEE,0xB88C,0xEEEE,0xA8BE,0xEEEE,0x8A6E,0xEEEE,0x8BCE,

	0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,0xEEEE,
	0xEEEE,0xCEEE,0xEEEE,0xBEEE,0xEEEC,0x6EEE,0xEEEC,0xCEEE,
	0xCCCC,0xECCC,0xCCCE,0xECCC,0xCCCE,0xEECC,0xCCEE,0xEECC,
	0xCCEE,0xEECC,0xCCCB,0xEECC,0xCCBA,0xEECC,0xCCAB,0xEECC,
	0xEEEE,0xDDDD,0xDEEE,0xDDDD,0xDEEE,0xDDDD,0xDEEE,0xDDDD,
	0xDEEE,0xDDDD,0xDEEE,0xDDDD,0xDEEE,0xDDDD,0xDEEE,0xDDDD,
	0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xDDDD,0xEEDD,
	0xDDDD,0xBCCD,0xEDDD,0x88BC,0xCEDD,0xB88B,0xA6ED,0xC6A8,

	0xDDDD,0x06DD,0xDDDD,0x06ED,0xEEED,0x06CC,0xB6CC,0x06AB,
	0x888A,0x06AA,0x6BB8,0x06CC,0xDDC6,0x06CD,0xDDDD,0x006D,
	0x0000,0x3606,0x0000,0x3600,0x0000,0x2600,0x0000,0x6600,
	0x0000,0x6000,0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,
	0x1121,0xBFB1,0x1121,0xFAA1,0x2126,0xFFF1,0x2160,0x66B1,
	0x2160,0x54B1,0x2160,0x5BA1,0x1160,0x9991,0x6600,0x77A6,
	0x7779,0x71A7,0x77AF,0x7197,0x7AF6,0x9B77,0x9666,0xBA77,
	0xA646,0x7777,0xAF55,0x7777,0xABAA,0x7777,0xAB97,0x7777,

	0xA977,0xF66B,0x6BA9,0xBBB6,0xB66B,0x66FF,0xFBF6,0x5664,
	0x7BAA,0x5555,0x9997,0xABBA,0x7777,0x7777,0x7777,0x7777,
	0x9B6B,0x32B3,0xAAAA,0x3192,0xABFF,0x2B71,0x9A74,0x1A7B,
	0x99A7,0xB97A,0x7779,0xA777,0x7777,0x9777,0x7777,0x7777,
	0x2223,0x2111,0x1223,0x1111,0xA123,0x1A99,0x9A23,0xB9BB,
	0xB913,0xA7BF,0xFAB2,0xA7AB,0xFBA1,0xB9BF,0xFFAB,0x1A9B,
	0x1313,0x0606,0x1311,0x0006,0x1311,0x0006,0x6211,0x0000,
	0x6111,0x0000,0x0621,0x0000,0x0622,0x0000,0x0062,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x6000,0x0000,0xB600,0x0000,0x8B66,0x6666,0x8A6B,
	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xB996,0x99AF,0x99A6,0x7799,
	0x99BF,0x7999,0x9A6F,0xABB9,0x9B66,0x9999,0x9F66,0x9999,
	0x7777,0x7777,0x7777,0x7777,0xAFBA,0x7779,0x9977,0x7779,
	0x7777,0x7777,0x7779,0x7777,0x7779,0x7777,0x7777,0x9777,

	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,
	0x777A,0x006A,0x7779,0x006A,0x7777,0x006A,0xA977,0x006A,
	0xFFBB,0x666F,0xBBBF,0x88AA,0x8888,0x8888,0xBBAA,0xC66B,
	0x0000,0x0000,0x0000,0x6000,0x0000,0xB660,0x6660,0x8AB6,
	0x8AB6,0xA888,0x8888,0xC6BA,0x6BAA,0xDDEC,0xDECC,0x6CCE,
	0x0000,0x0000,0x0006,0x0000,0x006A,0x0000,0x006A,0x0000,
	0x0066,0x0000,0x06EE,0x0000,0x66CE,0x0000,0x6666,0x6666,
};

const unsigned short ZelgiusPortraitPal[16] __attribute__((aligned(4)))=
{
	0x4F34,0x34C6,0x4966,0x6209,0x7314,0x22A6,0x2087,0x6BFF,
	0x13BF,0x433F,0x227D,0x25D3,0x0CF3,0x195F,0x151A,0x252C,
};

const unsigned short ZelgiusPortraitMini[242] __attribute__((aligned(4)))=
{
	0x0010,0x0002,0x002A,0xE000,0x6001,0x1300,0x0066,0x3206,
	0x0000,0x2600,0x0023,0x6660,0x0066,0x2660,0x3333,0x2316,
	0x3321,0x2600,0x3331,0x1133,0x3111,0x0033,0x3331,0x3213,
	0x2312,0x2133,0x1100,0x2131,0x6613,0x0006,0x0000,0x6122,
	0x0066,0x3333,0x6612,0x3240,0x0400,0x3323,0x3333,0x3233,
	0x008F,0x2301,0x2323,0x0600,0x4300,0x6170,0x2A00,0x002A,
	0x0062,0x2370,0x3300,0x0013,0x2108,0x2140,0x1110,0x1136,
	0x6000,0x1313,0x0082,0x1203,0x6000,0x1126,0x0F20,0x2800,

	0x1236,0x7B00,0x0026,0x208A,0x2111,0x1100,0xA132,0xB31A,
	0x7A31,0x00A7,0x19A3,0x7779,0x1791,0x777B,0x7B00,0xFAA7,
	0x797A,0x6B6A,0x0096,0xFFB7,0xA59A,0x9977,0x3321,0x2300,
	0x1232,0x3221,0x1321,0x0012,0x1321,0x23B3,0x2111,0x21B2,
	0x3100,0xBB11,0x392A,0xA612,0x0197,0x9217,0x7795,0xF2A7,
	0x0031,0x0463,0x1213,0x0062,0x0013,0x1170,0x0013,0x0066,
	0x1212,0x0060,0x6111,0x0017,0xBB00,0x0300,0x10AA,0x308C,
	0xF0EF,0x8001,0xF800,0x0000,0x88B6,0xA77A,0x0277,0x7677,

	0x7797,0x9677,0x0300,0x90A6,0x0700,0x7760,0x0300,0x7779,
	0x6677,0x9B04,0xBA9A,0x96FB,0x0C00,0x7777,0xFA50,0x1200,
	0x00AB,0xFB16,0x7777,0x8097,0x0700,0x99B7,0x7777,0x79A9,
	0x0077,0x9A97,0x77B7,0xFBA9,0x198B,0x01BD,0x2B1F,0x2301,
	0xF710,0x7600,0x0321,0x0106,0x005E,0x666B,0x068B,0x8888,
	0x6ECA,0x6600,0x8F66,0x88CB,0x8FB8,0x00EC,0xFCB8,0xEEA8,
	0xFCA8,0xCEB8,0x8600,0x68FC,0x8C6C,0x68F6,0x00E6,0x6A8C,
	0xEC68,0x686C,0xCD68,0xCC00,0x79B6,0xCE77,0x796C,0x0097,

	0x6CCC,0xFF66,0x6666,0xBBF6,0x8C00,0xAEDE,0xBE68,0xB8BA,
	0x00DC,0xB8EC,0xDDCE,0xB8C8,0xDCAC,0x9700,0x88BA,0xBBBA,
	0xB8F9,0x00DC,0xFA9A,0xDEB8,0xFBBB,0xDEB8,0xDE00,0xBAFC,
	0xDDEE,0x8AEE,0x00BE,0xEEDD,0xAC8B,0xEEDD,0x8BAF,0xCC00,
	0x6CDC,0xCD66,0x888B,0x0088,0xB88E,0xEC66,0xEB8B,0xDDCE,
	0xA800,0xDCEE,0xB8CD,0x6CEE,0x00EC,0xC6EB,0xEEEC,0xCEC6,
	0xDEEE,0x0E0E,
};

const unsigned short ZelgiusMouthFrame[128 * 6] __attribute__((aligned(4)))=
{
	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xF996,0xBBBB,0xA9A6,0xAAAF,
	0x99BF,0xBBBA,0x9A6F,0x7999,0x9B66,0xABB9,0x9F66,0x9999,
	0x7777,0x7777,0x9977,0x7777,0xAFBB,0x7777,0x9ABA,0x7777,
	0x779B,0x7777,0x7777,0x7777,0x7779,0x7777,0x7779,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x9999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,

	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xF996,0xBBBB,0xA9A6,0xAABB,
	0x99BF,0x7999,0x9A6F,0xABB9,0x9B66,0x9999,0x9F66,0x9999,
	0x7777,0x7777,0x9977,0x7777,0xAFBB,0x7779,0x9ABA,0x7777,
	0x7777,0x7777,0x7779,0x7777,0x7779,0x7777,0x7777,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x7999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,

	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xF996,0x999B,0x99A6,0x7799,
	0x99BF,0x7999,0x9A6F,0xABB9,0x9B66,0x9999,0x9F66,0x9999,
	0x7777,0x7777,0xA977,0x7779,0xAFBA,0x7777,0x7777,0x7777,
	0x7777,0x7777,0x7779,0x7777,0x7779,0x7777,0x7777,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x7999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,

	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xB996,0xBBFF,0xF9A6,0xAAAF,
	0xA9BF,0xBBBB,0x9A6F,0x7999,0x9B66,0xABB9,0x9F66,0x9999,
	0x7777,0x7777,0x7777,0x7777,0x9ABB,0x7777,0x9FAA,0x7777,
	0x7ABB,0x7777,0x7777,0x7777,0x7779,0x7777,0x7779,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x9999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,

	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xF996,0xBBBB,0xB9A6,0xAAAF,
	0x99BF,0x7999,0x9A6F,0xABB9,0x9B66,0x9999,0x9F66,0x9999,
	0x7777,0x7777,0x7777,0x7777,0xAFBB,0x7779,0x9BBA,0x7777,
	0x7777,0x7777,0x7779,0x7777,0x7779,0x7777,0x7777,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x7999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,

	0x0000,0x6000,0x0000,0x6000,0x0000,0x0000,0x6000,0x6666,
	0xB666,0xBAAA,0x888A,0xFBBA,0xBA88,0x6C66,0xCCBA,0xCCCC,
	0x999A,0x7799,0x999B,0x7779,0xB996,0x99AF,0x99A6,0x7799,
	0x99BF,0x7999,0x9A6F,0xABB9,0x9B66,0x9999,0x9F66,0x9999,
	0x7777,0x7777,0x7777,0x7777,0xAFBA,0x7779,0x9977,0x7779,
	0x7777,0x7777,0x7779,0x7777,0x7779,0x7777,0x7777,0x9777,
	0x7777,0xFB97,0x7777,0xAFA7,0x7777,0x9AF9,0x9777,0x99AB,
	0xB977,0xA99A,0xAB97,0xFFBA,0xAAB9,0x888F,0xB9AB,0x888F,

	0xEECB,0xCCCE,0xEEC6,0xCCEE,0xEEE6,0xCCCE,0xEEE6,0xCCCE,
	0xEEEC,0xCCCE,0xCEEC,0x6666,0x6CEC,0xBA6C,0xC6CC,0x99CC,
	0xA66C,0x7999,0xB6CC,0x7999,0x66CC,0x79AB,0x66CC,0x6666,
	0x6666,0xFFFF,0x6666,0xFF66,0xCCC6,0x666C,0xDDEC,0x6CED,
	0x7777,0xBA97,0x9777,0xBFBA,0xBA97,0xABFF,0xFFFF,0x9AAB,
	0xAABF,0xBAAA,0xBBBB,0xBBBB,0x66B6,0x6666,0x6B89,0xDEEC,
	0xB99B,0xA88B,0xF99A,0xB88B,0xFA99,0xB88B,0xFBA9,0xB88B,
	0xFBFB,0xB88B,0xFBBB,0xB886,0xBFF6,0xB886,0x66CE,0xB8A6,
};

const unsigned short ZelgiusEyeFrame[192] __attribute__((aligned(4)))=
{
	0x1121,0xBFB1,0x1121,0xFAA1,0x2126,0xFFF1,0x2160,0x66B1,
	0x2160,0x54B1,0x2160,0x3BA1,0x1160,0x9991,0x6600,0x77A6,
	0x7779,0x71A7,0x77AF,0x7197,0x7AF6,0x9B77,0x9666,0xBA77,
	0xA646,0x7777,0xAF35,0x7777,0xABAA,0x7777,0xAB97,0x7777,
	0xA977,0xF66B,0x6BA9,0xBBB6,0xB66B,0x66FF,0xFBF6,0x5667,
	0x7BAA,0x3553,0x9997,0xABBA,0x7777,0x7777,0x7777,0x7777,
	0x9B6B,0x32B3,0xAAAA,0x3192,0x9BFF,0x2B71,0x9774,0x1A7B,
	0x7777,0xB979,0x7779,0xA777,0x7777,0x9777,0x7777,0x7777,

	0x1121,0xBFB1,0x1121,0xFBA1,0x2126,0xBAB1,0x2160,0xFFF1,
	0x2160,0x54B1,0x2160,0x5BA1,0x1160,0x9991,0x6600,0x77A6,
	0x7779,0x71A7,0x77AF,0x7197,0x7AF6,0x9B77,0x96BF,0xBA77,
	0xA6FF,0x7777,0xAF36,0x7777,0xABAA,0x7777,0xAB97,0x7777,
	0xA977,0xF66B,0x6BA9,0xABB6,0xB66B,0x9AAB,0xFBF6,0x66FF,
	0x7BAA,0x3553,0x9997,0xABBA,0x7777,0x7777,0x7777,0x7777,
	0x9B6B,0x32B3,0xAAAA,0x3192,0x9A99,0x2B71,0x9BFF,0x1A7B,
	0x7777,0xB979,0x7779,0xA777,0x7777,0x9777,0x7777,0x7777,

	0x1121,0xBFB1,0x1121,0xFBA1,0x2126,0xBAA1,0x2160,0x99A1,
	0x2160,0xAAB1,0x2160,0x6FB1,0x1160,0x9991,0x6600,0x77A6,
	0x7779,0x71A7,0x77AF,0x7197,0x7AF6,0x9B77,0x96BA,0xBA77,
	0xA6AA,0x7777,0xAFBF,0x7777,0xABAA,0x7777,0xAB97,0x7777,
	0xA977,0xF66B,0x6BA9,0xABB6,0xB66B,0x9AAB,0x9AF6,0x7779,
	0xABAA,0xBA99,0xBA97,0xF6FF,0x7777,0x7777,0x7777,0x7777,
	0x9B6B,0x32B3,0xAAAA,0x3192,0x9A99,0x2B71,0x9AA9,0x1A7B,
	0x79BF,0xB979,0x779B,0xA777,0x7777,0x9777,0x7777,0x7777,
};

const s16 ZelgiusEyeFrameTemplate[1][4] =
{
	{getTileNo(18,3),getTileNo(19,3),getTileNo(20,3),getTileNo(21,3)}
};

const struct EyeFrameInfo ZelgiusEyeFrameInfo =
{
	4,1,
	2,1,
	{ZelgiusEyeFrame,&ZelgiusEyeFrame[16 * 4 * 1],&ZelgiusEyeFrame[16 * 4 * 1 * 2]},
	ZelgiusEyeFrameTemplate
};