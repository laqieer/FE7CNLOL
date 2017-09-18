// Fire Sea Spell Animation
// by laqieer
// 2017/9/17

#include "spellFireSea.h"

/*
// 修改火环调色板的透明色
__attribute__((section(".FireRingPaletteTColor")))
const u16 FireRingPaletteTColor = 0;
*/

/*
void ClearBG2Map()
{
	int src = 0;
	
	FE7JCPUFastSet(&src, BG2MapBuffer, 0x1000200u);
	SetBGMapSyncFlag(4u);
}
*/

void sub_807BFEC(struct context *ctx)
{
	// LOBYTE(BLDCNTBuffer) = BLDCNTBuffer & 0x3F | 0x40;
	BLDCNTBuffer = (BLDCNTBuffer & 0x3F | 0x40) | (BLDCNTBuffer & 0xFF00);
	BLDALPHABuffer = 0x1010;
	BLDYBuffer = 0;
	BLDCNTBuffer = (BLDCNTBuffer & 0xFFE0 | 1) & 0xE0FF | 0x1F00;
	isolateAndDeleteContext(findContext((struct coroutine *)0x8C01674));
//	sub(807BD00)(112, 32);
	*(u16 *)&ctx->userSpace[35] = 0;
	sub(8013EF8)(512, 512, 512, 256, 256, 256, -16, 4, ctx);
}

void sub_807C170()
{
  sub(8002DF0)(0);
  memClear2K(BG2MapBuffer, 0);
  // memClear2K(BG0MapBuffer, 0);
  // SetBGMapSyncFlag(5u);
  SetBGMapSyncFlag(4u);
/*  LOBYTE(BG0CNTBuffer) = BG0CNTBuffer & 0xFC;
  LOBYTE(BG1CNTBuffer) = BG1CNTBuffer & 0xFC | 1;
  LOBYTE(BG2CNTBuffer) = BG2CNTBuffer & 0xFC | 2;
  LOBYTE(BG3CNTBuffer) = BG3CNTBuffer | 3;
  LOBYTE(BLDCNTBuffer) = BLDCNTBuffer & 0x3F;	*/
  BG0CNTBuffer = BG0CNTBuffer & 0xFFFC;
  BG1CNTBuffer = BG1CNTBuffer & 0xFFFC | 1;
  BG2CNTBuffer = BG2CNTBuffer & 0xFFFC | 2;
  BG3CNTBuffer = BG3CNTBuffer | 3;
  BLDCNTBuffer = BLDCNTBuffer & 0xFF3F;
  BLDALPHABuffer = 0;
  BLDYBuffer = 0;
}

// 火环动画(有修改)
const struct coroutine efxFireRing[]={
	sleep(0),
	execFunc(sub(807BDFC)),
	sleep(0),
	setLoopFuncAndYield(sub(807BF08)),
	yield,
	setLabel(0),
	execFunc(sub(807B430)),
	execFunc(sub(807BF5C)),
/*	setLoopFuncAndYield(sub(807BF9C)),
	execFuncWithArgYieldIfReturn1(sub(80AB5E0),0),
	execFuncWithArgYieldIfReturn1(sub(8013F3C),0),	*/
	// execFunc(sub(807C170)),
	execFunc(sub_807C170),
	sleep(0),
	// execFunc(sub(807BFEC)),
	execFunc(sub_807BFEC),
	// execFuncWithArgYieldIfReturn1(sub(8013F3C),0),
	// setLoopFuncAndYield(sub(807C108)),	
	// execFuncWithArgYieldIfReturn1(sub(8013F3C),0),	
	// execFunc(sub(807C170)),
	execFunc(sub_807C170),
	execFunc(sub(807B43C)),	
	endofCoroutine
};

void FireSea(struct context *ctx)
{
	int v2,v3;
	u16 frameID;
	u8 *missOrHit;
	void* AIS;

	AIS = *(u32 *)&ctx->userSpace[51];
	v2 = sub(8054F90)(AIS);
	v3 = sub(8050F54)();
	missOrHit = ctx->userSpace;
	frameID = ++*(u16 *)&ctx->userSpace[3];
	if(1 == frameID)
		ScrollScreen(AIS,0xFFFF);
	switch(frameID - v3)
	{
		case 1:
			*(struct context **)&ctx->userSpace[63] = createContext(efxFireRing,ctx);
			// DEBUG("context of efxFireRing = 0x%x",*(struct context **)&ctx->userSpace[63])
			// loadFireRing(ctx);
			break;
		case 99:
			// isolateAndDeleteContext(*(struct context **)&ctx->userSpace[63]);
			letContextGotoLabel(*(struct context **)&ctx->userSpace[63],0);
			// EndFireRing();
			// ForceKillFireRing();
			break;
		case 100:
			loadFireSeaBG1(AIS,150);
			*(struct context **)&ctx->userSpace[63] = sub(80660F4)(AIS);
			*(struct context **)&ctx->userSpace[27] = sub(8066200)(AIS);
			*(struct context **)&ctx->userSpace[35] = sub(8066414)();
			*(struct context **)&ctx->userSpace[47] = sub(8066380)();
			*(struct context **)&ctx->userSpace[31] = loadFireSeaBG2(AIS);
			PlaySFX(752, 256, 120, 0);
			break;
		case 249:
			isolateAndDeleteContext(*(struct context **)&ctx->userSpace[63]);
			isolateAndDeleteContext(*(struct context **)&ctx->userSpace[27]);
			isolateAndDeleteContext(*(struct context **)&ctx->userSpace[35]);
			isolateAndDeleteContext(*(struct context **)&ctx->userSpace[47]);
			isolateAndDeleteContext(*(struct context **)&ctx->userSpace[31]);
			// 清掉两边的基石
			memClear2K(0x6005000,0); // 右侧
			memClear2K(0x6005800,0); // 左侧
			// 恢复两边的基石
			FE7JCPUFastSet(0x2015dc8,0x6005000,0x200);	// 右侧
			FE7JCPUFastSet(0x2014dc8,0x6005800,0x200);	// 左侧
			// ClearBG2Map();
			break;
		case 250:
			*(u16 *)(v2 + 16) |= 9u;
			reduceHPBar(v2,*missOrHit);
			if(!*missOrHit)
				playHitSound(v2);
			break;
		case 250+50:
			sub(80507D8)();
			breakLoop(ctx);
			break;
		default:
			break;
	}
	// 强制BG底色为黑色
	// *(u16 *)0x5000000 = 0;
	*BGPaletteBuffer = 0;
}

const struct coroutine efxFireSea[]={
	spellStart,
	setLoopFuncAndYield(FireSea),
	endofCoroutine
};

void spellFireSea(void *AIS)
{
	struct context *ctx;

	sub(80507CC)();
	sub(8050348)();
	sub(80507E4)();
	ctx = createContext(efxFireSea,3);
	*(void **)&ctx->userSpace[51] = AIS;
	*(u16 *)&ctx->userSpace[3] = 0;
	ctx->userSpace[0] = sub(8054E74)(sub(8054FEC)(AIS));
}

