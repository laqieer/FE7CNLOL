// by laqieer
// ֧��ս�������ֳɶ����
// 2017/6/13
// ֧����ѹ����data2/3/4,�����ѹ���ڴ�
// 2017/6/20

#pragma once

#include "AgbTypes.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"
#include "FE7JCoroutine.h"
#include "IDAPro.h"

#pragma long_calls
// ��ȡս������������ݵ��ڴ�
void battleAnimationInit();
#pragma long_calls_off

void callBattleAnimationInit();

// �հ��һ�ս��������
#define	FE7BattleAnimationBank	((BattleAnimation *)0x8E00008)

// ս�������ṹ�嶨��
typedef	struct {
	char identifier[12];	// ��ʶ��(�ַ���)
	int	*sectionOffset; // ��һ��ָ��(ָ�򶯻������ֻ���ƫ�Ʊ�)
	void *event;			// �ڶ���ָ��(ָ�򶯻��ű�(��ָ����߳�Ϊ�¼����))
	void *oamR2L;			// ������ָ��ָ��OAM����(���Ҳ೯���)
	void *oamL2R;			// ���ĸ�ָ��ָ��OAM����(����೯�Ҳ�)
	void *palGroup;			// �����ָ��ָ���ɫ����
} BattleAnimation;

// �������нṹ�嶨��
typedef struct ais {
	u16 state;	// ��ǰ����״̬
				// AND 0x02: True when cape flowing? Acts as though AND 0x01 is false?
				// AND 0x01: True to display sprites/continue animation
	s16 XOffset;	// X offset based on screen scroll
	s16 YOffset;	// unknown
	u16 delayCountdown;	// �ӳٵ���ʱ
	u16 OBJAttr2Base;	// ����OAM����2��ֵ
						// Halfword of basis for part 2 of 0-2 of OAM data (which selects which tile is the top left corner)
						// 0x9B00 for right unit (name = 0x300; tile 768 where the sheet is loaded to)
	u16 unk_A;
	u16 unk_C;
	u16 unk_E;
	u16 unk_10;
	u8 unk_12;
	u8 frameID;	// ֡ID
	/*
	u8 unk_14;
	u8 C85ID;	// ID of 0x85 command being executed
	u16 unk_16;
	u32 unk_18;
	u32 unk_1C;
	*/
	// C85ָ��ID�洢��ƫ��(ͨ����0)
	u8 C85IDBufferIndex;
	// C85ָ���ID(���һ���ֽ�)���Ա��洢��������һƬ�����Ļ�������(���建��������C85IDBufferIndex����)(ͨ��ֻ�Ǵ洢�ڵ�һ��λ��)
	u8 C85IDBuffer[11];
	u32 *nextCmd;	// Frame pointer
					// ��ǰִ�е���λ��(ָ����һ��ָ��)
	u32	*lastCmd;		// Pointer to last 0x86 command?
	void *sheet;	// ROM�е�sheet����(��ѹ��)
	void *sheetBuffer;	// RAM�е�sheet����(��ѹ��)
	void *OAMInfoBuffer;	// OAM start pointer
	// �����ڶ���typedef����֮ǰʹ����
//	AnimationInterpreter *parent;	// Parent AIS (drawn before this one)
//	AnimationInterpreter *child;	// Child AIS (drawn after this one)
	struct ais *parent;	// Parent AIS (drawn before this one)
	struct ais *child;	// Child AIS (drawn after this one)
	void *currentOAMInfo;	// OAM pointer
	u32 unk_40;
	u32 unk_44;
} AnimationInterpreter;

// �������ս��������ɫ���б�
#define	characterBattlePalTable	((CharacterBattlePal *)0x8FD8008)

// �������ս��������ɫ����Ϣ�ṹ�嶨��
typedef struct {
	char identifier[12];	// ��ʶ��(�ַ���)
	void *pal;				// ָ���ɫ��
} CharacterBattlePal;

// ս���������ȫ�ֱ���

// AISָ���(4��Ԫ�ص�����)
#define	AISTable							((AnimationInterpreter **)0x2000000)
// �ֱ���:
// ���ս������AIS
// #define	BattleAISLeftSide					(AISTable[0])
// �ݲ�����������;
// spell data struct for left unit?
// #define BattleAIS2LeftSide					(AISTable[1])
// �ұ�ս������AIS
// #define	BattleAISRightSide					(AISTable[2])
// #define	BattleAIS2RightSide					(AISTable[3])
// AIS��(�������50��AIS)��ʼ��ַ
#define	AISBank		((AnimationInterpreter *)0x2028E6C)
// AIS�����ڵ�
#define	RootAIS		((AnimationInterpreter **)0x2029C7C)

// ս������λ�����
#define	IfBattleAnimationIsAtTheLeftSide	(*(u16 *)0x203DFE8)
// ս������λ���Ҳ�
#define	IfBattleAnimationIsAtTheRightSide	(*(u16 *)0x203DFEA)
// ���ս������ID
#define	BattleAnimationIDLeftSide			(*(u16 *)0x203E066)
// �Ҳ�ս������ID
#define	BattleAnimationIDRightSide			(*(u16 *)0x203E068)
// ���ս��������ɫ���������
#define	BattleAnimationPalSlotLeftSide		(*(u16 *)0x203DFF8)
// �Ҳ�ս��������ɫ���������
#define	BattleAnimationPalSlotRightSide		(*(u16 *)0x203DFFA)
// ����������ս����ɫ��ID
#define	CharaterBattleAnimationPaletteIDLeftSide	(*(u16 *)0x203DFF4)
// �Ҳ��������ս����ɫ��ID
#define	CharaterBattleAnimationPaletteIDRightSide	(*(u16 *)0x203DFF6)
// ���ս�������¼��ű�����
#define	BattleAnimationEventBufferLeftSide			((u32 *)0x200F1C8)
// �Ҳ�ս�������¼��ű�����
#define	BattleAnimationEventBufferRightSide			((u32 *)0x2011BC8)
// ��ද���ĸ�ģʽ�ָ���Ϣ��ַ
#define	BattleAnimationSectionInfoLeftSide			(*(int **)0x200005C)
// �Ҳද���ĸ�ģʽ�ָ���Ϣ��ַ
#define	BattleAnimationSectionInfoRightSide			(*(int **)0x2000060)
// ��ද����ɫ���黺��
#define	BattleAnimationPaletteGroupBufferLeftSide	((u16 *)0x2004088)
// �Ҳද����ɫ���黺��
#define	BattleAnimationPaletteGroupBufferRightSide	((u16 *)0x2004128)	
// ��ද����ɫ���ַ
#define	BattleAnimationPaletteLeftSide				(*(u16 **)0x2000054)
// �Ҳද����ɫ���ַ
#define	BattleAnimationPaletteRightSide				(*(u16 **)0x2000058)
// ��ද��OAM��Ϣ����
#define	BattleAnimationOAML2RBuffer					((void *)0x20041C8)
// �Ҳද��OAM��Ϣ����
#define	BattleAnimationOAMR2LBuffer					((void *)0x20099C8)
// �Ҳද��sheet����
#define	BattleAnimationSheetBufferRightSide			((void *)0x2002088)
// ��ද��sheet����
#define	BattleAnimationSheetBufferLeftSide			((void *)0x2000088)
// ���������ħ������ID
#define	SpellAnimationIDLeftSide					(*(u16 *)0x203DFFC)
// �Ҳ�������ħ������ID
#define	SpellAnimationIDRightSide					(*(u16 *)0x203DFFE)
// ˵��ħ������IDҲ����Ϊ˫�ֽڴ����,����ڴ˻����Ͽ��Ժ�������չ���޵�0xFFFF,�������ǵ�ħ������������255�������κ��٣������ݲ���չ

// ��غ���

// �������ĸ�����ID�ĵ�ɫ����
// ����:��ĳЩ����ID�Ķ���������ɫ����
// signed int getAnimationIDForPaletteGroup(int animationID, int RightOrLeft);
#define	getAnimationIDForPaletteGroup	sub(80547C0)

// ����ս��������ö��ֵ��
enum {
	FE7BABank
};

// ekrUnitKakudaiЭ����
#define	ekrUnitKakudai		((struct coroutine *)0x8C0A560)
#define	UnitKakudai1	sub(8051F38)
#define	UnitKakudai2	sub(80520C4)
#define	UnitKakudai3	sub(805226C)

// ��չ���UnitKakudai1
void UnitKakudai1Ex(struct context *ctx);

// �������¼�(��չ)
//#pragma long_calls
//void battleAnimationEventHandlerEx();
//#pragma long_calls_off

//void callBattleAnimationEventHandlerEx();

// ԭ����ս�������¼��������
// void battleAnimationEventHandler();
#define	battleAnimationEventHandler	sub(8053C3C)

// �����е�AISִ��
// void ForAllAIS();
#define	ForAllAIS	sub(8006488)

// �������еĶ����ű�
// void battleAnimationScriptProc();
// #define	battleAnimationScriptProc	sub(8006320)

// �����������ű�
// signed int BattleAnimationScriptHandler(AnimationInterpreter *AIS);
// #define	BattleAnimationScriptHandler	sub(8006518)

// ������0x85ָ���¼�
// void battleAnimationEventHandler();
// #define	battleAnimationEventHandler		sub(8053C3C)

// ������0x86ָ�������OAM����
// void battleAnimationOAMInfoHandler(void *battleAnimationOAMInfoBuffer, int a2, unsigned __int16 a3, int a4);
#define	battleAnimationOAMInfoHandler	sub(8067C30)
// void BattleAnimationOAMInfoHandler2(AnimationInterpreter *AIS);
#define	BattleAnimationOAMInfoHandler2	sub(80066E0)

/*
// ��������ı���
#define a1a a1
#define a1b a1
#define a1c a1
#define a1d a1
#define a1e a1
*/

#pragma long_calls
void sub_8054AC0(int xl, int xr);
#pragma long_calls_off

void call_sub_8054AC0(int xl, int xr);

// ս��˫��AIS��ʼ��
// xl��xr�ֱ�Ϊ����˫��ƫ������ľ���
// ���ӹ���: xl = xr = 6
// Զ�̹���: xl = xr = 8
// void battleAnimationAISInit(int xl,int xr);
#define battleAnimationAISInit	sub_8054AC0


#pragma long_calls
void sub_8054D7C(int a1, int a2);
#pragma long_calls_off

void call_sub_8054D7C(int a1, int a2);

#pragma long_calls
void sub_8054764(void *AIS);
#pragma long_calls_off

// ����ս������sheet
void call_sub_8054764(void *AIS);

#define	updateBattleAnimationSheet	call_sub_8054764

#pragma long_calls
void DemoBattleAnimationInit(void *AIS);
#pragma long_calls_off

// ְҵ���ܵ�DEMOս��������ʼ��
// ��Ϊֻ��һ������������AIS����0x02000000
void callDemoBattleAnimationInit(void *AIS);

// �ж϶���������߻����ұ�
// bool isUnitAtRightOrLeft(int AIS);
#define isUnitAtRightOrLeft		sub(8054E60)

// ӳ����˵�ս������
#define	MirrorBattleAnimationID		0x5E5E

// ��ұ���������չ
// ��չC2E��C2Fָ��
// ifCritical�Ƿ��ɱ
void battleExtraAnimation(void *AIS, bool ifCritical);

// ����ʩ��ħ���󶯻�
// void loadMagfcast(void *AIS, bool ifCritical)
#define	loadMagfcast	sub(8063400)

// ���ʵ�ָ��Ӷ�����չ
extern const int callExtraAnimation;
extern const int callExtraAnimationCRT;
// extern int callExtraAnimation;
// extern int callExtraAnimationCRT;

// ���鱳��Э��
#define	efxFimbulvetrBG		((struct coroutine*)0x8C10FB8)

// �����չC0Dָ�ʹ��֧����ѹ��data
extern const int C0DHandlerJPTCase0_1_2_3_9;

// ��ʦ����ѭ����չ
extern const int loc_80065EC_EX;

// ����������չ
extern const int loc_806829C_EX;

// �Ŵ�����ͼƬ���
#define	FireDragonImg	0x82E445C	// ��������ͼ��
#define FireDragonPalGroup	0x82E6C60	// ����ͼ���ɫ����(���б�ɫ�ĵ�ɫ�嶯��)
#define	FireDragonTailTSA	0x82E6D40	// ����β��TSA
#define	FireDragonBodyTSA	0x82E6E8C	// �������岿�ֵ�TSA(��ͷ)
#define	FireDragonBodyUPTSA	0x82E7170	// �������岿�ֵ�TSA(̧ͷ)
#define	FireDragonBodyUPNoWingTSA	0x82E7418	// �������岿�ֵ�TSA(̧ͷ)(����)
#define	FireDragonBattleAnimationSheet1	0x82E76A4	// ����ս������sheet1
#define FireDragonBattleAnimationSheet2	0x82E8584	// ����ս������sheet2
#define	DyingDragonHeadImg	0x82E9240	// ������ʱ��ͷ�����ͼ��
#define	FireDragonSpriteAnimationPalGroup	0x82E9CD8	// �������鶯����ɫ����
// ����ɫ�嶯�����
#define	loadFireDragonBGPaletteAnimation	sub(80657D4)
// struct context *loadFireDragonBGPaletteAnimation(void *AIS);
#define	efxFireDragonBGPaletteAnimation		((struct coroutine *)0x8C4879C)
#define	FireDragonBGPaletteAnimation		sub(8066118)
// void FireDragonBGPaletteAnimation(struct context *ctx)

// BGͼƬ
typedef struct {
	void *img;
	void *pal;
	void *tsa;
} BGImage;

