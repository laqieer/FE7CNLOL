// 存档扩展UI菜单
// by laqieer
// 2018-08-03

#include "FE7JSave.h"

#include "FE7JCoroutine.h"
#include "AgbDebug.h"

// 读档时的章节标题界面菜单主循环函数
// void ChapterTitleLoadMenuMainLoop(struct context *ctx);
#define ChapterTitleLoadMenuMainLoop	sub(80A4B10)

// 加载读档时的章节标题界面菜单的章节标题文本（3条）
// void Load3ChapterTitleGfx(struct contect *ctx);
#define	Load3ChapterTitleGfx			sub(80A4254)

// 加载读档时的章节标题界面菜单的章节标题文本（单条）
// void LoadChapterTitleGfx(int tileNum, unsigned int chapterID);
#define	LoadChapterTitleGfx				sub(8082E2C)

// 游戏中菜单一级菜单中显示选项
// _BYTE *EnableItemInSavemenu(struct context *ctx, u8 flag);
#define EnableItemInSavemenu			sub(80A6CA8)

// 游戏中菜单附加内容子菜单中显示选项
// _BYTE *EnableItemInExtramenu(struct context *ctx, u8 flag);
#define EnableItemInExtramenu			sub(80A6CBC)

/*
void EndSaveMenu(struct context *ctx)
{
  struct context *v2; // r0
  int v3; // r2
  int v4; // r0
  u8 *v5; // r4

  v2 = *(struct context **)&ctx->userSpace[55];
  if ( v2 )
    isolateAndDeleteContextWrapper(v2);
  isolateAndDeleteContext(*(struct context **)&ctx->userSpace[47]);
  isolateAndDeleteContext(*(struct context **)&ctx->userSpace[51]);
  SetPrimaryHBlankCallback(0);
  v3 = *(unsigned __int16 *)&ctx->userSpace[25];
  if ( v3 == 32 )
  {
    v4 = ctx->userSpace[12];
    if ( v4 == 1 )
    {
      SetNextGameActionId(6u);
    }
    else if ( v4 == 16 )
    {
      SetNextGameActionId(7u);
    }
  }
  else if ( !(v3 & 0x40) )
  {
    if ( v3 & 0x100 )
    {
      StartSongVolumeTransitionB(192, 256, 16, 0);
      if ( *(_WORD *)&ctx->userSpace[25] & 0x80 )
        SetNextGameActionId(0xBu);
      else
        SetNextGameActionId(5u);
    }
    else if ( v3 & 1 )
    {
      LoadSuspendedGame(3);
      SetNextGameActionId(4u);
    }
    else if ( v3 & 0x82 )
    {
      v5 = &ctx->userSpace[3];
      LoadGame(*v5);
      SetNextGameActionId(*v5 + 1);
    }
    else if ( v3 & 0x10 )
    {
      SetNextGameActionId(0);
    }
  }
}
*/

void EndSaveMenuEx(struct context *ctx)
{
  struct context *v2; // r0
  int v3; // r2
  int v4; // r0
  u8 *v5; // r4
  enum saveslot saveslotNum;

  v2 = *(struct context **)&ctx->userSpace[55];
  if ( v2 )
    isolateAndDeleteContextWrapper(v2);
  isolateAndDeleteContext(*(struct context **)&ctx->userSpace[47]);
  isolateAndDeleteContext(*(struct context **)&ctx->userSpace[51]);
  SetPrimaryHBlankCallback(0);
  v3 = *(unsigned __int16 *)&ctx->userSpace[25];
  if ( v3 == 32 )
  {
    v4 = ctx->userSpace[12];
    if ( v4 == 1 )
    {
      SetNextGameActionId(6u);
    }
    else if ( v4 == 16 )
    {
      SetNextGameActionId(7u);
    }
  }
  else if ( !(v3 & 0x40) )
  {
    if ( v3 & 0x100 )
    {
      StartSongVolumeTransitionB(192, 256, 16, 0);
      if ( *(_WORD *)&ctx->userSpace[25] & 0x80 )
        SetNextGameActionId(0xBu);
      else
        SetNextGameActionId(5u);
    }
    else if ( v3 & 1 )
    {
      LoadSuspendedGame(3);
      SetNextGameActionId(4u);
    }
    else if ( v3 & 0x82 )
    {
      v5 = &ctx->userSpace[3];
	  saveslotNum = saveslotNumTable[*v5 + 3 * (*(u8 *)&ctx->userSpace[66] & 3)];
	  DEBUG("load save slot %d", saveslotNum)
	  LoadGame(saveslotNum);
      SetNextGameActionId(*v5 + 1);
    }
    else if ( v3 & 0x10 )
    {
      SetNextGameActionId(0);
    }
  }
}

#ifndef __INTELLISENSE__
__attribute__((section(".pEndSaveMenu1")))
#endif
void (*const pEndSaveMenu1)(struct context *) = EndSaveMenuEx;

#ifndef __INTELLISENSE__
__attribute__((section(".pEndSaveMenu2")))
#endif
void (*const pEndSaveMenu2)(struct context *) = EndSaveMenuEx;

#ifndef __INTELLISENSE__
__attribute__((section(".pEndSaveMenu3")))
#endif
void (*const pEndSaveMenu3)(struct context *) = EndSaveMenuEx;
/*
void readChapterInfoInSaveslot(enum saveslot saveslotNum, struct context *ctx)
{
  u8 *v6; // r5
  int chapterData; // [sp+0h] [bp-58h]
  u8 v8; // [sp+Ch] [bp-4Ch]
  char v9; // [sp+14h] [bp-44h]
  char v10; // [sp+1Bh] [bp-3Dh]
  
  if ( saveslotNum > 2 )
  {
    if ( *(_WORD *)&ctx->userSpace[27] == 256 )
    {
      if ( sub_80A1D18(3) << 24 )
      {
        sub_80A1D6C(3, (int)&chapterData);
        ctx->userSpace[22] = v8;
        *(_DWORD *)&ctx->userSpace[43] = chapterData;
      }
      else
      {
        *(_WORD *)&ctx->userSpace[27] = 240;
      }
    }
  }
  else if ( CheckSaveslot(saveslotNum) )
  {
    ReadSaveslotChapterData(saveslotNum, &chapterData);
    ctx->userSpace[saveslotNum + 14] = sub_8082F30((char *)&chapterData);
    *(_DWORD *)&ctx->userSpace[4 * saveslotNum + 31] = chapterData;
    v6 = &ctx->userSpace[saveslotNum + 17];
    *v6 = 0;
    if ( sub_80A1398(saveslotNum) << 24 )
      *v6 |= 1u;
    if ( sub_80A1384((int)&chapterData) << 24 )
      *v6 |= 2u;
    *((_BYTE *)&dword_2000064 + saveslotNum) = v9;
    *((_BYTE *)&dword_2000068 + saveslotNum) = v10;
  }
  else
  {
    ctx->userSpace[saveslotNum + 14] = -1;
    ctx->userSpace[saveslotNum + 17] = 0;
    *(_DWORD *)&ctx->userSpace[4 * saveslotNum + 31] = 0;
    *((_BYTE *)&dword_2000064 + saveslotNum) = 0;
    *((_BYTE *)&dword_2000068 + saveslotNum) = 0;
  }
}
*/

// 汇编实现
extern void readChapterInfoInSaveslotEx(enum saveslot saveslotNum, struct context *ctx, int i);

// fixme: when multiple keys are pressed at the same time
void ChapterTitleLoadMenuMainLoopEx(struct context *ctx)
{
	enum saveslot saveslotNum;
	int pageNum;
	int i;
	
	// Select Key to select save slot page
	// 3 save slots per page, 4 pages, 12 save slots in total
	if(gKeyNewPresses & 4)
	{
		/*
		// calculate current saveslotNum
		saveslotNum = *(u8 *)&ctx->userSpace[3];
		if(saveslotNum <= Saveslot3)
			saveslotNum += Saveslot4;
		else
			if(saveslotNum >= Saveslot10)
				saveslotNum -= Saveslot10;
			else
				saveslotNum += 3;
		*(u8 *)&ctx->userSpace[3] = saveslotNum;
		DEBUG("saveslotNum = %d", saveslotNum)
		// calculate the first saveslotNum in the page
		if(saveslotNum <= Saveslot3)
			saveslotNum = Saveslot1;
		else
			if(saveslotNum <= Saveslot6)
				saveslotNum = Saveslot4;
			else
				if(saveslotNum <= Saveslot9)
					saveslotNum = Saveslot7;
				else
					if(saveslotNum <= Saveslot12)
						saveslotNum = Saveslot10;
					else
						saveslotNum = Saveslot1;
		// refresh the chapter titles in the page
		for(i = 0; i < 3; i++)
			sub(80A7058)(saveslotNum+i, ctx);
		Load3ChapterTitleGfx(ctx);
		*/
		
		// sound effect
		m4aSongNumStart(0x387);
		
		// page number is stored in the last byte of the context
		pageNum = *(u8 *)&ctx->userSpace[66] & 3;
		if(pageNum == 3)
			pageNum = 0;
		else
			pageNum++;
		*(u8 *)&ctx->userSpace[66] = pageNum & 3;
		DEBUG("pageNum = %d", pageNum)
		for(i = 0; i < 3; i++)
//			sub(80A7058)(saveslotNumTable[3 * pageNum] + i, ctx);
//			readChapterInfoInSaveslot(saveslotNumTable[3 * pageNum] + i, ctx);
			readChapterInfoInSaveslotEx(saveslotNumTable[3 * pageNum] + i, ctx, i);
		Load3ChapterTitleGfx(ctx);
	}
	else
	{
		// convert current save slot number for A Key
		if(gKeyNewPresses & 1)
		{
			saveslotNum = *(u8 *)&ctx->userSpace[3];
			*(u8 *)&ctx->userSpace[3] = saveslotNumTable[saveslotNum + 3 * (*(u8 *)&ctx->userSpace[66] & 3)];
		}
		ChapterTitleLoadMenuMainLoop(ctx);
		// restore current save slot number for A Key
		if(gKeyNewPresses & 1)
		{
			*(u8 *)&ctx->userSpace[3] = saveslotNum;
		}
	}
}

#ifndef __INTELLISENSE__
__attribute__((section(".pChapterTitleLoadMenuMainLoop1")))
#endif
void (*const pChapterTitleLoadMenuMainLoop1)(struct context *) = ChapterTitleLoadMenuMainLoopEx;

#ifndef __INTELLISENSE__
__attribute__((section(".pChapterTitleLoadMenuMainLoop2")))
#endif
void (*const pChapterTitleLoadMenuMainLoop2)(struct context *) = ChapterTitleLoadMenuMainLoopEx;

#ifndef __INTELLISENSE__
__attribute__((section(".pChapterTitleLoadMenuMainLoop3")))
#endif
void (*const pChapterTitleLoadMenuMainLoop3)(struct context *) = ChapterTitleLoadMenuMainLoopEx;

/*void sub_80A4D80(struct context *ctx)
{
  u8 *v2; // r3
  int v3; // r0
  int v4; // r1
  u8 *v5; // r2
  int v6; // r0
  unsigned int v7; // r1
  u8 *v8; // r10
  __int16 v9; // r6
  __int16 v10; // r5
  __int16 v11; // r4
  __int16 v12; // ST04_2
  __int16 v13; // r8
  __int16 v14; // r5
  __int16 v15; // r4
  __int16 v16; // ST04_2
  __int16 v17; // r6
  __int16 v18; // r5
  __int16 v19; // r4
  __int16 v20; // r0

  v2 = ctx->userSpace;
  v3 = ctx->userSpace[0];
  if ( v3 == 8 )
  {
    sub(80A7058)(ctx->userSpace[3], ctx);
    sub(80A7058)(4, ctx);
    v4 = ctx->userSpace[3];
    v5 = &ctx->userSpace[v4 + 14];
    if ( *v5 == 255 )
      LoadChapterTitleGfx((((ctx->userSpace[3] << 11) + 0x16800) & 0x1FFFFu) >> 5, 0xFFFFFFFF);
    else
      LoadChapterTitleGfx((((ctx->userSpace[3] << 11) + 0x16800) & 0x1FFFFu) >> 5, *v5);
    sub(80A715C)(ctx->userSpace[3]);
    goto LABEL_20;
  }
  if ( v3 == 32 )
  {
    sub(80A6CD0)(ctx);
    v6 = *(unsigned __int16 *)&ctx->userSpace[25];
    if ( v6 == 16 )
    {
      letContextGotoLabel(ctx, 18);
      StartSongVolumeTransitionB(192, 0, 16, 0);
    }
    else if ( v6 == 64 )
    {
      letContextGotoLabel(ctx, 17);
    }
    else if ( sub(80A6EE0)(ctx) << 24 )
    {
      if ( ctx->userSpace[4] == 255 )
      {
        ctx->userSpace[3] = sub(80A6DD4)(ctx->userSpace[3], 1, 1);
      }
      else
      {
        ctx->userSpace[3] = ctx->userSpace[4];
        ctx->userSpace[4] = -1;
      }
      letContextGotoLabel(ctx, 5);
    }
    goto LABEL_20;
  }
  if ( v3 != 48 )
  {
LABEL_20:
    v7 = ctx->userSpace[0];
    v8 = ctx->userSpace;
    if ( v7 == 16 )
    {
      v9 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
      v10 = Div(-16 * *(short *)(0x80C0E24 + 4 * 29), 256);
      v11 = Div(16 * *(short *)(0x80C0E24 + 4 * 29), 256);
      v12 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
      SetOBJAttribute(ctx->userSpace[3], v9, v10, v11, v12);
    }
    else if ( v7 > 7 )
    {
      if ( v7 <= 0xF )
      {
        v17 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
        v18 = Div(-16 * *(short *)(0x80C0E24 + 4 * 29), 32 * *v8 - 224);
        v19 = Div(16 * *(short *)(0x80C0E24 + 4 * 29), 256);
        v20 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 32 * *v8 - 224);
        SetOBJAttribute(ctx->userSpace[3], v17, v18, v19, v20);
      }
    }
    else
    {
      v13 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
      v14 = Div(-16 * *(short *)(0x80C0E24 + 4 * 29), 256 - 32 * *v8);
      v15 = Div(16 * *(short *)(0x80C0E24 + 4 * 29), 256);
      v16 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256 - 32 * *v8);
      SetOBJAttribute(ctx->userSpace[3], v13, v14, v15, v16);
    }
    ++*v8;
    return;
  }
  ctx->userSpace[3] = 0;
  ctx->userSpace[4] = -1;
  *v2 = 0;
  ctx->userSpace[2] = 0;
  *(_WORD *)&ctx->userSpace[25] = (unsigned __int8)sub(80A3FE0)(ctx->userSpace[7], 0);
  if ( !(*(u8 *)0x202BC35 & 2) )
    m4aSongNumStart(0x38Bu);
  letContextGotoLabel(ctx, 4);
}	*/

void sub_80A4D80_Ex(struct context *ctx)
{
  u8 *v2; // r3
  int v3; // r0
  int v4; // r1
  u8 *v5; // r2
  int v6; // r0
  unsigned int v7; // r1
  u8 *v8; // r10
  __int16 v9; // r6
  __int16 v10; // r5
  __int16 v11; // r4
  __int16 v12; // ST04_2
  __int16 v13; // r8
  __int16 v14; // r5
  __int16 v15; // r4
  __int16 v16; // ST04_2
  __int16 v17; // r6
  __int16 v18; // r5
  __int16 v19; // r4
  __int16 v20; // r0
  int pageNum;

  v2 = ctx->userSpace;
  v3 = ctx->userSpace[0];
  pageNum = *(u8 *)&ctx->userSpace[66] & 3;
  if ( v3 == 8 )
  {
    v4 = ctx->userSpace[3];
    readChapterInfoInSaveslotEx(saveslotNumTable[3 * pageNum] + v4, ctx, v4);
    sub(80A7058)(4, ctx);
    v5 = &ctx->userSpace[v4 + 14];
    if ( *v5 == 255 )
      LoadChapterTitleGfx((((v4 << 11) + 0x16800) & 0x1FFFFu) >> 5, 0xFFFFFFFF);
    else
      LoadChapterTitleGfx((((v4 << 11) + 0x16800) & 0x1FFFFu) >> 5, *v5);
    sub(80A715C)(v4);
    goto LABEL_20;
  }
  if ( v3 == 32 )
  {
    sub(80A6CD0)(ctx);
    v6 = *(unsigned __int16 *)&ctx->userSpace[25];
    if ( v6 == 16 )
    {
      letContextGotoLabel(ctx, 18);
      StartSongVolumeTransitionB(192, 0, 16, 0);
    }
    else if ( v6 == 64 )
    {
      letContextGotoLabel(ctx, 17);
    }
    else if ( sub(80A6EE0)(ctx) << 24 )
    {
      if ( ctx->userSpace[4] == 255 )
      {
        ctx->userSpace[3] = sub(80A6DD4)(ctx->userSpace[3], 1, 1);
      }
      else
      {
        ctx->userSpace[3] = ctx->userSpace[4];
        ctx->userSpace[4] = -1;
      }
      letContextGotoLabel(ctx, 5);
    }
    goto LABEL_20;
  }
  if ( v3 != 48 )
  {
LABEL_20:
    v7 = ctx->userSpace[0];
    v8 = ctx->userSpace;
    if ( v7 == 16 )
    {
      v9 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
      v10 = Div(-16 * *(short *)(0x80C0E24 + 4 * 29), 256);
      v11 = Div(16 * *(short *)(0x80C0E24 + 4 * 29), 256);
      v12 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
      SetOBJAttribute(ctx->userSpace[3], v9, v10, v11, v12);
    }
    else if ( v7 > 7 )
    {
      if ( v7 <= 0xF )
      {
        v17 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
        v18 = Div(-16 * *(short *)(0x80C0E24 + 4 * 29), 32 * *v8 - 224);
        v19 = Div(16 * *(short *)(0x80C0E24 + 4 * 29), 256);
        v20 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 32 * *v8 - 224);
        SetOBJAttribute(ctx->userSpace[3], v17, v18, v19, v20);
      }
    }
    else
    {
      v13 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256);
      v14 = Div(-16 * *(short *)(0x80C0E24 + 4 * 29), 256 - 32 * *v8);
      v15 = Div(16 * *(short *)(0x80C0E24 + 4 * 29), 256);
      v16 = Div(16 * *(short *)(0x80C0E24 + 4 * 61), 256 - 32 * *v8);
      SetOBJAttribute(ctx->userSpace[3], v13, v14, v15, v16);
    }
    ++*v8;
    return;
  }
  ctx->userSpace[3] = 0;
  ctx->userSpace[4] = -1;
  *v2 = 0;
  ctx->userSpace[2] = 0;
  *(_WORD *)&ctx->userSpace[25] = (unsigned __int8)sub(80A3FE0)(ctx->userSpace[7], 0);
  if ( !(*(u8 *)0x202BC35 & 2) )
    m4aSongNumStart(0x38Bu);
  letContextGotoLabel(ctx, 4);
}

#ifndef __INTELLISENSE__
__attribute__((section(".pSub80A4D80_1")))
#endif
void (*const pSub80A4D80_1)(struct context *) = sub_80A4D80_Ex;

#ifndef __INTELLISENSE__
__attribute__((section(".pSub80A4D80_2")))
#endif
void (*const pSub80A4D80_2)(struct context *) = sub_80A4D80_Ex;

#pragma long_calls
bool sub_80A6E44_Ex(struct context *ctx, u8 DeltaY);
#pragma long_calls_off

bool sub_80A6E44_Ex(struct context *ctx, u8 DeltaY)
{
	int index;
	int OffsetY;
	
	OffsetY = DeltaY << 24;
	index = ctx->userSpace[3] & 3;
	if(OffsetY <= 0)
	{
		if(index)
			index--;
		else
			index = 2;
	}
	else
	{
		if(index == 2)
			index = 0;
		else
			index++;		
	}
	ctx->userSpace[3] = index & 3;
	return 1;
}

// enable to select all chapter titles in the menu
#ifndef __INTELLISENSE__
__attribute__((section(".call_sub_80A6E44_Ex")))
#endif
bool call_sub_80A6E44_Ex(struct context *ctx, u8 DeltaY)
{
	return sub_80A6E44_Ex(ctx, DeltaY);
}

// 计算主菜单中包含哪些选项，按位标识存储在userSpace[7]中
/*void CalculateItemsShowInSavemenu(struct context *ctx)
{
  signed int v2; // r5
  u8 *v3; // r0
  signed int v4; // r1
  _BYTE *v5; // r0

  v2 = 0;
  v3 = &ctx->userSpace[8];
  *v3-- = 0;
  *v3 = 0;
  ctx->userSpace[9] = 0;
  v3[3] = 0;
  if ( *(_WORD *)&ctx->userSpace[27] == 256 )
    sub(80A6CA8)(ctx, 1);
  v4 = 0;
  do
  {
    if ( ctx->userSpace[v4 + 14] != 255 )
      ++v2;
    ++v4;
  }
  while ( v4 <= 2 );
  if ( v2 > 0 )
  {
    EnableItemInSavemenu(ctx, 2);
    if ( v2 <= 2 )
      EnableItemInSavemenu(ctx, 4);
    EnableItemInSavemenu(ctx, 8);
  }
  if ( v2 <= 2 )
    EnableItemInSavemenu(ctx, 16);
  if ( sub(809F490)() << 24 )
    EnableItemInExtramenu(ctx, 1);
  if ( sub(809F4C8)() << 24 )
    EnableItemInExtramenu(ctx, 2);
  v5 = (_BYTE *)(sub(809F4F0)() << 24);
  if ( v5 )
    v5 = EnableItemInExtramenu(ctx, 4);
  if ( sub(809F50C)(v5) )
    EnableItemInExtramenu(ctx, 8);
  EnableItemInExtramenu(ctx, 16);
  if ( sub(809F5B0)() << 24 )
    EnableItemInExtramenu(ctx, 32);
  if ( sub(809F588)() << 24 )
    EnableItemInExtramenu(ctx, 64);
  if ( ctx->userSpace[9] )
  {
    ctx->userSpace[7] |= 0x20u;
    ++ctx->userSpace[8];
  }
}	*/

void CalculateItemsShowInSavemenuEx(struct context *ctx)
{
  u8 *v3; // r0
  _BYTE *v5; // r0

  v3 = &ctx->userSpace[8];
  *v3-- = 0;
  *v3 = 0;
  ctx->userSpace[9] = 0;
  v3[3] = 0;
  if ( *(_WORD *)&ctx->userSpace[27] == 256 )
    sub(80A6CA8)(ctx, 1);
  EnableItemInSavemenu(ctx, 2);
  EnableItemInSavemenu(ctx, 4);
  EnableItemInSavemenu(ctx, 8);
  EnableItemInSavemenu(ctx, 16);
  if ( sub(809F490)() << 24 )
    EnableItemInExtramenu(ctx, 1);
  if ( sub(809F4C8)() << 24 )
    EnableItemInExtramenu(ctx, 2);
  v5 = (_BYTE *)(sub(809F4F0)() << 24);
  if ( v5 )
    v5 = EnableItemInExtramenu(ctx, 4);
  if ( sub(809F50C)(v5) )
    EnableItemInExtramenu(ctx, 8);
  EnableItemInExtramenu(ctx, 16);
  if ( sub(809F5B0)() << 24 )
    EnableItemInExtramenu(ctx, 32);
  if ( sub(809F588)() << 24 )
    EnableItemInExtramenu(ctx, 64);
  if ( ctx->userSpace[9] )
  {
    ctx->userSpace[7] |= 0x20u;
    ++ctx->userSpace[8];
  }
}

#ifndef __INTELLISENSE__
__attribute__((section(".callCalculateItemsShowInSavemenu")))
#endif
void callCalculateItemsShowInSavemenu(struct context *ctx)
{
	CalculateItemsShowInSavemenuEx(ctx);
}