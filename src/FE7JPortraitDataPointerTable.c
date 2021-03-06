// 把FE7JPortarit.c中的数据部分剥离出来，各种指针表
// by laqieer
// 2019-2-9

#include "FE7JPortrait.h"

#include "SurtrPortrait.h"
#include "BlackKnightPortrait.h"
#include "ZelgiusPortrait.h"
#include "Fenrir.h"
#include "PortraitCherryBlue.h"
#include "CherryRed.h"

// 第二个头像指针表,起始序号0x100,旧扩展格式
const struct Portrait portraitTableNew[] = {
		{NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0x100 空白
		{SurtrPortraitMainL, SurtrPortraitMini, SurtrPortraitPal, SurtrMouthFrameL, {&SurtrEyeFrameInfoL}, 7 - 6, 2, 0, 0, 3, 11, 0, 0, 0}, // 0x101 斯尔特左半身
		{SurtrPortraitMainR, SurtrPortraitMini, SurtrPortraitPal, SurtrMouthFrameR, {&SurtrEyeFrameInfoR}, 1 - 2, 2, 0, 0, 3, 10, 0, 0, 0}, // 0x102 斯尔特右半身
		{SurtrPortraitMainS, SurtrPortraitMini, SurtrPortraitPal, NULL, NULL, 0, 0, 0, 0, 0, 0, 21, 4, 0}, // 0x103 斯尔特人物框
		{BlackKnightPortraitMainL, BlackKnightPortraitMini, BlackKnightPortraitPal, BlackKnightMouthFrameL, NULL, 6 + 1- 6, 7 - 2, 0, 0, 4, 11, 0, 0, 0}, // 0x104 漆黑的骑士左半身
		{BlackKnightPortraitMainR, BlackKnightPortraitMini, BlackKnightPortraitPal, BlackKnightMouthFrameR, NULL, 10 - 10 + 1 - 2, 7 - 2, 0, 0, 4, 10, 0, 0, 0}, // 0x105 漆黑的骑士右半身
		{BlackKnightPortraitMainS, BlackKnightPortraitMini, BlackKnightPortraitPal, NULL, NULL, 0, 0, 0, 0, 0, 0, 21, 4, 0}, // 0x106 漆黑的骑士人物框
		{BlackKnightPortraitMainM, BlackKnightPortraitMini, BlackKnightPortraitPal, BlackKnightMouthFrameM, NULL, 3, 7, 0, 0, 4, 9, 16, 4, 0}, // 0x107 漆黑的骑士中间 96x80
		{ZelgiusPortraitMain, ZelgiusPortraitMini, ZelgiusPortraitPal, ZelgiusMouthFrame, {&ZelgiusEyeFrameInfo}, 40 - 136 / 2 + 20, 40, 0, 0, 3, 12, 22, 5, 1}, // 0x108 塞尔基乌斯
		{Fenrir_portrait_tileset, Fenrir_portrait_mini, Fenrir_portrait_palette, Fenrir_portrait_mouth_frame, {&Fenrir_eye_frame_info}, -2, 56, 0, 0, 3, 13, 23, 6, 1}, // 0x109 Fenrir
};

// 第三个头像指针表,起始序号0x200,新扩展格式
const pPortraitNew portraitTableNewExtension[] = {
	//{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1, -1, 0x200}, // 0x200, 0标识文本结束, 所以不能用在剧情对话里
	NULL, // 0x200
	//{&CherryBlue_portrait_tileset, &CherryBlue_portrait_mini, &CherryBlue_portrait_palette, &CherryBlue_portrait_extra_info, NULL, NULL, NULL, NULL, NULL, 1, 0xFF, 0x201}, // 0x201 Cherry (Blue)
	&CherryBlue_portrait, // 0x201
	&portrait_CherryRed, // 0x202
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

// 96x80 新模板 简化型 朝左
const u16 newPortraitTemplateLeftHS[] = 
{
	7,
	getObjectAttribute1(1,0), getObjectAttribute2(3,0,-48), getObjectAttribute3(0), // 1
	getObjectAttribute1(0,0), getObjectAttribute2(2,0,16), getObjectAttribute3(8), // 2
	getObjectAttribute1(1,32), getObjectAttribute2(3,0,-48), getObjectAttribute3(8 + 4), // 3
	getObjectAttribute1(0,32), getObjectAttribute2(2,0,16), getObjectAttribute3(8 + 4 + 8), // 4
	getObjectAttribute1(1,64), getObjectAttribute2(2,0,-48), getObjectAttribute3(8 + 4 + 8 + 4), // 5
	getObjectAttribute1(1,64), getObjectAttribute2(2,0,-16), getObjectAttribute3(8 + 4 + 8 + 4 + 32 * 2), // 6
	getObjectAttribute1(1,64), getObjectAttribute2(2,0,16), getObjectAttribute3(8 + 4 + 8 + 4 + 4 + 32 * 2), // 7
};

// 96x80 新模板 简化型 朝右
const u16 newPortraitTemplateRightHS[] = 
{
	7,
	getObjectAttribute1(1,0), getObjectAttribute2(3,1,-16), getObjectAttribute3(0), // 1
	getObjectAttribute1(0,0), getObjectAttribute2(2,1,-48), getObjectAttribute3(8), // 2
	getObjectAttribute1(1,32), getObjectAttribute2(3,1,-16), getObjectAttribute3(8 + 4), // 3
	getObjectAttribute1(0,32), getObjectAttribute2(2,1,-48), getObjectAttribute3(8 + 4 + 8), // 4
	getObjectAttribute1(1,64), getObjectAttribute2(2,1,16), getObjectAttribute3(8 + 4 + 8 + 4), // 5
	getObjectAttribute1(1,64), getObjectAttribute2(2,1,-16), getObjectAttribute3(8 + 4 + 8 + 4 + 32 * 2), // 6
	getObjectAttribute1(1,64), getObjectAttribute2(2,1,-48), getObjectAttribute3(8 + 4 + 8 + 4 + 4 + 32 * 2), // 7
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

// 新模板，头像在左侧，面向右侧 (立式), 右移2格(16像素)
const u16 newPortraitTemplateRightVR2[1 + 3 * 7] =
{
	7,	// 精灵数量
	// 每个精灵3个word (3个OAM属性，求或的基础值)
	getObjectAttribute1(1,-16), getObjectAttribute2(3,1,40 - 64 + 16), getObjectAttribute3(0),											// 1
	getObjectAttribute1(2,-16), getObjectAttribute2(2,1,-40 + 16), getObjectAttribute3(8),										// 2
	getObjectAttribute1(1,16), getObjectAttribute2(3,1,40 - 64 + 16), getObjectAttribute3(8 + 2),										// 3
	getObjectAttribute1(2,16), getObjectAttribute2(2,1,-40 + 16), getObjectAttribute3(8 + 2 + 8),								// 4
	getObjectAttribute1(1,16 + 32), getObjectAttribute2(3,1,40 - 64 + 16), getObjectAttribute3(8 + 2 + 8 + 2),							// 5
	getObjectAttribute1(0,16 + 32), getObjectAttribute2(1,1,-40 + 16), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2),			// 6
	getObjectAttribute1(0,16 + 32 + 16), getObjectAttribute2(1,1,-40 + 16), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2 + 2)	// 7
};

// 新模板，头像在右侧，面向左侧 (立式), 左移2格(16像素)
const u16 newPortraitTemplateLeftVL2[1 + 3 * 7] =
{
	7,
	getObjectAttribute1(1,-16), getObjectAttribute2(3,0,-40 - 16), getObjectAttribute3(0),											// 1
	getObjectAttribute1(2,-16), getObjectAttribute2(2,0,40 - 16 - 16), getObjectAttribute3(8),										// 2
	getObjectAttribute1(1,16), getObjectAttribute2(3,0,-40 - 16), getObjectAttribute3(8 + 2),										// 3
	getObjectAttribute1(2,16), getObjectAttribute2(2,0,40 - 16 - 16), getObjectAttribute3(8 + 2 + 8),								// 4
	getObjectAttribute1(1,16 + 32), getObjectAttribute2(3,0,-40 - 16), getObjectAttribute3(8 + 2 + 8 + 2),							// 5
	getObjectAttribute1(0,16 + 32), getObjectAttribute2(1,0,40 - 16 - 16), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2),			// 6
	getObjectAttribute1(0,16 + 32 + 16), getObjectAttribute2(1,0,40 - 16 - 16), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2 + 2)	// 7
};

// 新模板，头像在左侧，面向右侧 (立式), 右移6格(48像素)
const u16 newPortraitTemplateRightVR6[1 + 3 * 7] =
{
	7,	// 精灵数量
	// 每个精灵3个word (3个OAM属性，求或的基础值)
	getObjectAttribute1(1,-16), getObjectAttribute2(3,1,40 - 64 + 48), getObjectAttribute3(0),											// 1
	getObjectAttribute1(2,-16), getObjectAttribute2(2,1,-40 + 48), getObjectAttribute3(8),										// 2
	getObjectAttribute1(1,16), getObjectAttribute2(3,1,40 - 64 + 48), getObjectAttribute3(8 + 2),										// 3
	getObjectAttribute1(2,16), getObjectAttribute2(2,1,-40 + 48), getObjectAttribute3(8 + 2 + 8),								// 4
	getObjectAttribute1(1,16 + 32), getObjectAttribute2(3,1,40 - 64 + 48), getObjectAttribute3(8 + 2 + 8 + 2),							// 5
	getObjectAttribute1(0,16 + 32), getObjectAttribute2(1,1,-40 + 48), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2),			// 6
	getObjectAttribute1(0,16 + 32 + 16), getObjectAttribute2(1,1,-40 + 48), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2 + 2)	// 7
};

// 新模板，头像在右侧，面向左侧 (立式), 左移6格(48像素)
const u16 newPortraitTemplateLeftVL6[1 + 3 * 7] =
{
	7,
	getObjectAttribute1(1,-16), getObjectAttribute2(3,0,-40 - 48), getObjectAttribute3(0),											// 1
	getObjectAttribute1(2,-16), getObjectAttribute2(2,0,40 - 16 - 48), getObjectAttribute3(8),										// 2
	getObjectAttribute1(1,16), getObjectAttribute2(3,0,-40 - 48), getObjectAttribute3(8 + 2),										// 3
	getObjectAttribute1(2,16), getObjectAttribute2(2,0,40 - 16 - 48), getObjectAttribute3(8 + 2 + 8),								// 4
	getObjectAttribute1(1,16 + 32), getObjectAttribute2(3,0,-40 - 48), getObjectAttribute3(8 + 2 + 8 + 2),							// 5
	getObjectAttribute1(0,16 + 32), getObjectAttribute2(1,0,40 - 16 - 48), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2),			// 6
	getObjectAttribute1(0,16 + 32 + 16), getObjectAttribute2(1,0,40 - 16 - 48), getObjectAttribute3(8 + 2 + 8 + 2 + 8 + 32 * 2 + 2)	// 7
};

extern const u16 TikiPortraitTemplateLeft[1 + 3 * 13];
extern const u16 TikiPortraitTemplateRight[1 + 3 * 13];

extern const u16 SharonPortraitTemplateLeft[1 + 3 * 16];
extern const u16 SharonPortraitTemplateRight[1 + 3 * 16];

extern const u16 TikiFPortraitTemplateLeft[1 + 3 * 9];
extern const u16 TikiFPortraitTemplateRight[1 + 3 * 9];

// 模板组表
const u32 portraitTemplatePairTable[][2] =
{
		{oldPortraitTemplate1Left, oldPortraitTemplate1Right},	// 0
		{oldPortraitTemplate2Left, oldPortraitTemplate2Right},	// 1
		{oldPortraitTemplate3Left, oldPortraitTemplate3Right},	// 2
		{oldPortraitTemplate4Left, oldPortraitTemplate4Right},	// 3
		{newPortraitTemplateLeftH, newPortraitTemplateRightH},	// 4
		{newPortraitTemplateLeftV, newPortraitTemplateRightV},	// 5
		{TikiPortraitTemplateLeft, TikiPortraitTemplateRight},	// 6
		{SharonPortraitTemplateLeft,SharonPortraitTemplateRight},	// 7
		{TikiFPortraitTemplateLeft,TikiFPortraitTemplateRight},	// 8
		{newPortraitTemplateLeftHS, newPortraitTemplateRightHS},	// 9
		{newPortraitTemplateLeftVL2, newPortraitTemplateRightVR2},	// 10
		{newPortraitTemplateLeftVL6, newPortraitTemplateRightVR6},	// 11
		{ZelgiusPortraitTemplateLeft, ZelgiusPortraitTemplateRight},	// 12
		{Fenrir_portrait_oam_left, Fenrir_portrait_oam_right},	// 13
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

// 96x80, 新模板, 简化型
const u16 newPortraitInBoxTemplateULHS[] = 
{
	0x809,
	getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(28,2), getTileNo(29,2),
	getTileNo(12,3), getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3), getTileNo(20,3), getTileNo(21,3),
	getTileNo(12,2), getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2), getTileNo(20,2), getTileNo(21,2),
	getTileNo(12,1), getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1), getTileNo(20,1), getTileNo(21,1),
	getTileNo(12,0), getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0), getTileNo(20,0), getTileNo(21,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3),
	getTileNo(0,2), getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2),
	getTileNo(0,1), getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1),
	getTileNo(0,0), getTileNo(1,0), getTileNo(2,0), getTileNo(3,0), getTileNo(4,0), getTileNo(5,0), getTileNo(6,0), getTileNo(7,0), getTileNo(8,0), getTileNo(9,0),
	0
};

// 96x80, 新模板, 简化型
const u16 newPortraitInBoxTemplateUHS[] = 
{
	0x809,
	getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(28,2), getTileNo(29,2), getTileNo(30,2),
	getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3), getTileNo(20,3), getTileNo(21,3), getTileNo(22,3),
	getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2), getTileNo(20,2), getTileNo(21,2), getTileNo(22,2),
	getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1), getTileNo(20,1), getTileNo(21,1), getTileNo(22,1),
	getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0), getTileNo(20,0), getTileNo(21,0), getTileNo(22,0),
	getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3), getTileNo(10,3),
	getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2), getTileNo(10,2),
	getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1), getTileNo(10,1),
	getTileNo(1,0), getTileNo(2,0), getTileNo(3,0), getTileNo(4,0), getTileNo(5,0), getTileNo(6,0), getTileNo(7,0), getTileNo(8,0), getTileNo(9,0), getTileNo(10,0),
	0
};

// 96x80, 新模板, 简化型
const u16 newPortraitInBoxTemplateURHS[] = 
{
	0x809,
	getTileNo(26,0), getTileNo(27,0), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(28,2), getTileNo(29,2), getTileNo(30,2), getTileNo(31,2),
	getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3), getTileNo(20,3), getTileNo(21,3), getTileNo(22,3), getTileNo(23,3),
	getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2), getTileNo(20,2), getTileNo(21,2), getTileNo(22,2), getTileNo(23,2),
	getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1), getTileNo(20,1), getTileNo(21,1), getTileNo(22,1), getTileNo(23,1),
	getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0), getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0),
	getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3), getTileNo(10,3), getTileNo(11,3),
	getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2), getTileNo(10,2), getTileNo(11,2),
	getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1), getTileNo(10,1), getTileNo(11,1),
	getTileNo(2,0), getTileNo(3,0), getTileNo(4,0), getTileNo(5,0), getTileNo(6,0), getTileNo(7,0), getTileNo(8,0), getTileNo(9,0), getTileNo(10,0), getTileNo(11,0),
	0
};

// 96x80, 新模板, 简化型
const u16 newPortraitInBoxTemplateLHS[] = 
{
	0x809,
	getTileNo(24,1), getTileNo(25,1), getTileNo(26,1), getTileNo(27,1), getTileNo(24,3), getTileNo(25,3), getTileNo(26,3), getTileNo(27,3), getTileNo(28,3), getTileNo(29,3),
	getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(28,2), getTileNo(29,2),
	getTileNo(12,3), getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3), getTileNo(20,3), getTileNo(21,3),
	getTileNo(12,2), getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2), getTileNo(20,2), getTileNo(21,2),
	getTileNo(12,1), getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1), getTileNo(20,1), getTileNo(21,1),
	getTileNo(12,0), getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0), getTileNo(20,0), getTileNo(21,0),
	getTileNo(0,3), getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3),
	getTileNo(0,2), getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2),
	getTileNo(0,1), getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1),
	0
};

// 96x80, 新模板, 简化型
const u16 newPortraitInBoxTemplateHS[] = 
{
	0x809,
	getTileNo(25,1), getTileNo(26,1), getTileNo(27,1), getTileNo(24,3), getTileNo(25,3), getTileNo(26,3), getTileNo(27,3), getTileNo(28,3), getTileNo(29,3), getTileNo(30,3),
	getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(28,2), getTileNo(29,2), getTileNo(30,2),
	getTileNo(13,3), getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3), getTileNo(20,3), getTileNo(21,3), getTileNo(22,3),
	getTileNo(13,2), getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2), getTileNo(20,2), getTileNo(21,2), getTileNo(22,2),
	getTileNo(13,1), getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1), getTileNo(20,1), getTileNo(21,1), getTileNo(22,1),
	getTileNo(13,0), getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0), getTileNo(20,0), getTileNo(21,0), getTileNo(22,0),
	getTileNo(1,3), getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3), getTileNo(10,3),
	getTileNo(1,2), getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2), getTileNo(10,2),
	getTileNo(1,1), getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1), getTileNo(10,1),
	0
};

// 96x80, 新模板, 简化型
const u16 newPortraitInBoxTemplateRHS[] = 
{
	0x809,
	getTileNo(26,1), getTileNo(27,1), getTileNo(24,3), getTileNo(25,3), getTileNo(26,3), getTileNo(27,3), getTileNo(28,3), getTileNo(29,3), getTileNo(30,3), getTileNo(31,3),
	getTileNo(26,0), getTileNo(27,0), getTileNo(24,2), getTileNo(25,2), getTileNo(26,2), getTileNo(27,2), getTileNo(28,2), getTileNo(29,2), getTileNo(30,2), getTileNo(31,2),
	getTileNo(14,3), getTileNo(15,3), getTileNo(16,3), getTileNo(17,3), getTileNo(18,3), getTileNo(19,3), getTileNo(20,3), getTileNo(21,3), getTileNo(22,3), getTileNo(23,3),
	getTileNo(14,2), getTileNo(15,2), getTileNo(16,2), getTileNo(17,2), getTileNo(18,2), getTileNo(19,2), getTileNo(20,2), getTileNo(21,2), getTileNo(22,2), getTileNo(23,2),
	getTileNo(14,1), getTileNo(15,1), getTileNo(16,1), getTileNo(17,1), getTileNo(18,1), getTileNo(19,1), getTileNo(20,1), getTileNo(21,1), getTileNo(22,1), getTileNo(23,1),
	getTileNo(14,0), getTileNo(15,0), getTileNo(16,0), getTileNo(17,0), getTileNo(18,0), getTileNo(19,0), getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0),
	getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3), getTileNo(8,3), getTileNo(9,3), getTileNo(10,3), getTileNo(11,3),
	getTileNo(2,2), getTileNo(3,2), getTileNo(4,2), getTileNo(5,2), getTileNo(6,2), getTileNo(7,2), getTileNo(8,2), getTileNo(9,2), getTileNo(10,2), getTileNo(11,2),
	getTileNo(2,1), getTileNo(3,1), getTileNo(4,1), getTileNo(5,1), getTileNo(6,1), getTileNo(7,1), getTileNo(8,1), getTileNo(9,1), getTileNo(10,1), getTileNo(11,1),
	0
};

// 只包含小头像和人物属性界面头像框的头像位用的
const u16 PurePortraitInBoxTemplate[] = 
{
	0x809,
	getTileNo(20,0), getTileNo(21,0), getTileNo(22,0), getTileNo(23,0), getTileNo(24,0), getTileNo(25,0), getTileNo(26,0), getTileNo(27,0), getTileNo(28,0), getTileNo(29,0),
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

extern const u16 TikiPortraitInBoxTemplate[1 + 10 * 9 + 1];

extern const u16 SharonPortraitInBoxTemplate[1 + 10 * 9 + 1];

extern const u16 TikiFPortraitInBoxTemplate[1 + 10 * 9 + 1];

// 人物界面头像框模板表

const void * const portraitInBoxTemplateTable[] =
{
	oldPortraitInBoxTemplateLow,	// 0 原来的模板(无上移)
	oldPortraitInBoxTemplateHigh,	// 1 原来的模板(有上移)
	newPortraitInBoxTemplateLH,		// 2 横式
	newPortraitInBoxTemplateH,		// 3
	newPortraitInBoxTemplateRH,		// 4
	newPortraitInBoxTemplateLUH,	// 5
	newPortraitInBoxTemplateUH,		// 6
	newPortraitInBoxTemplateRUH,	// 7
	newPortraitInBoxTemplateV,		// 8 立式
	newPortraitInBoxTemplateUV,		// 9
	newPortraitInBoxTemplateUUV,	// 10
	newPortraitInBoxTemplateUUUV,	// 11
	TikiPortraitInBoxTemplate,		// 12 幼女琪琪
	SharonPortraitInBoxTemplate,	// 13 夏隆
	TikiFPortraitInBoxTemplate,		// 14 成年琪琪
	newPortraitInBoxTemplateULHS,	// 15 96x80 简化型
	newPortraitInBoxTemplateUHS,	// 16
	newPortraitInBoxTemplateURHS,	// 17
	newPortraitInBoxTemplateLHS,	// 18
	newPortraitInBoxTemplateHS,		// 19
	newPortraitInBoxTemplateRHS,	// 20
	PurePortraitInBoxTemplate,		// 21 纯头像框(最简)
	ZelgiusPortraitInBoxTemplate,		// 22 成年琪琪
	Fenrir_portrait_in_status_screen_tsa, // 23 神兽芬利厄
};


const u16 portraitMaskCommon[9][10] = {
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1}
};

const u16 portraitMaskAll[9][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1}
};

extern const u16 portraitMaskTiki[9][10];
extern const u16 portraitMaskSharon[9][10];
extern const u16 portraitMaskTikiF[9][10];

const u16* const portraitMaskTable[] = {
	portraitMaskCommon, // 0
	portraitMaskTiki, // 1
	portraitMaskSharon, // 2
	portraitMaskTikiF, // 3
	portraitMaskAll, // 4
	portraitMaskZelgius, // 5
	Fenrir_portrait_in_status_screen_mask, // 6
};
