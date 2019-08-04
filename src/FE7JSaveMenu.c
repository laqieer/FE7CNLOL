// 存档扩展UI菜单
// by laqieer
// 2018-08-03

#include "FE7JSave.h"

#include "FE7JCoroutine.h"
#include "AgbDebug.h"

// 读档时的章节标题界面菜单主循环函数
// void ChapterTitleLoadMenuMainLoop(struct context *ctx);
#define ChapterTitleLoadMenuMainLoop	sub(80A4B10)

// 加载读档时的章节标题界面菜单的章节标题文本
// void Load3ChapterTitleGfx(struct contect *ctx);
#define	Load3ChapterTitleGfx			sub(80A4254)

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