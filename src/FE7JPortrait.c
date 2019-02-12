// by laqieer
// 2017/3/29
// ������ͷ��ϵͳ

#include "FE7JPortrait.h"

// գ��/ʹ��ɫ�ĺ���ָ���
const PTRFUN blinkOrWink[3] = 
{
	blinkOrWink0,
	blinkOrWink1,
	blinkOrWink2
};

// ���FF�Ժ��ͷ�񵥶���һ��ָ���,��0x100��ʼ
// longcall, Os, Cֱ�ӵ���һ��Ҫռ0x18���ֽ�, С����Ҫע�ⲻҪ��д����һ������������
// �û��д��Ϊ�˼�С���, ֻռ0xC���ֽ�
__attribute__((section(".callGetPortrait")))
struct Portrait *callGetPortrait(int portraitIndex)
{
	//return GetPortrait(portraitIndex);

	asm("ldr r1,=GetPortrait\nbx r1");
}

struct Portrait *GetPortrait(int portraitIndex)
{
  return (portraitIndex > 0xFF) ? &portraitTableNew[portraitIndex - 0x100] : &portraitTableOriginal[portraitIndex];
}

// գ�ۺ�ʹ��ɫ������һ�����飬Ȼ��ʵʱ��дVRAM�е�Tile���ݣ�֧�ַ�8���ض���
void blinkOrWink1(u32 *mempool, int eyeStatus)
{
	int eyeShape;	// ���ۻ��ǰ����
	int winkFlag;	// �Ƿ�ֻ���������ֻ�۾�
	struct Portrait *portrait;	// ͷ��
	int *data;
	int x; // �۾����������
	int y; // �۾�����������
	
	data = mempool[11];
	portrait = data[11];
	// дTile(������ʹ��ɫ��գ�۵�����)
	winkFlag = eyeStatus & 0x80;
	eyeShape = 2 - (eyeStatus & 1);
	if(eyeStatus & (~0x81))
		eyeShape = 0;
	changeTiles(portrait->ce.eyeFrameInfo->eyeFrame[eyeShape],32 * ((*(s16 *)((int)data + 60) + 28 + 32 * 2) & 0x3FF) + 0x6010000,4,2);
	// дOAM(�����￼�ǿ���ʹ��ɫ)
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

// գ�ۺ�ʹ��ɫ��ֱ��ʵʱ��дVRAM�е�Tile���ݣ�֧���Զ�����״�ߴ�
// eyeStatus=0 		����
// eyeStatus=1 		�����
// eyeStatus=0x80	�յ�����
// eyeStatus=0x81	�յ�����
void blinkOrWink2(u32 *mempool, int eyeStatus)
{
	int eyeShape;	// ���ۻ��ǰ����
	int winkFlag;	// �Ƿ�ֻ���������ֻ�۾�
	struct Portrait *portrait;	// ͷ��
	// ��i�е�j��
	int i;	// ѭ��������������
	int j;	// ѭ��������������

	portrait = (struct Portrait *)(*(u32 *)(mempool[11] + 44));
	if(eyeStatus & (~0x81))
	{
		for(i = 0;i < portrait->ce.eyeFrameInfo->height;i++)
			for(j = 0;j < portrait->ce.eyeFrameInfo->width;j++)
				changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[0] + 32 * (portrait->ce.eyeFrameInfo->width * i + j),0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * i + j]) & 0x3FF),1,1);
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
	// ���������tileд��ķ���ʱ�俪����,����Ҫ����changeTiles����������ڲ�ʵ�������ڴ��е�һ��tile������Ϣ������׷��һ�����ͼ�¼������ֱ��д���Դ棬���۾�֡�ߴ�ϴ��ʱ��(����64x32)���׵���һ��ʱ�����ڴ����,���Ը���ֱ������д��ķ���,��������ľ����������۾�֡������tile���Դ���Ҳ�����Ƕ�ά���ڵģ������ֽ�ͷ����۾�֡���뱣�����������ܴ�ɢ
	// ���õķ����Ǹ����۾�֡ģ������Լ�������Ѵ��ͷ����������ڵ�tileһ�δ��ͣ�����д����㷨�ˣ������������Ӱ�
	// ���߿���С�ߴ���۾�֡���дtile����ߴ���۾�֡������дtile����Ϊ���Է���
	if(winkFlag)
		changeTiles((int)portrait->ce.eyeFrameInfo->eyeFrame[eyeShape] + 32 * (portrait->ce.eyeFrameInfo->width * (portrait->ce.eyeFrameInfo->height - portrait->ce.eyeFrameInfo->winkHeight) + (portrait->ce.eyeFrameInfo->width - portrait->ce.eyeFrameInfo->winkWidth)), 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[portrait->ce.eyeFrameInfo->width * (portrait->ce.eyeFrameInfo->height - portrait->ce.eyeFrameInfo->winkHeight) + (portrait->ce.eyeFrameInfo->width - portrait->ce.eyeFrameInfo->winkWidth)]) & 0x3FF), portrait->ce.eyeFrameInfo->winkWidth, portrait->ce.eyeFrameInfo->winkHeight);
	else
		changeTiles(portrait->ce.eyeFrameInfo->eyeFrame[eyeShape], 0x6010000 + 32 * ((*(u16 *)(mempool[11] + 60) + portrait->ce.eyeFrameInfo->blinkTemplate[0]) & 0x3FF), portrait->ce.eyeFrameInfo->width, portrait->ce.eyeFrameInfo->height);
}

// �������ϸ�ʽ�Ĳ�ͬ������Ӧ��գ��/ʹ��ɫ����
void callBlinkOrWink(u32 *mempool, int eyeStatus)
{
	struct Portrait *portrait;	// ͷ��

	portrait = (struct Portrait *)(*(u32 *)(mempool[11] + 44));
	blinkOrWink[portrait->eyeControlFlag - 1](mempool,eyeStatus);
}

// գ��/ʹ��ɫ�����ӿ�
void callCallBlinkOrWink(u32 *mempool, int eyeStatus)
{
	callBlinkOrWink(mempool,eyeStatus);
}

// ���õ�BlinkOrWink�ĺ���1
// գ��
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

// ���õ�BlinkOrWink�ĺ���1�ӿ�
__attribute__((section(".callBlink")))
void callBlink(s16 *mempool)
{
	blink(mempool);
}

// ���õ�BlinkOrWink�ĺ���2
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

// ���õ�BlinkOrWink�ĺ���2�ӿ�
__attribute__((section(".call_sub_80077E8")))
void call_sub_80077E8(s16 *mempool)
{
	sub_80077E8(mempool);
}

// ���õ�BlinkOrWink�ĺ���3
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

// ���õ�BlinkOrWink�ĺ���3�ӿ�
__attribute__((section(".call_sub_8007824")))
void call_sub_8007824(s16 *mempool)
{
	sub_8007824(mempool);
}

// ���õ�BlinkOrWink�ĺ���4
// ʹ��ɫ
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

// ���õ�BlinkOrWink�ĺ���4�ӿ�
__attribute__((section(".callWink")))
void callWink(s16 *mempool)
{
	wink(mempool);
}

// ѡ���ͷ�������ģ�壬֧���Զ���ģ��
void chooseMainPortraitSpriteTemplate(u32 *mempool)
{
	u32 flag1;	// ����ģ��ѡ��
	u32 flag2;
	s16 delta;
	struct Portrait *portrait;	// ͷ��

	portrait = (struct Portrait *)mempool[11];
	flag1 = mempool[12] & 0x807;

	/*
	if(flag1 == 2 || flag1 == 3)				// �Ự�г��ֵ�ͷ��
		mempool[14] = portraitTemplatePairTable[max(portrait->portraitTemplatePair,1)][flag1 & 1];
	else if(flag1 == 0x800 || flag1 == 0x801)	// �鿴֧Ԯ�Ի�ʱ���ϵ�ͷ��
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

// �µ�ѡ���ͷ�������ģ�庯���Ľӿ�
__attribute__((section(".callChooseMainPortraitSpriteTemplate")))
void callChooseMainPortraitSpriteTemplate(s16 *mempool)
{
	chooseMainPortraitSpriteTemplate((u32 *)mempool);
}

// �µ������������ͷ�����ƺ���
void drawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	struct Portrait *portrait;	// ͷ��
	int i;
	int j;

	if(!portraitID)
		return;
	portrait = GetPortrait(portraitID);
	OutputToBGPaletteBuffer(portrait->portraitPalette, 32 * presentBGPaletteIndex, 32);
	if(portrait->mainPortrait)	// ��ͷ��ͷ��
	{
		AutoCopyOrDecompressImageToVRAM(portrait->mainPortrait, 32 * presentBGTileIndex + 0x6000000);
		OutputToBGPaletteBuffer(portrait->portraitPalette, 32 * presentBGPaletteIndex, 32);
		if(PortraitHeightFix(portraitID)<<24)
			writeTemplateTSA(TSABufferInWRAM, portraitInBoxTemplateTable[1], ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		else
			writeTemplateTSA(TSABufferInWRAM, portraitInBoxTemplateTable[portrait->portraitTemplateInBox], ((presentBGPaletteIndex & 0xF)<< 12) + (presentBGTileIndex & 0x3FF));
		// �ɰ�ü�
		for(i = 0; i < 9; i++)
			for(j = 0; j < 10; j++)
				TSABufferInWRAM[32 * i + j] &= - portraitMaskTable[portrait->portraitMaskInBox][10 * i + j];
	}
	else	// ��ͷ��ְҵ��
	{
		AutoCopyOrDecompressImageToVRAM(portrait->ce.classCard, 32 * presentBGTileIndex + 0x6000000);
		writePlainTSA(TSABufferInWRAM, (presentBGPaletteIndex << 12) + (presentBGTileIndex & 0x3FF), 10, 9);
	}
}

// �µ������������ͷ�����ƺ����Ľӿ�
__attribute__((section(".callDrawPortraitInBox")))
void callDrawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex)
{
	drawPortraitInBox(TSABufferInWRAM, portraitID, presentBGTileIndex, presentBGPaletteIndex);
}

// �µ�֧�ַ�8���ض����գ��/ʹ��ɫ����
void blinkOrWink0(int *mempool, int eyeStatus)
{
	int winkFlag;	// ʹ��ɫ��ʶ
	s16 eyeTileIndexDelta;	// �۾�֡Tile��ŵ�ƫ����
	int *data;	// ͷ����ʾ�����������
	struct Portrait *portrait;	// ͷ��
	int x;	// ���������
	int y;	// ����������

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

// �첿��������
void mouthAnimation(int *mempool)
{
	int mouthFrameTileNoDela; // ���ƶ�ȡ��ͬ��֡
	int *data;
	int x; // ��;��������
	int y; // ��;���������
	struct Portrait *portrait; // ͷ��

	data = mempool[11];
	portrait = data[11];
	// дTile
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

	// дOAM
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

// �첿�����ӿں���
__attribute__((section(".callMouthAnimation")))
void callMouthAnimation(int *mempool)
{
	mouthAnimation(mempool);
};

