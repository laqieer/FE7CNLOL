// 协程和上下文(6C)
// by laqieer
// 2017/6/1

#pragma once

#include "AgbTypes.h"
#include "callFunc.h"

// 协程中的原子定义
struct	coroutine{
	u16		codeIndex;	// 指令代码(在协程处理函数指针表中的索引)
	u16		sarg;		// 函数参数
	void*	larg;	// 指向字符串/协程/上下文/函数等的指针
};

// 协程(函数序列)(翻译6C)指令

// 结束协程
#define	endofCoroutine						{0,0,0}
// 命名，参数是指向名字字符串的地址
#define	setNameForContext(name)				{1,0,name}
// 对当前上下文执行指定函数
#define	execFunc(func)						{2,0,func}
// 设置循环函数后挂起
#define	setLoopFuncAndYield(func)			{3,0,func}
// 设置当前上下文的析构函数
#define	setDestructor(func)					{4,0,func}
// 根据指定协程为当前上下文创建子上下文
#define addChildContext(coroutine)			{5,0,coroutine}
// 根据指定协程为当前上下文创建子上下文并挂起
#define addChildContextAndYield(coroutine)	{6,0,coroutine}
// 根据指定协程创建全局上下文
#define addGlobalContext(coroutine)			{7,0,coroutine}
// 等待指定的协程对应的上下文存在再执行，在此之前一直挂起(即等待指定的协程先执行后再继续执行)
#define waitforCoroutine(coroutine)			{8,0,coroutine}
// 删除指定协程的所有上下文(即杀死指定的协程)
#define	killCoroutine(coroutine)			{9,0,coroutine}
// 唤醒指定协程(即清除给协程所对应的所有上下文的睡眠循环函数)
#define awakeCoroutine(coroutine)			{0xA,0,coroutine}
// 设置标签
#define setLabel(label)						{0xB,label,0}
// 移动到指定标签处执行
#define	gotoLabel(label)					{0xC,label,0}
// 跳至指定协程处执行
#define jumptoCoroutine(coroutine)			{0xD,0,coroutine}
// 阻塞(睡眠)给定的时间(其实是在这段时间内反复执行上下文中的特定函数，所以该叫法并不准确)
#define sleep(time)							{0xE,time,0}
// 传递一个标记给当前上下文
#define setMark(mark)					{0xF,(mark)&0xFF,0}
// 挂起
#define yield								{0x10,0,0}
// 如果自己不是该协程唯一的上下文，则删除自己(一个上下文对应一个活动的线程，相当于杀死自己这个线程)
#define killSelfIfDuplicate					{0x11,0,0}
// 设置上下文中的一个标识位
#define setBitFlag							{0x12,0,0}
// 什么都不做1
#define doNothing1							{0x13,0,0}
// 在当前上下文带参数调用指定函数，该函数返回值为1则挂起
#define execFuncWithArgYieldIfReturn1(func,arg)	{0x14,arg,func}
// 什么都不做2
#define doNothing2							{0x15,0,0}
// 带参调用，返回0则挂起
#define execFuncWithArgYieldIfReturn0(func,arg)	{0x16,arg,func}
// 删除当前协程的其他上下文(保证只有自己一个实例在运行)
#define killOtherSameContext				{0x17,0,0}
// 带参调用，但是把该参数作为第一个参数，而上下文指针(this)作为第2个参数
#define	execFuncArgFirst(func,arg)			{0x18,arg,func}
// 什么都不做，但是魔法动画协程均以此开始
#define spellStart							{0x19,0,0}

// 上下文结构体定义
struct context{
	struct coroutine* 	start;			// 起始协程
	struct coroutine* 	cursor;			// 当前执行的协程
	PTRFUN		destructor;		// 上下文析构函数
	PTRFUN		loop;			// 循环执行的函数
	char*		name;			// 名字字符串
	struct context*	parent;			// 父线程
	struct context*	firstChild;		// 第一个子线程
	struct context*	previous;		// 前一个线程
	struct context*	next;			// 后一个线程
	u16			sleepTimer;			// 睡眠(?)计数器
	u8			mark;			// 来自协程传递的用户参数
	u8			bitField;			// 标识位域
	u8			blockCounter;		// 阻塞计数器
/*	u8			dummy1;
	u16			dummy2;
	u8			userSpace[64];		// 用户可以自定义的空间
	*/
	u8			userSpace[67];		// 用户可以自定义的空间
};

// 协程处理(翻译)函数

// 指针表
#define	coroutineHandler	(PTRFUN)0x8BBFD28

// 翻译函数
#define handleCoroutine		sub(8004A60)

// 具体的处理函数
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


// 上下文处理函数(线程操作)

// 初始化
#define	intializeCoroutineEngine	sub(80042FC)
// void Reset6CEngine();

// 新建一个上下文
#define	createContext				sub(8004370)
// struct context *createContext(struct coroutine *coroutine, int parent);
// 第一个参数是指定的协程的指针，第二个参数是其父线程(父上下文)，全局上下文则直接指定其索引(0-6),否则则是其父节点的指针

// 新建一个阻塞的上下文
#define createContextAndBlock		sub(80043D4)
// struct context *createContextAndBlock(struct coroutine *coroutine, int parent);
// 第一个参数是指定的协程的指针，第二个参数是其父线程(父上下文)，全局上下文则直接指定其索引(0-6),否则则是其父节点的指针

// 删除指定的上下文(杀死这个线程)
#define	deleteContext				sub(8004404)
// void deleteContext(struct context *context);

// 孤立并删除指定的上下文
#define	isolateAndDeleteContext		sub(8004460)
// void isolateAndDeleteContext(struct context *context);
#define	isolateAndDeleteContextWrapper		sub(8012B8C)
// void isolateAndDeleteContextWrapper(struct context *context);

// 在分配表中新注册一个上下文(为新线程分配空间),返回指向新分配空间的指针
#define	registerContext				sub(8004478)
// struct context *registerContext();

// 在分配表中反注册最后一个上下文(收回该线程的空间)
#define	unregisterContext			sub(8004488)
// void unregisterContext(struct context *context);

// 为亲节点是根节点的上下文设置亲节点
#define setParentContextByIndex			sub(8004498)
// void setParentContextByIndex(struct context *context, int parentIndex);

// 将指定上下文设置为某个上下文的亲节点
#define setParentContextByPointer		sub(80044B8)
// void setParentContextByPointer(struct context *context, struct context *parentContext);

// 孤立指定的上下文(删除和树中其他上下文的联系)
#define	isolateContext					sub(80044CC)
// int isolateContext(struct context *context)

// 以下context变量，简记为ctx;coroutine变量，简记为cort

// 执行非空线程
// void execContextNotNull
#define	execContextNotNull				sub(800456C)

// 递归执行线程
// void execContext(struct context *ctx);
#define	execContext						sub(8004510)

// 停止循环执行函数
// void breakLoop(struct context *ctx);
#define	breakLoop						sub(800457C)

// 搜索指定协程的上下文
// struct context *findContext(struct coroutine *cort);
#define	findContext						sub(8004584)

// 搜索指定协程的正在运行的实例(活动上下文)
// struct context *findRunningContext(struct coroutine *cort);
#define	findRunningContext				sub(80045A4)

// 根据设定的标记搜索上下文
// struct context *findContextByMark(int mark);
#define	findContextByMark			sub(80045D0)

// 转到指定标签处执行
// void letContextGotoLabel(struct context *ctx,int label);
#define	letContextGotoLabel			sub(80045FC)

// 转去执行指定协程
// void gotoCoroutine(struct context *ctx,struct coroutine *cort);
#define	gotoCoroutine					sub(8004634)

// 设置标记
// void setMarkForContext(struct context *ctx,u8 mark);
#define setMarkForContext					sub(800463C)

// 设置析构函数
// void setDestructorForContext(struct context *ctx, PTRFUN destructor);
#define	setDestructorForContext					sub(8004644)

// 对所有的上下文执行指定函数
// void execFuncForEachContext(PTRFUN func);
#define	execFuncForEachContext			sub(8004648)

// 对指定协程的所有上下文执行指定函数
// void execFuncForEachContextOfCoroutine(struct coroutine *cort,PTRFUN func);
#define	execFuncForEachContextOfCoroutine	sub(8004670)

// 对带有指定标记的所有上下文执行指定函数
// void execFuncForEachContextMarked(int mark,PTRFUN func);
#define	execFuncForEachContextMarked		sub(8004698)

// 阻塞所有带有该标记的上下文
// void blockEachContextMarked(int mark);
#define	blockEachContextMarked				sub(80046C4)

// 唤醒所有带有该标记的上下文
// void unblockEachContextMarked(int mark);
#define	unblockEachContextMarked			sub(80046E8)

// 删除所有带有该标记的上下文
// void deleteEachContextMarked(int mark);
#define	deleteEachContextMarked				sub(8004710)

// 孤立并删除指定的上下文
// void callIsolateAndDeleteContext(struct context *ctx);
#define	callIsolateAndDeleteContext			sub(800473C)

// 删除指定协程的所有上下文(杀死该协程)
// void killACoroutine(stuct coroutine *cort);
#define	killACoroutine						sub(8004748)

// 使某个上下文停止循环执行函数
// void callBreakLoopForContext(struct context *ctx);
#define	callBreakLoopForContext				sub(8004758)

// 使某个协程对应的所有上下文停止循环执行函数
// void callBreakLoopForCoroutine(struct context *ctx);
#define	callBreakLoopForCoroutine			sub(8004764)

// 递归地对指定上下文的所有后继上下文和第一个子上下文执行指定函数
// void execFuncForAllFollowingContext(struct context *ctx, PTRFUN func);
#define	execFuncForAllFollowingContext		sub(8004774)

// 一些协程和对应函数

// 魔法施放协程
#define efxSpellCast				((struct coroutine*)0x8C0A2B0)

// 调用魔法释放
// void loadSpellCast();
#define	loadSpellCast				sub(8050348)

// 调色板渐变动画协程
#define	efxGradientPal				((struct coroutine*)0x8DAE4C4)

// 调用调色板渐变动画
// 在调色板1和2之间渐变
// void loadGradientPalette(void *palette1, void *palette2, int a3, int paletteSlot, int a5, struct context *parent);
#define	loadGradientPalette			sub(80AB7F4)

// 终止调色板动画
// void stopGradientPal();
#define	stopGradientPal				sub(80AB82C)

// alpha渲染
#define	efxALPHA					((struct coroutine*)0x8C108C0)

// 调用alpha
// void loadALPHA(int a1, __int16 a2, __int16 a3, int a4, int a5, int a6);
#define	loadALPHA					sub(80566F0)

// 音效播放协程
#define efxSoundSE					((struct coroutine*)0x8C4A2B4)

// 终末之冬(A理)魔法动画相关
#define	loadFimbulvetrOBJ			sub(805947C)
// #define	efxFimbulvetrOBJ			((struct coroutine*)0x8C11028)
#define	loadFimbulvetrOBJ2			sub(8059510)
#define	loadFimbulvetrOBJ2Fall		sub(8059588)
#define	loadFimbulvetrBG			sub(8059394)
#define	loadFimbulvetrBGTR			sub(80592AC)

// 火魔法动画相关
#define	loadFireBG					sub(8058CB8)
#define	loadFireOBJ					sub(8058D70)
#define	loadElfireBG				sub(8058F2C)
#define	loadElfireBGCOL				sub(8058FF8)
#define	loadElfireOBJ				sub(8059084)
#define	loadFireHITBG				sub(8058E44)
