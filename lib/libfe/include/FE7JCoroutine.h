// Э�̺�������(6C)
// by laqieer
// 2017/6/1

#pragma once

#include "AgbTypes.h"
#include "callFunc.h"

// Э���е�ԭ�Ӷ���
struct	coroutine{
	u16		codeIndex;	// ָ�����(��Э�̴�����ָ����е�����)
	u16		sarg;		// ��������
	void*	larg;	// ָ���ַ���/Э��/������/�����ȵ�ָ��
};

// Э��(��������)(����6C)ָ��

// ����Э��
#define	endofCoroutine						{0,0,0}
// ������������ָ�������ַ����ĵ�ַ
#define	setNameForContext(name)				{1,0,name}
// �Ե�ǰ������ִ��ָ������
#define	execFunc(func)						{2,0,func}
// ����ѭ�����������
#define	setLoopFuncAndYield(func)			{3,0,func}
// ���õ�ǰ�����ĵ���������
#define	setDestructor(func)					{4,0,func}
// ����ָ��Э��Ϊ��ǰ�����Ĵ�����������
#define addChildContext(coroutine)			{5,0,coroutine}
// ����ָ��Э��Ϊ��ǰ�����Ĵ����������Ĳ�����
#define addChildContextAndYield(coroutine)	{6,0,coroutine}
// ����ָ��Э�̴���ȫ��������
#define addGlobalContext(coroutine)			{7,0,coroutine}
// �ȴ�ָ����Э�̶�Ӧ�������Ĵ�����ִ�У��ڴ�֮ǰһֱ����(���ȴ�ָ����Э����ִ�к��ټ���ִ��)
#define waitforCoroutine(coroutine)			{8,0,coroutine}
// ɾ��ָ��Э�̵�����������(��ɱ��ָ����Э��)
#define	killCoroutine(coroutine)			{9,0,coroutine}
// ����ָ��Э��(�������Э������Ӧ�����������ĵ�˯��ѭ������)
#define awakeCoroutine(coroutine)			{0xA,0,coroutine}
// ���ñ�ǩ
#define setLabel(label)						{0xB,label,0}
// �ƶ���ָ����ǩ��ִ��
#define	gotoLabel(label)					{0xC,label,0}
// ����ָ��Э�̴�ִ��
#define jumptoCoroutine(coroutine)			{0xD,0,coroutine}
// ����(˯��)������ʱ��(��ʵ�������ʱ���ڷ���ִ���������е��ض����������Ըýз�����׼ȷ)
#define sleep(time)							{0xE,time,0}
// ����һ����Ǹ���ǰ������
#define setMark(mark)					{0xF,(mark)&0xFF,0}
// ����
#define yield								{0x10,0,0}
// ����Լ����Ǹ�Э��Ψһ�������ģ���ɾ���Լ�(һ�������Ķ�Ӧһ������̣߳��൱��ɱ���Լ�����߳�)
#define killSelfIfDuplicate					{0x11,0,0}
// �����������е�һ����ʶλ
#define setBitFlag							{0x12,0,0}
// ʲô������1
#define doNothing1							{0x13,0,0}
// �ڵ�ǰ�����Ĵ���������ָ���������ú�������ֵΪ1�����
#define execFuncWithArgYieldIfReturn1(func,arg)	{0x14,arg,func}
// ʲô������2
#define doNothing2							{0x15,0,0}
// ���ε��ã�����0�����
#define execFuncWithArgYieldIfReturn0(func,arg)	{0x16,arg,func}
// ɾ����ǰЭ�̵�����������(��ֻ֤���Լ�һ��ʵ��������)
#define killOtherSameContext				{0x17,0,0}
// ���ε��ã����ǰѸò�����Ϊ��һ����������������ָ��(this)��Ϊ��2������
#define	execFuncArgFirst(func,arg)			{0x18,arg,func}
// ʲô������������ħ������Э�̾��Դ˿�ʼ
#define spellStart							{0x19,0,0}

// �����Ľṹ�嶨��
struct context{
	struct coroutine* 	start;			// ��ʼЭ��
	struct coroutine* 	cursor;			// ��ǰִ�е�Э��
	PTRFUN		destructor;		// ��������������
	PTRFUN		loop;			// ѭ��ִ�еĺ���
	char*		name;			// �����ַ���
	struct context*	parent;			// ���߳�
	struct context*	firstChild;		// ��һ�����߳�
	struct context*	previous;		// ǰһ���߳�
	struct context*	next;			// ��һ���߳�
	u16			sleepTimer;			// ˯��(?)������
	u8			mark;			// ����Э�̴��ݵ��û�����
	u8			bitField;			// ��ʶλ��
	u8			blockCounter;		// ����������
/*	u8			dummy1;
	u16			dummy2;
	u8			userSpace[64];		// �û������Զ���Ŀռ�
	*/
	u8			userSpace[67];		// �û������Զ���Ŀռ�
};

// Э�̴���(����)����

// ָ���
#define	coroutineHandler	(PTRFUN)0x8BBFD28

// ���뺯��
#define handleCoroutine		sub(8004A60)

// ����Ĵ�����
#define handle00			sub(80047B8)
#define handle01			sub(80047C4)
#define handle02			sub(80047D4)
#define handle03			sub(800484C)
#define handle04			sub(800485C)
#define handle05			sub(8004878)
#define handle06			sub(8004894)
#define handle07			sub(80048B0)
#define handle08			sub(80048D0)
#define handle09			sub(80048F8)
#define handle0A			sub(8004914)
#define handle0B			sub(8004930)
#define handle0C			sub(800494C)
#define handle0D			sub(800493C)
#define handle0E			sub(800497C)
#define handle0F			sub(80049A0)
#define handle10			sub(80049C0)
#define handle11			sub(80049C4)
#define handle12			sub(8004A48)
#define handle13			sub(80049B4)
#define handle14			sub(8004820)
#define handle15			sub(8004A3C)
#define handle16			sub(80047E8)
#define handle17			sub(8004A04)
#define handle18			sub(8004800)
#define handle19			sub(8004930)


// �����Ĵ�����(�̲߳���)

// ��ʼ��
#define	intializeCoroutineEngine	sub(80042FC)
// void Reset6CEngine();

// �½�һ��������
#define	createContext				sub(8004370)
// struct context *createContext(struct coroutine *coroutine, int parent);
// ��һ��������ָ����Э�̵�ָ�룬�ڶ����������丸�߳�(��������)��ȫ����������ֱ��ָ��������(0-6),���������丸�ڵ��ָ��

// �½�һ��������������
#define createContextAndBlock		sub(80043D4)
// struct context *createContextAndBlock(struct coroutine *coroutine, int parent);
// ��һ��������ָ����Э�̵�ָ�룬�ڶ����������丸�߳�(��������)��ȫ����������ֱ��ָ��������(0-6),���������丸�ڵ��ָ��

// ɾ��ָ����������(ɱ������߳�)
#define	deleteContext				sub(8004404)
// void deleteContext(struct context *context);

// ������ɾ��ָ����������
#define	isolateAndDeleteContext		sub(8004460)
// void isolateAndDeleteContext(struct context *context);
#define	isolateAndDeleteContextWrapper		sub(8012B8C)
// void isolateAndDeleteContextWrapper(struct context *context);

// �ڷ��������ע��һ��������(Ϊ���̷߳���ռ�),����ָ���·���ռ��ָ��
#define	registerContext				sub(8004478)
// struct context *registerContext();

// �ڷ�����з�ע�����һ��������(�ջظ��̵߳Ŀռ�)
#define	unregisterContext			sub(8004488)
// void unregisterContext(struct context *context);

// Ϊ�׽ڵ��Ǹ��ڵ�������������׽ڵ�
#define setParentContextByIndex			sub(8004498)
// void setParentContextByIndex(struct context *context, int parentIndex);

// ��ָ������������Ϊĳ�������ĵ��׽ڵ�
#define setParentContextByPointer		sub(80044B8)
// void setParentContextByPointer(struct context *context, struct context *parentContext);

// ����ָ����������(ɾ�����������������ĵ���ϵ)
#define	isolateContext					sub(80044CC)
// int isolateContext(struct context *context)

// ����context���������Ϊctx;coroutine���������Ϊcort

// ִ�зǿ��߳�
// void execContextNotNull
#define	execContextNotNull				sub(800456C)

// �ݹ�ִ���߳�
// void execContext(struct context *ctx);
#define	execContext						sub(8004510)

// ֹͣѭ��ִ�к���
// void breakLoop(struct context *ctx);
#define	breakLoop						sub(800457C)

// ����ָ��Э�̵�������
// struct context *findContext(struct coroutine *cort);
#define	findContext						sub(8004584)

// ����ָ��Э�̵��������е�ʵ��(�������)
// struct context *findRunningContext(struct coroutine *cort);
#define	findRunningContext				sub(80045A4)

// �����趨�ı������������
// struct context *findContextByMark(int mark);
#define	findContextByMark			sub(80045D0)

// ת��ָ����ǩ��ִ��
// void letContextGotoLabel(struct context *ctx,int label);
#define	letContextGotoLabel			sub(80045FC)

// תȥִ��ָ��Э��
// void gotoCoroutine(struct context *ctx,struct coroutine *cort);
#define	gotoCoroutine					sub(8004634)

// ���ñ��
// void setMarkForContext(struct context *ctx,u8 mark);
#define setMarkForContext					sub(800463C)

// ������������
// void setDestructorForContext(struct context *ctx, PTRFUN destructor);
#define	setDestructorForContext					sub(8004644)

// �����е�������ִ��ָ������
// void execFuncForEachContext(PTRFUN func);
#define	execFuncForEachContext			sub(8004648)

// ��ָ��Э�̵�����������ִ��ָ������
// void execFuncForEachContextOfCoroutine(struct coroutine *cort,PTRFUN func);
#define	execFuncForEachContextOfCoroutine	sub(8004670)

// �Դ���ָ����ǵ�����������ִ��ָ������
// void execFuncForEachContextMarked(int mark,PTRFUN func);
#define	execFuncForEachContextMarked		sub(8004698)

// �������д��иñ�ǵ�������
// void blockEachContextMarked(int mark);
#define	blockEachContextMarked				sub(80046C4)

// �������д��иñ�ǵ�������
// void unblockEachContextMarked(int mark);
#define	unblockEachContextMarked			sub(80046E8)

// ɾ�����д��иñ�ǵ�������
// void deleteEachContextMarked(int mark);
#define	deleteEachContextMarked				sub(8004710)

// ������ɾ��ָ����������
// void callIsolateAndDeleteContext(struct context *ctx);
#define	callIsolateAndDeleteContext			sub(800473C)

// ɾ��ָ��Э�̵�����������(ɱ����Э��)
// void killACoroutine(stuct coroutine *cort);
#define	killACoroutine						sub(8004748)

// ʹĳ��������ֹͣѭ��ִ�к���
// void callBreakLoopForContext(struct context *ctx);
#define	callBreakLoopForContext				sub(8004758)

// ʹĳ��Э�̶�Ӧ������������ֹͣѭ��ִ�к���
// void callBreakLoopForCoroutine(struct context *ctx);
#define	callBreakLoopForCoroutine			sub(8004764)

// �ݹ�ض�ָ�������ĵ����к�������ĺ͵�һ����������ִ��ָ������
// void execFuncForAllFollowingContext(struct context *ctx, PTRFUN func);
#define	execFuncForAllFollowingContext		sub(8004774)

// һЩЭ�̺Ͷ�Ӧ����

// ħ��ʩ��Э��
#define efxSpellCast				((struct coroutine*)0x8C0A2B0)

// ����ħ���ͷ�
// void loadSpellCast();
#define	loadSpellCast				sub(8050348)

// ��ɫ�彥�䶯��Э��
#define	efxGradientPal				((struct coroutine*)0x8DAE4C4)

// ���õ�ɫ�彥�䶯��
// �ڵ�ɫ��1��2֮�佥��
// void loadGradientPalette(void *palette1, void *palette2, int a3, int paletteSlot, int a5, struct context *parent);
#define	loadGradientPalette			sub(80AB7F4)

// ��ֹ��ɫ�嶯��
// void stopGradientPal();
#define	stopGradientPal				sub(80AB82C)

// alpha��Ⱦ
#define	efxALPHA					((struct coroutine*)0x8C108C0)

// ����alpha
// void loadALPHA(int a1, __int16 a2, __int16 a3, int a4, int a5, int a6);
#define	loadALPHA					sub(80566F0)

// ��Ч����Э��
#define efxSoundSE					((struct coroutine*)0x8C4A2B4)

// ��ĩ֮��(A��)ħ���������
#define	loadFimbulvetrOBJ			sub(805947C)
// #define	efxFimbulvetrOBJ			((struct coroutine*)0x8C11028)
#define	loadFimbulvetrOBJ2			sub(8059510)
#define	loadFimbulvetrOBJ2Fall		sub(8059588)
#define	loadFimbulvetrBG			sub(8059394)
#define	loadFimbulvetrBGTR			sub(80592AC)

// ��ħ���������
#define	loadFireBG					sub(8058CB8)
#define	loadFireOBJ					sub(8058D70)
#define	loadElfireBG				sub(8058F2C)
#define	loadElfireBGCOL				sub(8058FF8)
#define	loadElfireOBJ				sub(8059084)
#define	loadFireHITBG				sub(8058E44)
