// by laqieer
// 2017/4/3
// 幼女琪琪头像测试

#include "FE7JPortrait.h"


#include "TikiMainPortraitPal_bin.h"
#include "TikiMainPortraitImg_bin.h"
#include "TikiEyeFrameImg_bin.h"
#include "TikiMouthFrameImg_bin.h"


// 眨眼区域模板
const s16 TikiBlinkTemplate[3][6] =
{
	{getTileNo(2,3), getTileNo(3,3), getTileNo(4,3), getTileNo(5,3), getTileNo(6,3), getTileNo(7,3) },
	{getTileNo(12,0),getTileNo(13,0),getTileNo(14,0),getTileNo(15,0),getTileNo(16,0),getTileNo(17,0)},
	{getTileNo(12,1),getTileNo(13,1),getTileNo(14,1),getTileNo(15,1),getTileNo(16,1),getTileNo(17,1)}
};

// 眼睛动画信息
const struct EyeFrameInfo TikiEyeFrameInfo =
{
	6,
	3,
	3,
	3,
	{TikiEyeFrameImg_bin, &TikiEyeFrameImg_bin[32 * 6 * 3], &TikiEyeFrameImg_bin[32 * 6 * 3 * 2]},
//	0,
	TikiBlinkTemplate
};

// 头像控制信息
__attribute__((section(".TikiPortrait")))
const struct Portrait TikiPortrait =
{
	TikiMainPortraitImg_bin,
//	0,
	0x8D3F2A8,
	TikiMainPortraitPal_bin,
//	0,
	TikiMouthFrameImg_bin,
//	0,
	{&TikiEyeFrameInfo},
	3,6,
	2,3,
	3,
	6,
	12,
	1,
	0
};

// 头像框中的蒙版
const u16 portraitMaskTiki[9][10] = {
	{0,0,0,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1}
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

