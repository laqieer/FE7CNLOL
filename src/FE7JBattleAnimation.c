// 改造战斗动画相关函数
// by laqieer
// 2017/6/13

#include "FE7JBattleAnimation.h"

// 扩展后的战斗动画协程
__attribute__((section(".ekrUnitKakudaiEx")))
const struct coroutine ekrUnitKakudaiEx[] =
{
	spellStart,
	setLoopFuncAndYield(UnitKakudai1Ex),
//	setLoopFuncAndYield(UnitKakudai1),
	setLoopFuncAndYield(UnitKakudai2),
	setLoopFuncAndYield(UnitKakudai3),
	endofCoroutine
};

// 战斗动画库地址表
const BattleAnimation * const battleAnimationBank[] =
{
	FE7BattleAnimationBank
};

// 读取战斗动画相关数据到内存
void battleAnimationInit()
{
  int animationID; // 动画ID
  int palSlotIDInPalGroup; // 用动画调色板组中的哪个槽
  int characterBattlePaletteID; // 人物指定动画调色板ID
  BattleAnimation *animation; // 战斗动画数据
  signed int animationID_PalGroup; // 用这个动画ID的调色板组
  short v10; // r0@10
  short v11; // r0@12
  int v12; // [sp+0h] [bp-24h]@10

  *(u32 *)0x201FB14 = 0;
  *(u32 *)0x201FB10 = 0;
  if ( IfBattleAnimationIsAtTheLeftSide == 1 )
  {
    animationID = BattleAnimationIDLeftSide;
    palSlotIDInPalGroup = BattleAnimationPalSlotLeftSide;
    characterBattlePaletteID = CharaterBattleAnimationPaletteIDLeftSide;
//    animation = FE7BattleAnimationBank + BattleAnimationIDLeftSide;
	animation = &battleAnimationBank[animationID>>8][animationID & 0xFF];
//    FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferLeftSide);

//	无压缩data2支持
	if(*(u8 *)(animation->event) == 0x10)
		FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferLeftSide);
	else
	{
		BattleAnimationEventBufferLeftSide[0] = 'l' + ('a'<<8) +('q'<<16);
		BattleAnimationEventBufferLeftSide[1] = animation->event;
	}
	
    BattleAnimationSectionInfoLeftSide = animation->sectionOffset;
    animationID_PalGroup = getAnimationIDForPaletteGroup(animationID, 0);
    FE7JLZ77UnCompWram(
//      FE7BattleAnimationBank[animationID_PalGroup].palGroup,
	  battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup,
      BattleAnimationPaletteGroupBufferLeftSide);
    if ( characterBattlePaletteID != -1 )
    {
      FE7JLZ77UnCompWram(
        characterBattlePalTable[characterBattlePaletteID].pal,
        BattleAnimationPaletteGroupBufferLeftSide);
      sub(8054798)(BattleAnimationPaletteGroupBufferLeftSide, 0);
    }
    BattleAnimationPaletteLeftSide = BattleAnimationPaletteGroupBufferLeftSide + 16 * palSlotIDInPalGroup;
    FE7JCPUFastSet(BattleAnimationPaletteGroupBufferLeftSide + 16 * palSlotIDInPalGroup, &OBJPaletteBuffer[112], 8u);
    FE7JCPUFastSet(*(void **)0x203E080, &OBJPaletteBuffer[128], 8u);
    EnablePaletteSync();
//    FE7JLZ77UnCompWram(animation->oamL2R, BattleAnimationOAML2RBuffer);
		
//	 无压缩data4支持
	if(*(u8 *)(animation->oamL2R) == 0x10)
		FE7JLZ77UnCompWram(animation->oamL2R, BattleAnimationOAML2RBuffer);
	else
	{
		((u32 *)BattleAnimationOAML2RBuffer)[0] = 'l' + ('a' << 8) + ('q' << 16);
		((void **)BattleAnimationOAML2RBuffer)[1] = animation->oamL2R;
	}

    *(u32 *)0x20099B8 = 1;
  }
  if ( IfBattleAnimationIsAtTheRightSide == 1 )
  {
    animationID = BattleAnimationIDRightSide;
    palSlotIDInPalGroup = BattleAnimationPalSlotRightSide;
    characterBattlePaletteID = CharaterBattleAnimationPaletteIDRightSide;
//    animation = FE7BattleAnimationBank + BattleAnimationIDRightSide;
	animation = &battleAnimationBank[animationID>>8][animationID & 0xFF];
//    FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferRightSide);

//	无压缩data2支持
	if(*(u8 *)(animation->event) == 0x10)
		FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferRightSide);
	else
	{
		BattleAnimationEventBufferRightSide[0] = 'l' + ('a'<<8) +('q'<<16);
		BattleAnimationEventBufferRightSide[1] = animation->event;
	}
	
    BattleAnimationSectionInfoRightSide = animation->sectionOffset;
    animationID_PalGroup = getAnimationIDForPaletteGroup(animationID, 1);
    FE7JLZ77UnCompWram(
//      FE7BattleAnimationBank[animationID_PalGroup].palGroup,
	  battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup,
      BattleAnimationPaletteGroupBufferRightSide);
    if ( characterBattlePaletteID != -1 )
    {
      FE7JLZ77UnCompWram(
        characterBattlePalTable[characterBattlePaletteID].pal,
        BattleAnimationPaletteGroupBufferRightSide);
      sub(8054798)(BattleAnimationPaletteGroupBufferRightSide, 1);
    }
    BattleAnimationPaletteRightSide = BattleAnimationPaletteGroupBufferRightSide + 16 * palSlotIDInPalGroup;
    FE7JCPUFastSet(BattleAnimationPaletteGroupBufferRightSide + 16 * palSlotIDInPalGroup, &OBJPaletteBuffer[144], 8u);
    FE7JCPUFastSet(*(void **)0x203E084, &OBJPaletteBuffer[160], 8u);
    EnablePaletteSync();
//    FE7JLZ77UnCompWram(animation->oamR2L, BattleAnimationOAMR2LBuffer);

//	 无压缩data3支持
	if(*(u8 *)(animation->oamR2L) == 0x10)
		FE7JLZ77UnCompWram(animation->oamR2L, BattleAnimationOAMR2LBuffer);
	else
	{
		((u32 *)BattleAnimationOAMR2LBuffer)[0] = 'l' + ('a' << 8) + ('q' << 16);
		((void **)BattleAnimationOAMR2LBuffer)[1] = animation->oamR2L;
	}
	
    *(u32 *)0x200F1B8 = 1;
  }
  if ( *(u32 *)0x203E078 )
  {
//    *(u16 **)0x203E080 = (char *)(FE7BattleAnimationBank->palGroup)
	animationID_PalGroup = sub(8053040)(*(u32 *)0x203E078, *(u32 *)(*(u32 *)(*(u32 *)0x203E078 + 4) + 52), 0, &v12);
	*(u16 **)0x203E080 = battleAnimationBank[animationID_PalGroup>>8][0xFF & animationID_PalGroup].palGroup;
//                           + (32 * sub(8053040)(*(u32 *)0x203E078, *(u32 *)(*(u32 *)(*(u32 *)0x203E078 + 4) + 52), 0, &v12) & 0x1FFFFF);
    v10 = sub(8053A14)(*(u32 *)0x203E078);
    if ( v10 != -1 )
      *(u16 **)0x203E080 = characterBattlePalTable[v10].pal;
//    *(u16 **)0x203E084 = (char *)(FE7BattleAnimationBank->palGroup)
//                           + (32 * sub(8053040)(*(u32 *)0x203E07C, *(u32 *)(*(u32 *)(*(u32 *)0x203E07C + 4) + 52), 0, &v12) & 0x1FFFFF);
	animationID_PalGroup = sub(8053040)(*(u32 *)0x203E07C, *(u32 *)(*(u32 *)(*(u32 *)0x203E07C + 4) + 52), 0, &v12);
	*(u16 **)0x203E084 = battleAnimationBank[animationID_PalGroup>>8][0xFF & animationID_PalGroup].palGroup;
	v11 = sub(8053A14)(*(u32 *)0x203E07C);
    if ( v11 != -1 )
      *(u16 **)0x203E084 = characterBattlePalTable[v11].pal;
  }
}


__attribute__((section(".callBattleAnimationInit")))
void callBattleAnimationInit()
{
	battleAnimationInit();
}

// 扩展后的UnitKakudai1
void UnitKakudai1Ex(struct context *ctx)
{
  int v2; // r6@1
  char *v3; // r1@5
  void *v4; // r0@5
  char *v5; // r1@7
  void *v6; // r0@7
  short v7; // r5@12
  short v8; // r3@12

  v2 = ((u32 *)0x81DE1E0)[*((u8 *)0x81DE208 + *(u16 *)0x203E004)] & 0xFF;
  battleAnimationInit();
  if ( !*(u32 *)&ctx->userSpace[27] && *(u16 *)0x203A3D4 & 0x40 )
    sub(806788C)(BGPaletteBuffer, 23, 1);
  if ( IfBattleAnimationIsAtTheLeftSide == 1 )
  {
//    v3 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v2];

//	无压缩data2支持
	if(BattleAnimationEventBufferLeftSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v3 = (char *)BattleAnimationEventBufferLeftSide[1] + BattleAnimationSectionInfoLeftSide[v2];
	else
		v3 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v2];
	
    v4 = (void *)*((u32 *)v3 + 1);
//    *(u32 *)&ctx->userSpace[43] = (char *)BattleAnimationOAML2RBuffer + *((u32 *)v3 + 2);

// 无压缩data4支持
	if(*(u32 *)BattleAnimationOAML2RBuffer == 'l' + ('a'<<8) + ('q'<<16))
		*(u32 *)&ctx->userSpace[43] = *((char **)BattleAnimationOAML2RBuffer + 1) + *((u32 *)v3 + 2);
	else
		*(u32 *)&ctx->userSpace[43] = (char *)BattleAnimationOAML2RBuffer + *((u32 *)v3 + 2);
	
    FE7JLZ77UnCompWram(v4, 0x2000088);
  }
  if ( IfBattleAnimationIsAtTheRightSide == 1 )
  {
//    v5 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[v2];

//	无压缩data2支持
	if(BattleAnimationEventBufferRightSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v5 = (char *)BattleAnimationEventBufferRightSide[1] + BattleAnimationSectionInfoRightSide[v2];
	else
		v5 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[v2];
	
    v6 = *((void **)v5 + 1);
//    *(u32 *)&ctx->userSpace[47] = (char *)BattleAnimationOAMR2LBuffer + *((u32 *)v5 + 2);

// 无压缩data3支持
	if(*(u32 *)BattleAnimationOAMR2LBuffer == 'l' + ('a'<<8) + ('q'<<16))
		*(u32 *)&ctx->userSpace[47] = *((char **)BattleAnimationOAMR2LBuffer + 1) + *((u32 *)v5 + 2);
	else
		*(u32 *)&ctx->userSpace[47] = (char *)BattleAnimationOAMR2LBuffer + *((u32 *)v5 + 2);
	
    FE7JLZ77UnCompWram(v6, 0x2002088);
  }
  if ( *(u32 *)0x203E088 )
    FE7JLZ77UnCompWram(*(void **)0x203E088, 0x2001088);
  if ( *(u32 *)0x203E08C )
    FE7JLZ77UnCompWram(*(void **)0x203E08C, 0x2003088);
  TileTransferInfoAdd(*(void **)0x2000088, (void *)0x6014000, 0x4000);
  *(u16 *)&ctx->userSpace[3] = 0;
  *(u16 *)&ctx->userSpace[5] = 11;
  *(u16 *)&ctx->userSpace[9] = 16 * *(u16 *)0x203E006 + 8;
  *(u16 *)&ctx->userSpace[17] = 16 * *(u16 *)0x203E008 + 8;
  *(u16 *)&ctx->userSpace[11] = 16 * *(u16 *)0x203E00A + 8;
  *(u16 *)&ctx->userSpace[19] = 16 * *(u16 *)0x203E00C + 8;
  v7 = ((unsigned char *)0x81DE20D)[*(u16 *)0x203E004];
  *(u16 *)&ctx->userSpace[13] = v7;
  v8 = ((unsigned char *)0x81DE212)[*(u16 *)0x203E004];
  *(u16 *)&ctx->userSpace[15] = v8;
  if ( *(u32 *)0x2017744 )
    *(u16 *)&ctx->userSpace[13] = v7 - *(*(u16 **)0x81DE218 + *(u16 *)0x203E004);
  else
    *(u16 *)&ctx->userSpace[15] = *(*(u16 **)0x81DE218 + *(u16 *)0x203E004) + v8;
  breakLoop(ctx);
}

/*
// 处理动画事件(扩展)
void battleAnimationEventHandlerEx()
{
  int v0; // r2@1
  int v1; // r7@2
  unsigned int v2; // r9@2
  signed int v3; // r8@3
  int v4; // r0@5
  unsigned int v5; // r1@6
  int v6; // r0@9
  __int16 v7; // r1@10
  int v8; // r0@13
  signed __int16 v9; // r1@15
  signed __int16 v10; // r0@16
  __int16 v11; // r1@17
  __int16 v12; // r1@20
  __int16 v13; // r1@21
  __int16 v14; // r2@23
  signed int v15; // r0@24
  int v16; // r4@24
  int v17; // r0@27
  __int16 v18; // r1@28
  __int16 v19; // r2@30
  int v20; // r0@32
  int v21; // r0@34
  __int16 v22; // r0@38
  signed int v23; // r0@38
  int v24; // r2@38
  __int16 v25; // r0@39
  bool v26; // r0@40
  int v27; // r0@46
  int v28; // r6@47
  unsigned int v29; // r0@47
  int v30; // r4@50
  int **v31; // r0@51
  int v32; // r4@53
  char *v33; // r1@53
  bool v34; // r0@53
  int v35; // r2@53
  bool v36; // r0@54
  bool v37; // r0@55
  __int16 v38; // r2@59
  __int16 v39; // r0@62
  __int16 v40; // r1@67
  int v41; // r0@70
  int v42; // r2@70
  int v43; // ST00_4@71
  __int16 v44; // r0@71
  int v45; // r0@71
  bool v46; // r0@73
  bool v47; // r0@82
  __int16 v48; // r1@99
  bool v49; // r0@109
  int v50; // r8@131
  int *v51; // r6@132
  signed __int16 v52; // r4@132
  bool v53; // r0@133
  bool v54; // r0@133
  int v55; // r6@137
  bool v56; // r0@139
  int a1; // [sp+0h] [bp-20h]@24
//  int a1a; // [sp+0h] [bp-20h]@35
//  int a1b; // [sp+0h] [bp-20h]@38
//  int a1c; // [sp+0h] [bp-20h]@47
//  int a1d; // [sp+0h] [bp-20h]@72
//  int a1e; // [sp+0h] [bp-20h]@132

  v0 = 0;
  do
  {
    *(u32 *)0x3004750 = v0;
    v1 = ((u32 *)0x2000000)[v0];
    v2 = v0 + 1;
    if ( v1 )
    {
//      LOWORD(v3) = *(_WORD *)(v1 + 12) & 0xF000;
//	  v3 = *(_WORD *)(v1 + 12) & 0xF000 | (v3 & 0xFFFF0000);
	  v3 = *(_WORD *)(v1 + 12) & 0xF000;
      if ( (_WORD)v3 )
      {
        if ( *(_WORD *)(v1 + 12) & 0x1000 )
        {
          while ( 1 )
          {
            v4 = *(_BYTE *)(v1 + 20);
            if ( !*(_BYTE *)(v1 + 20) )
              break;
            v5 = *(_BYTE *)(v1 + 21 + v4 - 1);
            if ( v5 <= 0x52 )
            {
              switch ( v5 )
              {
                case 1u:
                  if ( *(u32 *)0x2000024 == 1 )
                  {
                    v6 = *(_DWORD *)(v1 + 36);
                    goto LABEL_118;
                  }
                  v7 = *(_WORD *)(v1 + 16);
                  if ( !(v7 & 4) )
                    goto LABEL_117;
                  if ( v7 & 8 && sub(804DD50)() == 1 )
                  {
                    *(_WORD *)(v1 + 16) &= 0xFFF2u;
                    v8 = *(_DWORD *)(v1 + 32) + 4;
                    *(_DWORD *)(v1 + 32) = v8;
                    if ( sub(8050FE4)(v8) )
                      sub(8050FF0)(0);
                  }
                  break;
                case 2u:
                  v9 = *(_WORD *)(v1 + 16);
                  if ( !(v9 & 1) )
                    break;
                  v10 = -2;
                  goto LABEL_115;
                case 3u:
                  v11 = *(_WORD *)(v1 + 16);
                  if ( !(v11 & 0x20) )
                  {
                    *(_WORD *)(v1 + 16) = v11 | 0x20;
                    if ( !sub(8054E4C)(v1) )
                      sub(8063B64)(v1);
                  }
                  goto LABEL_20;
                case 4u:
                  v13 = *(_WORD *)(v1 + 16);
                  if ( !(v13 & 0x20) )
                    *(_WORD *)(v1 + 16) = v13 | 0x60;
                  v14 = *(_WORD *)(v1 + 16);
                  if ( !(v14 & 0x40) )
                    break;
                  *(_DWORD *)(v1 + 32) += 4;
                  *(_WORD *)(v1 + 16) = v14 & 0xFF9F | 9;
                  a1 = sub(8054F90)(v1);
                  v15 = sub(8054FEC)(v1) << 16;
                  v3 = v15 >> 16;
                  v16 = v15 >> 16;
                  if ( sub(8054E74)(v15 >> 16) != 1 )
                    break;
                  if ( !a1 )
                    break;
                  *(_WORD *)(a1 + 16) |= 9u;
                  if ( sub(8054E4C)(v1) )
                    break;
                  v17 = v16;
                  goto LABEL_46;
                case 5u:
                  v18 = *(_WORD *)(v1 + 16);
                  if ( !(v18 & 0x20) )
                    *(_WORD *)(v1 + 16) = v18 | 0x60;
                  v19 = *(_WORD *)(v1 + 16);
                  if ( v19 & 0x40 )
                  {
                    *(_DWORD *)(v1 + 32) += 4;
                    *(_WORD *)(v1 + 16) = v19 & 0xFF9F | 9;
                    if ( !sub(8054E4C)(v1) )
                    {
                      v20 = sub(8056070)(v1);
                      if ( sub(8050FE4)(v20) )
                        sub(8050FF0)(2);
                    }
                  }
                  break;
                case 6u:
                  v21 = sub(8054F90)(v1);
                  if ( v21 )
                  {
                    a1a = v21;
                    v3 = (signed __int16)sub(8055010)();
                    if ( v3 != -1 )
                      *(_WORD *)(a1a + 16) |= 2u;
                  }
                  break;
                case 8u:
                case 9u:
                case 0xAu:
                case 0xBu:
                case 0xCu:
                  if ( !sub(8054E4C)(v1) )
                  {
                    a1b = sub(8054F90)(v1);
                    v22 = sub(8054FEC)(v1);
//                    LOWORD(v3) = v22;
//					v3 = (v22 & 0xFFFF) | (v3 & 0xFFFF0000);
					v3 = v22;
                    v23 = sub(8054E74)(v22);
                    v24 = a1b;
                    if ( !v23 )
                    {
                      v25 = sub(80684B0)(a1b);
                      v24 = a1b;
                      if ( v25 != 2 )
                      {
                        v26 = sub(8054E60)(v1);
                        if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v26) & 0x1000 )
                          sub(80641B0)(a1b);
                        else
                          criticalEffect(a1b);
                        v24 = a1b;
                      }
                    }
                    if ( v24 )
                    {
                      *(_WORD *)(v24 + 16) |= 9u;
                      a1 = v24;
                      v17 = (signed __int16)sub(8054FEC)(v1);
//                      LOWORD(v3) = v17;
//					  v3 = (v17 & 0xFFFF) | (v3 & 0xFFFF0000);
					  v3 = v17;
LABEL_46:
                      v27 = sub(8054E74)(v17);
                      reduceHPBar(a1, v27);
                    }
                  }
                  break;
                case 0xDu:
                  v3 = (signed __int16)sub(8054FCC)(v1);
                  a1c = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
                  v28 = ((u32 *)0x2000000)[2 * sub(8054E60)(v1) + 1];
                  v29 = *(_BYTE *)(v1 + 18);
                  if ( v29 > 9 )
                    break;
                  switch ( v29 )
                  {
                    case 0u:
                    case 1u:
                    case 2u:
                    case 3u:
                    case 9u:
                      if ( v3 == -1 )
                        goto LABEL_56;
                      ++*(_WORD *)(a1c + 14);
                      ++*(_WORD *)(v28 + 14);
                      sub(8054D7C)(a1c, v3);
                      sub(8054D7C)(v28, v3);
                      *(_WORD *)(a1c + 16) |= 4u;
                      *(_WORD *)(v28 + 16) |= 4u;
                      v3 = *((_BYTE *)0x81DE208 + *(u16 *)0x203E004);
//                      v30 = LOBYTE(((u32 *)0x81DE1E0)[v3]);
					  v30 = ((u32 *)0x81DE1E0)[v3] & 0xFF;
                      if ( sub(8054E60)(v1) )
//                        v31 = &BattleAnimationSectionInfoRightSide;
						v31 = 0x2000060;
                      else
//                        v31 = &BattleAnimationSectionInfoLeftSide;
					  	v31 = 0x200005C;
                      v32 = (*v31)[v30];
                      v33 = (char *)BattleAnimationEventBufferLeftSide + 0x2A00 * sub(8054E60)(v1) + v32;
                      *(_DWORD *)(a1c + 40) = *((_DWORD *)v33 + 1);
                      *(_DWORD *)(a1c + 60) = *(_DWORD *)(a1c + 48) + *((_DWORD *)v33 + 2);
                      *(_DWORD *)(v28 + 60) = *(_DWORD *)(v28 + 48) + 0x57F0;
                      v34 = sub(8054E60)(v1);
                      v35 = a1c;
                      if ( !((u32 *)0x203E088)[v34] )
                      {
                        v36 = sub(8054E60)(a1c);
                        v35 = a1c;
                        if ( ((u32 *)0x201FB10)[v36] != *(_DWORD *)(a1c + 40) )
                        {
                          sub(8054734)(a1c);
                          v37 = sub(8054E60)(a1c);
                          v35 = a1c;
                          ((u32 *)0x201FB10)[v37] = *(_DWORD *)(a1c + 40);
                        }
                      }
                      goto LABEL_58;
                    case 4u:
                    case 5u:
LABEL_56:
                      v3 = *((_BYTE *)0x81DE208 + *(u16 *)0x203E004);
                      break;
                    case 6u:
                    case 7u:
                    case 8u:
                      break;
                    default:
                      goto def_8054080;
                  }
                  sub(8054D7C)(a1c, v3);
                  sub(8054D7C)(v28, v3);
                  v35 = a1c;
LABEL_58:
                  sub(80546F0)(v35);
                  sub(80546F0)(v28);
                  goto LABEL_120;
                case 0x13u:
                  v38 = *(_WORD *)(v1 + 16);
                  if ( !(v38 & 0x20) )
                  {
                    *(_WORD *)(v1 + 16) = v38 | 0x20;
                    break;
                  }
                  if ( *(u32 *)0x2017758 != 1 )
                    break;
                  *(u32 *)0x2017758 = 0;
                  v39 = v38 & 0xFFDF;
                  goto LABEL_116;
                case 0x14u:
                  if ( !sub(8054E4C)(v1) )
                    sub(804EFE0)(3);
                  break;
                case 0x15u:
                  if ( !sub(8054E4C)(v1) )
                    sub(804EFE0)(0);
                  break;
                case 0x18u:
                  v40 = *(_WORD *)(v1 + 16);
                  if ( v40 & 1 )
                  {
                    *(_WORD *)(v1 + 16) = v40 & 0xFFFE;
                    *(_DWORD *)(v1 + 32) += 4;
                    *(_WORD *)(v1 + 8) = *(_WORD *)(v1 + 8) & 0xF3FF | 0x400;
                    *(_WORD *)(v1 + 10) = 140;
                    sub(8006488)(140);
                  }
                  break;
                case 0x1Au:
                  if ( !sub(8054E4C)(v1) )
                  {
                    v41 = sub(8054F90)(v1);
                    v42 = v41;
                    if ( v41 )
                    {
                      *(_WORD *)(v41 + 16) |= 9u;
                      v43 = v41;
                      v44 = sub(8054FEC)(v1);
//                      LOWORD(v3) = v44;
//					  v3 = (v3 & 0xFFFF0000) | (v44 & 0xFFFF);
					  v3 = v44;
                      v45 = sub(8054E74)(v44);
                      reduceHPBar(v43, v45);
                      v42 = v43;
                    }
                    a1d = v42;
                    if ( (signed __int16)sub(80684B0)(v42) != 2 )
                    {
                      v46 = sub(8054E60)(v1);
                      if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v46) & 0x1000 )
                        sub(80641B0)(a1d);
                      else
                        normalAttackEffect(v1);
                    }
                  }
                  break;
                case 0x26u:
                  if ( !sub(8054E4C)(v1) )
                    sub(8062FE0)(v1, 0);
                  break;
                case 0x27u:
                  if ( !sub(8054E4C)(v1) )
                    sub(8062FE0)(v1, 1);
                  break;
                case 0x2Cu:
                  if ( !sub(8054E4C)(v1) )
                    sub(80631B0)(v1);
                  break;
                case 0x2Du:
                  v47 = sub(8054E60)(v1);
                  if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v47) & 0x1000) )
                    goto LABEL_117;
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                    goto LABEL_113;
                  *(_WORD *)(v1 + 16) = v12 | 0x20;
                  if ( !sub(8054E4C)(v1) )
                    sub(8064330)(v1, 0);
                  break;
                case 0x2Eu:
                  if ( !sub(8054E4C)(v1) )
                    sub(8063400)(v1, 0);
                  break;
                case 0x2Fu:
                  if ( !sub(8054E4C)(v1) )
                    sub(8063400)(v1, 1);
                  break;
                case 0x30u:
                  if ( !sub(8054E4C)(v1) )
                    sub(80635B4)(v1, 0);
                  break;
                case 0x31u:
                  if ( !sub(8054E4C)(v1) )
                    sub(80635B4)(v1, 1);
                  break;
                case 0x32u:
                  if ( !sub(8054E4C)(v1) )
                    sub(80635B4)(v1, 2);
                  break;
                case 0x39u:
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                    goto LABEL_113;
                  *(_WORD *)(v1 + 16) = v12 | 0x20;
                  if ( !sub(8054E4C)(v1) )
                    sub(80638F0)(v1);
                  break;
                case 0x3Du:
                  v48 = *(_WORD *)(v1 + 16);
                  if ( !(v48 & 0x20) )
                  {
                    *(_WORD *)(v1 + 16) = v48 | 0x20;
                    if ( !sub(8054E4C)(v1) )
                      sub(8050FF0)(1);
                    sub(8064458)(v1);
                    sub(8050FFC)(v1);
                  }
LABEL_20:
                  v12 = *(_WORD *)(v1 + 16);
                  goto LABEL_113;
                case 0x47u:
                  sub(8063FBC)(v1);
                  break;
                case 0x4Eu:
                  sub(8063804)(v1);
                  break;
                case 0x19u:
                case 0x1Bu:
                case 0x1Cu:
                case 0x1Du:
                case 0x1Eu:
                case 0x1Fu:
                case 0x20u:
                case 0x21u:
                case 0x22u:
                case 0x23u:
                case 0x24u:
                case 0x25u:
                case 0x28u:
                case 0x29u:
                case 0x2Au:
                case 0x2Bu:
                case 0x33u:
                case 0x34u:
                case 0x35u:
                case 0x36u:
                case 0x37u:
                case 0x38u:
                case 0x3Au:
                case 0x3Bu:
                case 0x3Cu:
                case 0x3Eu:
                case 0x3Fu:
                case 0x40u:
                case 0x41u:
                case 0x42u:
                case 0x43u:
                case 0x44u:
                case 0x45u:
                case 0x46u:
                case 0x48u:
                case 0x49u:
                case 0x4Au:
                case 0x4Bu:
                case 0x4Cu:
                case 0x4Du:
                case 0x4Fu:
                  sub(8067F90)(v1, *(_BYTE *)(v1 + 21 + v4 - 1));
                  break;
                case 0x51u:
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                    goto LABEL_113;
                  *(_WORD *)(v1 + 16) = v12 | 0x20;
                  if ( !sub(8054E4C)(v1) )
                    sub(806397C)(v1);
                  break;
                case 0x52u:
                  v49 = sub(8054E60)(v1);
                  if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v49) & 0x1000) )
                    goto LABEL_117;
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                  {
LABEL_113:
                    if ( v12 & 0x40 )
                    {
                      v10 = v12 & 0xFFDF;
                      v9 = -65;
LABEL_115:
                      v39 = v10 & v9;
LABEL_116:
                      *(_WORD *)(v1 + 16) = v39;
LABEL_117:
                      v6 = *(_DWORD *)(v1 + 32) + 4;
LABEL_118:
                      *(_DWORD *)(v1 + 32) = v6;
                    }
                  }
                  else
                  {
                    *(_WORD *)(v1 + 16) = v12 | 0x20;
                    if ( !sub(8054E4C)(v1) )
                      sub(8064330)(v1, 1);
                  }
                  break;
                default:
                  break;
              }
            }
def_8054080:
            --*(_BYTE *)(v1 + 20);
          }
LABEL_120:
          *(_WORD *)(v1 + 12) &= 0xE700u;
        }
        if ( v3 & 0x2000 )
        {
          if ( !sub(8054E4C)(v1)
            && !((u32 *)0x203E088)[sub(8054E60)(v1)]
            && !(*(_WORD *)(v1 + 16) & 0x4000)
            && ((u32 *)0x201FB10)[sub(8054E60)(v1)] != *(_DWORD *)(v1 + 40) )
          {
            sub(8054764)(v1);
            ((u32 *)0x201FB10)[sub(8054E60)(v1)] = *(_DWORD *)(v1 + 40);
          }
          *(_WORD *)(v1 + 12) &= 0xD700u;
        }
        if ( v3 & 0x4000 || *(u32 *)0x2000024 == 1 )
        {
          if ( *(_WORD *)(v1 + 16) & 2 )
          {
            v50 = (signed __int16)sub(8054FCC)(v1);
            if ( v50 == -1 )
            {
              v53 = sub(8054E60)(v1);
              *(_WORD *)(((u32 *)0x2000000)[2 * v53] + 16) &= 0xFFFDu;
              v54 = sub(8054E60)(v1);
              *(_WORD *)(((u32 *)0x2000000)[2 * v54 + 1] + 16) &= 0xFFFDu;
              goto LABEL_141;
            }
            v51 = *(u32 *)0x2000000;
            a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
            sub(8054D7C)(a1e, v50);
            v52 = -3;
LABEL_137:
            *(_WORD *)(a1e + 16) = v52 & *(_WORD *)(a1e + 16) | 4;
            v55 = v51[2 * sub(8054E60)(v1) + 1];
            sub(8054D7C)(v55, v50);
            *(_WORD *)(v55 + 16) = v52 & *(_WORD *)(v55 + 16) | 4;
            ++*(_WORD *)(a1e + 14);
            ++*(_WORD *)(v55 + 14);
            sub(80546F0)(a1e);
            sub(80546F0)(v55);
            goto LABEL_141;
          }
          if ( *(_WORD *)(v1 + 16) & 0x8000 )
          {
            v50 = (signed __int16)sub(8054FCC)(v1);
            if ( v50 == -1 )
              goto LABEL_141;
            v51 = *(u32 *)0x2000000;
            a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
            sub(8054D7C)(a1e, v50);
            v52 = 0x7FFF;
            goto LABEL_137;
          }
          if ( !sub(8054E4C)(v1) )
          {
            v56 = sub(8054E60)(v1);
            if ( (signed __int16)sub(8053AD4)(2 * *(_WORD *)(v1 + 14) + v56) == -1 )
              ((u32 *)0x201FAF8)[sub(8054E60)(v1)] = 1;
          }
        }
      }
    }
LABEL_141:
    v0 = v2;
  }
  while ( v2 <= 3 );
}
*/

/*
// 处理动画事件
void battleAnimationEventHandlerEx()
{
	int v0; // r2@1
	int v1; // r7@2
	unsigned int v2; // r9@2
	signed int v3; // r8@3
	int v4; // r0@5
	unsigned int v5; // r1@6
	int v6; // r0@9
	__int16 v7; // r1@10
	signed __int16 v8; // r1@15
	signed __int16 v9; // r0@16
	__int16 v10; // r1@17
	__int16 v11; // r1@20
	__int16 v12; // r1@21
	__int16 v13; // r2@23
	signed int v14; // r0@24
	int v15; // r4@24
	int v16; // r0@27
	__int16 v17; // r1@28
	__int16 v18; // r2@30
	int v19; // r0@34
	__int16 v20; // r0@38
	signed int v21; // r0@38
	int v22; // r2@38
	__int16 v23; // r0@39
	bool v24; // r0@40
	int v25; // r0@46
	int v26; // r6@47
	unsigned int v27; // r0@47
	int v28; // r4@50
	int **v29; // r0@51
	int v30; // r4@53
	char *v31; // r1@53
	bool v32; // r0@53
	int v33; // r2@53
	bool v34; // r0@54
	bool v35; // r0@55
	__int16 v36; // r2@59
	__int16 v37; // r0@62
	__int16 v38; // r1@67
	int v39; // r0@70
	int v40; // r2@70
	int v41; // ST00_4@71
	__int16 v42; // r0@71
	int v43; // r0@71
	bool v44; // r0@73
	bool v45; // r0@82
	__int16 v46; // r1@99
	bool v47; // r0@109
	int v48; // r8@131
	int *v49; // r6@132
	signed __int16 v50; // r4@132
	bool v51; // r0@133
	bool v52; // r0@133
	int v53; // r6@137
	bool v54; // r0@139
	int a1; // [sp+0h] [bp-20h]@24
	int a1a; // [sp+0h] [bp-20h]@35
	int a1b; // [sp+0h] [bp-20h]@38
	int a1c; // [sp+0h] [bp-20h]@47
	int a1d; // [sp+0h] [bp-20h]@72
	int a1e; // [sp+0h] [bp-20h]@132

	v0 = 0;
	do
	{
		(*(u32 *)0x3004750) = v0;
		v1 = ((u32 *)0x2000000)[v0];
		v2 = v0 + 1;
		if ( v1 )
		{
			LOWORD(v3) = *(_WORD *)(v1 + 12) & 0xF000;
			if ( (_WORD)v3 )
			{
				if ( *(_WORD *)(v1 + 12) & 0x1000 )
				{
					while ( 1 )
					{
						v4 = *(_BYTE *)(v1 + 20);
						if ( !*(_BYTE *)(v1 + 20) )
							break;
						v5 = *(_BYTE *)(v1 + 21 + v4 - 1);
						if ( v5 <= 0x52 )
						{
							switch ( v5 )
							{
								case 1u:
									if ( (*(u32 *)0x2000024) == 1 )
									{
										v6 = *(_DWORD *)(v1 + 36);
										goto LABEL_118;
									}
									v7 = *(_WORD *)(v1 + 16);
									if ( !(v7 & 4) )
										goto LABEL_117;
									if ( v7 & 8 && sub(804DD50)() == 1 )
									{
										*(_WORD *)(v1 + 16) &= 0xFFF2u;
										*(_DWORD *)(v1 + 32) += 4;
										if ( sub(8050FE4)() )
											sub(8050FF0)(0);
									}
									break;
								case 2u:
									v8 = *(_WORD *)(v1 + 16);
									if ( !(v8 & 1) )
										break;
									v9 = -2;
									goto LABEL_115;
								case 3u:
									v10 = *(_WORD *)(v1 + 16);
									if ( !(v10 & 0x20) )
									{
										*(_WORD *)(v1 + 16) = v10 | 0x20;
										if ( !sub(8054E4C)(v1) )
											sub(8063B64)(v1);
									}
									goto LABEL_20;
								case 4u:
									v12 = *(_WORD *)(v1 + 16);
									if ( !(v12 & 0x20) )
										*(_WORD *)(v1 + 16) = v12 | 0x60;
									v13 = *(_WORD *)(v1 + 16);
									if ( !(v13 & 0x40) )
										break;
									*(_DWORD *)(v1 + 32) += 4;
									*(_WORD *)(v1 + 16) = v13 & 0xFF9F | 9;
									a1 = sub(8054F90)(v1);
									v14 = sub(8054FEC)(v1) << 16;
									v3 = v14 >> 16;
									v15 = v14 >> 16;
									if ( sub(8054E74)(v14 >> 16) != 1 )
										break;
									if ( !a1 )
										break;
									*(_WORD *)(a1 + 16) |= 9u;
									if ( sub(8054E4C)(v1) )
										break;
									v16 = v15;
									goto LABEL_46;
								case 5u:
									v17 = *(_WORD *)(v1 + 16);
									if ( !(v17 & 0x20) )
										*(_WORD *)(v1 + 16) = v17 | 0x60;
									v18 = *(_WORD *)(v1 + 16);
									if ( v18 & 0x40 )
									{
										*(_DWORD *)(v1 + 32) += 4;
										*(_WORD *)(v1 + 16) = v18 & 0xFF9F | 9;
										if ( !sub(8054E4C)(v1) )
										{
											sub(8056070)(v1);
											if ( sub(8050FE4)() )
												sub(8050FF0)(2);
										}
									}
									break;
								case 6u:
									v19 = sub(8054F90)(v1);
									if ( v19 )
									{
										a1a = v19;
										v3 = (signed __int16)sub(8055010)();
										if ( v3 != -1 )
											*(_WORD *)(a1a + 16) |= 2u;
									}
									break;
								case 8u:
								case 9u:
								case 0xAu:
								case 0xBu:
								case 0xCu:
									if ( !sub(8054E4C)(v1) )
									{
										a1b = sub(8054F90)(v1);
										v20 = sub(8054FEC)(v1);
										LOWORD(v3) = v20;
										v21 = sub(8054E74)(v20);
										v22 = a1b;
										if ( !v21 )
										{
											v23 = sub(80684B0)(a1b);
											v22 = a1b;
											if ( v23 != 2 )
											{
												v24 = sub(8054E60)(v1);
												if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v24) & 0x1000 )
													sub(80641B0)(a1b);
												else
													criticalEffect(a1b);
												v22 = a1b;
											}
										}
										if ( v22 )
										{
											*(_WORD *)(v22 + 16) |= 9u;
											a1 = v22;
											v16 = (signed __int16)sub(8054FEC)(v1);
											LOWORD(v3) = v16;
LABEL_46:
											v25 = sub(8054E74)(v16);
											reduceHPBar(a1, v25);
										}
									}
									break;
								case 0xDu:
									v3 = (signed __int16)sub(8054FCC)(v1);
									a1c = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
									v26 = ((u32 *)0x2000000)[2 * sub(8054E60)(v1) + 1];
									v27 = *(_BYTE *)(v1 + 18);
									if ( v27 > 9 )
										break;
									switch ( v27 )
									{
										case 0u:
										case 1u:
										case 2u:
										case 3u:
										case 9u:
											if ( v3 == -1 )
												goto LABEL_56;
											++*(_WORD *)(a1c + 14);
											++*(_WORD *)(v26 + 14);
											sub(8054D7C)(a1c, v3);
											sub(8054D7C)(v26, v3);
											*(_WORD *)(a1c + 16) |= 4u;
											*(_WORD *)(v26 + 16) |= 4u;
											v3 = *((_BYTE *)0x81DE208 + (*(u16 *)0x203E004));
											v28 = LOBYTE(((u32 *)0x81DE1E0)[v3]);
											if ( sub(8054E60)(v1) )
												v29 = &BattleAnimationSectionInfoRightSide;
											else
												v29 = &BattleAnimationSectionInfoLeftSide;
											v30 = (*v29)[v28];
											v31 = (char *)BattleAnimationEventBufferLeftSide + 0x2A00 * sub(8054E60)(v1) + v30;
											*(_DWORD *)(a1c + 40) = *((_DWORD *)v31 + 1);
											*(_DWORD *)(a1c + 60) = *(_DWORD *)(a1c + 48) + *((_DWORD *)v31 + 2);
											*(_DWORD *)(v26 + 60) = *(_DWORD *)(v26 + 48) + 0x57F0;
											v32 = sub(8054E60)(v1);
											v33 = a1c;
											if ( !((u32 *)0x203E088)[v32] )
											{
												v34 = sub(8054E60)(a1c);
												v33 = a1c;
												if ( ((u32 *)0x201FB10)[v34] != *(_DWORD *)(a1c + 40) )
												{
													sub(8054734)(a1c);
													v35 = sub(8054E60)(a1c);
													v33 = a1c;
													((u32 *)0x201FB10)[v35] = *(_DWORD *)(a1c + 40);
												}
											}
											goto LABEL_58;
										case 4u:
										case 5u:
LABEL_56:
											v3 = *((_BYTE *)0x81DE208 + (*(u16 *)0x203E004));
											break;
										case 6u:
										case 7u:
										case 8u:
											break;
										default:
											goto def_8054080;
									}
									sub(8054D7C)(a1c, v3);
									sub(8054D7C)(v26, v3);
									v33 = a1c;
LABEL_58:
									sub(80546F0)(v33);
									sub(80546F0)(v26);
									goto LABEL_120;
								case 0x13u:
									v36 = *(_WORD *)(v1 + 16);
									if ( !(v36 & 0x20) )
									{
										*(_WORD *)(v1 + 16) = v36 | 0x20;
										break;
									}
									if ( (*(u32 *)0x2017758) != 1 )
										break;
									(*(u32 *)0x2017758) = 0;
									v37 = v36 & 0xFFDF;
									goto LABEL_116;
								case 0x14u:
									if ( !sub(8054E4C)(v1) )
										sub(804EFE0)(3);
									break;
								case 0x15u:
									if ( !sub(8054E4C)(v1) )
										sub(804EFE0)(0);
									break;
								case 0x18u:
									v38 = *(_WORD *)(v1 + 16);
									if ( v38 & 1 )
									{
										*(_WORD *)(v1 + 16) = v38 & 0xFFFE;
										*(_DWORD *)(v1 + 32) += 4;
										*(_WORD *)(v1 + 8) = *(_WORD *)(v1 + 8) & 0xF3FF | 0x400;
										*(_WORD *)(v1 + 10) = 140;
										sub(8006488)(140);
									}
									break;
								case 0x1Au:
									if ( !sub(8054E4C)(v1) )
									{
										v39 = sub(8054F90)(v1);
										v40 = v39;
										if ( v39 )
										{
											*(_WORD *)(v39 + 16) |= 9u;
											v41 = v39;
											v42 = sub(8054FEC)(v1);
											LOWORD(v3) = v42;
											v43 = sub(8054E74)(v42);
											reduceHPBar(v41, v43);
											v40 = v41;
										}
										a1d = v40;
										if ( (signed __int16)sub(80684B0)(v40) != 2 )
										{
											v44 = sub(8054E60)(v1);
											if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v44) & 0x1000 )
												sub(80641B0)(a1d);
											else
												normalEffect(v1);
										}
									}
									break;
								case 0x26u:
									if ( !sub(8054E4C)(v1) )
										sub(8062FE0)(v1, 0);
									break;
								case 0x27u:
									if ( !sub(8054E4C)(v1) )
										sub(8062FE0)(v1, 1);
									break;
								case 0x2Cu:
									if ( !sub(8054E4C)(v1) )
										sub(80631B0)(v1);
									break;
								case 0x2Du:
									v45 = sub(8054E60)(v1);
									if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v45) & 0x1000) )
										goto LABEL_117;
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
										goto LABEL_113;
									*(_WORD *)(v1 + 16) = v11 | 0x20;
									if ( !sub(8054E4C)(v1) )
										sub(8064330)(v1, 0);
									break;
								case 0x2Eu:
									if ( !sub(8054E4C)(v1) )
										sub(8063400)(v1, 0);
									break;
								case 0x2Fu:
									if ( !sub(8054E4C)(v1) )
										sub(8063400)(v1, 1);
									break;
								case 0x30u:
									if ( !sub(8054E4C)(v1) )
										sub(80635B4)(v1, 0);
									break;
								case 0x31u:
									if ( !sub(8054E4C)(v1) )
										sub(80635B4)(v1, 1);
									break;
								case 0x32u:
									if ( !sub(8054E4C)(v1) )
										sub(80635B4)(v1, 2);
									break;
								case 0x39u:
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
										goto LABEL_113;
									*(_WORD *)(v1 + 16) = v11 | 0x20;
									if ( !sub(8054E4C)(v1) )
										sub(80638F0)(v1);
									break;
								case 0x3Du:
									v46 = *(_WORD *)(v1 + 16);
									if ( !(v46 & 0x20) )
									{
										*(_WORD *)(v1 + 16) = v46 | 0x20;
										if ( !sub(8054E4C)(v1) )
											sub(8050FF0)(1);
										sub(8064458)(v1);
										sub(8050FFC)(v1);
									}
LABEL_20:
									v11 = *(_WORD *)(v1 + 16);
									goto LABEL_113;
								case 0x47u:
									sub(8063FBC)(v1);
									break;
								case 0x4Eu:
									sub(8063804)(v1);
									break;
								case 0x19u:
								case 0x1Bu:
								case 0x1Cu:
								case 0x1Du:
								case 0x1Eu:
								case 0x1Fu:
								case 0x20u:
								case 0x21u:
								case 0x22u:
								case 0x23u:
								case 0x24u:
								case 0x25u:
								case 0x28u:
								case 0x29u:
								case 0x2Au:
								case 0x2Bu:
								case 0x33u:
								case 0x34u:
								case 0x35u:
								case 0x36u:
								case 0x37u:
								case 0x38u:
								case 0x3Au:
								case 0x3Bu:
								case 0x3Cu:
								case 0x3Eu:
								case 0x3Fu:
								case 0x40u:
								case 0x41u:
								case 0x42u:
								case 0x43u:
								case 0x44u:
								case 0x45u:
								case 0x46u:
								case 0x48u:
								case 0x49u:
								case 0x4Au:
								case 0x4Bu:
								case 0x4Cu:
								case 0x4Du:
								case 0x4Fu:
									sub(8067F90)(v1, *(_BYTE *)(v1 + 21 + v4 - 1));
									break;
								case 0x51u:
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
										goto LABEL_113;
									*(_WORD *)(v1 + 16) = v11 | 0x20;
									if ( !sub(8054E4C)(v1) )
										sub(806397C)(v1);
									break;
								case 0x52u:
									v47 = sub(8054E60)(v1);
									if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v47) & 0x1000) )
										goto LABEL_117;
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
									{
LABEL_113:
										if ( v11 & 0x40 )
										{
											v9 = v11 & 0xFFDF;
											v8 = -65;
LABEL_115:
											v37 = v9 & v8;
LABEL_116:
											*(_WORD *)(v1 + 16) = v37;
LABEL_117:
											v6 = *(_DWORD *)(v1 + 32) + 4;
LABEL_118:
											*(_DWORD *)(v1 + 32) = v6;
										}
									}
									else
									{
										*(_WORD *)(v1 + 16) = v11 | 0x20;
										if ( !sub(8054E4C)(v1) )
											sub(8064330)(v1, 1);
									}
									break;
								default:
									break;
							}
						}
def_8054080:
						--*(_BYTE *)(v1 + 20);
					}
LABEL_120:
					*(_WORD *)(v1 + 12) &= 0xE700u;
				}
				if ( v3 & 0x2000 )
				{
					if ( !sub(8054E4C)(v1)
						&& !((u32 *)0x203E088)[sub(8054E60)(v1)]
						&& !(*(_WORD *)(v1 + 16) & 0x4000)
						&& ((u32 *)0x201FB10)[sub(8054E60)(v1)] != *(_DWORD *)(v1 + 40) )
					{
						sub(8054764)(v1);
						((u32 *)0x201FB10)[sub(8054E60)(v1)] = *(_DWORD *)(v1 + 40);
					}
					*(_WORD *)(v1 + 12) &= 0xD700u;
				}
				if ( v3 & 0x4000 || (*(u32 *)0x2000024) == 1 )
				{
					if ( *(_WORD *)(v1 + 16) & 2 )
					{
						v48 = (signed __int16)sub(8054FCC)(v1);
						if ( v48 == -1 )
						{
							v51 = sub(8054E60)(v1);
							*(_WORD *)(((u32 *)0x2000000)[2 * v51] + 16) &= 0xFFFDu;
							v52 = sub(8054E60)(v1);
							*(_WORD *)(((u32 *)0x2000000)[2 * v52 + 1] + 16) &= 0xFFFDu;
							goto LABEL_141;
						}
						v49 = (*(u32 *)0x2000000);
						a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
						sub(8054D7C)(a1e, v48);
						v50 = -3;
LABEL_137:
						*(_WORD *)(a1e + 16) = v50 & *(_WORD *)(a1e + 16) | 4;
						v53 = v49[2 * sub(8054E60)(v1) + 1];
						sub(8054D7C)(v53, v48);
						*(_WORD *)(v53 + 16) = v50 & *(_WORD *)(v53 + 16) | 4;
						++*(_WORD *)(a1e + 14);
						++*(_WORD *)(v53 + 14);
						sub(80546F0)(a1e);
						sub(80546F0)(v53);
						goto LABEL_141;
					}
					if ( *(_WORD *)(v1 + 16) & 0x8000 )
					{
						v48 = (signed __int16)sub(8054FCC)(v1);
						if ( v48 == -1 )
							goto LABEL_141;
						v49 = (*(u32 *)0x2000000);
						a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
						sub(8054D7C)(a1e, v48);
						v50 = 0x7FFF;
						goto LABEL_137;
					}
					if ( !sub(8054E4C)(v1) )
					{
						v54 = sub(8054E60)(v1);
						if ( (signed __int16)sub(8053AD4)(2 * *(_WORD *)(v1 + 14) + v54) == -1 )
							((u32 *)0x201FAF8)[sub(8054E60)(v1)] = 1;
					}
				}
			}
		}
LABEL_141:
		v0 = v2;
	}
	while ( v2 <= 3 );
}
*/

__attribute__((section(".callBattleAnimationEventHandlerEx")))
void callBattleAnimationEventHandlerEx()
{
	battleAnimationEventHandlerEx();
}

