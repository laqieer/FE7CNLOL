// by laqieer
// 支持战斗动画分成多个表
// 2017/6/13
// 支持无压缩的data2/3/4,无需解压至内存
// 2017/6/20

#pragma once

#include "AgbTypes.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"
#include "FE7JCoroutine.h"
#include "IDAPro.h"
#include "FE7JItemList.h"
#include "AgbMemoryMap.h"

#pragma long_calls
// 读取战斗动画相关数据到内存
void battleAnimationInit();
#pragma long_calls_off

void callBattleAnimationInit();

// 日版烈火战斗动画库
#define	FE7BattleAnimationBank	((BattleAnimation *)0x8E00008)

// 战斗动画结构体定义
typedef	struct {
	char identifier[12];	// 标识符(字符串)
	int	*sectionOffset; // 第一个指针(指向动画各部分划分偏移表)
	void *event;			// 第二个指针(指向动画脚本(由指令或者称为事件组成))
	void *oamR2L;			// 第三个指针指向OAM数据(在右侧朝左侧)
	void *oamL2R;			// 第四个指针指向OAM数据(在左侧朝右侧)
	void *palGroup;			// 第五个指针指向调色板组
} BattleAnimation, *pBattleAnimation;

// 战斗动画bank信息
typedef struct {
	void *array;
	bool is_pointer;
} BattleAnimationBankInfo;

extern const pBattleAnimation BattleAnimationPointerBank[];

// 动画运行结构体定义
typedef struct ais {
	u16 state;	// 当前运行状态
				// AND 0x02: True when cape flowing? Acts as though AND 0x01 is false?
				// AND 0x01: True to display sprites/continue animation
	s16 XOffset;	// X offset based on screen scroll
	s16 YOffset;	// unknown
	u16 delayCountdown;	// 延迟倒计时
	u16 OBJAttr2Base;	// 精灵OAM属性2基值
						// Halfword of basis for part 2 of 0-2 of OAM data (which selects which tile is the top left corner)
						// 0x9B00 for right unit (name = 0x300; tile 768 where the sheet is loaded to)
	u16 unk_A;
	u16 unk_C;
	u16 unk_E;
	u16 unk_10;
	u8 modeX;	// 控制当前所处的模式
	u8 frameID;	// 帧ID
	/*
	u8 unk_14;
	u8 C85ID;	// ID of 0x85 command being executed
	u16 unk_16;
	u32 unk_18;
	u32 unk_1C;
	*/
	// C85指令ID存储的偏移(通常是0)
	u8 C85IDBufferIndex;
	// C85指令的ID(最低一个字节)可以被存储到接下来一片连续的缓冲区中(具体缓存在哪由C85IDBufferIndex决定)(通常只是存储在第一个位置)
	u8 C85IDBuffer[11];
	u32 *nextCmd;	// Frame pointer
					// 当前执行到的位置(指向下一条指令)
	u32	*lastCmd;		// Pointer to last 0x86 command?
	void *sheet;	// ROM中的sheet数据(可压缩)
	void *sheetBuffer;	// RAM中的sheet数据(无压缩)
	void *OAMInfoBuffer;	// OAM start pointer
	// 不能在定义typedef类型之前使用它
//	AnimationInterpreter *parent;	// Parent AIS (drawn before this one)
//	AnimationInterpreter *child;	// Child AIS (drawn after this one)
	struct ais *parent;	// Parent AIS (drawn before this one)
	struct ais *child;	// Child AIS (drawn after this one)
	void *currentOAMInfo;	// OAM pointer
	u32 unk_40;
	u32 unk_44;
} AnimationInterpreter;

// 人物个别战斗动画调色板列表
#define	characterBattlePalTable	((CharacterBattlePal *)0x8FD8008)

// 人物个别战斗动画调色板信息结构体定义
typedef struct {
	char identifier[12];	// 标识符(字符串)
	void *pal;				// 指向调色板
} CharacterBattlePal;

// 战斗动画相关全局变量

// AIS指针表(4个元素的数组)
#define	AISTable							((AnimationInterpreter **)0x2000000)
// 分别是:
// 左边战斗动画AIS
// #define	BattleAISLeftSide					(AISTable[0])
// 暂不清楚这个的用途
// spell data struct for left unit?
// #define BattleAIS2LeftSide					(AISTable[1])
// 右边战斗动画AIS
// #define	BattleAISRightSide					(AISTable[2])
// #define	BattleAIS2RightSide					(AISTable[3])
// AIS池(最多容纳50个AIS)起始地址
#define	AISBank		((AnimationInterpreter *)0x2028E6C)
// AIS树根节点
#define	RootAIS		((AnimationInterpreter **)0x2029C7C)

// 战斗动画位于左侧
#define	IfBattleAnimationIsAtTheLeftSide	(*(u16 *)0x203DFE8)
// 战斗动画位于右侧
#define	IfBattleAnimationIsAtTheRightSide	(*(u16 *)0x203DFEA)
// 左侧战斗动画ID
#define	BattleAnimationIDLeftSide			(*(u16 *)0x203E066)
// 右侧战斗动画ID
#define	BattleAnimationIDRightSide			(*(u16 *)0x203E068)
#define	BattleAnimationIDArray				((u16 *)0x203E066)
// 左侧战斗动画调色板组中序号
#define	BattleAnimationPalSlotLeftSide		(*(u16 *)0x203DFF8)
// 右侧战斗动画调色板组中序号
#define	BattleAnimationPalSlotRightSide		(*(u16 *)0x203DFFA)
// 左侧人物个别战斗调色板ID
#define	CharaterBattleAnimationPaletteIDLeftSide	(*(u16 *)0x203DFF4)
// 右侧人物个别战斗调色板ID
#define	CharaterBattleAnimationPaletteIDRightSide	(*(u16 *)0x203DFF6)
// 左侧战斗动画事件脚本缓存
#define	BattleAnimationEventBufferLeftSide			((u32 *)0x200F1C8)
// 右侧战斗动画事件脚本缓存
#define	BattleAnimationEventBufferRightSide			((u32 *)0x2011BC8)
// 左侧动画的各模式分割信息地址
#define	BattleAnimationSectionInfoLeftSide			(*(int **)0x200005C)
// 右侧动画的各模式分割信息地址
#define	BattleAnimationSectionInfoRightSide			(*(int **)0x2000060)
// 左侧动画调色板组缓存
#define	BattleAnimationPaletteGroupBufferLeftSide	((u16 *)0x2004088)
// 右侧动画调色板组缓存
#define	BattleAnimationPaletteGroupBufferRightSide	((u16 *)0x2004128)	
// 左侧动画调色板地址
#define	BattleAnimationPaletteLeftSide				(*(u16 **)0x2000054)
// 右侧动画调色板地址
#define	BattleAnimationPaletteRightSide				(*(u16 **)0x2000058)
// 左侧动画OAM信息缓存
#define	BattleAnimationOAML2RBuffer					((void *)0x20041C8)
// 右侧动画OAM信息缓存
#define	BattleAnimationOAMR2LBuffer					((void *)0x20099C8)
// 右侧动画sheet缓存
#define	BattleAnimationSheetBufferRightSide			((void *)0x2002088)
// 左侧动画sheet缓存
#define	BattleAnimationSheetBufferLeftSide			((void *)0x2000088)
// 左侧武器的魔法动画ID
#define	SpellAnimationIDLeftSide					(*(u16 *)0x203DFFC)
// 右侧武器的魔法动画ID
#define	SpellAnimationIDRightSide					(*(u16 *)0x203DFFE)
// 说明魔法动画ID也是作为双字节处理的,因此在此基础上可以很容易扩展上限到0xFFFF,不过考虑到魔法动画本身超过255个的情形很少，所以暂不扩展

// 相关函数

// 返回用哪个动画ID的调色板组
// 作用:对某些特殊ID的动画更换调色板组
// signed int getAnimationIDForPaletteGroup(int animationID, int RightOrLeft);
#define	getAnimationIDForPaletteGroup	sub(80547C0)

// 定义战斗动画库枚举值表
enum {
	FE7BABank
};

// ekrUnitKakudai协程组
#define	ekrUnitKakudai		((struct coroutine *)0x8C0A560)
#define	UnitKakudai1	sub(8051F38)
#define	UnitKakudai2	sub(80520C4)
#define	UnitKakudai3	sub(805226C)

// 扩展后的UnitKakudai1
void UnitKakudai1Ex(struct context *ctx);

// 处理动画事件(扩展)
//#pragma long_calls
//void battleAnimationEventHandlerEx();
//#pragma long_calls_off

//void callBattleAnimationEventHandlerEx();

// 原来的战斗动画事件处理程序
// void battleAnimationEventHandler();
#define	battleAnimationEventHandler	sub(8053C3C)

// 对所有的AIS执行
// void ForAllAIS();
#define	ForAllAIS	sub(8006488)

// 处理所有的动画脚本
// void battleAnimationScriptProc();
// #define	battleAnimationScriptProc	sub(8006320)

// 处理单个动画脚本
// signed int BattleAnimationScriptHandler(AnimationInterpreter *AIS);
// #define	BattleAnimationScriptHandler	sub(8006518)

// 处理动画0x85指令事件
// void battleAnimationEventHandler();
// #define	battleAnimationEventHandler		sub(8053C3C)

// 处理动画0x86指令载入的OAM属性
// void battleAnimationOAMInfoHandler(void *battleAnimationOAMInfoBuffer, int a2, unsigned __int16 a3, int a4);
#define	battleAnimationOAMInfoHandler	sub(8067C30)
// void BattleAnimationOAMInfoHandler2(AnimationInterpreter *AIS);
#define	BattleAnimationOAMInfoHandler2	sub(80066E0)

/*
// 定义变量的别名
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

// 战斗双方AIS初始化
// xl和xr分别为左右双方偏离中央的距离
// 进接攻击: xl = xr = 6
// 远程攻击: xl = xr = 8
// void battleAnimationAISInit(int xl,int xr);
#define battleAnimationAISInit	sub_8054AC0

/*
#pragma long_calls
void sub_8054D7C(int a1, int a2);
#pragma long_calls_off

void call_sub_8054D7C(int a1, int a2);

#define	InitAIS	call_sub_8054D7C
// void InitAIS(AnimationInterpreter *AIS, int x);
*/

#pragma long_calls
void InitAIS(AnimationInterpreter *AIS, int x);
#pragma long_calls_off

void callInitAIS(AnimationInterpreter *AIS, int x);

// 初始化两侧的AIS
#define	initBothAIS	sub(8054A30)
// void initBothAIS();

#pragma long_calls
void sub_8054764(void *AIS);
#pragma long_calls_off

// 更新战斗动画sheet
void call_sub_8054764(void *AIS);

#define	updateBattleAnimationSheet	call_sub_8054764

#pragma long_calls
void DemoBattleAnimationInit(void *AIS);
#pragma long_calls_off

// 职业介绍的DEMO战斗动画初始化
// 因为只有一个动画，所以AIS就在0x02000000
void callDemoBattleAnimationInit(void *AIS);

// 判断动画是在左边还是右边
// bool isUnitAtRightOrLeft(int AIS);
#define isUnitAtRightOrLeft		sub(8054E60)

// 映射敌人的战斗动画
#define	MirrorBattleAnimationID		0x5E5E

// 外挂背景动画扩展
// 扩展C2E和C2F指令
// ifCritical是否必杀
void battleExtraAnimation(void *AIS, bool ifCritical);

// 贤者施法魔法阵动画
// void loadMagfcast(void *AIS, bool ifCritical)
#define	loadMagfcast	sub(8063400)

// 汇编实现附加动画扩展
extern const int callExtraAnimation;
extern const int callExtraAnimationCRT;
// extern int callExtraAnimation;
// extern int callExtraAnimationCRT;

// 冰块背景协程
#define	efxFimbulvetrBG		((struct coroutine*)0x8C10FB8)

// 汇编扩展C0D指令，使其支持无压缩data
extern const int C0DHandlerJPTCase0_1_2_3_9;

// 法师斗篷循环扩展
extern const int loc_80065EC_EX;

// 声音播放扩展
extern const int loc_806829C_EX;

// 古代火龙图片相关
#define	FireDragonImg	0x82E445C	// 火龙背景图块
#define FireDragonPalGroup	0x82E6C60	// 火龙图块调色板组(翼有变色的调色板动画)
#define	FireDragonTailTSA	0x82E6D40	// 火龙尾部TSA
#define	FireDragonBodyTSA	0x82E6E8C	// 火龙身体部分的TSA(低头)
#define	FireDragonBodyUPTSA	0x82E7170	// 火龙身体部分的TSA(抬头)
#define	FireDragonBodyUPNoWingTSA	0x82E7418	// 火龙身体部分的TSA(抬头)(无翼)
#define	FireDragonBattleAnimationSheet1	0x82E76A4	// 火龙战斗动画sheet1
#define FireDragonBattleAnimationSheet2	0x82E8584	// 火龙战斗动画sheet2
#define	DyingDragonHeadImg	0x82E9240	// 火龙死时龙头下落的图块
#define	FireDragonSpriteAnimationPalGroup	0x82E9CD8	// 火龙精灵动画调色板组
// 火龙色板动画相关
#define	loadFireDragonBGPaletteAnimation	sub(80657D4)
// struct context *loadFireDragonBGPaletteAnimation(void *AIS);
#define	efxFireDragonBGPaletteAnimation		((struct coroutine *)0x8C4879C)
#define	FireDragonBGPaletteAnimation		sub(8066118)
// void FireDragonBGPaletteAnimation(struct context *ctx)

// BG图片
typedef struct {
	void *img;
	void *pal;
	void *tsa;
} BGImage;

// 原作中的特殊动画效果(身体的一部分是背景的敌方和龙人变身动画)控制
typedef	struct {
	u16 type; // 指定具体是哪一种特殊效果(0=什么都没有;烈火里1=古火龙;圣魔里1=僵尸龙,2=魔王,3=梅尔变身)
	u16 state; // 1->3->7->F,似乎是用来标识进行到了哪个阶段,每一位代表一个阶段
	struct context *ctx; // 特效协程的上下文
	// u32 unk_8; // 原来是未使用的(,这里我们用来记录变身前的原始动画以便最后返回到这个动画，不需要,去掉)(这里用来存储解除变身的动画ID和变身后动画的模式控制字)
	// u16 inversAnimationID;	// 新增,解除变身动画ID
	u16 animationID;	// 改用原动画ID,为了最后返回
	u16 modeX;	// 动画模式控制字(BattleAnimationModeConfig的索引)
	AnimationInterpreter *AIS; // 当前的AIS
} SpecialAnimationEffectInfo;
#define	SpecialAnimationEffectInfoLeftSide	((SpecialAnimationEffectInfo *)0x2020040)
#define	SpecialAnimationEffectInfoRightSide	((SpecialAnimationEffectInfo *)0x2020050)
#define	initSpecialAnimationEffectInfo			sub(8065214)
// void initSpecialAnimationEffectInfo();
#define	getSpecialAnimationEffectInfo			sub(8065238)
// SpecialAnimationEffectInfo *getSpecialAnimationEffectInfo(AnimationInterpreter *AIS);
#define	getSpecialAnimationEffectInfoType		sub(8065288)
// int getSpecialAnimationEffectType(AnimationInterpreter *AIS);
#define	callSpecialAnimationEffectTypeGetter	sub(806527C)
// int callSpecialAnimationEffectTypeGetter(AnimationInterpreter *AIS);
#define	getSpecialAnimationEffectInfoState		sub(8065258)
// int getSpecialAnimationEffectInfoState(AnimationInterpreter *AIS);
#define	setSpecialAnimationEffectInfoState		sub(8065264)
// void setSpecialAnimationEffectInfoState(int AIS, __int16 state);
#define	setSpecialAnimationEffectInfoState4		sub(8065430)
// void setSpecialAnimationEffectInfoState4(AnimationInterpreter *AIS);
#define	callSpecialAnimationEffectTypeGetter	sub(806527C)
// int callSpecialAnimationEffectTypeGetter(AnimationInterpreter *AIS);
#define	setSpecialAnimationEffectInfoType		sub(8065294)
// void setSpecialAnimationEffectInfoType(AnimationInterpreter *AIS, __int16 type);
#define	ifSpecialAnimationEffectExist			sub(80652AC)
// bool ifSpecialAnimationEffectExist();

// 变换战斗动画(用于龙人变身,古代火龙等)
#define	transformateBattleAnimation				sub(8053AA8)
// void transformateBattleAnimation(AnimationInterpreter *AIS, __int16 animationID;

// 变身动画信息
typedef	struct {
	u16	transAnimationID;	// 变身动画ID
	u16 inversAnimationID;	// 反变换动画ID
} BattleAnimationTransInfo;

#pragma long_calls
void sub_804C7C4(struct context *ctx);
#pragma long_calls_off

// 梅尔变身前动画
extern const int BattleAnimation_Myrrh_data1;
extern const int BattleAnimation_Myrrh_data2;
extern const int BattleAnimation_Myrrh_data3;
extern const int BattleAnimation_Myrrh_data4;
// 梅尔变身动画
extern const int BattleAnimation_MyrrhTrans_data1;
extern const int BattleAnimation_MyrrhTrans_data2;
extern const int BattleAnimation_MyrrhTrans_data3;
extern const int BattleAnimation_MyrrhTrans_data4;
// 梅尔解除变身动画
extern const int BattleAnimation_MyrrhInvers_data1;
extern const int BattleAnimation_MyrrhInvers_data2;
extern const int BattleAnimation_MyrrhInvers_data3;
extern const int BattleAnimation_MyrrhInvers_data4;
// 梅尔龙动画
extern const int BattleAnimation_MyrrhDragon_data1;
extern const int BattleAnimation_MyrrhDragon_data2;
extern const int BattleAnimation_MyrrhDragon_data3;
extern const int BattleAnimation_MyrrhDragon_data4;
// 珐变身前动画
extern const int BattleAnimation_Fa_data1;
extern const int BattleAnimation_Fa_data2;
extern const int BattleAnimation_Fa_data3;
extern const int BattleAnimation_Fa_data4;
// 珐变身后动画(神龙)
extern const int BattleAnimation_FaDragon_data1;
extern const int BattleAnimation_FaDragon_data2;
extern const int BattleAnimation_FaDragon_data3;
extern const int BattleAnimation_FaDragon_data4;
// 珐变身成神龙的动画
extern const int BattleAnimation_FaTrans_data1;
extern const int BattleAnimation_FaTrans_data2;
extern const int BattleAnimation_FaTrans_data3;
extern const int BattleAnimation_FaTrans_data4;
// 珐解除变身的动画
extern const int BattleAnimation_FaInvers_data1;
extern const int BattleAnimation_FaInvers_data2;
extern const int BattleAnimation_FaInvers_data3;
extern const int BattleAnimation_FaInvers_data4;

