// 冰世界魔法动画
// by laqieer
// 2017/6/4

#include "spellIceWorld.h"

// 冰世界魔法主协程
struct coroutine efxIceWorld[]={
	spellStart,
	setLoopFuncAndYield(IceWorld),
	endofCoroutine
};

// 冰世界主函数
void spellIceWorld(void *AIS)
{
	struct context *ctx;

	sub(80507CC)();
	sub(8050348)();
	sub(80507E4)();
	ctx = createContext(efxIceWorld,3);
	*(void **)&ctx->userSpace[51] = AIS;
	*(u16 *)&ctx->userSpace[3] = 0;
	ctx->userSpace[0] = sub(8054E74)(sub(8054FEC)(AIS));
}

// 冰世界魔法动画
// 废弃
/*
void IceWorld(struct context *ctx)
{
	int v2,v3;
	u16 frameID;
	u8 *missOrHit;
	void* AIS;
//	struct context *ctxFubukiParent,*ctxIceCrystalParent;
//	struct context *ctxFubuki,*ctxIceCrystal;

	AIS = *(u32 *)&ctx->userSpace[51];
	v2 = sub(8054F90)(AIS);
	v3 = sub(8050F54)();
	frameID = ++*(u16 *)&ctx->userSpace[3];
	if(1 == frameID)
		ScrollScreen(AIS,0xFFFF);
	if(1 == frameID - v3)
	{
//		关掉BG0
		DISPCNTBuffer &= ~(1<<8);
//		ctxFubukiParent = createContext(efxSpellCast,4);
//		loadFubuki(ctxFubukiParent);	
		loadFubuki(createContext(efxSpellCast,4));
//		loadFubuki(0x2025330);
//		loadFubuki(ctx);
//		ctxFubuki = createContext(efxFubuki,3);
//		*(u16 *)&ctxFubuki->userSpace[3] = 0x1E;	
	}	
	if(85 == frameID - v3)
	{
//		loadIceCrystal(0x2025330);
//		DISPCNTBuffer &= ~(1<<8);
//		ctxIceCrystalParent = createContext(efxSpellCast,4);
//		loadIceCrystal(ctxIceCrystalParent);
//		killACoroutine(efxGradientPal);
//		killACoroutine(efxFubuki);		
		loadIceCrystal(createContext(efxSpellCast,4));
//		ctxIceCrystal = createContext(efxIceCrystal,3);
//		*(u16 *)&ctxIceCrystal->userSpace[35] = 0;	
	}	
	if(88 == frameID - v3)
	{
		*(u16 *)(v2 + 16) |= 9u;
	    missOrHit = ctx->userSpace;
    	reduceHPBar(v2, *missOrHit);
    	if ( !*missOrHit )
      		playHitSound((void *)v2);
	}
	if(136 != frameID - v3 && 161 == frameID - v3)
	{
		killACoroutine(efxGradientPal);
		killACoroutine(efxFubuki);
		killACoroutine(0x8D6F7EC);
		killACoroutine(efxIceCrystal);
		killACoroutine(efxSpellCast);
		sub(80507D8)();
    	sub(80503A0)();
		// 打开BG0
//		DISPCNTBuffer |= 1<<8;
//		execFuncForAllFollowingContext(ctxFubukiParent,callIsolateAndDeleteContext);
//		execFuncForAllFollowingContext(ctxIceCrystalParent,callIsolateAndDeleteContext);
//		deleteContext(ctxFubukiParent);
    	breakLoop(ctx);
	}
}
*/

void fubuki1(struct context *ctx)
{
	// 开启alpha渲染
	BLDCNTBuffer = BLDALPHABuffer & 0xFF3F | 0x40;
	// 设置第二层混合参数EVB=16
	BLDALPHABuffer = 0x1000;
	// 清BLDY
	BLDYBuffer = 0;
	// 设置第一层为BG1,第二层为BG3和OBJ
	BLDCNTBuffer = (BLDCNTBuffer & 0xFFE0 | 2) & 0xE0FF | 0x1800;
	// 写Tile(魔法动画Tile从0x6001C00(Tile=224)开始)
	AutoCopyOrDecompressImageToVRAM(fubukiBGImgLZ,spellBGTile);
	// 写调色板
//	OutputToBGPaletteBuffer(fubukiBGPal1,0x180,32);	// 0x5000180对应BG调色板12(从0开始数)
//	OutputToBGPaletteBuffer(fubukiBGPal1,0x1E0,32);
//	FE7JCPUFastSet(fubukiBGPal1,0x5000180,32>>2);
//	BGPaletteBufferSyncFlag = BGPaletteBufferSyncDisable;
	// 魔法动画用BG调色板1(地址:0x5000020)，否则会被覆写
	// 魔法动画OBJ用调色板2(地址:0x5000240)
	OutputToBGPaletteBuffer(fubukiBGPal1,0x20,32);
	// 写TSA
//	writeTemplateTSA(BG1MapBuffer,fubukiBGMap,(12<<12)|224);
//	writeTemplateTSA(BG1MapBuffer,fubukiBGMap,(15<<12)|224);
	writeTemplateTSA(BG1MapBuffer,fubukiBGMap,(1<<12)|224);
	// 开BGMap同步
	SetBGMapSyncFlag(1<<1);
	// 调色板渐变动画
//	loadGradientPalette(fubukiBGPal1,fubukiBGPal2,32,15,1,ctx);
	loadGradientPalette(fubukiBGPal1,fubukiBGPal2,32,1,1,ctx);
	// 设置一些参数
	*(u32 *)&ctx->userSpace[7]=0;
	*(u32 *)&ctx->userSpace[11]=32;
	*(u32 *)&ctx->userSpace[19]=0;
	*(u32 *)&ctx->userSpace[23]=0;
	// 设置背景位置
	setBGnPosition(1u,0,0);
}

void fubuki2(struct context *ctx)
{
	int frameID;
	int EVA,EVB;
	int v5;

	frameID = ++*(u32 *)&ctx->userSpace[7];
	// 开启alpha渲染
	BLDCNTBuffer = BLDALPHABuffer & 0xFF3F | 0x40;
	// 第一层混合系数
	EVA = frameID >> 1;
	BLDALPHABuffer = BLDALPHABuffer & 0xFF00 | EVA;
	// 第二层混合系数
	EVB = 16 - EVA;
	if(EVB < 13)
		EVB = 13;
	BLDALPHABuffer = BLDALPHABuffer & 0x00FF | (EVB << 8);
	// 清BLDY
	BLDYBuffer = 0;
	if(frameID >> 1 == 16)
	{
		*(u32 *)&ctx->userSpace[7] = 0;
		breakLoop(ctx);
	}
	// 设置一些参数
	v5 = ++*(u32 *)&ctx->userSpace[11];
	*(u32 *)&ctx->userSpace[19] += 3 * v5;
	*(u32 *)&ctx->userSpace[23] += v5;
	// 移动背景
	setBGnPosition(1u,-(s16)((*(u32 *)&ctx->userSpace[19])>>5),-(s16)((*(u32 *)&ctx->userSpace[23])>>5));
}

void fubuki3(struct context *ctx)
{
	int frameID;
	int v3;

	frameID = ++*(u32 *)&ctx->userSpace[7];
	if(frameID >= *(u32 *)&ctx->userSpace[3])
	{
		*(u32 *)&ctx->userSpace[7] = 0;
		breakLoop(ctx);
	}
	v3 = *(u32 *)&ctx->userSpace[11];
	*(u32 *)&ctx->userSpace[19] += 3 * v3;
	*(u32 *)&ctx->userSpace[23] += v3;
	setBGnPosition(1u,-(s16)((*(u32 *)&ctx->userSpace[19])>>5),-(s16)((*(u32 *)&ctx->userSpace[23])>>5));
}

void fubuki4(struct context *ctx)
{
	int frameID;
	int EVA,EVB;
	int v5;

	frameID = ++*(u32 *)&ctx->userSpace[7];
	// 开启alpha渲染
	BLDCNTBuffer = BLDALPHABuffer & 0xFF3F | 0x40;
	// 第一层混合系数
	EVA = 16 - (frameID >> 3);
	BLDALPHABuffer = BLDALPHABuffer & 0xFF00 | EVA;
	// 第二层混合系数
	EVB = 13 + (frameID >> 3);
	if(EVB > 16)
		EVB = 16;
	BLDALPHABuffer = BLDALPHABuffer & 0x00FF | (EVB << 8);
	// 清BLDY
	BLDYBuffer = 0;
	// 滚屏
	v5 = *(u32 *)&ctx->userSpace[11];
	*(u32 *)&ctx->userSpace[19] += 3 * v5;
	*(u32 *)&ctx->userSpace[23] += v5;
	// 移动背景
	setBGnPosition(1u,-(s16)((*(u32 *)&ctx->userSpace[19])>>5),-(s16)((*(u32 *)&ctx->userSpace[23])>>5));
	// 跳出循环
	if(16 == frameID >> 3)
		breakLoop(ctx);
	
}

void fubuki5()
{
	// 清零BG1使用的Tile区域
	memClear2K(BG1MapBuffer,0);
	// 开启BGMap同步
	SetBGMapSyncFlag(1<<1);
	// 关闭alpha渲染
	BLDCNTBuffer &= 0xFF3F;
	// 设置第二层混合参数EVB=16
	BLDALPHABuffer = 0x1000;
	// 清BLDY
	BLDYBuffer = 0;
	// 终止调色板渐变动画
	stopGradientPal();
}

// 吹雪协程
struct coroutine efxFubuki[]={
	spellStart,
	execFunc(fubuki1),
	setLoopFuncAndYield(fubuki2),
	setLoopFuncAndYield(fubuki3),
	setLoopFuncAndYield(fubuki4),
	execFunc(fubuki5),
	endofCoroutine
};

// 吹雪动画
void loadFubuki()
{
	struct context *ctx;

	ctx = createContext(efxFubuki,3);
	*(u32 *)(&ctx->userSpace[3]) = 0x1E;
}

// 冰世界魔法动画
void IceWorld(struct context *ctx)
{
	int v2,v3;
	u16 frameID;
	u8 *missOrHit;
	void* AIS;

	AIS = *(u32 *)&ctx->userSpace[51];
	v2 = sub(8054F90)(AIS);
	v3 = sub(8050F54)();
	frameID = ++*(u16 *)&ctx->userSpace[3];
	if(1 == frameID)
		ScrollScreen(AIS,0xFFFF);
//	若想用12号开始的BG调色板则需要每帧强制刷新一下，否则会被清零
//	if(frameID - v3 > 1)
//		FE7JCPUFastSet(fubukiBGPal1,0x5000180,32>>2);
	switch(frameID - v3)
	{
		case 1:
			loadFubuki();
			PlaySFX(290,256,*(u16 *)(v2 + 2),1);
			break;
		case 85:
//			createContext(0x8D6FB1C,3);
//			loadFimbulvetrBG(v2);
			loadFimbulvetrOBJ(v2);
//			loadALPHA(v2,24,16,16,0,0);
//			PlaySFX(291,256,*(u16 *)(v2 + 2),1);
			break;
		case 88:
			*(u16 *)(v2 + 16) |= 9u;
	    	missOrHit = ctx->userSpace;
    		reduceHPBar(v2, *missOrHit);
    		if ( !*missOrHit )
      			playHitSound((void *)v2);
			break;
		case 90:
			sub(80507D8)();
    		sub(80503A0)();
			breakLoop(ctx);
			break;
		default:
			break;
	}
}

