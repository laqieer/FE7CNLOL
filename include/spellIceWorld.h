// ������ħ������
// by laqieer
// 2017/6/4

#pragma once

#include "FE7JCoroutine.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"

// ������ħ������������
void spellIceWorld(void *AIS);

// ������ħ������
void IceWorld(struct context *ctx);

/*
// ��ѩЭ��
#define	efxFubuki		((struct coroutine*)0x8C0127C)

// ����Э��
#define	efxIceCrystal	((struct coroutine*)0x8D6FB1C)

// ��ɫ�彥��Э��
#define	efxGradientPal		((struct coroutine*)0x8DAE4C4)
*/

// ��ѩ����ͼ��(ѹ����)
#define fubukiBGImgLZ	((void *)0x8198D98)

// ��ѩ����ɫ��1
#define fubukiBGPal1	((void *)0x8199250)

// ��ѩ����ɫ��2
#define fubukiBGPal2	((void *)0x8199270)

// ��ѩ����TSA
#define fubukiBGMap		((void *)0x8199290)

// ��ĩ֮���ı���
// void loadFimbulvetrBG(int a1);
#define loadFimbulvetrBG	sub(8059394)
// void loadFimbulvetrOBJ(int a1);
#define loadFimbulvetrOBJ	sub(805947C)
