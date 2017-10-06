// 职业战斗动画配置
// by laqieer
// 2017/10/5

#include "ClassBattleAnimationConfig.h"

const BattleAnimationConf NilsBattleAnimationConf[] = {
	{{Disarmed},1,0x8E},
	{{AllAnima},1,0x8E},
	{{AllLight},1,0x8E},
	{{AllDark},1,0x8E},
	{{FillaMight},0,0x104+1},
	{{NinisGrace},0,0x8E},
	{{ThorIre},0,0x8E},	
	{{SetLitany},0,0x8E},
	{{AllDragonStones},1,0x100+1},
	// {{AllDragonStones},1,0x103+1},
	endBattleAnimationConf
};

__attribute__((section(".NilsBattleAnimationConf")))
const BattleAnimationConf * const NilsBattleAnimationConfAddr = NilsBattleAnimationConf;

// 解锁吟游诗人使用龙石
__attribute__((section(".BardAbility")))
const u32 BardAbility = (1<<5)|(1<<18);

// 关掉尼尔斯的个人调色板
__attribute__((section(".DisableNilsCharacterPalette")))
const u8 DisableNilsCharacterPalette = 0;

// 灼热的吐息的射程改为1
__attribute__((section(".FlametongueRange")))
const u8 FlametongueRange = 0x11;
