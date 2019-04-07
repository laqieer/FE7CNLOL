// by laqieer
// 2017/3/29
// ���µ�����ͷ��ϵͳ��صĶ���

#pragma once

#include "AgbDefine.h"
#include "AgbTypes.h"
#include "FE7JFunc.h"
#include "IDAPro.h"
#include "FE7JStructDef.h"
#include "FE7JCoroutine.h"
#include "FE7JMemoryMap.h"
#include "FE7JBattleAnimation.h"

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

// �����첿֡����Ϣ
struct MouthFrameInfo{
	u16 width;	// ��(��λ:tile)
	u16 height;	// ��(��λ:tile)
	u16 tileX; // �첿֡���Ͻ���ͷ�����еĺ�����(��λ:tile)
	u16 tileY; // �첿֡���Ͻ���ͷ�����е�������(��λ:tile)
	void *mouthFrame;	// ָ���첿֡��ָ��(ԭ�����첿ָ֡��)
	s16 *mouthTemplate;	// ָ��գ��֡ģ���ָ��(��ʱ����,�������������Ժ���չ)
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
	s8 eyeControlFlag;	// �۾����Ʊ�ʶ,գ�۷�ʽ 1=ԭ����(��������2֡) 2=���Ƕ����ľ���(��������1֡) 3=ʵʱ��дͼ������(������û���۾�֡��) 4=һֱ����(û���۾�֡,��գ��) 6=һֱ����(����ԭ���) 
	s8 portraitTemplatePair;	// �Ի���ͷ��ģ������
	s8 portraitTemplateInBox;	// �������ݽ���ͷ���ģ�����
	s8 portraitMaskInBox:7;	// �������ݽ���ͷ����ɰ����
	s8 eyeMouthPositionAlignmentFlag:1;		// ���λ��ʶ�۾�����������Ƿ���8���صı������Ǿ�ϸ������
};

// �����ɵ�ͷ��(�Ự��ʹ����Ʒ��תְ��)
typedef struct PortraitObject
{
	u8 width;	// width (unit: pixel). �� (��λ: ����).
	u8 height;	// height (unit: pixel). �� (��λ: ����).
	s8 offsetX;	// x offset (unit: pixel). ����ƫ�� (��λ: ����).
	s8 offsetY;	// y offset (unit: pixel). ����ƫ�� (��λ: ����).
	u16 *oamL; // Face to left. ͷ����ʱ��OAM.
	u16 *oamR; // Face to Rifgt. ͷ����ʱ��OAM.
}PortraitOBJ,*pPortraitOBJ;

// ����ͷ��(�������������)
typedef struct PortraitBackground
{
	u16 *tsa; // BG Map
	u8 *mask; // �ɰ�
}PortraitBG,*pPortraitBG;

// �۾�����
typedef struct EyeAnimationInfo
{
	u8 width;	// width (unit: pixel). �� (��λ: ����).
	u8 height;	// height (unit: pixel). �� (��λ: ����).
	u8 widthRight;	// right eye width (unit: pixel). ���۵Ŀ� (��λ: ����).
	u8 heightBottom;	// bottom eye (monster?) height (unit: pixel). ����(����?)�ĸ� (��λ: ����).
	int tileNo;	// top left tile number in the tileset. ���Ͻǵ�tile���.
	u8 *frame;	// animation frame (3 frames). ����֡ͼ (3֡). 
				// Frame 0: open. ����.
				// Frame 1: half open half closed. �������.
				// Frame 2: closed. ����.
}EyeAnimation,*pEyeAnimation;

// �첿����
typedef struct MouthAnimationInfo
{
	u8 width;	// width (unit: pixel). �� (��λ: ����).
	u8 height;	// height (unit: pixel). �� (��λ: ����).
	s16 tileNo;	// top left tile number in the tileset. ���Ͻǵ�tile���.
	u8 *frame;	// animation frame (6 frames). ����֡ͼ (6֡). 
				// Frame 0: open (smile). ���� (΢Ц).
				// Frame 1: half open half closed (smile). ���Ű�� (΢Ц).
				// Frame 2: closed (smile). ���� (΢Ц).
				// Frame 3: open. ����.
				// Frame 4: half open half closed. ���Ű��.
				// Frame 5: closed. ����.
}MouthAnimation,*pMouthAnimation;

// ����ͷ����Ϣ����
typedef struct PortraitInfoExtra
{
	pPortraitOBJ obj;	// dialogue portrait. �Ի�ͷ��.
	pPortraitBG bg;	// status screen portrait. ��������ͷ��.
	pEyeAnimation eye;	// eye animation. �۾�����
	pMouthAnimation mouth;	// mouth animation. �첿����.
	char *name;	// portrait name. ͷ������.
}PortraitExtra,*pPortraitExtra;

// ����չͷ����Ϣ�ṹ��
// ��ԭ���Լ�����չ��ʽ������,��newFlag����
typedef struct PortraitInfoNew
{
	u8 *tileset; // 8x8 tile, 256x32 image. ����ͼƬ.
	u8 *mini; // mini portrait. Сͷ��.
	u16 *palette; // palette. ��ɫ��.
	pPortraitExtra extra; // extra portrait info. ����ͷ����Ϣ.
	u8 *card; // class card. ְҵ����.
/*	s8 mouthX; // useless. ����.
	s8 mouthY; // useless. ����.
	s8 eyeX; // useless. ����.
	s8 eyeY; // useless. ����.	*/
	u32 preserve; // preserve for future extension. ����, Ϊ�˱���eyeFlag��ƫ�Ʋ���(��Ϊû���޸�eyeFlag�Ķ�ȡ����).
	u8 eyeFlag; // eye control flag. 1-Normal. 6-always closed.
	s8 newFlag; // new portrait struct format flag (should be set to -1). ��ͷ����Ϣ��ʽ��ʶ, ��Ϊ-1.
	PortraitID id; // self id. ͷ�����.
}PortraitNew,*pPortraitNew;

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

// ����Ҫ�۾�֡��ͷ���ʲô�����������������ʿ����ͷ������
void blinkOrWink3(u32 *mempool, int eyeStatus);

void blinkOrWinkNew(u32 *mempool, int eyeStatus);

// ���ò�ͬ��գ��/ʹ��ɫ����
void callBlinkOrWink(u32 *mempool, int eyeStatus);

void callBlinkOrWinkNew(u32 *mempool, int eyeStatus);

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

void chooseDialoguePortraitOAM(u32 *mempool);

// �µ�ѡ���ͷ�������ģ�庯���Ľӿ�
void callChooseMainPortraitSpriteTemplate(s16 *mempool);

// ��չ������λְҵͷ��
#pragma long_calls
PortraitID GetUnitPortraitID(Unit *pUnit);
PortraitID GetUnitPortraitIDEx(Unit *pUnit);
#pragma long_calls_off

PortraitID callGetUnitPortraitID(Unit *pUnit);

// ͷ��ָ�����չ��0x100֮��
#pragma long_calls
struct Portrait *GetPortrait(int portraitIndex);
pPortraitNew GetPortraitNew(int portraitIndex);
#pragma long_calls_off

// ͷ��ָ�����չ�����Ľӿ�
struct Portrait *callGetPortrait(int portraitIndex);

// ����ͷ��ID�ж�ͷ����Ƿ���Ҫ����
#define	PortraitHeightFix	sub(80070AC)
// signed int PortraitHeightFix(int portraitID)

// �µ������������ͷ�����ƺ�����֧���Զ���ģ��
void drawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex);

void showStatusScreenPortrait(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex);

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

// GBA Text BG Screen (2 bytes per entry)
#define BGTile(tile_number,palette_number,horizontal_flip,vertical_flip)	(((tile_number)&1023)|(((palette_number)&15)<<12)|(((horizontal_flip)&1)<<10)|(((vertical_flip)&1)<<11))

// GBA Color RGB555
#define RGB5(red,green,blue)	(((red)&31)|(((green)&31)<<5)|(((blue)&31)<<10))

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
void playMouthAnimation(int *mempool);
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

// ����չͷ��ָ���(��0x200��ʼ)
extern const pPortraitNew portraitTableNewExtension[];

// ������λְҵͷ���
extern const PortraitID promotedUnitPortraitID[];

#define	paFaceProcs	((int *)0x30040E0)

// int SetupFaceGfxData(int *a1);
#define SetupFaceGfxData	sub(80069E0)

// ��ʾͷ��
// _DWORD *ShowFace(int faceId, int portraitId, int x, int y, int dispType);
#define ShowFace	sub(8006AC4)

// ����ͷ��
// void DeleteFaceByIndex(int faceIndex);
#define DeleteFaceByIndex	sub(8006BE0)

// תְ�ӵ�ʱ��ʾͷ��Ķ���
void playClassChangePortraitAnimation(struct context *ctx);

// ����תְʱ������λͷ��
void playClassChangePortraitAnimationEx(struct context *ctx);

// �ж��Ƿ�������չͷ���ʽ
bool isNewPortraitExtension(pPortraitNew portrait);