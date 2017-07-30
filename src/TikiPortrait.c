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