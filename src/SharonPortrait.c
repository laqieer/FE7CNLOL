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

const u16 portraitMaskSharon[9][10] = {
	{1,1,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1}
};

// ÏÄÂ¡¶Ô»°Í·ÏñÄ£°å(×ó)
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

// ÏÄÂ¡¶Ô»°Í·ÏñÄ£°å(ÓÒ)
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

// ÏÄÂ¡Í·Ïñ¿òÄ£°å
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

