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

// �������ս��������ɫ���б�
#define	characterBattlePalTable	((CharacterBattlePal *)0x8FD8008)

// �������ս��������ɫ����Ϣ�ṹ�嶨��
typedef struct {
	char identifier[12];	// ��ʶ��(�ַ���)
	void *pal;				// ָ���ɫ��
} CharacterBattlePal;

// ս���������ȫ�ֱ���

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

// �ж϶���������߻����ұ�
// bool isUnitAtRightOrLeft(int AIS);
#define isUnitAtRightOrLeft		sub(8054E60)
