// 职业战斗动画配置相关定义
// by laqieer
// 2017/10/5

#pragma once

#include "AgbTypes.h"
#include "FE7JItemList.h"

typedef struct {
	union {
		u8 weaponType;
		u8 weaponID;
	} id;
	u8 type; // 0-weaponID,1-weaponType
	u16 animationID;
} BattleAnimationConf;

// weaponType
#define	AllSwords	0
#define	AllSpears	1
#define	AllAxes		2
#define	AllBows		3
#define	AllStaves	4
#define	AllAnima	5
#define	AllLight	6
#define AllDark		7
#define	Disarmed	9
#define	AllDragonStones	0xB
#define	AllMonsters		0xB
#define	AllRings		0xC

// To separate animation chains, you must add a set of five 00s.
#define	endBattleAnimationConf {{0},0,0},{{0},0,0}
