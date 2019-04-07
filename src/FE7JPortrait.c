// by laqieer
// 2017/3/29
// 新自由头像系统

#include "FE7JPortrait.h"

// 眨眼/使眼色的函数指针表
const PTRFUN blinkOrWink[] = 
{
	blinkOrWink0,
	blinkOrWink1,
	blinkOrWink2,
	blinkOrWink3
};

// 序号FF以后的头像单独设一个指针表,从0x100开始
// longcall, Os, C直接调用一般要占0x18个字节, 小函数要注意不要复写到下一个函数的区域
// 用汇编写是为了减小体积, 只占0xC个字节
__attribute__((section(".callGetPortrait")))
struct Portrait *callGetPortrait(int portraitIndex)
{
	//return GetPortrait(portraitIndex);

	//asm("ldr r1,=GetPortrait\nbx r1");
	asm("ldr r1,=GetPortraitNew\nbx r1");
}

struct Portrait *GetPortrait(int portraitIndex)
{
  return (portraitIndex > 0xFF) ? &portraitTableNew[portraitIndex - 0x100] : &portraitTableOriginal[portraitIndex];
}

pPortraitNew GetPortraitNew(int portraitIndex)
{
	if(portraitIndex >= 0x200)
		// return &portraitTableNewExtension[portraitIndex - 0x200];
		return portraitTableNewExtension[portraitIndex - 0x200];
	return GetPortrait(portraitIndex);
}

__attribute__((section(".callGetUnitPortraitID")))
PortraitID callGetUnitPortraitID(Unit *pUnit)
{
//	return GetUnitPortraitID(pUnit);
	return GetUnitPortraitIDEx(pUnit);
}

// 原版的读取人物头像id的函数
PortraitID GetUnitPortraitID(Unit *pUnit)
{
  int portraitIndex;
  Class *pClass;

  portraitIndex = pUnit->character->portrait;
  if ( !portraitIndex )
  {
    pClass = pUnit->m_class;
    if ( pClass->classCard )
      portraitIndex = pClass->classCard;
    else
      portraitIndex = 0;
  }
  return portraitIndex;
}

// 扩展人物上位职业头像
PortraitID GetUnitPortraitIDEx(Unit *pUnit)
{
  int portraitIndex;
  Class *pClass;

  pClass = pUnit->m_class;
  if( pClass->ability_promoted && promotedUnitPortraitID[pUnit->character->id] )
  	portraitIndex = promotedUnitPortraitID[pUnit->character->id];
  else
  	portraitIndex = pUnit->character->portrait;
  if ( !portraitIndex )
  {
    if ( pClass->classCard )
      portraitIndex = pClass->classCard;
    else
      portraitIndex = NULL;
  }
  return portraitIndex;
}

__attribute__((section(".playClassChangePortraitAnimationFunc")))
// const PTRFUN playClassChangePortraitAnimationFunc = playClassChangePortraitAnimation;
const PTRFUN playClassChangePortraitAnimationFunc = playClassChangePortraitAnimationEx;

// 转职加点时显示头像的动画
void playClassChangePortraitAnimation(struct context *ctx)
{
  AnimationInterpreter *AIS; // r6
  Unit *pCurrentUnit; // r1
  int portraitIndex; // r4
  int src; // [sp+8h] [bp-20h]

  AIS = *(AnimationInterpreter **)&ctx->userSpace[51];
  FE7JLZ77UnCompWram(0x81E0C60, 0x2017784);
  FE7JLZ77UnCompWram(0x81E0EAC, 0x2019784);
  sub(80672B8)(0x2019784, &((u16 *)BG1MapBuffer)[192], 0x20u, 0x14u, 1, 0x100);
  TileTransferInfoAdd(0x2017784, 0x6002000, 0x400);
  FE7JCPUFastSet(0x81E0FA8, &BGPaletteBuffer[16], 8u);
  FE7JLZ77UnCompWram(0x81E0FC8, 0x201A784);
  TileTransferInfoAdd(0x201A784, 0x6011400, 0xC00);
  FE7JCPUFastSet(0x81E11DC, &OBJPaletteBuffer[16], 8u);
  EnablePaletteSync();
  *(_WORD *)&ctx->userSpace[3] = 80;
  if ( isUnitAtRightOrLeft(AIS) )
    pCurrentUnit = pUnitRight;
  else
    pCurrentUnit = pUnitLeft;
  portraitIndex = pCurrentUnit->character->portrait;
  SetupFaceGfxData(0x8C4A8E8);
  ShowFace(0, portraitIndex, 188, 80, 0x1042);
  *(_WORD *)(paFaceProcs[0] + 54) = 160;
  src = 0;
  FE7JCPUFastSet(&src, BG2MapBuffer, 0x1000200u);
  sub(8069314)(ctx);
  breakLoop(ctx);
}

// 加入转职时显示上位头像
void playClassChangePortraitAnimationEx(struct context *ctx)
{
  AnimationInterpreter *AIS; // r6
  Unit *pCurrentUnit; // r1
  int portraitIndex; // r4
  int src; // [sp+8h] [bp-20h]

  AIS = *(AnimationInterpreter **)&ctx->userSpace[51];
  FE7JLZ77UnCompWram(0x81E0C60, 0x2017784);
  FE7JLZ77UnCompWram(0x81E0EAC, 0x2019784);
  sub(80672B8)(0x2019784, &((u16 *)BG1MapBuffer)[192], 0x20u, 0x14u, 1, 0x100);
  TileTransferInfoAdd(0x2017784, 0x6002000, 0x400);
  FE7JCPUFastSet(0x81E0FA8, &BGPaletteBuffer[16], 8u);
  FE7JLZ77UnCompWram(0x81E0FC8, 0x201A784);
  TileTransferInfoAdd(0x201A784, 0x6011400, 0xC00);
  FE7JCPUFastSet(0x81E11DC, &OBJPaletteBuffer[16], 8u);
  EnablePaletteSync();
  *(_WORD *)&ctx->userSpace[3] = 80;
  if ( isUnitAtRightOrLeft(AIS) )
    pCurrentUnit = pUnitRight;
  else
    pCurrentUnit = pUnitLeft;
  portraitIndex = promotedUnitPortraitID[pCurrentUnit->character->id] ? promotedUnitPortraitID[pCurrentUnit->character->id] : pCurrentUnit->character->portrait;
  SetupFaceGfxData(0x8C4A8E8);
  ShowFace(0, portraitIndex, 188, 80, 0x1042);
  *(_WORD *)(paFaceProcs[0] + 54) = 160;
  src = 0;
  FE7JCPUFastSet(&src, BG2MapBuffer, 0x1000200u);
  sub(8069314)(ctx);
  breakLoop(ctx);
}

// 不需要眼睛帧的头像就什么都不做
void blinkOrWink3(u32 *mempool, int eyeStatus)
{

}

// 眨眼和使眼色，新增一个精灵，然后实时覆写VRAM中的Tile数据，支持非8像素对齐
void blinkOrWink1(u32 *mempool, int eyeStatus)
{
	int eyeShape;	// 闭眼还是半闭眼
	int winkFlag;	// 是否只针对外侧的那只眼睛
	struct Portrait *portrait;	// 头像
	int *data;
	int x; // 眼睛精灵横坐标
	int y; // 眼睛精灵纵坐标
	
	data = mempool[11];
	portrait = data[11];
	// 写Tile(不考虑使眼色和眨眼的区别)
	winkFlag = eyeStatus & 0x80;
	eyeShape = 2 - (eyeStatus & 1);
	if(eyeStatus & (~0x81))
		eyeShape = 0;
	changeTiles(portrait->ce.eyeFrameInfo->eyeFrame[eyeShape],32 * ((*(s16 *)((int)data + 60) + 28 + 32 * 2) & 0x3FF) + 0x6010000,4,2);
	// 写OAM(在这里考虑考虑使眼色)
	x = 4 - portrait->x.eyePositionX;
	if(winkFlag)
		x += 2;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		x = 8 * x;
	if(!checkPortraitInvert(data))
		x = - x;
	x = 0x1FF & (x + *(s16 *)((int)data + 52) - 16);
	if(checkPortraitInvert(data))
		LOWORD(x) = x + 0x1000;
	y = portrait->y.eyePositionY;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		y = 8 * y;
	y = ((y + *(s16 *)((int)data + 54)) & 0xFF) + (0x400 & (-(0x400 & getPortraitControlFlag(data)) >> 31));
	if(winkFlag)
		if(!checkPortraitInvert(data))
			LOWORD(x) = x + 16 + 2;
	AddSprite(*(s8 *)((int)data + 65),x,y,winkFlag ? winkFrameTemplate : blinkFrameTemplate,*(s16 *)((int)data + 60) + 28 + 32 * 2 + 2 * !!winkFlag);	
}

// 眨眼和使眼色，直接实时覆写VRAM中的Tile数据，支持自定义形状尺寸
// eyeStatus=0 		闭眼
// eyeStatus=1 		半闭眼
// eyeStatus=0x80	闭单侧眼
// eyeStatus=0x81	闭单侧眼
void blinkOrWink2(u32 *mempool, int eyeStatus)
{
	int eyeShape;	// 闭眼还是半闭眼
	int winkFlag;	// 是否只针对外侧的那只眼睛
	struct Portrait *portrait;	// 头像
	// 第i行第j列
	int i;	// 循环变量，纵坐标
	int j;	// 循环变量，横坐标

	portrait = (struct Portrait *)(*(u32 *)(mempool[11] + 44));
	if(eyeStatus & (~0x81))
	{
		/*for(i = 0;i < portrait->ce.eyeFrameInfo->height;i++)
			for(j = 0;j < portrait->ce.eyeFrameInfo->width;j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[0] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);*/
		changeTiles(portrait->ce.eyeFrameInfo->eyeFrame[0], 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[0]) & 0x3FF), portrait->ce.eyeFrameInfo->width, portrait->ce.eyeFrameInfo->height);
		return;
	}
	winkFlag = eyeStatus & 0x80;
	eyeShape = 2 - (eyeStatus & 1);
	/*if(winkFlag)
		for(i = portrait->ce.eyeFrameInfo->height - portrait->ce.eyeFrameInfo->winkHeight;i < portrait->ce.eyeFrameInfo->height; i++)
			for(j = portrait->ce.eyeFrameInfo->width - portrait->ce.eyeFrameInfo->winkWidth;j < portrait->ce.eyeFrameInfo->width; j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[eyeShape] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);
	else
		for(i = 0;i < portrait->ce.eyeFrameInfo->height;i++)
			for(j = 0;j < portrait->ce.eyeFrameInfo->width;j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[eyeShape] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);*/
	// 上面这个逐tile写入的方案时间开销大,最重要的是changeTiles这个函数的内部实现是向内存中的一个tile传送信息队列中追加一条传送记录而不是直接写入显存，在眼睛帧尺寸较大的时候(比如64x32)容易导致一段时间后的内存溢出,所以改用直接整体写入的方案,这个方案的局限性在于眼睛帧的所有tile在显存里也必须是二维相邻的，这样分解头像的眼睛帧必须保持完整，不能打散
	// 更好的方案是根据眼睛帧模板程序自己计算最佳传送方案，让相邻的tile一次传送，懒得写这个算法了，这里先留个坑吧
	// 或者可以小尺寸的眼睛帧逐个写tile，大尺寸的眼睛帧就整体写tile，作为折衷方案
	if(winkFlag)
		changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[eyeShape] + 32 * (portrait->ce.eyeFrameInfo->width * (portrait->ce.eyeFrameInfo->height - portrait->ce.eyeFrameInfo->winkHeight) + (portrait->ce.eyeFrameInfo->width - portrait->ce.eyeFrameInfo->winkWidth)), 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * (portrait->ce.eyeFrameInfo->height - portrait->ce.eyeFrameInfo->winkHeight) + (portrait->ce.eyeFrameInfo->width - portrait->ce.eyeFrameInfo->winkWidth)]) & 0x3FF), portrait->ce.eyeFrameInfo->winkWidth, portrait->ce.eyeFrameInfo->winkHeight);
	else
		changeTiles(portrait->ce.eyeFrameInfo->eyeFrame[eyeShape], 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[0]) & 0x3FF), portrait->ce.eyeFrameInfo->width, portrait->ce.eyeFrameInfo->height);
}

void blinkOrWinkNew(u32 *mempool, int eyeStatus)
{
	int *data;
	pPortraitNew portrait;
	int frameNum;
	int tileNumFrame;

	data = mempool[11];
	portrait = data[11];

	if(portrait->extra->eye->frame && portrait->extra->eye->width && portrait->extra->eye->height)
	{
		tileNumFrame = (portrait->extra->eye->width / 8) * (portrait->extra->eye->height / 8);
		if(eyeStatus & (~0x81))
			frameNum = 0;
		else
			frameNum = 2 - (eyeStatus & 1);
		if(eyeStatus & 0x80)
			// wink
			changeTiles(&portrait->extra->eye->frame[32 * tileNumFrame * frameNum] + 32 * ((portrait->extra->eye->width / 8) * ((portrait->extra->eye->height / 8) - (portrait->extra->eye->heightBottom / 8)) + ((portrait->extra->eye->width / 8) - (portrait->extra->eye->widthRight/ 8))), 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->extra->eye->tileNo + 32 * ((portrait->extra->eye->height / 8) - (portrait->extra->eye->heightBottom / 8)) + (portrait->extra->eye->width / 8) - (portrait->extra->eye->widthRight/ 8)) & 0x3FF), portrait->extra->eye->widthRight / 8, portrait->extra->eye->heightBottom / 8);
		else
			// blink
			changeTiles(&portrait->extra->eye->frame[32 * tileNumFrame * frameNum], 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->extra->eye->tileNo) & 0x3FF), portrait->extra->eye->width / 8, portrait->extra->eye->height / 8);
	}
};

// 根据新老格式的不同调用相应的眨眼/使眼色函数
void callBlinkOrWink(u32 *mempool, int eyeStatus)
{
	struct Portrait *portrait;	// 头像

	portrait = (struct Portrait *)(*(u32 *)(mempool[11] + 44));
	blinkOrWink[portrait->eyeControlFlag - 1](mempool,eyeStatus);
}

void callBlinkOrWinkNew(u32 *mempool, int eyeStatus)
{
	int *data;
	pPortraitNew portrait;	// 头像

	data = mempool[11];
	portrait = data[11];

	if(isNewPortraitExtension(portrait))
		blinkOrWinkNew(mempool,eyeStatus);
	else
		callBlinkOrWink(mempool,eyeStatus);
}

// 眨眼/使眼色函数接口
void callCallBlinkOrWink(u32 *mempool, int eyeStatus)
{
	//callBlinkOrWink(mempool,eyeStatus);
	callBlinkOrWinkNew(mempool,eyeStatus);
}

// 调用到BlinkOrWink的函数1
// 眨眼
void blink(s16 *mempool)
{
	int eyeStatus;

	eyeStatus = 2;
	if(mempool[26] <= 0xA)
	{
		switch(mempool[26])
		{
			case 3u:
			case 4u:
			case 5u:
				eyeStatus = 0;
				break;
			case 0u:
			case 1u:
			case 2u:
			case 6u:
			case 7u:
			case 8u:
				eyeStatus = 1;
				break;
			case 0xAu:
				sub(80045FC)((int)mempool,0);
				break;
			default:
				break;
		}
	}
	callCallBlinkOrWink((u32 *)mempool,eyeStatus);
	++mempool[26];
}

// 调用到BlinkOrWink的函数1接口
__attribute__((section(".callBlink")))
void callBlink(s16 *mempool)
{
	blink(mempool);
}

// 调用到BlinkOrWink的函数2
void sub_80077E8(s16 *mempool)
{
	if(mempool[26] > 5)
	{
		callCallBlinkOrWink((u32 *)mempool,0);
		if(!mempool[25])
			sub(80045FC)((int)mempool,1);
	}
	else
		blink(mempool);
}

// 调用到BlinkOrWink的函数2接口
__attribute__((section(".call_sub_80077E8")))
void call_sub_80077E8(s16 *mempool)
{
	sub_80077E8(mempool);
}

// 调用到BlinkOrWink的函数3
void sub_8007824(s16 *mempool)
{
	if(mempool[26] > 2)
	{
		callCallBlinkOrWink((u32 *)mempool,1);
		if(!mempool[25])
			sub(80045FC)((int)mempool,1);
	}
	else
		blink(mempool);
}

// 调用到BlinkOrWink的函数3接口
__attribute__((section(".call_sub_8007824")))
void call_sub_8007824(s16 *mempool)
{
	sub_8007824(mempool);
}

// 调用到BlinkOrWink的函数4
// 使眼色
void wink(s16 *mempool)
{
	int eyeStatus;

	eyeStatus = 2;
	if(mempool[26] <= 0xA)
	{
		switch(mempool[26])
		{
			case 3u:
			case 4u:
			case 5u:
				eyeStatus = 0;
				break;
			case 0u:
			case 1u:
			case 2u:
			case 6u:
			case 7u:
			case 8u:
				eyeStatus = 1;
				break;
			case 0xAu:
				sub(80045FC)((int)mempool,0);
				break;
			default:
				break;
		}
	}
	callCallBlinkOrWink((u32 *)mempool,eyeStatus + 0x80);
	++mempool[26];
}

// 调用到BlinkOrWink的函数4接口
__attribute__((section(".callWink")))
void callWink(s16 *mempool)
{
	wink(mempool);
}

// 选择大头像精灵组合模板，支持自定义模板
void chooseMainPortraitSpriteTemplate(u32 *mempool)
{
	u32 flag1;	// 控制模板选择
	u32 flag2;
	s16 delta;
	struct Portrait *portrait;	// 头像

	portrait = (struct Portrait *)mempool[11];
	flag1 = mempool[12] & 0x807;

	/*
	if(flag1 == 2 || flag1 == 3)				// 会话中出现的头像
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,1)][flag1 & 1];
	else if(flag1 == 0x800 || flag1 == 0x801)	// 查看支援对话时左上的头像
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,3)][flag1 & 1];
	else if(flag1 == 0 || flag1 == 1)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,0)][flag1 & 1];	
	else if(flag1 == 4 || flag1 == 5)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,2)][flag1 & 1];
	*/
	if(flag1 == 0x800 || flag1 == 0x801)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,3)][flag1 & 1];
	else if(flag1 <= 5)
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,flag1 >> 1)][flag1 & 1];

	flag2 = mempool[12] & 0x3C0;
	if ( flag2 == 0x80 )
	{
		delta = 0x400;
	}
	else if ( flag2 > 0x80 )
	{
		if ( flag2 != 0x200 )
			goto LABEL_1;
		delta = 0xC00;
	}
	else
	{
		if ( flag2 != 0x40 )
		{
LABEL_1:
			delta = 0x800;
			goto LABEL_2;
		}
		delta = 0;
	}
LABEL_2:
	*((s16 *)mempool + 30) = (*(s32 *)(8 * *((s8 *)mempool + 64) + 0x202A580) >> 5)
															 + ((*(s16 *)(8 * *((s8 *)mempool + 64) + 0x202A584) & 0xF) << 12)
															 + delta;
}

void chooseDialoguePortraitOAM(u32 *data)
{
	pPortraitNew portrait;
	u32 flag1;
	u32 flag2;
	s16 delta;

	portrait = (pPortraitNew)data[11];
	flag1 = data[12] & 0x807;
	if(isNewPortraitExtension(portrait))
	{
		if(flag1 == 0x800 || flag1 == 0x801 || flag1 <= 5)
		{
			if(flag1 & 1)
				data[14] = portrait->extra->obj->oamR; // face to right
			else
				data[14] = portrait->extra->obj->oamL; // face to left
		}

		flag2 = data[12] & 0x3C0;
		if ( flag2 == 0x80 )
		{
			delta = 0x400;
		}
		else if ( flag2 > 0x80 )
		{
			if ( flag2 != 0x200 )
				goto LABEL_4;
			delta = 0xC00;
		}
		else
		{
			if ( flag2 != 0x40 )
			{
LABEL_4:
				delta = 0x800;
				goto LABEL_5;
			}
			delta = 0;
	}
LABEL_5:
	*((s16 *)data + 30) = (*(s32 *)(8 * *((s8 *)data + 64) + 0x202A580) >> 5)
															 + ((*(s16 *)(8 * *((s8 *)data + 64) + 0x202A584) & 0xF) << 12)
															 + delta;
	}
	else
		chooseMainPortraitSpriteTemplate(data);
}


// 新的选择大头像精灵组合模板函数的接口
__attribute__((section(".callChooseMainPortraitSpriteTemplate")))
void callChooseMainPortraitSpriteTemplate(s16 *mempool)
{
	//chooseMainPortraitSpriteTemplate((u32 *)mempool);
	chooseDialoguePortraitOAM((u32 *)mempool);
}

// 新的人物详情界面头像框绘制函数
void drawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	struct Portrait *portrait;	// 头像
	int i;
	int j;

	if(!portraitID)
		return;
	portrait = GetPortraitNew(portraitID);
	OutputToBGPaletteBuffer(portrait->portraitPalette, 32 * presentBGPaletteIndex, 32);
	if(portrait->mainPortrait)	// 有头像画头像
	{
		AutoCopyOrDecompressImageToVRAM(portrait->mainPortrait, 32 * presentBGTileIndex + 0x6000000);
		OutputToBGPaletteBuffer(portrait->portraitPalette, 32 * presentBGPaletteIndex, 32);
		if(PortraitHeightFix(portraitID)<<24)
			writeTemplateTSA(TSABufferInWRAM, portraitInBoxTemplateTable[1], ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		else
			writeTemplateTSA(TSABufferInWRAM, portraitInBoxTemplateTable[portrait->portraitTemplateInBox], ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		// 蒙版裁剪
		for(i = 0; i < 9; i++)
			for(j = 0; j < 10; j++)
				TSABufferInWRAM[32 * i + j] &= - portraitMaskTable[portrait->portraitMaskInBox][10 * i + j];
	}
	else	// 无头像画职业卡
	{
		AutoCopyOrDecompressImageToVRAM(portrait->ce.classCard, 32 * presentBGTileIndex + 0x6000000);
		writePlainTSA(TSABufferInWRAM, (presentBGPaletteIndex << 12) + (presentBGTileIndex & 0x3FF), 10, 9);
	}
}

void showStatusScreenPortrait(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	pPortraitNew portrait;
	int i, j;

	if(portraitID == NULL)
		return;
	portrait = (pPortraitNew)GetPortraitNew(portraitID);
	if(isNewPortraitExtension(portrait) == FALSE)
	{
		drawPortraitInBox(TSABufferInWRAM, portraitID, presentBGTileIndex, presentBGPaletteIndex);
		return;
	}
	if(portrait->card)
	{
		AutoCopyOrDecompressImageToVRAM(portrait->card, 32 * presentBGTileIndex + 0x6000000);
		writePlainTSA(TSABufferInWRAM, (presentBGPaletteIndex << 12) + (presentBGTileIndex & 0x3FF), 10, 9);
		return;
	}
	if(portrait->tileset && portrait->extra->bg->tsa)
	{
		AutoCopyOrDecompressImageToVRAM(portrait->tileset, 32 * presentBGTileIndex + 0x6000000);
		OutputToBGPaletteBuffer(portrait->palette, 32 * presentBGPaletteIndex, 32);
		writeTemplateTSA(TSABufferInWRAM, portrait->extra->bg->tsa, ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		if(portrait->extra->bg->mask)
		{
			for(i = 0; i < 9; i++)
				for(j = 0; j < 10; j++)
					TSABufferInWRAM[32 * i + j] &= - portrait->extra->bg->mask[10 * i + j];
		}
	}
}


// 新的人物详情界面头像框绘制函数的接口
__attribute__((section(".callDrawPortraitInBox")))
void callDrawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	// drawPortraitInBox(TSABufferInWRAM, portraitID, presentBGTileIndex, presentBGPaletteIndex);
	showStatusScreenPortrait(TSABufferInWRAM,portraitID,presentBGTileIndex,presentBGPaletteIndex);
}

// 新的支持非8像素对齐的眨眼/使眼色函数
void blinkOrWink0(int *mempool, int eyeStatus)
{
	int winkFlag;	// 使眼色标识
	s16 eyeTileIndexDelta;	// 眼睛帧Tile编号的偏移量
	int *data;	// 头像显示控制相关数据
	struct Portrait *portrait;	// 头像
	int x;	// 精灵横坐标
	int y;	// 精灵纵坐标

	if(eyeStatus & (~0x81))
		return;
	winkFlag = eyeStatus & 0x80;
	eyeTileIndexDelta = 88 - (eyeStatus & 1)*(88 - 24);
	data = (int *)mempool[11];
	portrait = data[11];
	x = 4 - portrait->x.eyePositionX;
	if(!checkPortraitInvert(data))
		x = -x;
	x = (8 * x * (1-portrait->eyeMouthPositionAlignmentFlag) + x * portrait->eyeMouthPositionAlignmentFlag + (s16)data[13] - 16) & 0x1FF;
//	x = (8 * x + data[26] - 16) & 0x1FF;
	if(checkPortraitInvert(data))
		LOWORD(x) = x + 0x1000;
//		x = (((x & 0xFFFF) + 0x1000) & 0xFFFF)|(x & 0xFFFF0000);
	y = ((-(getPortraitControlFlag(data) & 0x400)>>31) & 0x400) + ((*(u16 *)((int)data + 54) + 8 * portrait->y.eyePositionY * (1 - portrait->eyeMouthPositionAlignmentFlag) + portrait->y.eyePositionY * portrait->eyeMouthPositionAlignmentFlag) & 0xFF);
	if(winkFlag)
	{
		if(!checkPortraitInvert(data))
			LOWORD(x) = x + 16;
//			x = (((x & 0xFFFF) + 16) & 0xFFFF)|(x & 0xFFFF0000);
		AddSprite(*(s8 *)((int)data + 65),x,y,winkFrameTemplate,*(s16 *)((int)data + 60) + eyeTileIndexDelta + 2);
	}
	else
		AddSprite(*(s8 *)((int)data + 65),x,y,blinkFrameTemplate,*(s16 *)((int)data + 60) + eyeTileIndexDelta);
	
}

// 嘴部动画函数
void mouthAnimation(int *mempool)
{
	int mouthFrameTileNoDela; // 控制读取不同的帧
	int *data;
	int x; // 嘴巴精灵横坐标
	int y; // 嘴巴精灵纵坐标
	struct Portrait *portrait; // 头像

	data = mempool[11];
	portrait = data[11];
	// 写Tile
	mouthFrameTileNoDela = 0;
	if(!(getPortraitControlFlag(data) & 8))
		mouthFrameTileNoDela = 24;

	if(getPortraitControlFlag(data) & 0x30)
	{
		if(!(--*((s16 *)mempool + 25) & 0x8000))
			goto LABEL_3;
		*((s16 *)mempool + 25) = ((sub(8000EB4)() >> 16) & 7) + 1;
		*((s16 *)mempool + 24) = (*((s16 *)mempool + 24) + 1) & 3;
		if(*((s16 *)mempool + 24) == 1 || *((s16 *)mempool + 24) == 3)
			mouthFrameTileNoDela += 8;
		if(*((s16 *)mempool + 24) == 2)
			mouthFrameTileNoDela += 16;
		changeTiles((int)portrait->mouthFrame + 32 * mouthFrameTileNoDela,32 * ((*(s16 *)((int)data + 60) + 28) & 0x3FF) + 0x6010000,4,2);
		goto LABEL_3;
	}

	changeTiles((int)portrait->mouthFrame + 32 * (mouthFrameTileNoDela + 16),32 * ((*(s16 *)((int)data + 60) + 28) & 0x3FF) + 0x6010000,4,2);

	// 写OAM
LABEL_3:
	x = 4 - portrait->mouthPositionX;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		x = 8 * x;
	if(!checkPortraitInvert(data))
		x = - x;
	x = 0x1FF & (x + *(s16 *)((int)data + 52) - 16);
	if(checkPortraitInvert(data))
		LOWORD(x) = x + 0x1000;
	y = portrait->mouthPositionY;
	if(!portrait->eyeMouthPositionAlignmentFlag)
		y = 8 * y;
	y = ((y + *(s16 *)((int)data + 54)) & 0xFF) + (0x400 & (-(0x400 & getPortraitControlFlag(data)) >> 31));
	AddSprite(*(s8 *)((int)data + 65),x,y,mouthFrameTemplate,*(s16 *)((int)data + 60) + 28);

}

// 嘴部动画接口函数
__attribute__((section(".callMouthAnimation")))
void callMouthAnimation(int *mempool)
{
	//mouthAnimation(mempool);
	playMouthAnimation(mempool);
};

void playMouthAnimation(int *mempool)
{
	int *data;
	pPortraitNew portrait;
	bool smile; // 是否微笑
	int tileNumOffset;
	int tileNumFrame; // 一帧的tile数

	data = mempool[11];
	portrait = data[11];
	if(isNewPortraitExtension(portrait))
	{
		if(portrait->extra->mouth->frame && portrait->extra->mouth->width && portrait->extra->mouth->height)
		{
			data = mempool[11];
			portrait = data[11];

			smile = FALSE;
			tileNumFrame = (portrait->extra->mouth->width / 8) * (portrait->extra->mouth->height / 8);
			if(getPortraitControlFlag(data) & 8)
				smile = TRUE;
			if(smile)
				tileNumOffset = 0;
			else
				tileNumOffset = tileNumFrame * 3;
			if(getPortraitControlFlag(data) & 0x30 && (--*((s16 *)mempool + 25) & 0x8000))
			{
				*((s16 *)mempool + 25) = ((sub(8000EB4)() >> 16) & 7) + 1;
				*((s16 *)mempool + 24) = (*((s16 *)mempool + 24) + 1) & 3;
				if(*((s16 *)mempool + 24) == 1 || *((s16 *)mempool + 24) == 3)
					tileNumOffset += tileNumFrame;
				if(*((s16 *)mempool + 24) == 2)
					tileNumOffset += tileNumFrame * 2;
				changeTiles(portrait->extra->mouth->frame + 32 * tileNumOffset, 32 * ((*(s16 *)((int)data + 60) + portrait->extra->mouth->tileNo) & 0x3FF) + 0x6010000, portrait->extra->mouth->width / 8, portrait->extra->mouth->height / 8);

			}
			else
				changeTiles(portrait->extra->mouth->frame + 32 * (tileNumOffset + tileNumFrame * 2), 32 * ((*(s16 *)((int)data + 60) + portrait->extra->mouth->tileNo) & 0x3FF) + 0x6010000, portrait->extra->mouth->width / 8, portrait->extra->mouth->height / 8);
		}
	}
	else
		mouthAnimation(mempool);
};

__attribute__((section(".playMouthAnimation")))
void (* const pPlayMouthAnimation)(int *) = playMouthAnimation;

// 判断是否是新扩展头像格式
bool isNewPortraitExtension(pPortraitNew portrait)
{
	//if(portrait->newFlag == 0xFF)
	if(portrait->newFlag == -1)
		return TRUE;
	return FALSE;
}
