// 战斗动画数据
// by laqieer
// 2019/4/20

#include "FE7JBattleAnimation.h"

#include "roy_sword_animation.h"

extern const unsigned char thief_f_sword_animation[];

// 指针表
const pBattleAnimation BattleAnimationPointerBank[] = {
	&roy_sword_animation, // 0x200
	thief_f_sword_animation, // 0x201
};