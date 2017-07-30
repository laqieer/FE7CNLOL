// 冰世界魔法动画
// by laqieer
// 2017/6/4

#pragma once

#include "FE7JCoroutine.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"

// 冰世界魔法动画主函数
void spellIceWorld(void *AIS);

// 冰世界魔法动画
void IceWorld(struct context *ctx);

/*
// 吹雪协程
#define	efxFubuki		((struct coroutine*)0x8C0127C)

// 冰晶协程
#define	efxIceCrystal	((struct coroutine*)0x8D6FB1C)

// 调色板渐变协程
#define	efxGradientPal		((struct coroutine*)0x8DAE4C4)
*/

// 吹雪背景图块(压缩后)
#define fubukiBGImgLZ	((void *)0x8198D98)

// 吹雪背景色板1
#define fubukiBGPal1	((void *)0x8199250)

// 吹雪背景色板2
#define fubukiBGPal2	((void *)0x8199270)

// 吹雪背景TSA
#define fubukiBGMap		((void *)0x8199290)

// 终末之冬的冰块
// void loadFimbulvetrBG(int a1);
#define loadFimbulvetrBG	sub(8059394)
// void loadFimbulvetrOBJ(int a1);
#define loadFimbulvetrOBJ	sub(805947C)
