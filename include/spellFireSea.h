// Fire Sea Spell Animation
// by laqieer
// 2017/9/17

#pragma once

#include "FE7JMemoryMap.h"
#include "FE7JFunc.h"
#include "FE7JCoroutine.h"

void spellFireSea(void *AIS);

#define	loadFireSeaBG1	sub(8066CAC)
// void loadFireSeaBG1(void *AIS, __int16 duration);
#define	loadFireSeaBG2	sub(80662F4)
// struct context *loadFireSeaBG2(void *AIS);

// ��
// #define	efxFireRing		((struct coroutine *)0x8D6F8BC)
// ��ʼ�𻷶���
#define	loadFireRing	sub(807C1E8)
// void loadFireRing(signed int parent);
// �����𻷶���
#define	EndFireRing		sub(807C210)
// void EndFireRing();
// ǿ����ֹ�𻷶���
#define	ForceKillFireRing	sub(807C1FC)
// void ForceKillFireRing();

// ��������
// #define	__DEBUG
#include "AgbDebug.h"
