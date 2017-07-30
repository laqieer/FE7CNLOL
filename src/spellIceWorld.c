// ������ħ������
// by laqieer
// 2017/6/4

#include "spellIceWorld.h"

// ������ħ����Э��
struct coroutine efxIceWorld[]={
	spellStart,
	setLoopFuncAndYield(IceWorld),
	endofCoroutine
};

// ������������
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

// ������ħ������
// ����
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
//		�ص�BG0
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
		// ��BG0
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
	// ����alpha��Ⱦ
	BLDCNTBuffer = BLDALPHABuffer & 0xFF3F | 0x40;
	// ���õڶ����ϲ���EVB=16
	BLDALPHABuffer = 0x1000;
	// ��BLDY
	BLDYBuffer = 0;
	// ���õ�һ��ΪBG1,�ڶ���ΪBG3��OBJ
	BLDCNTBuffer = (BLDCNTBuffer & 0xFFE0 | 2) & 0xE0FF | 0x1800;
	// дTile(ħ������Tile��0x6001C00(Tile=224)��ʼ)
	AutoCopyOrDecompressImageToVRAM(fubukiBGImgLZ,spellBGTile);
	// д��ɫ��
//	OutputToBGPaletteBuffer(fubukiBGPal1,0x180,32);	// 0x5000180��ӦBG��ɫ��12(��0��ʼ��)
//	OutputToBGPaletteBuffer(fubukiBGPal1,0x1E0,32);
//	FE7JCPUFastSet(fubukiBGPal1,0x5000180,32>>2);
//	BGPaletteBufferSyncFlag = BGPaletteBufferSyncDisable;
	// ħ��������BG��ɫ��1(��ַ:0x5000020)������ᱻ��д
	// ħ������OBJ�õ�ɫ��2(��ַ:0x5000240)
	OutputToBGPaletteBuffer(fubukiBGPal1,0x20,32);
	// дTSA
//	writeTemplateTSA(BG1MapBuffer,fubukiBGMap,(12<<12)|224);
//	writeTemplateTSA(BG1MapBuffer,fubukiBGMap,(15<<12)|224);
	writeTemplateTSA(BG1MapBuffer,fubukiBGMap,(1<<12)|224);
	// ��BGMapͬ��
	SetBGMapSyncFlag(1<<1);
	// ��ɫ�彥�䶯��
//	loadGradientPalette(fubukiBGPal1,fubukiBGPal2,32,15,1,ctx);
	loadGradientPalette(fubukiBGPal1,fubukiBGPal2,32,1,1,ctx);
	// ����һЩ����
	*(u32 *)&ctx->userSpace[7]=0;
	*(u32 *)&ctx->userSpace[11]=32;
	*(u32 *)&ctx->userSpace[19]=0;
	*(u32 *)&ctx->userSpace[23]=0;
	// ���ñ���λ��
	setBGnPosition(1u,0,0);
}

void fubuki2(struct context *ctx)
{
	int frameID;
	int EVA,EVB;
	int v5;

	frameID = ++*(u32 *)&ctx->userSpace[7];
	// ����alpha��Ⱦ
	BLDCNTBuffer = BLDALPHABuffer & 0xFF3F | 0x40;
	// ��һ����ϵ��
	EVA = frameID >> 1;
	BLDALPHABuffer = BLDALPHABuffer & 0xFF00 | EVA;
	// �ڶ�����ϵ��
	EVB = 16 - EVA;
	if(EVB < 13)
		EVB = 13;
	BLDALPHABuffer = BLDALPHABuffer & 0x00FF | (EVB << 8);
	// ��BLDY
	BLDYBuffer = 0;
	if(frameID >> 1 == 16)
	{
		*(u32 *)&ctx->userSpace[7] = 0;
		breakLoop(ctx);
	}
	// ����һЩ����
	v5 = ++*(u32 *)&ctx->userSpace[11];
	*(u32 *)&ctx->userSpace[19] += 3 * v5;
	*(u32 *)&ctx->userSpace[23] += v5;
	// �ƶ�����
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
	// ����alpha��Ⱦ
	BLDCNTBuffer = BLDALPHABuffer & 0xFF3F | 0x40;
	// ��һ����ϵ��
	EVA = 16 - (frameID >> 3);
	BLDALPHABuffer = BLDALPHABuffer & 0xFF00 | EVA;
	// �ڶ�����ϵ��
	EVB = 13 + (frameID >> 3);
	if(EVB > 16)
		EVB = 16;
	BLDALPHABuffer = BLDALPHABuffer & 0x00FF | (EVB << 8);
	// ��BLDY
	BLDYBuffer = 0;
	// ����
	v5 = *(u32 *)&ctx->userSpace[11];
	*(u32 *)&ctx->userSpace[19] += 3 * v5;
	*(u32 *)&ctx->userSpace[23] += v5;
	// �ƶ�����
	setBGnPosition(1u,-(s16)((*(u32 *)&ctx->userSpace[19])>>5),-(s16)((*(u32 *)&ctx->userSpace[23])>>5));
	// ����ѭ��
	if(16 == frameID >> 3)
		breakLoop(ctx);
	
}

void fubuki5()
{
	// ����BG1ʹ�õ�Tile����
	memClear2K(BG1MapBuffer,0);
	// ����BGMapͬ��
	SetBGMapSyncFlag(1<<1);
	// �ر�alpha��Ⱦ
	BLDCNTBuffer &= 0xFF3F;
	// ���õڶ����ϲ���EVB=16
	BLDALPHABuffer = 0x1000;
	// ��BLDY
	BLDYBuffer = 0;
	// ��ֹ��ɫ�彥�䶯��
	stopGradientPal();
}

// ��ѩЭ��
struct coroutine efxFubuki[]={
	spellStart,
	execFunc(fubuki1),
	setLoopFuncAndYield(fubuki2),
	setLoopFuncAndYield(fubuki3),
	setLoopFuncAndYield(fubuki4),
	execFunc(fubuki5),
	endofCoroutine
};

// ��ѩ����
void loadFubuki()
{
	struct context *ctx;

	ctx = createContext(efxFubuki,3);
	*(u32 *)(&ctx->userSpace[3]) = 0x1E;
}

// ������ħ������
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
//	������12�ſ�ʼ��BG��ɫ������Ҫÿ֡ǿ��ˢ��һ�£�����ᱻ����
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

