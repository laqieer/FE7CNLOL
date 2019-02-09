// by laqieer
// 2017/4/9
// 成年琪琪头像

#include "FE7JPortrait.h"


#include "TikiFMainPortrait_bin.h"
#include "TikiFMiniPortraitLZ_bin.h"
#include "TikiFEyeFrame_bin.h"
#include "TikiFMouthFrame_bin.h"


const u16 TikiFPortraitPal[16] =
{
	0x757A, 0x67DF, 0x77DF, 0x5B3E, 0x675E, 0x5EFA, 0x4E99, 0x2537,
	0x4F56, 0x3A15,	0x1CF3, 0x46D3, 0x3A4F, 0x320D, 0x108C, 0x258A
};

const s16 TikiFEyeFrameTemplate[2][4] =
{
	{getTileNo(9,0),getTileNo(10,0),getTileNo(11,0),getTileNo(12,0)},
	{getTileNo(9,1),getTileNo(10,1),getTileNo(11,1),getTileNo(12,1)}
};

const struct EyeFrameInfo TikiFEyeFrameInfo =
{
	4,2,
	2,2,
	{TikiFEyeFrame_bin,&TikiFEyeFrame_bin[32 * 4 * 2],&TikiFEyeFrame_bin[32 * 4 * 2 * 2]},
//	0,
	TikiFEyeFrameTemplate
};

__attribute__((section(".TikiFPortrait")))
const struct Portrait TikiFPortrait =
{
	TikiFMainPortrait_bin,
//	0,
	TikiFMiniPortraitLZ_bin,
//	0,
	TikiFPortraitPal,
//	0,
	TikiFMouthFrame_bin,
//	0,
	{&TikiFEyeFrameInfo},
	-1 * 8 + 4, 8 * 3 + 4,
	0, 0,
	3,
	8,
	14,
	3,
	1
};

const u16 portraitMaskTikiF[9][10] = {
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1}
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

