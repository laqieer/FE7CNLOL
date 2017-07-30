// by laqieer
// 2017/4/7
// ÏÄÂ¡Í·Ïñ²âÊÔ

#include "FE7JPortrait.h"

#include "SharonPortraitSheetPal.h"
#include "SharonMainPortraitImg_bin.h"
#include "SharonMiniPortraitImgLZ_bin.h"
#include "SharonEyeFrameImg_bin.h"
#include "SharonMouthFrameImg_bin.h"

const struct EyeFrameInfo SharonEyeFrameInfo = 
{
	0,
	0,
	0,
	0,
	{SharonEyeFrameImg_bin,&SharonEyeFrameImg_bin[32 * 4 * 2],&SharonEyeFrameImg_bin[32 * 4 * 2 * 2]},
//	0,
	0
};

__attribute__((section(".SharonPortrait")))
const struct Portrait SharonPortrait =
{
	SharonMainPortraitImg_bin,
//	0,
	SharonMiniPortraitImgLZ_bin,
//	0,
	SharonPortraitSheetPalPal,
//	0,
	SharonMouthFrameImg_bin,
//	0,
	{&SharonEyeFrameInfo},
	8 * 2 + 2 - 8 * 3 - 4,8 * 7,
	8 * 1 + 5 - 8 * 3 - 4,8 * 4,
	2,
	7,
	13,
	2,
	1
};