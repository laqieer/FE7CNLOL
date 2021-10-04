// Blood Moon Spell Animation
// by laqieer
// 2017/6/6

#include "spellBloodMoon.h"

int RGB2Gray(u16 rgb)
{
	int r,g,b;
	r = rgb & 0b11111;
	g = (rgb & (0b11111 << 5)) >> 5;
	b = (rgb & (0b11111 << 10)) >> 10;
	return ((38 * r + 75 * g + 15 * b)>>7)&0b11111;
}

void Pal2Red(u16 *pal)
{
	int i = 0;
	
	for(i=0;i<16;i++)
		pal[i] = RGB2Gray(pal[i]);
}

void BloodMoon(struct context *ctx)
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
			BLDCNTBuffer = BLDCNTBuffer & 0xFF3F | 0x40;
			BLDALPHABuffer = 0x1000;
			BLDYBuffer = 0;
			loadALPHA(v2,0,15,0,16,0);
			loadALPHA(v2,80,15,16,0,0);
			loadHazymoonBG1(AIS);
			loadHazymoonOBJ3(AIS);
			Pal2Red((u32)BGPaletteBuffer + 32 * 1);
			Pal2Red((u32)OBJPaletteBuffer + 32 * 2);
			//PlaySFX(312,256,120,0);
			m4aMPlayStart(mp08,&se_mixkit_fire_explosion_1343);
			break;
		case 70:
			loadResireRST3(v2,loadResireRST5(v2,42,15,0,2),30);
			loadRestWINH1(v2,43,0);
			break;
		case 120:
			loadHazymoonBG2(v2);
			Pal2Red((u32)BGPaletteBuffer + 32 * 1);
			break;
		case 125:
			//PlaySFX(313,256,*(u16 *)(v2 + 2),1);
			break;
		case 151:
			loadHazymoonOBJ2(AIS);
			break;
		case 220:
//			PlaySFX(738,256,*(u16 *)(v2 + 2),1);
			// m4aSongNumStartOrChange(mp07,&se_d01);
			// m4aSongNumStartOrContinue(mp07,&se_d01);
 			// 用其他的音乐播放器此处播放不了，必须用mp08
 			// &se_d01是传地址，而se_d01则是传值
 			// 使用自适应函数也会导致无法播放音乐,猜测是因为其对第一个参数<=127(地址以0x8,0x9开头，是负数)的特殊处理导致的
//			m4aSongAutoStart(mp08,&se_d01);
			// 直接用指定播放器播放指定音乐的m4aMPlayStart函数
			//m4aMPlayStart(mp08,&se_d01);
//			m4aMPlayStart(0x3005D10,&se_d01);
			break;
		case 226:
			BLDCNTBuffer = BLDCNTBuffer & 0xFF3F | 0x40;
			BLDALPHABuffer = 0x1000;
			BLDYBuffer = 0;
			loadALPHA(v2,0,10,0,16,0);
			loadALPHA(v2,35,20,16,0,0);
			loadResireBG2(v2);
			Pal2Red((u32)BGPaletteBuffer + 32 * 1);
			//PlaySFX(124,256,*(u16 *)(v2 + 2),1);
			break;
		case 240:
			loadResireRST3(v2,loadResireRST5(v2,42,15,0,2),30);
			loadRestWINH(v2,43,BG1HOFSBuffer,0);
			break;
		case 285:
			loadResireBG(v2,missOrHit);
			Pal2Red((u32)BGPaletteBuffer + 32 * 1);
			//PlaySFX(125,256,*(u16 *)(v2 + 2),1);
			break;
		case 290:
			*(u16 *)(v2 + 16) |= 9u;
			suckBloodAnimation(v2,*missOrHit);
			if(!*missOrHit)
				playHitSound(v2);
			break;
		case 290+65:
			sub(80507D8)();
			breakLoop(ctx);
			break;
		default:
			break;
	}
}

const struct coroutine efxBloodMoon[]={
	spellStart,
	setLoopFuncAndYield(BloodMoon),
	endofCoroutine
};

void spellBloodMoon(void *AIS)
{
	struct context *ctx;

	sub(80507CC)();
	sub(8050348)();
	sub(80507E4)();
	ctx = createContext(efxBloodMoon,3);
	*(void **)&ctx->userSpace[51] = AIS;
	*(u16 *)&ctx->userSpace[3] = 0;
	ctx->userSpace[0] = sub(8054E74)(sub(8054FEC)(AIS));
}
