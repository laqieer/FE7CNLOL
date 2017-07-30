// by laqieer
// 2017/3/22
// 琳头像测试

#include "FE7JPortrait.h"
#include "LynMainPortraitH_bin.h"
#include "LynMainPortraitV_bin.h"
#include "LynEyeFrameH_bin.h"
#include "LynEyeFrameV_bin.h"

// 横式
__attribute__((section(".LynPortraitH")))
const struct Portrait LynPortraitH =
{
	LynMainPortraitH_bin,
//	0,
	0x8D3F2A8,
	0x8D3EC88,
	0x8D3ECA8,
	LynEyeFrameH_bin,
//	0,
	1,6,
	2,4,
	1,
	1,
	0,
	0
};

// 立式
__attribute__((section(".LynPortraitV")))
const struct Portrait LynPortraitV =
{
	LynMainPortraitV_bin,
//	0,
	0x8D3F2A8,
	0x8D3EC88,
	0x8D3ECA8,
	LynEyeFrameV_bin,
//	0,
	1,4,
	2,2,
	1,
	2,
	0,
	-2
};

