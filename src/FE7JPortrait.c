// by laqieer
// 2017/3/29
// 新自由头像系统

#include "FE7JPortrait.h"

// 眨眼/使眼色的函数指针表
const PTRFUN blinkOrWink[3] = 
{
	blinkOrWink0,
	blinkOrWink1,
	blinkOrWink2
};

// 大头像精灵组合模板

// 新模板，头像在右侧，面向左侧 (横式)
const u16 newPortraitTemplateLeftH[1 + 3 * 10] =
{
	10,	// 精灵数量
	// 每个精灵3个word
	0x4000, 0xC1E0, 0,
	0x4020, 0xC1E0, 8,
	0x4040, 0x81E0, 0x10,
	0x4040, 0x8000, 0x50,
	0x8030, 0x81D0, 0x14,
	0x8030, 0x8020, 0x16,
	0x8010, 0x81D0, 0x18,
	0x8010, 0x8020, 0x1A,
	0, 0x41D0, 0x5C,
	0, 0X4020, 0X5E
};

// 新模板，头像在左侧，面向右侧 (横式)
const u16 newPortraitTemplateRightH[1 + 3 * 10] =
{
	10,
	0x4000, 0xD1E0, 0,
	0x4020, 0xD1E0, 8,
	0x4040, 0x91E0, 0x50,
	0x4040, 0x9000, 0x10,
	0x8030, 0x91D0, 0x16,
	0x8030, 0x9020, 0x14,
	0x8010, 0x91D0, 0x1A,
	0x8010, 0x9020, 0x18,
	0, 0x51D0, 0x5E,
	0, 0X5020, 0X5C
};

// 新模板，头像在左侧，面向右侧 (立式)
const u16 newPortraitTemplateRightV[1 + 3 * 7] =
{
	7,	// 精灵数量
	// 每个精灵3个word (3个OAM属性，求或的基础值)
	getObjectAttribute1(1,-16), getObjectAttribute2(3,1,40 - 64), getObjectAttribute3(0),											// 1
	getObjectAttribute1(2,-16), getObjectAttribute2(2,1,-40), getObjectAttribute3(8),										// 2
	getObjectAttribute1(1,16), getObjectAttribute2(3,1,40 - 64), getObjectAttribute3(8 + 2),										// 3
	getObjectAttribute1(2,16), getObjectAttribute2(2,1,-40), getObjectAttribute3(8 + 2 + 8),								// 4
	getObjectAttribute1(1,16 + 32), getObjectAttribute2(3,1,40 - 64), getObjectAttribute3(8 + 2 + 8 + 2),							// 5
	getObjectAttribute1(0,16 + 32), getObjectAttribute2(1,1,-40), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2),			// 6
	getObjectAttribute1(0,16 + 32 + 16), getObjectAttribute2(1,1,-40), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2 + 2)	// 7

};

// 新模板，头像在右侧，面向左侧 (立式)
const u16 newPortraitTemplateLeftV[1 + 3 * 7] =
{
	7,
	getObjectAttribute1(1,-16), getObjectAttribute2(3,0,-40), getObjectAttribute3(0),											// 1
	getObjectAttribute1(2,-16), getObjectAttribute2(2,0,40 - 16), getObjectAttribute3(8),										// 2
	getObjectAttribute1(1,16), getObjectAttribute2(3,0,-40), getObjectAttribute3(8 + 2),										// 3
	getObjectAttribute1(2,16), getObjectAttribute2(2,0,40 - 16), getObjectAttribute3(8 + 2 + 8),								// 4
	getObjectAttribute1(1,16 + 32), getObjectAttribute2(3,0,-40), getObjectAttribute3(8 + 2 + 8 + 2),							// 5
	getObjectAttribute1(0,16 + 32), getObjectAttribute2(1,0,40 - 16), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2),			// 6
	getObjectAttribute1(0,16 + 32 + 16), getObjectAttribute2(1,0,40 - 16), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2 + 2)	// 7
};

// 幼女琪琪对话头像模板(左侧)
const u16 TikiPortraitTemplateLeft[1 + 3 * 13] =
{
	13,
	getObjectAttribute1(1,-2 * 8),	getObjectAttribute2(2,0,-3 * 8),	getObjectAttribute3(27 + 32 * 2),
	getObjectAttribute1(2,-2 * 8),	getObjectAttribute2(0,0,1 * 8),		getObjectAttribute3(31 + 32 * 2),
	getObjectAttribute1(1,0),		getObjectAttribute2(3,0,-6 * 8),	getObjectAttribute3(0),
	getObjectAttribute1(2,0),		getObjectAttribute2(2,0,2 * 8),		getObjectAttribute3(8),
	getObjectAttribute1(0,2 * 8 + 4),getObjectAttribute2(0,0,4 * 8),	getObjectAttribute3(27),
	getObjectAttribute1(1,4 * 8),	getObjectAttribute2(3,0,-6 * 8),	getObjectAttribute3(10),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(2,0,2 * 8),		getObjectAttribute3(18),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(1,0,4 * 8),		getObjectAttribute3(20),
	getObjectAttribute1(0,7 * 8),	getObjectAttribute2(0,0,5 * 8),		getObjectAttribute3(27 + 32 * 1),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,0,-5 * 8),	getObjectAttribute3(21),
	getObjectAttribute1(0,8 * 8),	getObjectAttribute2(1,0,-1 * 8),	getObjectAttribute3(25),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,0,1 * 8),		getObjectAttribute3(21 + 32 * 2),
	getObjectAttribute1(0,8 * 8),	getObjectAttribute2(1,0,5 * 8),		getObjectAttribute3(25 + 32 * 2)
};

// 幼女琪琪对话头像模板(右侧)
const u16 TikiPortraitTemplateRight[1 + 3 * 13] =
{
	13,
	getObjectAttribute1(1,-2 * 8),	getObjectAttribute2(2,1,-1 * 8),	getObjectAttribute3(27 + 32 * 2),
	getObjectAttribute1(2,-2 * 8),	getObjectAttribute2(0,1,-2 * 8),	getObjectAttribute3(31 + 32 * 2),
	getObjectAttribute1(1,0),		getObjectAttribute2(3,1,-2 * 8),	getObjectAttribute3(0),
	getObjectAttribute1(2,0),		getObjectAttribute2(2,1,-4 * 8),	getObjectAttribute3(8),
	getObjectAttribute1(0,2 * 8 + 4),getObjectAttribute2(0,1,-5 * 8),	getObjectAttribute3(27),
	getObjectAttribute1(1,4 * 8),	getObjectAttribute2(3,1,-2 * 8),	getObjectAttribute3(10),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(2,1,-4 * 8),	getObjectAttribute3(18),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(1,1,-5 * 8),	getObjectAttribute3(20),
	getObjectAttribute1(0,7 * 8),	getObjectAttribute2(0,1,-6 * 8),	getObjectAttribute3(27 + 32 * 1),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,1,1 * 8),		getObjectAttribute3(21),
	getObjectAttribute1(0,8 * 8),	getObjectAttribute2(1,1,-1 * 8),	getObjectAttribute3(25),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,1,-5 * 8),	getObjectAttribute3(21 + 32 * 2),
	getObjectAttribute1(0,8 * 8),	getObjectAttribute2(1,1,-7 * 8),	getObjectAttribute3(25 + 32 * 2)
};

// 夏隆对话头像模板(左)
const u16 SharonPortraitTemplateLeft[1 + 3 * 16] =
{
	16,
	getObjectAttribute1(1,0),		getObjectAttribute2(3,0,-5 * 8),	getObjectAttribute3(0),
	getObjectAttribute1(1,4 * 8),	getObjectAttribute2(2,0,-5 * 8),	getObjectAttribute3(8),
	getObjectAttribute1(1,4 * 8),	getObjectAttribute2(2,0,-1 * 8),	getObjectAttribute3(12),
	getObjectAttribute1(1,6 * 8),	getObjectAttribute2(2,0,-4 * 8),	getObjectAttribute3(8 + 32 * 2),
	getObjectAttribute1(1,6 * 8),	getObjectAttribute2(2,0,0),			getObjectAttribute3(12 + 32 * 2),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,0,-7 * 8),	getObjectAttribute3(16),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,0,-3 * 8),	getObjectAttribute3(20),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,0,1 * 8),		getObjectAttribute3(16 + 32 * 2),
	getObjectAttribute1(1,9 * 8),	getObjectAttribute2(0,0,5 * 8),		getObjectAttribute3(20 + 32 * 2),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(2,0,4 * 8),		getObjectAttribute3(24),
	getObjectAttribute1(2,3 * 8),	getObjectAttribute2(2,0,6 * 8),		getObjectAttribute3(26),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(0,0,3 * 8),		getObjectAttribute3(23 + 32 * 2),
	getObjectAttribute1(0,3 * 8),	getObjectAttribute2(0,0,4 * 8),		getObjectAttribute3(20 + 32 * 3),
	getObjectAttribute1(0,8 * 8),	getObjectAttribute2(0,0,5 * 8),		getObjectAttribute3(22 + 32 * 3),
	getObjectAttribute1(0,9 * 8),	getObjectAttribute2(0,0,-8 * 8),	getObjectAttribute3(21 + 32 * 3),
	getObjectAttribute1(0,9 * 8),	getObjectAttribute2(0,0,7 * 8),		getObjectAttribute3(22 + 32 * 2)
};

// 夏隆对话头像模板(右)
const u16 SharonPortraitTemplateRight[1 + 3 * 16] =
{
	16,
	getObjectAttribute1(1,0),		getObjectAttribute2(3,1,-3 * 8),	getObjectAttribute3(0),
	getObjectAttribute1(1,4 * 8),	getObjectAttribute2(2,1,1 * 8),		getObjectAttribute3(8),
	getObjectAttribute1(1,4 * 8),	getObjectAttribute2(2,1,-3 * 8),	getObjectAttribute3(12),
	getObjectAttribute1(1,6 * 8),	getObjectAttribute2(2,1,0),			getObjectAttribute3(8 + 32 * 2),
	getObjectAttribute1(1,6 * 8),	getObjectAttribute2(2,1,-4 * 8),	getObjectAttribute3(12 + 32 * 2),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,1,3 * 8),		getObjectAttribute3(16),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,1,-1 * 8),	getObjectAttribute3(20),
	getObjectAttribute1(1,8 * 8),	getObjectAttribute2(2,1,-5 * 8),	getObjectAttribute3(16 + 32 * 2),
	getObjectAttribute1(1,9 * 8),	getObjectAttribute2(0,1,-7 * 8),	getObjectAttribute3(20 + 32 * 2),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(2,1,-6 * 8),	getObjectAttribute3(24),
	getObjectAttribute1(2,3 * 8),	getObjectAttribute2(2,1,-8 * 8),	getObjectAttribute3(26),
	getObjectAttribute1(2,4 * 8),	getObjectAttribute2(0,1,-4 * 8),	getObjectAttribute3(23 + 32 * 2),
	getObjectAttribute1(0,3 * 8),	getObjectAttribute2(0,1,-5 * 8),	getObjectAttribute3(20 + 32 * 3),
	getObjectAttribute1(0,8 * 8),	getObjectAttribute2(0,1,-6 * 8),	getObjectAttribute3(22 + 32 * 3),
	getObjectAttribute1(0,9 * 8),	getObjectAttribute2(0,1,7 * 8),		getObjectAttribute3(21 + 32 * 3),
	getObjectAttribute1(0,9 * 8),	getObjectAttribute2(0,1,-8 * 8),	getObjectAttribute3(22 + 32 * 2)
};

// 成年琪琪对话头像模板(左)
const u16 TikiFPortraitTemplateLeft[1 + 3 * 9] =
{
	9,
	getObjectAttribute1(0,-2 * 8),getObjectAttribute2(2,0,-4 * 8),getObjectAttribute3(0),
	getObjectAttribute1(2,-2 * 8),getObjectAttribute2(2,0,0),getObjectAttribute3(4),
	getObjectAttribute1(1,2 * 8),getObjectAttribute2(3,0,-6 * 8),getObjectAttribute3(6),
	getObjectAttribute1(2,2 * 8),getObjectAttribute2(2,0,2 * 8),getObjectAttribute3(14),
	getObjectAttribute1(2,2 * 8),getObjectAttribute2(1,0,4 * 8),getObjectAttribute3(16),
	getObjectAttribute1(1,6 * 8),getObjectAttribute2(3,0,-6 * 8),getObjectAttribute3(17),
	getObjectAttribute1(0,6 * 8),getObjectAttribute2(1,0,2 * 8),getObjectAttribute3(25),
	getObjectAttribute1(0,6 * 8),getObjectAttribute2(1,0,4 * 8),getObjectAttribute3(25 + 32 * 2),
	getObjectAttribute1(1,8 * 8),getObjectAttribute2(2,0,2 * 8),getObjectAttribute3(28 + 32 * 2)
};

// 成年琪琪对话头像模板(右)
const u16 TikiFPortraitTemplateRight[1 + 3 * 9] =
{
	9,
	getObjectAttribute1(0,-2 * 8),getObjectAttribute2(2,1,0),getObjectAttribute3(0),
	getObjectAttribute1(2,-2 * 8),getObjectAttribute2(2,1,-2 * 8),getObjectAttribute3(4),
	getObjectAttribute1(1,2 * 8),getObjectAttribute2(3,1,-2 * 8),getObjectAttribute3(6),
	getObjectAttribute1(2,2 * 8),getObjectAttribute2(2,1,-4 * 8),getObjectAttribute3(14),
	getObjectAttribute1(2,2 * 8),getObjectAttribute2(1,1,-5 * 8),getObjectAttribute3(16),
	getObjectAttribute1(1,6 * 8),getObjectAttribute2(3,1,-2 * 8),getObjectAttribute3(17),
	getObjectAttribute1(0,6 * 8),getObjectAttribute2(1,1,-4 * 8),getObjectAttribute3(25),
	getObjectAttribute1(0,6 * 8),getObjectAttribute2(1,1,-6 * 8),getObjectAttribute3(25 + 32 * 2),
	getObjectAttribute1(1,8 * 8),getObjectAttribute2(2,1,-6 * 8),getObjectAttribute3(28 + 32 * 2)
};

// 模板组表
const u32 portraitTemplatePairTable[][2] =
{
		{oldPortraitTemplate1Left, oldPortraitTemplate1Right},
		{oldPortraitTemplate2Left, oldPortraitTemplate2Right},
		{oldPortraitTemplate3Left, oldPortraitTemplate3Right},
		{oldPortraitTemplate4Left, oldPortraitTemplate4Right},
		{newPortraitTemplateLeftH, newPortraitTemplateRightH},
		{newPortraitTemplateLeftV, newPortraitTemplateRightV},
		{TikiPortraitTemplateLeft, TikiPortraitTemplateRight},
		{SharonPortraitTemplateLeft,SharonPortraitTemplateRight},
		{TikiFPortraitTemplateLeft,TikiFPortraitTemplateRight}
};

// 人物详细界面头像框内TSA模板

// 新模板，x=0,y=0 (横式)
const u16 newPortraitInBoxTemplateH[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	0x55, 0x10, 0x11, 0x12, 0x13, 0x50, 0x51, 0x52, 0x53, 0x56,
	0x35, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x36,
	0x15, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x16,
	0x79, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x7A,
	0x59, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x5A,
	0x39, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x3A,
	0x19, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x1A,
	0x7D, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x7E,
	0x5D, 0, 1, 2, 3, 4, 5, 6, 7, 0x5E,
	0
};

// 新模板，x=-1,y=0 (横式)
const u16 newPortraitInBoxTemplateLH[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	0x10, 0x11, 0x12, 0x13, 0x50, 0x51, 0x52, 0x53, 0x56, 0x57,
	0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x36, 0x37,
	0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x16, 0x17,
	0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x7A, 0x7B,
	8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x5A, 0x5B,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x3A, 0x3B,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x1A, 0x1B,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x7E, 0x7F,
	0, 1, 2, 3, 4, 5, 6, 7, 0x5E, 0x5F,
	0
};

// 新模板，x=1,y=0 (横式)
const u16 newPortraitInBoxTemplateRH[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	0x54, 0x55, 0x10, 0x11, 0x12, 0x13, 0x50, 0x51, 0x52, 0x53,
	0x34, 0x35, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
	0x14, 0x15, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	0x78, 0x79, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	0x58, 0x59, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
	0x38, 0x39, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x18, 0x19, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x7C, 0x7D, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x5C, 0x5D, 0, 1, 2, 3, 4, 5, 6, 7,
	0
};

// 新模板，x=0,y=-1 (横式)
const u16 newPortraitInBoxTemplateUH[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	0x75, 0x30, 0x31, 0x32, 0x33, 0x70, 0x71, 0x72, 0x73, 0x76,
	0x55, 0x10, 0x11, 0x12, 0x13, 0x50, 0x51, 0x52, 0x53, 0x56,
	0x35, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x36,
	0x15, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x16,
	0x79, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x7A,
	0x59, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x5A,
	0x39, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x3A,
	0x19, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x1A,
	0x7D, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x7E,
	0
};

// 新模板，x=-1,y=-1 (横式)
const u16 newPortraitInBoxTemplateLUH[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	0x30, 0x31, 0x32, 0x33, 0x70, 0x71, 0x72, 0x73, 0x76, 0x77,
	0x10, 0x11, 0x12, 0x13, 0x50, 0x51, 0x52, 0x53, 0x56, 0x57,
	0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x36, 0x37,
	0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x16, 0x17,
	0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x7A, 0x7B,
	8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x5A, 0x5B,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x3A, 0x3B,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x1A, 0x1B,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x7E, 0x7F,
	0
};

// 新模板，x=1,y=-1 (横式)
const u16 newPortraitInBoxTemplateRUH[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	0x74, 0x75, 0x30, 0x31, 0x32, 0x33, 0x70, 0x71, 0x72, 0x73,
	0x54, 0x55, 0x10, 0x11, 0x12, 0x13, 0x50, 0x51, 0x52, 0x53,
	0x34, 0x35, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
	0x14, 0x15, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	0x78, 0x79, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	0x58, 0x59, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
	0x38, 0x39, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x18, 0x19, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x7C, 0x7D, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0
};

// 新模板，y=0 (立式)
const u16 newPortraitInBoxTemplateV[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	getTileNo(20,3), getTileNo(21,3), getTileNo(22,3), getTileNo(23,3), getTileNo(24,3), getTileNo(25,3), getTileNo(26,3), getTileNo(27,3), getTileNo(30,3), getTileNo(31,3),
	getTileNo(20,2), getTileNo(21,2), getTileNo(22,2), getTileNo(23,2), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(30,2), getTileNo(31,2),
	getTileNo(20,1), getTileNo(21,1), getTileNo(22,1), getTileNo(23,1), getTileNo(24,1), getTileNo(25,1), getTileNo(26,1), getTileNo(27,1), getTileNo(28,3), getTileNo(29,3),
	getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0), getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(28,2), getTileNo(29,2),
	getTileNo(10,3), getTileNo(11,3), getTileNo(12,3), getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3),
	getTileNo(10,2), getTileNo(11,2), getTileNo(12,2), getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2),
	getTileNo(10,1), getTileNo(11,1), getTileNo(12,1), getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1),
	getTileNo(10,0), getTileNo(11,0), getTileNo(12,0), getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3),
	0
};

// 新模板，y=-1 (立式)
const u16 newPortraitInBoxTemplateUV[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	getTileNo(20,2), getTileNo(21,2), getTileNo(22,2), getTileNo(23,2), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(30,2), getTileNo(31,2),
	getTileNo(20,1), getTileNo(21,1), getTileNo(22,1), getTileNo(23,1), getTileNo(24,1), getTileNo(25,1), getTileNo(26,1), getTileNo(27,1), getTileNo(28,3), getTileNo(29,3),
	getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0), getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(28,2), getTileNo(29,2),
	getTileNo(10,3), getTileNo(11,3), getTileNo(12,3), getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3),
	getTileNo(10,2), getTileNo(11,2), getTileNo(12,2), getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2),
	getTileNo(10,1), getTileNo(11,1), getTileNo(12,1), getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1),
	getTileNo(10,0), getTileNo(11,0), getTileNo(12,0), getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3),
	getTileNo(0,2), getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2),
	0
};

// 新模板，y=-2 (立式)
const u16 newPortraitInBoxTemplateUUV[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	getTileNo(20,1), getTileNo(21,1), getTileNo(22,1), getTileNo(23,1), getTileNo(24,1), getTileNo(25,1), getTileNo(26,1), getTileNo(27,1), getTileNo(28,3), getTileNo(29,3),
	getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0), getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(28,2), getTileNo(29,2),
	getTileNo(10,3), getTileNo(11,3), getTileNo(12,3), getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3),
	getTileNo(10,2), getTileNo(11,2), getTileNo(12,2), getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2),
	getTileNo(10,1), getTileNo(11,1), getTileNo(12,1), getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1),
	getTileNo(10,0), getTileNo(11,0), getTileNo(12,0), getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3),
	getTileNo(0,2), getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2),
	getTileNo(0,1), getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1),
	0
};

// 新模板，y=-3 (立式)
const u16 newPortraitInBoxTemplateUUUV[1 + 10 * 9 + 1] =
{
	0x809, // 宽度9+1,高度8+1
	getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0), getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(28,2), getTileNo(29,2),
	getTileNo(10,3), getTileNo(11,3), getTileNo(12,3), getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3),
	getTileNo(10,2), getTileNo(11,2), getTileNo(12,2), getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2),
	getTileNo(10,1), getTileNo(11,1), getTileNo(12,1), getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1),
	getTileNo(10,0), getTileNo(11,0), getTileNo(12,0), getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3),
	getTileNo(0,2), getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2),
	getTileNo(0,1), getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1),
	getTileNo(0,0), getTileNo(1,0), getTileNo(2,0), getTileNo(3,0), getTileNo(4,0), getTileNo(5,0), getTileNo(6,0), getTileNo(7,0), getTileNo(8,0), getTileNo(9,0),
	0
};

// 幼女琪琪头像框模板
const u16 TikiPortraitInBoxTemplate[1 + 10 * 9 + 1] =
{
	0x809,
	getTileNo(10,3),getTileNo(11,3),getTileNo(12,3),getTileNo(13,3),getTileNo(14,3),getTileNo(15,3),getTileNo(16,3),getTileNo(17,3),getTileNo(18,3),getTileNo(19,3),
	getTileNo(10,2),getTileNo(11,2),getTileNo(12,2),getTileNo(13,2),getTileNo(14,2),getTileNo(15,2),getTileNo(16,2),getTileNo(17,2),getTileNo(18,2),getTileNo(19,2),
	getTileNo(10,1),getTileNo(11,1),getTileNo(12,1),getTileNo(13,1),getTileNo(14,1),getTileNo(15,1),getTileNo(16,1),getTileNo(17,1),getTileNo(18,1),getTileNo(19,1),
	getTileNo(10,0),getTileNo(11,0),getTileNo(12,0),getTileNo(13,0),getTileNo(14,0),getTileNo(15,0),getTileNo(16,0),getTileNo(17,0),getTileNo(18,0),getTileNo(19,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3), 
	getTileNo(0,2), getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2),
	getTileNo(0,1), getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1),
	getTileNo(0,0), getTileNo(1,0), getTileNo(2,0), getTileNo(3,0), getTileNo(4,0), getTileNo(5,0), getTileNo(6,0), getTileNo(7,0), getTileNo(8,0), getTileNo(9,0),
	getTileNo(31,0),getTileNo(31,0),getTileNo(31,0),getTileNo(27,3),getTileNo(28,3),getTileNo(29,3),getTileNo(30,3),getTileNo(31,3),getTileNo(31,0),getTileNo(31,0),
	0
};

// 夏隆头像框模板
const u16 SharonPortraitInBoxTemplate[1 + 10 * 9 + 1] =
{
	0x809,
	getTileNo(18,0),getTileNo(19,0),getTileNo(20,0),getTileNo(21,0),getTileNo(22,0),getTileNo(23,0),getTileNo(16,2),getTileNo(17,2),getTileNo(18,2),getTileNo(19,2),
	getTileNo(31,0),getTileNo(8,3),getTileNo(9,3),getTileNo(10,3),getTileNo(11,3),getTileNo(12,3),getTileNo(13,3),getTileNo(14,3),getTileNo(15,3),getTileNo(24,3),
	getTileNo(31,0),getTileNo(8,2),getTileNo(9,2),getTileNo(10,2),getTileNo(11,2),getTileNo(12,2),getTileNo(13,2),getTileNo(14,2),getTileNo(15,2),getTileNo(24,2),
	getTileNo(8,1),getTileNo(9,1),getTileNo(10,1),getTileNo(11,1),getTileNo(12,1),getTileNo(13,1),getTileNo(14,1),getTileNo(15,1),getTileNo(23,3),getTileNo(24,1),
	getTileNo(8,0),getTileNo(9,0),getTileNo(10,0),getTileNo(11,0),getTileNo(12,0),getTileNo(13,0),getTileNo(14,0),getTileNo(15,0),getTileNo(23,2),getTileNo(24,0),
	getTileNo(0,3),getTileNo(1,3),getTileNo(2,3),getTileNo(3,3),getTileNo(4,3),getTileNo(5,3),getTileNo(6,3),getTileNo(7,3),getTileNo(31,0),getTileNo(20,3),
	getTileNo(0,2),getTileNo(1,2),getTileNo(2,2),getTileNo(3,2),getTileNo(4,2),getTileNo(5,2),getTileNo(6,2),getTileNo(7,2),getTileNo(31,0),getTileNo(31,0),
	getTileNo(0,1),getTileNo(1,1),getTileNo(2,1),getTileNo(3,1),getTileNo(4,1),getTileNo(5,1),getTileNo(6,1),getTileNo(7,1),getTileNo(31,0),getTileNo(31,0),
	getTileNo(0,0),getTileNo(1,0),getTileNo(2,0),getTileNo(3,0),getTileNo(4,0),getTileNo(5,0),getTileNo(6,0),getTileNo(7,0),getTileNo(31,0),getTileNo(31,0),
	0
};

// 成年琪琪头像框模板
const u16 TikiFPortraitInBoxTemplate[1 + 10 * 9 + 1] =
{
	0x809,
//	getTileNo(17,1),getTileNo(18,1),getTileNo(19,1),getTileNo(20,1),getTileNo(21,1),getTileNo(22,1),getTileNo(23,1),getTileNo(24,1),getTileNo(25,1),getTileNo(26,1),
	getTileNo(17,0),getTileNo(18,0),getTileNo(19,0),getTileNo(20,0),getTileNo(21,0),getTileNo(22,0),getTileNo(23,0),getTileNo(24,0),getTileNo(25,0),getTileNo(26,0),
	getTileNo(6,3),getTileNo(7,3),getTileNo(8,3),getTileNo(9,3),getTileNo(10,3),getTileNo(11,3),getTileNo(12,3),getTileNo(13,3),getTileNo(14,3),getTileNo(15,3),
	getTileNo(6,2),getTileNo(7,2),getTileNo(8,2),getTileNo(9,2),getTileNo(10,2),getTileNo(11,2),getTileNo(12,2),getTileNo(13,2),getTileNo(14,2),getTileNo(15,2),
	getTileNo(6,1),getTileNo(7,1),getTileNo(8,1),getTileNo(9,1),getTileNo(10,1),getTileNo(11,1),getTileNo(12,1),getTileNo(13,1),getTileNo(14,1),getTileNo(15,1),
	getTileNo(6,0),getTileNo(7,0),getTileNo(8,0),getTileNo(9,0),getTileNo(10,0),getTileNo(11,0),getTileNo(12,0),getTileNo(13,0),getTileNo(14,0),getTileNo(15,0),
	getTileNo(31,0),getTileNo(31,0),getTileNo(0,3),getTileNo(1,3),getTileNo(2,3),getTileNo(3,3),getTileNo(4,3),getTileNo(5,3),getTileNo(31,0),getTileNo(31,0),
	getTileNo(31,0),getTileNo(31,0),getTileNo(0,2),getTileNo(1,2),getTileNo(2,2),getTileNo(3,2),getTileNo(4,2),getTileNo(5,2),getTileNo(31,0),getTileNo(31,0),
	getTileNo(31,0),getTileNo(31,0),getTileNo(0,1),getTileNo(1,1),getTileNo(2,1),getTileNo(3,1),getTileNo(4,1),getTileNo(5,1),getTileNo(31,0),getTileNo(31,0),
	getTileNo(31,0),getTileNo(31,0),getTileNo(0,0),getTileNo(1,0),getTileNo(2,0),getTileNo(3,0),getTileNo(4,0),getTileNo(5,0),getTileNo(31,0),getTileNo(31,0),
	0
};

// 人物界面头像框模板表

const void *portraitInBoxTemplateTable[] =
{
	oldPortraitInBoxTemplateLow,	// 原来的模板(无上移)
	oldPortraitInBoxTemplateHigh,	// 原来的模板(有上移)
	newPortraitInBoxTemplateLH,		// 横式
	newPortraitInBoxTemplateH,
	newPortraitInBoxTemplateRH,
	newPortraitInBoxTemplateLUH,
	newPortraitInBoxTemplateUH,
	newPortraitInBoxTemplateRUH,
	newPortraitInBoxTemplateV,		// 立式
	newPortraitInBoxTemplateUV,
	newPortraitInBoxTemplateUUV,
	newPortraitInBoxTemplateUUUV,
	TikiPortraitInBoxTemplate,		// 幼女琪琪
	SharonPortraitInBoxTemplate,	// 夏隆
	TikiFPortraitInBoxTemplate		// 成年琪琪
};

// 蒙版表
const u16 portraitMaskInBoxTable[][9][10] =
{
	// 原来的凸形对应的蒙版
	{
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	},
	// 幼女琪琪的蒙版
	{
		{0,0,0,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	},
	// 夏隆的蒙版
	{
		{1,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	},
	// 成年琪琪的蒙版
	{
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}		
	}
};

// 眨眼和使眼色，新增一个精灵，然后实时覆写VRAM中的Tile数据，支持非8像素对齐
void blinkOrWink1(u32 *mempool, int eyeStatus)
{
	int eyeShape;	// 闭眼还是半闭眼
	int winkFlag;	// 是否只针对外侧的那只眼睛
	struct Portrait *portrait;	// 头像
	int *data;
	int x; // 眼睛精灵横坐标
	int y; // 眼睛精灵纵坐标
	
	data = mempool[11];
	portrait = data[11];
	// 写Tile(不考虑使眼色和眨眼的区别)
	winkFlag = eyeStatus & 0x80;
	eyeShape = 2 - (eyeStatus & 1);
	if(eyeStatus & (~0x81))
		eyeShape = 0;
	changeTiles(portrait->ce.eyeFrameInfo->eyeFrame[eyeShape],32 * ((*(s16 *)((int)data + 60) + 28 + 32 * 2) & 0x3FF) + 0x6010000,4,2);
	// 写OAM(在这里考虑考虑使眼色)
	x = 4 - portrait->eyePositionX;
	if(winkFlag)
		x += 2;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		x = 8 * x;
	if(!checkPortraitInvert(data))
		x = - x;
	x = 0x1FF & (x + *(s16 *)((int)data + 52) - 16);
	if(checkPortraitInvert(data))
		LOWORD(x) = x + 0x1000;
	y = portrait->eyePositionY;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		y = 8 * y;
	y = ((y + *(s16 *)((int)data + 54)) & 0xFF) + (0x400 & (-(0x400 & getPortraitControlFlag(data)) >> 31));
	if(winkFlag)
		if(!checkPortraitInvert(data))
			LOWORD(x) = x + 16 + 2;
	AddSprite(*(s8 *)((int)data + 65),x,y,winkFlag ? winkFrameTemplate : blinkFrameTemplate,*(s16 *)((int)data + 60) + 28 + 32 * 2 + 2 * !!winkFlag);	
}

// 眨眼和使眼色，直接实时覆写VRAM中的Tile数据，支持自定义形状尺寸
// eyeStatus=0 		闭眼
// eyeStatus=1 		半闭眼
// eyeStatus=0x80	闭单侧眼
// eyeStatus=0x81	闭单侧眼
void blinkOrWink2(u32 *mempool, int eyeStatus)
{
	int eyeShape;	// 闭眼还是半闭眼
	int winkFlag;	// 是否只针对外侧的那只眼睛
	struct Portrait *portrait;	// 头像
	// 第i行第j列
	int i;	// 循环变量，纵坐标
	int j;	// 循环变量，横坐标

	portrait = (struct Portrait *)(*(u32 *)(mempool[11] + 44));
	if(eyeStatus & (~0x81))
	{
		for(i = 0;i < portrait->ce.eyeFrameInfo->height;i++)
			for(j = 0;j < portrait->ce.eyeFrameInfo->width;j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[0] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);
		return;
	}
	winkFlag = eyeStatus & 0x80;
	eyeShape = 2 - (eyeStatus & 1);
	if(winkFlag)
		for(i = portrait->ce.eyeFrameInfo->height - portrait->ce.eyeFrameInfo->winkHeight;i < portrait->ce.eyeFrameInfo->height; i++)
			for(j = portrait->ce.eyeFrameInfo->width - portrait->ce.eyeFrameInfo->winkWidth;j < portrait->ce.eyeFrameInfo->width; j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[eyeShape] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);
	else
		for(i = 0;i < portrait->ce.eyeFrameInfo->height;i++)
			for(j = 0;j < portrait->ce.eyeFrameInfo->width;j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[eyeShape] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);				
}

// 根据新老格式的不同调用相应的眨眼/使眼色函数
void callBlinkOrWink(u32 *mempool, int eyeStatus)
{
	struct Portrait *portrait;	// 头像

	portrait = (struct Portrait *)(*(u32 *)(mempool[11] + 44));
	blinkOrWink[portrait->eyeControlFlag - 1](mempool,eyeStatus);
}

// 眨眼/使眼色函数接口
void callCallBlinkOrWink(u32 *mempool, int eyeStatus)
{
	callBlinkOrWink(mempool,eyeStatus);
}

// 调用到BlinkOrWink的函数1
// 眨眼
void blink(s16 *mempool)
{
	int eyeStatus;

	eyeStatus = 2;
	if(mempool[26] <= 0xA)
	{
		switch(mempool[26])
		{
			case 3u:
			case 4u:
			case 5u:
				eyeStatus = 0;
				break;
			case 0u:
			case 1u:
			case 2u:
			case 6u:
			case 7u:
			case 8u:
				eyeStatus = 1;
				break;
			case 0xAu:
				sub(80045FC)((int)mempool,0);
				break;
			default:
				break;
		}
	}
	callCallBlinkOrWink((u32 *)mempool,eyeStatus);
	++mempool[26];
}

// 调用到BlinkOrWink的函数1接口
__attribute__((section(".callBlink")))
void callBlink(s16 *mempool)
{
	blink(mempool);
}

// 调用到BlinkOrWink的函数2
void sub_80077E8(s16 *mempool)
{
	if(mempool[26] > 5)
	{
		callCallBlinkOrWink((u32 *)mempool,0);
		if(!mempool[25])
			sub(80045FC)((int)mempool,1);
	}
	else
		blink(mempool);
}

// 调用到BlinkOrWink的函数2接口
__attribute__((section(".call_sub_80077E8")))
void call_sub_80077E8(s16 *mempool)
{
	sub_80077E8(mempool);
}

// 调用到BlinkOrWink的函数3
void sub_8007824(s16 *mempool)
{
	if(mempool[26] > 2)
	{
		callCallBlinkOrWink((u32 *)mempool,1);
		if(!mempool[25])
			sub(80045FC)((int)mempool,1);
	}
	else
		blink(mempool);
}

// 调用到BlinkOrWink的函数3接口
__attribute__((section(".call_sub_8007824")))
void call_sub_8007824(s16 *mempool)
{
	sub_8007824(mempool);
}

// 调用到BlinkOrWink的函数4
// 使眼色
void wink(s16 *mempool)
{
	int eyeStatus;

	eyeStatus = 2;
	if(mempool[26] <= 0xA)
	{
		switch(mempool[26])
		{
			case 3u:
			case 4u:
			case 5u:
				eyeStatus = 0;
				break;
			case 0u:
			case 1u:
			case 2u:
			case 6u:
			case 7u:
			case 8u:
				eyeStatus = 1;
				break;
			case 0xAu:
				sub(80045FC)((int)mempool,0);
				break;
			default:
				break;
		}
	}
	callCallBlinkOrWink((u32 *)mempool,eyeStatus + 0x80);
	++mempool[26];
}

// 调用到BlinkOrWink的函数4接口
__attribute__((section(".callWink")))
void callWink(s16 *mempool)
{
	wink(mempool);
}

// 选择大头像精灵组合模板，支持自定义模板
void chooseMainPortraitSpriteTemplate(u32 *mempool)
{
	u32 flag1;	// 控制模板选择
	u32 flag2;
	s16 delta;
	struct Portrait *portrait;	// 头像

	portrait = (struct Portrait *)mempool[11];
	flag1 = mempool[12] & 0x807;

	/*
	if(flag1 == 2 || flag1 == 3)				// 会话中出现的头像
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,1)][flag1 & 1];
	else if(flag1 == 0x800 || flag1 == 0x801)	// 查看支援对话时左上的头像
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,3)][flag1 & 1];
	else if(flag1 == 0 || flag1 == 1)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,0)][flag1 & 1];	
	else if(flag1 == 4 || flag1 == 5)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,2)][flag1 & 1];
	*/
	if(flag1 == 0x800 || flag1 == 0x801)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,3)][flag1 & 1];
	else if(flag1 <= 5)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,flag1 >> 1)][flag1 & 1];

	flag2 = mempool[12] & 0x3C0;
	if ( flag2 == 0x80 )
	{
		delta = 0x400;
	}
	else if ( flag2 > 0x80 )
	{
		if ( flag2 != 0x200 )
			goto LABEL_1;
		delta = 0xC00;
	}
	else
	{
		if ( flag2 != 0x40 )
		{
LABEL_1:
			delta = 0x800;
			goto LABEL_2;
		}
		delta = 0;
	}
LABEL_2:
	*((s16 *)mempool + 30) = (*(s32 *)(8 * *((s8 *)mempool + 64) + 0x202A580) >> 5)
															 + ((*(s16 *)(8 * *((s8 *)mempool + 64) + 0x202A584) & 0xF) << 12)
															 + delta;
}

// 新的选择大头像精灵组合模板函数的接口
__attribute__((section(".callChooseMainPortraitSpriteTemplate")))
void callChooseMainPortraitSpriteTemplate(s16 *mempool)
{
	chooseMainPortraitSpriteTemplate((u32 *)mempool);
}

// 新的人物详情界面头像框绘制函数
void drawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	struct Portrait *portrait;	// 头像
	int i;
	int j;

	if(!portraitID)
		return;
	portrait = GetPortrait(portraitID);
	OutputToBGPaletteBuffer(portrait->portraitPalette, 32 * presentBGPaletteIndex, 32);
	if(portrait->mainPortrait)	// 有头像画头像
	{
		AutoCopyOrDecompressImageToVRAM(portrait->mainPortrait, 32 * presentBGTileIndex + 0x6000000);
		OutputToBGPaletteBuffer(portrait->portraitPalette, 32 * presentBGPaletteIndex, 32);
		if(PortraitHeightFix(portraitID)<<24)
			writeTemplateTSA(TSABufferInWRAM, portraitInBoxTemplateTable[1], ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		else
			writeTemplateTSA(TSABufferInWRAM, portraitInBoxTemplateTable[portrait->portraitTemplateInBox], ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		// 蒙版裁剪
		for(i = 0; i < 9; i++)
			for(j = 0; j < 10; j++)
				TSABufferInWRAM[32 * i + j] &= - portraitMaskInBoxTable[portrait->portraitMaskInBox][i][j];
	}
	else	// 无头像画职业卡
	{
		AutoCopyOrDecompressImageToVRAM(portrait->ce.classCard, 32 * presentBGTileIndex + 0x6000000);
		writePlainTSA(TSABufferInWRAM, (presentBGPaletteIndex << 12) + (presentBGTileIndex & 0x3FF), 10, 9);
	}
}

// 新的人物详情界面头像框绘制函数的接口
__attribute__((section(".callDrawPortraitInBox")))
void callDrawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	drawPortraitInBox(TSABufferInWRAM, portraitID, presentBGTileIndex, presentBGPaletteIndex);
}

// 新的支持非8像素对齐的眨眼/使眼色函数
void blinkOrWink0(int *mempool, int eyeStatus)
{
	int winkFlag;	// 使眼色标识
	s16 eyeTileIndexDelta;	// 眼睛帧Tile编号的偏移量
	int *data;	// 头像显示控制相关数据
	struct Portrait *portrait;	// 头像
	int x;	// 精灵横坐标
	int y;	// 精灵纵坐标

	if(eyeStatus & (~0x81))
		return;
	winkFlag = eyeStatus & 0x80;
	eyeTileIndexDelta = 88 - (eyeStatus & 1)*(88 - 24);
	data = (int *)mempool[11];
	portrait = data[11];
	x = 4 - portrait->eyePositionX;
	if(!checkPortraitInvert(data))
		x = -x;
	x = (8 * x * (1-portrait->eyeMouthPositionAlignmentFlag) + x * portrait->eyeMouthPositionAlignmentFlag + (s16)data[13] - 16) & 0x1FF;
//	x = (8 * x + data[26] - 16) & 0x1FF;
	if(checkPortraitInvert(data))
		LOWORD(x) = x + 0x1000;
//		x = (((x & 0xFFFF) + 0x1000) & 0xFFFF)|(x & 0xFFFF0000);
	y = ((-(getPortraitControlFlag(data) & 0x400)>>31) & 0x400) + ((*(u16 *)((int)data + 54) + 8 * portrait->eyePositionY * (1 - portrait->eyeMouthPositionAlignmentFlag) + portrait->eyePositionY * portrait->eyeMouthPositionAlignmentFlag) & 0xFF);
	if(winkFlag)
	{
		if(!checkPortraitInvert(data))
			LOWORD(x) = x + 16;
//			x = (((x & 0xFFFF) + 16) & 0xFFFF)|(x & 0xFFFF0000);
		AddSprite(*(s8 *)((int)data + 65),x,y,winkFrameTemplate,*(s16 *)((int)data + 60) + eyeTileIndexDelta + 2);
	}
	else
		AddSprite(*(s8 *)((int)data + 65),x,y,blinkFrameTemplate,*(s16 *)((int)data + 60) + eyeTileIndexDelta);
	
}

// 嘴部动画函数
void mouthAnimation(int *mempool)
{
	int mouthFrameTileNoDela; // 控制读取不同的帧
	int *data;
	int x; // 嘴巴精灵横坐标
	int y; // 嘴巴精灵纵坐标
	struct Portrait *portrait; // 头像

	data = mempool[11];
	portrait = data[11];
	// 写Tile
	mouthFrameTileNoDela = 0;
	if(!(getPortraitControlFlag(data) & 8))
		mouthFrameTileNoDela = 24;

	if(getPortraitControlFlag(data) & 0x30)
	{
		if(!(--*((s16 *)mempool + 25) & 0x8000))
			goto LABEL_3;
		*((s16 *)mempool + 25) = ((sub(8000EB4)() >> 16) & 7) + 1;
		*((s16 *)mempool + 24) = (*((s16 *)mempool + 24) + 1) & 3;
		if(*((s16 *)mempool + 24) == 1 || *((s16 *)mempool + 24) == 3)
			mouthFrameTileNoDela += 8;
		if(*((s16 *)mempool + 24) == 2)
			mouthFrameTileNoDela += 16;
		changeTiles((int)portrait->mouthFrame + 32 * mouthFrameTileNoDela,32 * ((*(s16 *)((int)data + 60) + 28) & 0x3FF) + 0x6010000,4,2);
		goto LABEL_3;
	}

	changeTiles((int)portrait->mouthFrame + 32 * (mouthFrameTileNoDela + 16),32 * ((*(s16 *)((int)data + 60) + 28) & 0x3FF) + 0x6010000,4,2);

	// 写OAM
LABEL_3:
	x = 4 - portrait->mouthPositionX;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		x = 8 * x;
	if(!checkPortraitInvert(data))
		x = - x;
	x = 0x1FF & (x + *(s16 *)((int)data + 52) - 16);
	if(checkPortraitInvert(data))
		LOWORD(x) = x + 0x1000;
	y = portrait->mouthPositionY;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		y = 8 * y;
	y = ((y + *(s16 *)((int)data + 54)) & 0xFF) + (0x400 & (-(0x400 & getPortraitControlFlag(data)) >> 31));
	AddSprite(*(s8 *)((int)data + 65),x,y,mouthFrameTemplate,*(s16 *)((int)data + 60) + 28);

}

// 嘴部动画接口函数
__attribute__((section(".callMouthAnimation")))
void callMouthAnimation(int *mempool)
{
	mouthAnimation(mempool);
};

