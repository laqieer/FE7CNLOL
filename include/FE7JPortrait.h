// by laqieer
// 2017/3/29
// ���µ�����ͷ��ϵͳ��صĶ���

#pragma once

#include "AgbTypes.h"
#include "FE7JFunc.h"
#include "IDAPro.h"

/*
// ԭ����ͷ��ָ��ṹ��
struct Portrait{
	void *mainPortrait;	// ָ���ͷ���ָ��
	void *miniPortrait;	// ָ��Сͷ���ָ��
	void *portraitPalette;	// ָ���ɫ���ָ��
	void *mouthFrame;	// ָ���첿֡��ָ��
	void *classCard;	// ָ��ְҵ����ָ��
	s8 mouthPositionX;	// �첿֡��λ��
	s8 mouthPositionY;	// �첿֡��λ��
	s8 eyePositionX;		// �۾�֡��λ��
	s8 eyePositionY;		// �۾�֡��λ��
	s8 eyeControlFlag;	// �۾����Ʊ�ʶ
	s8 dummy1;
	s8 dummy2;
	s8 dummy3;
};
*/

// �����۾�֡����Ϣ
struct EyeFrameInfo{
	s8 width;	// ��(��λ:tile)(ֻ��blinkOrWink2��Ч)
	s8 height;	// ��(��λ:tile)(ֻ��blinkOrWink2��Ч)
	s8 winkWidth;	// գ��֡�Ŀ��(��λ:tile)(ֻ��blinkOrWink2��Ч)
	s8 winkHeight;	// գ��֡�ĸ߶�(��λ:tile)(ֻ��blinkOrWink2��Ч)
	u8 *eyeFrame[3];	// ָ��գ��֡��ָ������: ���ۣ�����ۣ�����
	s16 *blinkTemplate;	// ָ��գ��֡ģ���ָ��(ֻ��blinkOrWink2��Ч)
};

// ��չ��ͷ��ָ��ṹ��
struct Portrait{
	void *mainPortrait;	// ָ���ͷ���ָ��
	void *miniPortrait;	// ָ��Сͷ���ָ��
	void *portraitPalette;	// ָ���ɫ���ָ��
	void *mouthFrame;	// ָ���첿֡��ָ��
	union
	{
		void *classCard;	// ָ��ְҵ����ָ��
		struct EyeFrameInfo*eyeFrameInfo;		// ��ְҵ�����������ָ���۾�֡��Ϣ��ָ��
	} ce;
	s8 mouthPositionX;	// �첿֡��λ��
	s8 mouthPositionY;	// �첿֡��λ��
	union
	{
		s8 eyePositionX;		// �۾�֡��λ��
		s8 offsetX;			//TODO eyeControlFlag=3ʱΪͷ������ˮƽλ��
	} x;
	union
	{
		s8 eyePositionY;		// �۾�֡��λ��
		s8 offsetY;			//TODO eyeControlFlag=3ʱΪͷ�����崹ֱλ��
	} y;
	s8 eyeControlFlag;	// �۾����Ʊ�ʶ,գ�۷�ʽ
	s8 portraitTemplatePair;	// �Ի���ͷ��ģ������
	s8 portraitTemplateInBox;	// �������ݽ���ͷ���ģ�����
	s8 portraitMaskInBox:7;	// �������ݽ���ͷ����ɰ����
	s8 eyeMouthPositionAlignmentFlag:1;		// ���λ��ʶ�۾�����������Ƿ���8���صı������Ǿ�ϸ������
};

// ��ͷ�������ģ��

// ��ģ��, 4�飬ͷ�����Ҳ࣬�������
#define	oldPortraitTemplate1Left		0x8BFF828
// ��ģ�壬4�飬ͷ������࣬�����Ҳ�
#define	oldPortraitTemplate1Right	0x8BFF842
// ��ģ��, 6�飬ͷ�����Ҳ࣬�������
#define	oldPortraitTemplate2Left		0x8BFF85C
// ��ģ�壬6�飬ͷ������࣬�����Ҳ�
#define	oldPortraitTemplate2Right	0x8BFF882
// ��ģ��, 8�飬ͷ�����Ҳ࣬�������
#define	oldPortraitTemplate3Left		0x8BFF8A8
// ��ģ�壬8�飬ͷ������࣬�����Ҳ�
#define	oldPortraitTemplate3Right	0x8BFF8DA
// ��ģ��, 8�飬ͷ�����Ҳ࣬�������
#define	oldPortraitTemplate4Left		0x8BFF90C
// ��ģ�壬8�飬ͷ������࣬�����Ҳ�
#define	oldPortraitTemplate4Right	0x8BFF93E

// ������ϸ����ͷ�����TSAģ��

// ��ģ�壬��
#define	oldPortraitInBoxTemplateLow		0x81911D4
// ��ģ�壬��
#define	oldPortraitInBoxTemplateHigh	0x819128C

// ͷ��ָ���
#define portraitTableBase	0x8D5E23C
#define	portraitTableOriginal	((struct Portrait*)portraitTableBase)

// ����ͷ��ID����ROM�е�ͷ���ַ
//#define	GetPortrait			sub(80069B0)
// Portrait * GetPortrait(int portraitIndex)

/*
// ԭ����գ�ۺ�ʹ��ɫ����
#define blinkOrWink0		sub(80075F0)
// void oldBlinkOrWink(u32 *mempool, int eyeStatus);
*/

// �µ�գ��/ʹ��ɫ(գ�����)����,����һ�����飬Ȼ��ʵʱ��дVRAM�е�Tile���ݣ�֧�ַ�8���ض���
void blinkOrWink1(u32 *mempool, int eyeStatus);

// �µ�գ��/ʹ��ɫ(գ�����)����,ֱ��ʵʱ��дVRAM�е�Tile���ݣ�֧���Զ�����״�ߴ�
void blinkOrWink2(u32 *mempool, int eyeStatus);

// ���ò�ͬ��գ��/ʹ��ɫ����
void callBlinkOrWink(u32 *mempool, int eyeStatus);

// գ��/ʹ��ɫ�����ӿ�
void callCallBlinkOrWink(u32 *mempool, int eyeStatus);

// ���õ�BlinkOrWink�ĺ���1
// գ��
#pragma long_calls
void blink(s16 *mempool);
#pragma long_calls_off

// ���õ�BlinkOrWink�ĺ���1�ӿ�
void callBlink(s16 *mempool);

// ���õ�BlinkOrWink�ĺ���2
void sub_80077E8(s16 *mempool);

// ���õ�BlinkOrWink�ĺ���2�ӿ�
void call_sub_80077E8(s16 *mempool);

// ���õ�BlinkOrWink�ĺ���3
#pragma long_calls
void sub_8007824(s16 *mempool);
#pragma long_calls_off

// ���õ�BlinkOrWink�ĺ���3�ӿ�
void call_sub_8007824(s16 *mempool);

// ���õ�BlinkOrWink�ĺ���4
// ʹ��ɫ
void wink(s16 *mempool);

// ���õ�BlinkOrWink�ĺ���4�ӿ�
void callWink(s16 *mempool);

// ѡ���ͷ�������ģ��
void chooseMainPortraitSpriteTemplate(u32 *mempool);

// �µ�ѡ���ͷ�������ģ�庯���Ľӿ�
void callChooseMainPortraitSpriteTemplate(s16 *mempool);

// ͷ��ָ�����չ��0x100֮��
#pragma long_calls
struct Portrait *GetPortrait(int portraitIndex);
#pragma long_calls_off

// ͷ��ָ�����չ�����Ľӿ�
struct Portrait *callGetPortrait(int portraitIndex);

// ����ͷ��ID�ж�ͷ����Ƿ���Ҫ����
#define	PortraitHeightFix	sub(80070AC)
// signed int PortraitHeightFix(int portraitID)

// �µ������������ͷ�����ƺ�����֧���Զ���ģ��
void drawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex);

// �µ������������ͷ�����ƺ����Ľӿ�
void callDrawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex);

// ����ͷ��ģ����ÿ�������3������
// X��Y�ֱ��Ƕ�Ӧԭ����ʽͷ��Ĳο��������ƫ����
#define	getObjectAttribute1(shape,Y)		((((shape)&3)<<14)|((Y)&255))
#define	getObjectAttribute2(size,HFlip,X)	((((size)&3)<<14)|(((HFlip)&1)<<12)|((X)&511))
#define	getObjectAttribute3(tileNo)			((tileNo)&1023)

// �����������ͷ���TSA(tile���)
// x��y�ֱ��Ƕ�ӦTile��256x32��ͼ�е�����
#define	getTileNo(x,y)						((32 * (y) + (x))&1023)

// ������ѹ��ͼƬ���ݳ���(�ֽ���)��Ϊ����ͷ
#define getUncompressedImageLength(byteNum)	((byteNum)<<8)

// ȡ2�����Ľ�Сֵ
#define min(a,b)	((a)<(b)?(a):(b))

// ȡ2�����Ľϴ�ֵ
#define max(a,b)	((a)>(b)?(a):(b))

// ��ȡͷ����ʾ���Ʊ�ʶ
#define getPortraitControlFlag		sub(8006C2C)
// int getPortraitControlFlag(int *data)

// ���ͷ���Ƿ���Ҫ���ҷ�ת����ʾ
#define checkPortraitInvert(data)	((getPortraitControlFlag(data)) & 1)

// �µ�֧�ַ�8���ض����գ��/ʹ��ɫ����
void blinkOrWink0(int *mempool, int eyeStatus);

// ʹ��ɫ֡��������
#define	winkFrameTemplate	0x8BFF768
// գ��֡�ľ�������
#define	blinkFrameTemplate	0x8BFF7A8

// �첿��������
#pragma long_calls
void mouthAnimation(int *mempool);
#pragma long_calls_off

// ��;�������
#define	mouthFrameTemplate	0x8BFF7A8

// �첿�����ӿں���
void callMouthAnimation(int *mempool);

// �ɰ�ָ���
extern const u16* const portraitMaskTable[];

// �������ͷ���ģ���
extern const void * const portraitInBoxTemplateTable[];

// ģ�����
extern const u32 portraitTemplatePairTable[][2];

// ��ͷ��ָ���(��0x100��ʼ)
extern const struct Portrait portraitTableNew[];