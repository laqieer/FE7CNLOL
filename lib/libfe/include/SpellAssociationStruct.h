// by laqieer
// 2017/1/28
// 魔法动画指定相关的结构体定义

#pragma once

#include "AgbTypes.h"

struct SpellAssociation
{
	u16 weaponID;
	u16 characterNo;
	u16 spellAnimationID;
	u16 dummy1;
	u32 alternatePoiner;
	u8 returning;
	u8 facing;
	u8 flashingColor;
	u8 dummy2;
};

enum Returning{returning_off,returning_on};
enum Facing{facing_target,facing_right,facing_up,facing_selected};
enum FlashingColor{flashingColor_white,flashingColor_dark,flashingColor_red,flashingColor_green,flashingColor_blue,flashingColor_yellow};
