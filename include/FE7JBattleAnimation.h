// by laqieer
// 支持战斗动画分成多个表
// 2017/6/13
// 支持无压缩的data2/3/4,无需解压至内存
// 2017/6/20

#pragma once

#include "AgbTypes.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"
#include "FE7JCoroutine.h"
#include "IDAPro.h"

#pragma long_calls
// 读取战斗动画相关数据到内存
void battleAnimationInit();
#pragma long_calls_off

void callBattleAnimationInit();

// 日版烈火战斗动画库
#define	FE7BattleAnimationBank	((BattleAnimation *)0x8E00008)

// 战斗动画结构体定义
typedef	struct {
	char identifier[12];	// 标识符(字符串)
	int	*sectionOffset; // 第一个指针(指向动画各部分划分偏移表)
	void *event;			// 第二个指针(指向动画脚本(由指令或者称为事件组成))
	void *oamR2L;			// 第三个指针指向OAM数据(在右侧朝左侧)
	void *oamL2R;			// 第四个指针指向OAM数据(在左侧朝右侧)
	void *palGroup;			// 第五个指针指向调色板组
} BattleAnimation;

// 人物个别战斗动画调色板列表
#define	characterBattlePalTable	((CharacterBattlePal *)0x8FD8008)

// 人物个别战斗动画调色板信息结构体定义
typedef struct {
	char identifier[12];	// 标识符(字符串)
	void *pal;				// 指向调色板
} CharacterBattlePal;

// 战斗动画相关全局变量

// 战斗动画位于左侧
#define	IfBattleAnimationIsAtTheLeftSide	(*(u16 *)0x203DFE8)
// 战斗动画位于右侧
#define	IfBattleAnimationIsAtTheRightSide	(*(u16 *)0x203DFEA)
// 左侧战斗动画ID
#define	BattleAnimationIDLeftSide			(*(u16 *)0x203E066)
// 右侧战斗动画ID
#define	BattleAnimationIDRightSide			(*(u16 *)0x203E068)
// 左侧战斗动画调色板组中序号
#define	BattleAnimationPalSlotLeftSide		(*(u16 *)0x203DFF8)
// 右侧战斗动画调色板组中序号
#define	BattleAnimationPalSlotRightSide		(*(u16 *)0x203DFFA)
// 左侧人物个别战斗调色板ID
#define	CharaterBattleAnimationPaletteIDLeftSide	(*(u16 *)0x203DFF4)
// 右侧人物个别战斗调色板ID
#define	CharaterBattleAnimationPaletteIDRightSide	(*(u16 *)0x203DFF6)
// 左侧战斗动画事件脚本缓存
#define	BattleAnimationEventBufferLeftSide			((u32 *)0x200F1C8)
// 右侧战斗动画事件脚本缓存
#define	BattleAnimationEventBufferRightSide			((u32 *)0x2011BC8)
// 左侧动画的各模式分割信息地址
#define	BattleAnimationSectionInfoLeftSide			(*(int **)0x200005C)
// 右侧动画的各模式分割信息地址
#define	BattleAnimationSectionInfoRightSide			(*(int **)0x2000060)
// 左侧动画调色板组缓存
#define	BattleAnimationPaletteGroupBufferLeftSide	((u16 *)0x2004088)
// 右侧动画调色板组缓存
#define	BattleAnimationPaletteGroupBufferRightSide	((u16 *)0x2004128)	
// 左侧动画调色板地址
#define	BattleAnimationPaletteLeftSide				(*(u16 **)0x2000054)
// 右侧动画调色板地址
#define	BattleAnimationPaletteRightSide				(*(u16 **)0x2000058)
// 左侧动画OAM信息缓存
#define	BattleAnimationOAML2RBuffer					((void *)0x20041C8)
// 右侧动画OAM信息缓存
#define	BattleAnimationOAMR2LBuffer					((void *)0x20099C8)

// 相关函数

// 返回用哪个动画ID的调色板组
// 作用:对某些特殊ID的动画更换调色板组
// signed int getAnimationIDForPaletteGroup(int animationID, int RightOrLeft);
#define	getAnimationIDForPaletteGroup	sub(80547C0)

// 定义战斗动画库枚举值表
enum {
	FE7BABank
};

// ekrUnitKakudai协程组
#define	ekrUnitKakudai		((struct coroutine *)0x8C0A560)
#define	UnitKakudai1	sub(8051F38)
#define	UnitKakudai2	sub(80520C4)
#define	UnitKakudai3	sub(805226C)

// 扩展后的UnitKakudai1
void UnitKakudai1Ex(struct context *ctx);

// 处理动画事件(扩展)
//#pragma long_calls
//void battleAnimationEventHandlerEx();
//#pragma long_calls_off

//void callBattleAnimationEventHandlerEx();

// 原来的战斗动画事件处理程序
// void battleAnimationEventHandler();
#define	battleAnimationEventHandler	sub(8053C3C)

/*
// 定义变量的别名
#define a1a a1
#define a1b a1
#define a1c a1
#define a1d a1
#define a1e a1
*/

#pragma long_calls
void sub_8054AC0(int xl, int xr);
#pragma long_calls_off

void call_sub_8054AC0(int xl, int xr);

// 战斗双方AIS初始化
// xl和xr分别为左右双方偏离中央的距离
// 进接攻击: xl = xr = 6
// 远程攻击: xl = xr = 8
// void battleAnimationAISInit(int xl,int xr);
#define battleAnimationAISInit	sub_8054AC0


#pragma long_calls
void sub_8054D7C(int a1, int a2);
#pragma long_calls_off

void call_sub_8054D7C(int a1, int a2);

// 判断动画是在左边还是右边
// bool isUnitAtRightOrLeft(int AIS);
#define isUnitAtRightOrLeft		sub(8054E60)
