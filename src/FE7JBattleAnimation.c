// 改造战斗动画相关函数
// Important! 风险提示: 通过检查第1个字节是否是0x10来判断数据是否经过lz77压缩，这是存在失败风险的（潜在的bug）。
// 出于对已经做好的动画数据的兼容性考虑我没有修复这个bug。如果从0开始的话应该设计为添加压缩头并采用自适应解压函数解压数据的方式。
// by laqieer
// 2017/6/13

#include "FE7JBattleAnimation.h"

#include	"spellIceWorld.h"

#define __DEBUG

#include "agbDebug.h"

// 0x8A载入BG图片库
const BGImage C8ABGBank[] = {
	0
};

// 普莉希拉上层色板
const u16 PriscillaAnimationTest_PalA[] = {
	0x5355, 0x4106, 0x7733, 0x51C3, 0x7FFA, 0x2F01, 0x1140, 0x474D,
	0x0DE2, 0x5FDF, 0x3ADD, 0x1D50, 0x00B4, 0x14FC, 0x7FFF, 0x14A5
};

// 梅尔动画调色板
const u16 BattleAnimation_Myrrh_pal[] = {
0x5355,0x7BDE,0x5BFF,0x4B1F,0x1592,0x07FF,0x173B,0x1677,	// Player
0x6D9B,0x4CF2,0x344B,0x093D,0x0054,0x438C,0x2E87,0x14A5,
0x5355,0x7BDE,0x5BFF,0x4B1F,0x1592,0x07FF,0x173B,0x1677,	// Enemy
0x6D9B,0x4CF2,0x344B,0x093D,0x0054,0x438C,0x2E87,0x14A5,
0x5355,0x7BDE,0x5BFF,0x4B1F,0x1592,0x07FF,0x173B,0x1677,	// NPC
0x6D9B,0x4CF2,0x344B,0x093D,0x0054,0x438C,0x2E87,0x14A5,
0x5355,0x7BDE,0x5BFF,0x4B1F,0x1592,0x07FF,0x173B,0x1677,	// 4th(arena)
0x6D9B,0x4CF2,0x344B,0x093D,0x0054,0x438C,0x2E87,0x14A5,
};

// 梅尔变身和解除变身动画调色板
const u16 BattleAnimation_MyrrhTrans_pal[] = {
0x5355,0x7BDE,0x5BFF,0x4B1F,0x1592,0x07FF,0x173B,0x1677,	// Player
0x6D9B,0x4CF2,0x344B,0x093D,0x0054,0x438C,0x2E87,0x14A5,
0x5355,0x0FBD,0x1F3C,0x0E78,0x6B37,0x4E2C,0x7FFF,0x53DB,	// Enemy
0x2B4A,0x2267,0x17DE,0x235D,0x16B9,0x09F4,0x054C,0x14A5,
0x5355,0x7BDE,0x5BFF,0x4B1F,0x1592,0x07FF,0x173B,0x1677,	// NPC
0x6D9B,0x4CF2,0x344B,0x093D,0x0054,0x438C,0x2E87,0x14A5,
0x5355,0x0FBD,0x1F3C,0x0E78,0x6B37,0x4E2C,0x7FFF,0x53DB,	// 4th(arena)
0x2B4A,0x2267,0x17DE,0x235D,0x16B9,0x09F4,0x054C,0x14A5,
};

// 梅尔龙动画调色板
const u16 BattleAnimation_MyrrhDragon_pal[] = {
0x5355,0x0FBD,0x1F3C,0x0E78,0x6B37,0x4E2C,0x7FFF,0x53DB,	// Player
0x2B4A,0x2267,0x17DE,0x235D,0x16B9,0x09F4,0x054C,0x14A5,
0x5355,0x0FBD,0x1F3C,0x0E78,0x6B37,0x4E2C,0x7FFF,0x53DB,	// Enemy
0x2B4A,0x2267,0x17DE,0x235D,0x16B9,0x09F4,0x054C,0x14A5,
0x5355,0x0FBD,0x1F3C,0x0E78,0x6B37,0x4E2C,0x7FFF,0x53DB,	// NPC
0x2B4A,0x2267,0x17DE,0x235D,0x16B9,0x09F4,0x054C,0x14A5,
0x5355,0x0FBD,0x1F3C,0x0E78,0x6B37,0x4E2C,0x7FFF,0x53DB,	// 4th(arena)
0x2B4A,0x2267,0x17DE,0x235D,0x16B9,0x09F4,0x054C,0x14A5,
};

// 珐变身前动画调色板
const u16 BattleAnimation_Fa_pal[] = {
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x7E7F,0x5538,0x4132,	// Player
0x07FF,0x1A9E,0x0AFA,0x7FF5,0x7FAD,0x7E0A,0x60E7,0x14A5,
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x7F55,0x7E8E,0x696B,	// Enemy
0x07FF,0x1A9E,0x0AFA,0x3ABF,0x15DD,0x0C9B,0x0051,0x14A5,
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x7F3F,0x7A9B,0x454E,	// NPC
0x07FF,0x1A9E,0x0AFA,0x4FD9,0x3352,0x26E8,0x2628,0x14A5,
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x4ADE,0x201F,0x0052,	// 4th(arena)
0x07FF,0x1A9E,0x0AFA,0x737B,0x62F7,0x5A72,0x458C,0x14A5,
};

// 珐变身后动画(神龙)调色板
const u16 BattleAnimation_FaDragon_pal[] = {
0x5355,0x7FFF,0x5FDF,0x3F5C,0x06D9,0x0615,0x1D6E,0x5355,	// Player
0x5355,0x7FF5,0x7FAD,0x732A,0x5E66,0x61C5,0x40E3,0x14A5,
0x5355,0x7FFF,0x5FDF,0x3F5C,0x06D9,0x0615,0x1D6E,0x5355,	// Enemy
0x5355,0x2A3F,0x215E,0x291C,0x5138,0x0053,0x000D,0x14A5,
0x5355,0x7FFF,0x5FDF,0x3F5C,0x06D9,0x0615,0x1D6E,0x5355,	// NPC
0x5355,0x4FF6,0x178D,0x0B4A,0x0EA7,0x0202,0x1582,0x14A5,
0x5355,0x7FFF,0x5FDF,0x3F5C,0x06D9,0x0615,0x1D6E,0x5355,	// 4th(arena)
0x5355,0x735A,0x62F7,0x5EB5,0x4E10,0x458C,0x3D4A,0x14A5,
};

// 珐变身成神龙的动画调色板
const u16 BattleAnimation_FaTrans_pal[] = {
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x7E7F,0x5538,0x4132,	// Player
0x07FF,0x1A9E,0x0AFA,0x7FF5,0x7FAD,0x7E0A,0x60E7,0x14A5,
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x7F55,0x7E8E,0x696B,	// Enemy
0x07FF,0x1A9E,0x0AFA,0x3ABF,0x15DD,0x0C9B,0x0051,0x14A5,
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x7F3F,0x7A9B,0x454E,	// NPC
0x07FF,0x1A9E,0x0AFA,0x4FD9,0x3352,0x26E8,0x2628,0x14A5,
0x5355,0x7FFF,0x6BFF,0x439D,0x192E,0x4ADE,0x201F,0x0052,	// 4th(arena)
0x07FF,0x1A9E,0x0AFA,0x737B,0x62F7,0x5A72,0x458C,0x14A5,
};

// 人物别第二调色板表
const u16 * const characterBattleSecondPalTable[] = {
	[0x79-1] = PriscillaAnimationTest_PalA
};

// 动画第二调色板组表
const u16 * const battleAnimationSecondPalTable[] = {
	[0x101] = BattleAnimation_MyrrhDragon_pal,
	[0x102] = BattleAnimation_MyrrhDragon_pal,
	[0x106] = BattleAnimation_FaDragon_pal,
	[0x107] = BattleAnimation_FaDragon_pal
};

// 扩展后的战斗动画协程
__attribute__((section(".ekrUnitKakudaiEx")))
const struct coroutine ekrUnitKakudaiEx[] =
{
	spellStart,
	setLoopFuncAndYield(UnitKakudai1Ex),
//	setLoopFuncAndYield(UnitKakudai1),
	setLoopFuncAndYield(UnitKakudai2),
	setLoopFuncAndYield(UnitKakudai3),
	endofCoroutine
};

// C0D指令处理函数中的跳转表扩展
// 还有卡机bug(已修复 2017/8/13)
__attribute__((section(".C0DHandlerJPT")))
const int C0DHandlerJPT[] = {
//	0x080540B4,
	&C0DHandlerJPTCase0_1_2_3_9,
//	0x080540B4,
	&C0DHandlerJPTCase0_1_2_3_9,
//	0x080540B4,
	&C0DHandlerJPTCase0_1_2_3_9,
//	0x080540B4,
	&C0DHandlerJPTCase0_1_2_3_9,
	0x080541B8,
	0x080541B8,
	0x080541C6,
	0x080541C6,
	0x080541C6,
//	0x080540B4
	&C0DHandlerJPTCase0_1_2_3_9
};

// 法师施法斗篷飘动效果扩展(整体循环)
// 有卡机bug(已修复 2017/8/13)
__attribute__((section(".capeFlowingAnimationEx")))
const int capeFlowingAnimationEx = &loc_80065EC_EX;

// 战斗动画中声音播放扩展
__attribute__((section(".battleAnimationSoundEx")))
const int battleAnimationSoundEx = &loc_806829C_EX;

// 附加动画扩展C2E(普通)
__attribute__((section(".C2E_EX")))
const int C2E_EX = &callExtraAnimation;
// int C2E_EX = callExtraAnimation;

// 附加动画扩展C2F(必杀)
__attribute__((section(".C2F_EX")))
const int C2F_EX = &callExtraAnimationCRT;
// int C2F_EX = callExtraAnimationCRT;

// 新增战斗动画数据
const BattleAnimation NewBattleAnimationBank[] = {
	// 梅尔变身前动画(0x100)
	{
		"mf_mi1",
		&BattleAnimation_Myrrh_data1,	// Mode divider
		&BattleAnimation_Myrrh_data2,	// Script
		&BattleAnimation_Myrrh_data3,	// Right X Y Position
		&BattleAnimation_Myrrh_data4,	// Left X Y Position
		&BattleAnimation_Myrrh_pal,	// Palette Group
	},
	// 梅尔变身动画(0x101)
	{
		"fifd_he1",	// Identifier
		&BattleAnimation_MyrrhTrans_data1,	// Mode divider
		&BattleAnimation_MyrrhTrans_data2,	// Script
		&BattleAnimation_MyrrhTrans_data3,	// Right X Y Position
		&BattleAnimation_MyrrhTrans_data4,	// Left X Y Position
		&BattleAnimation_MyrrhTrans_pal,	// Palette Group
	},
	// 梅尔解除变身动画(0x102)
	{
		"fifd_hk1",	// Identifier
		&BattleAnimation_MyrrhInvers_data1,	// Mode divider
		&BattleAnimation_MyrrhInvers_data2,	// Script
		&BattleAnimation_MyrrhInvers_data3,	// Right X Y Position
		&BattleAnimation_MyrrhInvers_data4,	// Left X Y Position
		&BattleAnimation_MyrrhTrans_pal,	// Palette Group
	},
	// 梅尔龙动画(0x103)
	{
		"fifd_mg1",	// Identifier
		&BattleAnimation_MyrrhDragon_data1,	// Mode divider
		&BattleAnimation_MyrrhDragon_data2,	// Script
		&BattleAnimation_MyrrhDragon_data3,	// Right X Y Position
		&BattleAnimation_MyrrhDragon_data4,	// Left X Y Position
		&BattleAnimation_MyrrhDragon_pal,	// Palette Group
	},
	// 珐变身前动画(0x104)
	{
		"mamf_no1",	// Identifier
		&BattleAnimation_Fa_data1,	// Mode divider
		&BattleAnimation_Fa_data2,	// Script
		&BattleAnimation_Fa_data3,	// Right X Y Position
		&BattleAnimation_Fa_data4,	// Left X Y Position
		&BattleAnimation_Fa_pal,	// Palette Group
	},
	// 珐变身后动画(神龙)(0x105)
	{
		"godd_mg1",	// Identifier
		&BattleAnimation_FaDragon_data1,	// Mode divider
		&BattleAnimation_FaDragon_data2,	// Script
		&BattleAnimation_FaDragon_data3,	// Right X Y Position
		&BattleAnimation_FaDragon_data4,	// Left X Y Position
		&BattleAnimation_FaDragon_pal,	// Palette Group
	},
	// 珐变身成神龙的动画(0x106)
	{
		"godd_he1",	// Identifier
		&BattleAnimation_FaTrans_data1,	// Mode divider
		&BattleAnimation_FaTrans_data2,	// Script
		&BattleAnimation_FaTrans_data3,	// Right X Y Position
		&BattleAnimation_FaTrans_data4,	// Left X Y Position
		&BattleAnimation_FaTrans_pal,	// Palette Group
	},
	// 珐解除变身的动画(0x107)
	{
		"godd_hk1",	// Identifier
		&BattleAnimation_FaInvers_data1,	// Mode divider
		&BattleAnimation_FaInvers_data2,	// Script
		&BattleAnimation_FaInvers_data3,	// Right X Y Position
		&BattleAnimation_FaInvers_data4,	// Left X Y Position
		&BattleAnimation_FaTrans_pal,	// Palette Group
	}
};

// 战斗动画库地址表
const BattleAnimation * const battleAnimationBank[] =
{
	FE7BattleAnimationBank,
	NewBattleAnimationBank
};

// 战斗动画bank信息表
const BattleAnimationBankInfo battleAnimationBankInfoTable[] =
{
	{FE7BattleAnimationBank, 0},
	{&NewBattleAnimationBank, 0},
	{&BattleAnimationPointerBank, 1},
};

// 根据战斗动画id取战斗动画数据地址
pBattleAnimation GetBattleAnimation(u16 index)
{
	u8 bank_number;
	u8 animation_number;
	BattleAnimationBankInfo bank_info;
	
	bank_number = index >> 8;
	animation_number = index & 0xFF;
	bank_info = battleAnimationBankInfoTable[bank_number];
	if(bank_info.is_pointer)
		return ((pBattleAnimation*)(bank_info.array))[animation_number];
	return (pBattleAnimation)(bank_info.array) + animation_number;
}

// 交换2个双字节
void swap_u16(u16 *a,u16 *b)
{
	u16 c;
	
	c = *a;
	*a = *b;
	*b = c;
}

// 调色板动画
// 输入参数:是精灵还是背景,调色板所在的槽的序号,调色板组地址,调色板组中包含的调色板数,间隔,持续时间
// bool IsSpriteOrBG,int palSlot,u16 *paletteGroup,int paletteNum,int interval,int duration
// 分别存储在userSpace[0],[4],[8],[12],[20],[24]
// 静态局部变量: 当前使用的调色板在调色板组中的序号,存在userSpace[16];计时,存在[28]
// 但是考虑到4字节对齐可以提高效率,故作如下调整(+3):
// 3,7,11,15,19,23,27,31
void paletteAnimation(struct context *ctx)
{
	*(int *)&ctx->userSpace[31] = *(int *)&ctx->userSpace[31] + 1;
	if(*(int *)&ctx->userSpace[31] > *(int *)&ctx->userSpace[27])
		breakLoop(ctx);
	else
		if(!FE7JMod(*(int *)&ctx->userSpace[31],*(int *)&ctx->userSpace[23]))
		{
			*(int *)&ctx->userSpace[19] += 1;
			if(*(int *)&ctx->userSpace[19] > *(int *)&ctx->userSpace[15] - 1)
				*(int *)&ctx->userSpace[19] = 0;
			// DEBUG("Current palette index = %d",*(int *)&ctx->userSpace[19])
			FE7JCPUFastSet(*(u16 **)&ctx->userSpace[11] + 0x10 * *(int *)&ctx->userSpace[19],BGPaletteBuffer + 0x100 * *(bool *)&ctx->userSpace[3] + 0x10 * *(int *)&ctx->userSpace[7],8);
			EnablePaletteSync();
		}
}

const struct coroutine efxPaletteAnimation[] = {
	setLoopFuncAndYield(paletteAnimation),
	endofCoroutine
};

// 输入参数:是精灵还是背景,调色板所在的槽的序号,调色板组地址,调色板组中包含的调色板数,间隔,持续时间
void loadPaletteAnimation(bool isSpriteOrBG,int palSlot,u16 *paletteGroup,int paletteNum,int interval,int duration)
{
	struct context *ctx = createContext(efxPaletteAnimation,4);
	*(bool *)&ctx->userSpace[3] = isSpriteOrBG;
	*(int *)&ctx->userSpace[7] = palSlot;
	*(u16 **)&ctx->userSpace[11] = paletteGroup;
	*(int *)&ctx->userSpace[15] = paletteNum;
	*(int *)&ctx->userSpace[23] = interval;
	*(int *)&ctx->userSpace[27] = duration;
	*(int *)&ctx->userSpace[19] = 1;	// 初始色板ID
	*(int *)&ctx->userSpace[31] = 1;	// 计时器初值
}

// 水平翻转再加一定位移的冰块背景
void loadFimbulvetrBGFlipH(void *AIS)
{
//  void *v1; // r4@1
	struct context *ctx; // r5@1

//  v1 = AIS;
	++*(u32 *)0x201774C;
	ctx = createContext(efxFimbulvetrBG, 3);
	*(_DWORD *)&ctx->userSpace[51] = AIS;
	*(_WORD *)&ctx->userSpace[3] = 0;
	*(_DWORD *)&ctx->userSpace[27] = 0;
	*(_DWORD *)&ctx->userSpace[31] = 0x81EE05A;
	*(_DWORD *)&ctx->userSpace[35] = 0x8C10FD0;
	*(_DWORD *)&ctx->userSpace[39] = 0x8C10FD0;
	*(_DWORD *)&ctx->userSpace[43] = 0x8C10FFC;
	sub(8050E10)((const char *)0x8219AF4, 32);
//	if ( *(u16 *)0x203E004 )
//	{
		if ( !isUnitAtRightOrLeft(*(_DWORD *)&ctx->userSpace[51]) )
			setBGnPosition(1u, 232 - 40, 0);
		else
			setBGnPosition(1u, 24 + 40, 0);
//	}
	sub(805081C)();
}

// 寒风
void showColdWind(void *AIS)
{
	void *targetAIS = getTargetAIS(AIS);
	loadFimbulvetrBGTR(targetAIS);
    loadFimbulvetrOBJ2(targetAIS);
    LOBYTE(BLDCNTBuffer) = BLDCNTBuffer & 0x3F | 0x40;
    BLDALPHABuffer = 0x1000;
    BLDYBuffer = 0;
    loadALPHA(targetAIS, 0, 16, 0, 16, 0);
//    PlaySFX(290, 256, *((_WORD *)targetAIS + 1), 1);
}

// 攻击附带碎冰效果
void showIcePiecesEffect(void *AIS,bool ifCritical)
{
	void *targetAIS = getTargetAIS(AIS);
	loadFimbulvetrOBJ(targetAIS);
/*	if(ifCritical)
	{
//		loadFlashBG(AIS,4);
		loadFimbulvetrBG(targetAIS);
//		loadALPHA(targetAIS, 24, 16, 16, 0, 0);
//		PlaySFX(291, 256, *((_WORD *)targetAIS + 1), 1);
	}	*/
}

// 冰封效果
void showIceCrystal(void *AIS)
{
	void *targetAIS = getTargetAIS(AIS);
	loadFimbulvetrBG(targetAIS);
//	loadALPHA(targetAIS, 24, 16, 16, 0, 0);
	PlaySFX(291, 256, *((_WORD *)targetAIS + 1), 1);
}

// 攻击附带火炎效果
void showFireHitEffect(void *AIS,bool ifCritical)
{
	u16 *targetAIS = getTargetAIS(AIS);
	
	// 为了避免和8500001A(Normal hit)互相干扰,用此函数取代之
	// 让动画能继续进行下去
	if(targetAIS[0])
	{
		targetAIS[8] |= 9u;
		reduceHPBar(targetAIS,sub(8054E74)(sub(8054FEC)(AIS)));
	}
	
	if(ifCritical)
	{
		PlaySFX(248, 256, targetAIS[1], 1);
        loadElfireBG(targetAIS);
        loadElfireBGCOL(targetAIS);
        loadElfireOBJ(targetAIS);
	}
	else
	{
		PlaySFX(247, 256, targetAIS[1], 1);
        loadFireHITBG(targetAIS);
	}
}

// 显示古代火龙的身体
void showFireDragonBody(void *AIS)
{
	// int a = 0x1F001F;
	// int v2 = -16;
	// int v2 = 192;
	// int v2 = 248;
	// int v3 = 0;

	BG2CNTBuffer = BG2CNTBuffer | 3;
	BG3CNTBuffer = (BG3CNTBuffer >> 2 << 2) | 2;
	// Text Mode 下这个标识位无效
	// BG3CNTBuffer &= ~(1<<13);
	FE7JLZ77UnCompVram(FireDragonImg, 0x6008000);
	FE7JCPUFastSet(FireDragonPalGroup, BGPaletteBuffer+96, 8u);
	EnableBGPaletteSync();
	// FE7JLZ77UnCompWram(FireDragonBodyTSA, 0x2019784);
	// FE7JLZ77UnCompWram(FireDragonBodyTSA, BG3MapBuffer);
	// EnableBGMapSync(1<<3);
	// FE7JCPUSet(&a, 0x2019F04, 0x5000020);
	// sub(8050F94)(0x1F001F);
    // memClear2K(BG3MapBuffer, 31);
    // sub(8065388)();
	// sub(8065328)(*(u32 *)0x201FB00, 0);
	// sub(80673C8)(0x2019784, -1, 0x201D41C + 132 * (v3 >> 3) + 2 * (v2 >> 3), 66, 0x20u, 0x20u, 6, 0);
	// sub(8067318)(2 * (v2 >> 3) + 0x201D45E + 132 * (v3 >> 3),66,BG3MapBuffer,32,0x20u,0x20u,-1,-1);
	/*
	if(isUnitAtRightOrLeft(AIS))
	{
		FE7JLZ77UnCompWram(FireDragonBodyTSA, BG3MapBuffer);
		for(int i = 0; i < 0x800/4; i++)
			*((u32 *)BG3MapBuffer + i) |= (6<<12) * 0x10001;
	}
	else
	{
		FE7JLZ77UnCompWram(FireDragonBodyTSA, 0x2019784);
		for(int i = 0; i < 32; i++)
			for(int j = 0; j < 32; j++)
				((u16 **)BG3MapBuffer)[i][j] = ((u16 **)0x2019784)[i][31 - j] + (6<<12);
	}
	*/
	FE7JLZ77UnCompWram(FireDragonBodyTSA, BG3MapBuffer);
	for(int i = 0; i < 0x800/4; i++)
	{
		*((u32 *)BG3MapBuffer + i) |= (6<<12) * 0x10001;
		if(!isUnitAtRightOrLeft(AIS))
			*((u32 *)BG3MapBuffer + i) |= (1<<10) * 0x10001;
	}
	if(!isUnitAtRightOrLeft(AIS))
	{
		for(int i = 0; i < 32; i++)
			for(int j = 0; j < 15; j++)
				// swap(((u16 **)BG3MapBuffer)[i][j],((u16 **)BG3MapBuffer)[i][31-j]);
				// swap_u16(((u16 **)BG3MapBuffer+32*i)+j,((u16 **)BG3MapBuffer+32*i)+31-j);
				swap_u16((u16 *)BG3MapBuffer+32*i+j,(u16 *)BG3MapBuffer+32*i+31-j);
	}
	SetBGMapSyncFlag(8u);
	// setBGnPosition(3,16,0);
}

// 火龙抬头
void FireDragonRaiseHead(void *AIS)
{
	FE7JLZ77UnCompWram(FireDragonBodyUPTSA, BG3MapBuffer);
	for(int i = 0; i < 0x800/4; i++)
	{
		*((u32 *)BG3MapBuffer + i) |= (6<<12) * 0x10001;
		if(!isUnitAtRightOrLeft(AIS))
			*((u32 *)BG3MapBuffer + i) |= (1<<10) * 0x10001;
	}
	if(!isUnitAtRightOrLeft(AIS))
	{
		for(int i = 0; i < 32; i++)
			for(int j = 0; j < 15; j++)
				// swap(((u16 **)BG3MapBuffer)[i][j],((u16 **)BG3MapBuffer)[i][31-j]);
				// swap_u16(((u16 **)BG3MapBuffer+32*i)+j,((u16 **)BG3MapBuffer+32*i)+31-j);
				swap_u16((u16 *)BG3MapBuffer+32*i+j,(u16 *)BG3MapBuffer+32*i+31-j);
	}
	SetBGMapSyncFlag(8u);
}

// 火龙低头
void FireDragonBowHead(void *AIS)
{
	FE7JLZ77UnCompWram(FireDragonBodyTSA, BG3MapBuffer);
	for(int i = 0; i < 0x800/4; i++)
	{
		*((u32 *)BG3MapBuffer + i) |= (6<<12) * 0x10001;
		if(!isUnitAtRightOrLeft(AIS))
			*((u32 *)BG3MapBuffer + i) |= (1<<10) * 0x10001;
	}
	if(!isUnitAtRightOrLeft(AIS))
	{
		for(int i = 0; i < 32; i++)
			for(int j = 0; j < 15; j++)
				// swap(((u16 **)BG3MapBuffer)[i][j],((u16 **)BG3MapBuffer)[i][31-j]);
				// swap_u16(((u16 **)BG3MapBuffer+32*i)+j,((u16 **)BG3MapBuffer+32*i)+31-j);
				swap_u16((u16 *)BG3MapBuffer+32*i+j,(u16 *)BG3MapBuffer+32*i+31-j);
	}
	SetBGMapSyncFlag(8u);
}

// 超出范围会有bug,废弃
/*
// 对BG3移屏(配合魔法动画)
void ScrollBG3(void *AIS)
{
	// Text Mode 下这个标识位无效
	// BG3CNTBuffer &= ~(1<<13);
	if(isUnitAtRightOrLeft(AIS))
		// setBGnPosition(3,-16,0);
		setBGnPosition(3,240,0);
	else
		setBGnPosition(3,0,0);
}

// 复位BG3(魔法结束)
void ScrollBG3Back(void *AIS)
{
	// Text Mode 下这个标识位无效
	// BG3CNTBuffer &= ~(1<<13);
	if(isUnitAtRightOrLeft(AIS))
		setBGnPosition(3,0,0);
	else
		setBGnPosition(3,-16,0);
}
*/

void ScrollBG3(void *AIS)
{
	if(isUnitAtRightOrLeft(AIS))
	{
		for(int i = 0; i < 32; i++)
			for(int j = 31; j > 1; j--)
				((u16 *)BG3MapBuffer)[32*i+j] = ((u16 *)BG3MapBuffer)[32*i+j-2];
	}
	else
	{
		for(int i = 0; i < 32; i++)
			for(int j = 0; j < 30; j++)
				((u16 *)BG3MapBuffer)[32*i+j] = ((u16 *)BG3MapBuffer)[32*i+j+2];
	}
	SetBGMapSyncFlag(1<<3);
}

// 开始火龙背景调色板动画效果(翼变色)
/*
void startFireDragonBGPaletteAnimation()
{
	// loadFireDragonBGPaletteAnimation(AIS);
	struct context *ctx = createContext(efxPaletteAnimation,4);
	*(bool *)&ctx->userSpace[3] = 0; // IsSpriteOrBG
	*(int *)&ctx->userSpace[7] = 6;	// palSlot
	*(u16 **)&ctx->userSpace[11] = FireDragonPalGroup;	// paletteGroup
	*(int *)&ctx->userSpace[15] = 7;	// paletteNum
	*(int *)&ctx->userSpace[19] = 0;	// 初始色板ID
	// DEBUG("0x%x,%d,%d,0x%x,%d,%d",ctx,*(bool *)&ctx->userSpace[3],*(int *)&ctx->userSpace[7],*(u16 **)&ctx->userSpace[11],*(int *)&ctx->userSpace[15],*(int *)&ctx->userSpace[19])
}
*/

void startFireDragonBGPaletteAnimation()
{
	loadPaletteAnimation(0,6,FireDragonPalGroup,4,5,65535);
}

// 终止调色板动画效果
void endBGPaletteAnimation()
{
	// isolateAndDeleteContext(findContext(efxFireDragonBGPaletteAnimation));
	isolateAndDeleteContext(findContext(efxPaletteAnimation));
	// DEBUG("endBGPaletteAnimation")
}

// 附加外挂动画函数指针表
const PTRFUN ExtraAnimation[] = {
	loadMagfcast,						// EFX 0
//	loadFimbulvetrBG
	loadFimbulvetrBGFlipH,				// EFX 1
	showIcePiecesEffect,				// EFX 2
	showColdWind,						// EFX 3
	showIceCrystal,						// EFX 4
	showFireHitEffect,					// EFX 5
	showFireDragonBody,					// EFX 6
	FireDragonRaiseHead,				// EFX 7
	FireDragonBowHead,					// EFX 8
	ScrollBG3,							// EFX 9
//	ScrollBG3Back
	startFireDragonBGPaletteAnimation,	// EFX 10
	endBGPaletteAnimation		// EFX 11
};

// C87扩展事件处理函数模板
void C87DoNothing(AnimationInterpreter *AIS)
{

}

// 龙人变身过程:原动画->变身动画->变身后的动画(由当前装备品ID决定)->变身解除动画(->原动画,不需要,去掉)->原动画(需要- -)
// trans1 : 原动画->变身动画
// trans2 : 变身动画->变身后的动画
// trans3 : 变身后的动画->变身解除动画
// trans4 : 变身解除动画->原动画

// 根据原动画ID查找变身动画ID和变身解除动画ID
const BattleAnimationTransInfo BattleAnimationTransTable[] = {
	[0x100] = {0x101,0x102},
	// [0x103] = {0x102,0x101}
	// [0x102] = {0x100,0}
	[0x104] = {0x106,0x107}
};

// 根据当前装备品的代码决定变身后的动画
const u16 Item2TransAnimationID[] = {
	[Flametongue] = 0x103,
	[FillaMight] = 0x105
};

// 获取当前动画ID
u16 getAnimationID(AnimationInterpreter *AIS)
{
	return BattleAnimationIDArray[isUnitAtRightOrLeft(AIS)];
}

// 获取当前装备品ID
u8 getEquippedItemID(AnimationInterpreter *AIS)
{
	return *(u8 *)(((u32 *)0x203E06C)[isUnitAtRightOrLeft(AIS)] + 74);
}

void C87Trans1(AnimationInterpreter *AIS)
{
//	int mode;

	if(getAnimationID(AIS) < sizeof(BattleAnimationTransTable)/sizeof(BattleAnimationTransTable[0]) && BattleAnimationTransTable[getAnimationID(AIS)].transAnimationID)
	{
		// TODO : 获取当前mode
		// ((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->inversAnimationID = BattleAnimationTransTable[getAnimationID(AIS)].inversAnimationID;
		((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->animationID = getAnimationID(AIS);
		((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->modeX = (*(AIS->nextCmd-1)>>8)&0xFF;
		transformateBattleAnimation(AIS,BattleAnimationTransTable[getAnimationID(AIS)].transAnimationID);
		/*
		// 变身动画只用mode1
		if(isUnitAtRightOrLeft(AIS))
		{
			if(BattleAnimationEventBufferRightSide[0] == 'l' + ('a'<<8) +('q'<<16))
				AIS->nextCmd = BattleAnimationEventBufferRightSide[1];
			else
				AIS->nextCmd = BattleAnimationEventBufferRightSide;
		}
		else
		{
			if(BattleAnimationEventBufferLeftSide[0] == 'l' + ('a'<<8) +('q'<<16))
				AIS->nextCmd = BattleAnimationEventBufferLeftSide[1];
			else
				AIS->nextCmd = BattleAnimationEventBufferLeftSide;
		}
		*/
		InitAIS(AIS,0);
	//	getSpecialAnimationEffectInfo(AIS)->unk_8 = mode;
	}
}

void C87Trans2(AnimationInterpreter *AIS)
{
	int mode;
	int sectionOffset;
	int eventBuffer;
	int modeX;
	
	if(getEquippedItemID(AIS) < sizeof(Item2TransAnimationID)/sizeof(Item2TransAnimationID[0]) && Item2TransAnimationID[getEquippedItemID(AIS)])
	/*
	{
		transformateBattleAnimation(AIS,Item2TransAnimationID[getEquippedItemID(AIS)]);
		
		// mode = ((u32 *)0x81DE1E0)[*((u8 *)0x81DE208 + *(u16 *)0x203E004)] & 0xFF;
		mode = 0;	// TODO : 从脚本指令里获取
		if(isUnitAtRightOrLeft(AIS))
		{
			sectionOffset = BattleAnimationSectionInfoRightSide[mode];
			eventBuffer = BattleAnimationEventBufferRightSide;
		}
		else
		{
			sectionOffset = BattleAnimationSectionInfoLeftSide[mode];
			eventBuffer = BattleAnimationEventBufferLeftSide;
		}
		if(*(u32 *)eventBuffer == 'l' + ('a'<<8) +('q'<<16))
			eventBuffer = *((u32 *)eventBuffer + 1);
		AIS->lastCmd = eventBuffer + sectionOffset;
		AIS->nextCmd = eventBuffer + sectionOffset;
		
	}
	*/
	{
		// BattleAnimationIDArray[isUnitAtRightOrLeft(AIS)] = Item2TransAnimationID[getEquippedItemID(AIS)];
		// battleAnimationInit();
		// initBothAIS();
		modeX = ((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->modeX;
		((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->modeX = 0;
		transformateBattleAnimation(AIS,Item2TransAnimationID[getEquippedItemID(AIS)]);
		InitAIS(AIS,modeX);
		// AIS->unk_E = 0;
		// AIS->modeX = 6;
	}
}

void sub_804C7C4(struct context *ctx)
{
	AnimationInterpreter *AISLeft; // r0@4
	signed int v3; // r0@6
	AnimationInterpreter *AISRight; // r0@7

	if ( *(_DWORD *)&ctx->userSpace[31] == 2 )
	{
		ctx->loop = sub(804C854);
	}
	else
	{
		if ( *(_DWORD *)&ctx->userSpace[27] )
		{
			AISRight = AISTable[2];
			*(_DWORD *)&ctx->userSpace[51] = AISTable[2];
			// 为了让变身解除协程知道动画何时结束,故修改下面的判断
			// if ( callSpecialAnimationEffectTypeGetter(AISRight) )
			if(callSpecialAnimationEffectTypeGetter(AISRight) || ((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AISRight))->animationID)
			{
				setSpecialAnimationEffectInfoState4(*(AnimationInterpreter **)&ctx->userSpace[51]);
				ctx->loop = sub(804C834);
			}
			v3 = 0;
		}
		else
		{
			AISLeft = AISTable[0];
			*(_DWORD *)&ctx->userSpace[51] = AISTable[0];
			// 为了让变身解除协程知道动画何时结束,故修改下面的判断
			// if ( callSpecialAnimationEffectTypeGetter(AISLeft) )
			if(callSpecialAnimationEffectTypeGetter(AISLeft) || ((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AISLeft))->animationID)
			{
				setSpecialAnimationEffectInfoState4(*(AnimationInterpreter **)&ctx->userSpace[51]);
				ctx->loop = sub(804C834);
			}
			v3 = 1;
		}
		*(_DWORD *)&ctx->userSpace[27] = v3;
		++*(_DWORD *)&ctx->userSpace[31];
	}
}

__attribute__((section(".call_sub_804C7C4")))
void call_sub_804C7C4(struct context *ctx)
{
	sub_804C7C4(ctx);
}

void InversTransformate(struct context *ctx)
{
	AnimationInterpreter *AIS;

	AIS = *(AnimationInterpreter **)&ctx->userSpace[51];
	if ( getSpecialAnimationEffectInfoState(AIS) & 4 )
	{
		((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->state = 0;
		transformateBattleAnimation(AIS,*(u16 *)&ctx->userSpace[55]);
		InitAIS(AIS,0);
		breakLoop(ctx);
	}
}

const struct coroutine InversTrans[] = {
	setLoopFuncAndYield(InversTransformate),
	endofCoroutine
};

void C87Trans3(AnimationInterpreter *AIS)
{
	struct context *ctx;

	if(BattleAnimationTransTable[((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->animationID].inversAnimationID && !getSpecialAnimationEffectInfoState(AIS))
	{
		// transformateBattleAnimation(AIS,((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->inversAnimationID);
		/*
		// 变身解除动画只用mode1
		if(isUnitAtRightOrLeft(AIS))
		{
			if(BattleAnimationEventBufferRightSide[0] == 'l' + ('a'<<8) +('q'<<16))
				AIS->nextCmd = BattleAnimationEventBufferRightSide[1];
			else
				AIS->nextCmd = BattleAnimationEventBufferRightSide;
		}
		else
		{
			if(BattleAnimationEventBufferLeftSide[0] == 'l' + ('a'<<8) +('q'<<16))
				AIS->nextCmd = BattleAnimationEventBufferLeftSide[1];
			else
				AIS->nextCmd = BattleAnimationEventBufferLeftSide;
		}
		*/
		// InitAIS(AIS,0);
		ctx = createContext(InversTrans,3);
		*(AnimationInterpreter **)&ctx->userSpace[51] = AIS;
		*(u16 *)&ctx->userSpace[55] = BattleAnimationTransTable[((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->animationID].inversAnimationID;
		// ((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->inversAnimationID = 0;
		((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->state = 1;	// 避免重复创建上下文
	}
}

void C87Trans4(AnimationInterpreter *AIS)
{
	transformateBattleAnimation(AIS,((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->animationID);
	((SpecialAnimationEffectInfo *)getSpecialAnimationEffectInfo(AIS))->animationID = 0;
	setSpecialAnimationEffectInfoState(AIS, 8);
}

// C87扩展动画指令函数表
const PTRFUN BattleAnimationEventEX[] = {
	C87DoNothing,
	C87Trans1,
	C87Trans2,
	C87Trans3,
	C87Trans4
};

// 读取战斗动画相关数据到内存
void battleAnimationInit()
{
  int animationID; // 动画ID
  int palSlotIDInPalGroup; // 用动画调色板组中的哪个槽
  s16 characterBattlePaletteID; // 人物指定动画调色板ID
  BattleAnimation *animation; // 战斗动画数据
  signed int animationID_PalGroup; // 用这个动画ID的调色板组
  short v10; // r0@10
  short v11; // r0@12
  int v12; // [sp+0h] [bp-24h]@10
  int i; // 循环变量
  pBattleAnimation animation_p; // 调色板所在的战斗动画

  *(u32 *)0x201FB14 = 0;
  *(u32 *)0x201FB10 = 0;
  if ( IfBattleAnimationIsAtTheLeftSide == 1 )
  {
    animationID = BattleAnimationIDLeftSide;
	DEBUG("Animation ID (Left): 0x%x", animationID)
    palSlotIDInPalGroup = BattleAnimationPalSlotLeftSide;
    characterBattlePaletteID = CharaterBattleAnimationPaletteIDLeftSide;
//    animation = FE7BattleAnimationBank + BattleAnimationIDLeftSide;
//	animation = &battleAnimationBank[animationID>>8][animationID & 0xFF];
	animation = GetBattleAnimation(animationID);
//    FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferLeftSide);

//	无压缩data2支持
	if(*(u8 *)(animation->event) == 0x10)
		FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferLeftSide);
	else
	{
		BattleAnimationEventBufferLeftSide[0] = 'l' + ('a'<<8) +('q'<<16);
		BattleAnimationEventBufferLeftSide[1] = animation->event;
	}
	
    BattleAnimationSectionInfoLeftSide = animation->sectionOffset;
    animationID_PalGroup = getAnimationIDForPaletteGroup(animationID, 0);
	
//	无压缩data5支持
/*	if( *(u8 *)battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup == 0x10)
    	FE7JLZ77UnCompWram(
	//      FE7BattleAnimationBank[animationID_PalGroup].palGroup,
		  battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup,
	      BattleAnimationPaletteGroupBufferLeftSide);
	else
		FE7JCPUFastSet(battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup,
						BattleAnimationPaletteGroupBufferLeftSide,0x80/4);	*/
						
	// data5(调色板组)双倍扩展(16 x 5 => 32 x 5)
	animation_p = GetBattleAnimation(animationID_PalGroup);
	if(*(int *)animation_p->palGroup == -1)	// 头部加4个0xFF标识32色板组
		for(i = 0; i < 5; i++)
			FE7JCPUFastSet((int)animation_p->palGroup + 4 + 0x20 * 2 * i, (int)BattleAnimationPaletteGroupBufferLeftSide + 0x20 * i, 0x20 / 4);
	else
		if(*(u8 *)animation_p->palGroup == 0x10)	// 这种压缩识别方式这是为了兼容以前做好的动画,假设无压缩数据的第一个字节刚好是0x10的话...
			FE7JLZ77UnCompWram(animation_p->palGroup, BattleAnimationPaletteGroupBufferLeftSide);
		else
			FE7JCPUFastSet(animation_p->palGroup, BattleAnimationPaletteGroupBufferLeftSide, 0xA0 / 4);
	
    if ( characterBattlePaletteID != -1 )
    {
	//	无压缩人物调色板支持
	// 个人调色板双倍扩展(16 x 1 => 32 x 1)
		if(*(int *)characterBattlePalTable[characterBattlePaletteID].pal == -1)
			FE7JCPUFastSet((int)characterBattlePalTable[characterBattlePaletteID].pal + 4, BattleAnimationPaletteGroupBufferLeftSide, 0x20 / 4);
		else
			if( *(u8 *)characterBattlePalTable[characterBattlePaletteID].pal == 0x10)
			  FE7JLZ77UnCompWram(
				characterBattlePalTable[characterBattlePaletteID].pal,
				BattleAnimationPaletteGroupBufferLeftSide);
			else
				FE7JCPUFastSet(characterBattlePalTable[characterBattlePaletteID].pal,BattleAnimationPaletteGroupBufferLeftSide,0x20/4);
		
      sub(8054798)(BattleAnimationPaletteGroupBufferLeftSide, 0);
    }
    BattleAnimationPaletteLeftSide = BattleAnimationPaletteGroupBufferLeftSide + 16 * palSlotIDInPalGroup;
    FE7JCPUFastSet(BattleAnimationPaletteGroupBufferLeftSide + 16 * palSlotIDInPalGroup, &OBJPaletteBuffer[112], 8u);
    FE7JCPUFastSet(*(void **)0x203E080, &OBJPaletteBuffer[128], 8u);
	
	// 第二调色板扩展
//	if(characterBattlePaletteID == 0x79-1)
	//	FE7JCPUFastSet(&PriscillaAnimationTest_PalA, &OBJPaletteBuffer[128], 8u);
	if(characterBattlePaletteID != -1)
	{
		if(characterBattlePaletteID < sizeof(characterBattleSecondPalTable)/sizeof(characterBattleSecondPalTable[0]) && characterBattleSecondPalTable[characterBattlePaletteID])
			FE7JCPUFastSet(characterBattleSecondPalTable[characterBattlePaletteID], &OBJPaletteBuffer[128], 8);
		else	// 直接扩展色板支持
			if(*(int *)characterBattlePalTable[characterBattlePaletteID].pal == -1)
				FE7JCPUFastSet((int)characterBattlePalTable[characterBattlePaletteID].pal + 4 + 0x20, &OBJPaletteBuffer[128], 8);
	}
	else
	{
		if(animationID < sizeof(battleAnimationSecondPalTable)/sizeof(battleAnimationSecondPalTable[0]) && battleAnimationSecondPalTable[animationID])
			FE7JCPUFastSet(battleAnimationSecondPalTable[animationID] + 16 * palSlotIDInPalGroup, &OBJPaletteBuffer[128], 8);
		else	// 直接扩展色板支持
			if(*(int *)animation_p->palGroup == -1)
				FE7JCPUFastSet((int)animation_p->palGroup + 4 + 0x20 * 2 * palSlotIDInPalGroup + 0x20, &OBJPaletteBuffer[128], 8);
	}
	
    EnablePaletteSync();
//    FE7JLZ77UnCompWram(animation->oamL2R, BattleAnimationOAML2RBuffer);
		
//	 无压缩data4支持
	if(*(u8 *)(animation->oamL2R) == 0x10)
		FE7JLZ77UnCompWram(animation->oamL2R, BattleAnimationOAML2RBuffer);
	else
		//	不要拷贝到RAM里的无压缩格式(头部4字节:字符串'laq',大小固定,以01000000 00000000 00000000 00000000结尾,总计0x5800+4字节)
		if(*(u32 *)(animation->oamL2R) == 'l' + ('a' << 8) + ('q' << 16))
		{
			((u32 *)BattleAnimationOAML2RBuffer)[0] = 'l' + ('a' << 8) + ('q' << 16);
			((void **)BattleAnimationOAML2RBuffer)[1] = (u32 *)animation->oamL2R+1;
		}
		//	需要拷贝到RAM里的无压缩格式(无头部,大小不定,以连续12个0xFF结尾,节约空间)
		else
		{
			/*
			int *p = animation->oamL2R;
			int *q = BattleAnimationOAML2RBuffer;
			for(int i=0;;i++)
			{
				if(p[i] == -1 && p[i+1] == -1 && p[i+2] == -1)
					break;
				q[i] = p[i];
			}
			*/
			// 先清零这片内存区域
			int zero = 0;
			FE7JCPUFastSet(&zero,BattleAnimationOAML2RBuffer,0x5800/4+(1<<24));
			
			for(int i=0;i<0x5800/4;i++)
			{
				if(((int *)animation->oamL2R)[i] == -1 && ((int *)animation->oamL2R)[i+1] == -1 && ((int *)animation->oamL2R)[i+2] == -1)
					break;
				((int *)BattleAnimationOAML2RBuffer)[i] = ((int *)animation->oamL2R)[i];
			}
			
//			FE7JCPUFastSet(animation->oamL2R, BattleAnimationOAML2RBuffer, 0x57f0/4);
		}

//	_pause();
//	_print("void battleAnimationInit()\n");
/*
	char szBuffer[BufferMaxLength];
//	sprintf(szBuffer,"The sum of %i and %i is %i", 5, 3, 5+3);
	sprintf(szBuffer,"The sum of %d and %d is %d", 5, 3, 5+3);
	_print(szBuffer);
	*/
//	DEBUG("animation = 0x%x", animation)
//	_pause();

    *(u32 *)0x20099B8 = 1;	// 在OAM信息缓存(大小0x5800字节)的最后一行加01000000 00000000 00000000 00000000(标识一个Frame的结束?)
  }
  if ( IfBattleAnimationIsAtTheRightSide == 1 )
  {
    animationID = BattleAnimationIDRightSide;	
	DEBUG("Animation ID (Right): 0x%x", animationID)

//	映射敌人的战斗动画
	if(animationID == MirrorBattleAnimationID - 1)
		animationID = BattleAnimationIDLeftSide;

    palSlotIDInPalGroup = BattleAnimationPalSlotRightSide;
    characterBattlePaletteID = CharaterBattleAnimationPaletteIDRightSide;
//    animation = FE7BattleAnimationBank + BattleAnimationIDRightSide;
//	animation = &battleAnimationBank[animationID>>8][animationID & 0xFF];
	animation = GetBattleAnimation(animationID);
//    FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferRightSide);

//	无压缩data2支持
	if(*(u8 *)(animation->event) == 0x10)
		FE7JLZ77UnCompWram(animation->event, BattleAnimationEventBufferRightSide);
	else
	{
		BattleAnimationEventBufferRightSide[0] = 'l' + ('a'<<8) +('q'<<16);
		BattleAnimationEventBufferRightSide[1] = animation->event;
	}
	
    BattleAnimationSectionInfoRightSide = animation->sectionOffset;
    animationID_PalGroup = getAnimationIDForPaletteGroup(animationID, 1);
	
//	无压缩data5支持
/*	if(*(u8 *)battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup == 0x10)
    	FE7JLZ77UnCompWram(
	//      FE7BattleAnimationBank[animationID_PalGroup].palGroup,
		  battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup,
	      BattleAnimationPaletteGroupBufferRightSide);
	else
		FE7JCPUFastSet(battleAnimationBank[animationID_PalGroup>>8][animationID_PalGroup & 0xFF].palGroup,
						BattleAnimationPaletteGroupBufferRightSide,0x80/4);	*/
						
	animation_p = GetBattleAnimation(animationID_PalGroup);
	if(*(int *)animation_p->palGroup == -1)	// 头部加4个0xFF标识32色板组
		for(i = 0; i < 5; i++)
			FE7JCPUFastSet((int)animation_p->palGroup + 4 + 0x20 * 2 * i, (int)BattleAnimationPaletteGroupBufferRightSide + 0x20 * i, 0x20 / 4);
	else
		if(*(u8 *)animation_p->palGroup == 0x10)	// 这种压缩识别方式这是为了兼容以前做好的动画,假设无压缩数据的第一个字节刚好是0x10的话...
			FE7JLZ77UnCompWram(animation_p->palGroup, BattleAnimationPaletteGroupBufferRightSide);
		else
			FE7JCPUFastSet(animation_p->palGroup, BattleAnimationPaletteGroupBufferRightSide, 0xA0 / 4);
	
    if ( characterBattlePaletteID != -1 )
    {
	//	无压缩人物调色板支持
		if(*(int *)characterBattlePalTable[characterBattlePaletteID].pal == -1)
			FE7JCPUFastSet((int)characterBattlePalTable[characterBattlePaletteID].pal + 4, BattleAnimationPaletteGroupBufferRightSide, 0x20 / 4);
		else
			if(*(u8 *)characterBattlePalTable[characterBattlePaletteID].pal == 0x10)
				FE7JLZ77UnCompWram(
					characterBattlePalTable[characterBattlePaletteID].pal,
					BattleAnimationPaletteGroupBufferRightSide);
			else
				FE7JCPUFastSet(characterBattlePalTable[characterBattlePaletteID].pal,BattleAnimationPaletteGroupBufferRightSide,0x20/4);
			
			  sub(8054798)(BattleAnimationPaletteGroupBufferRightSide, 1);
    }
    BattleAnimationPaletteRightSide = BattleAnimationPaletteGroupBufferRightSide + 16 * palSlotIDInPalGroup;
    FE7JCPUFastSet(BattleAnimationPaletteGroupBufferRightSide + 16 * palSlotIDInPalGroup, &OBJPaletteBuffer[144], 8u);
    FE7JCPUFastSet(*(void **)0x203E084, &OBJPaletteBuffer[160], 8u);
	
	// 第二调色板扩展
//	if(characterBattlePaletteID == 0x79-1)
	//	FE7JCPUFastSet(&PriscillaAnimationTest_PalA, &OBJPaletteBuffer[160], 8u);
	if(characterBattlePaletteID != -1)
	{
		if(characterBattlePaletteID < sizeof(characterBattleSecondPalTable)/sizeof(characterBattleSecondPalTable[0]) && characterBattleSecondPalTable[characterBattlePaletteID])
			FE7JCPUFastSet(characterBattleSecondPalTable[characterBattlePaletteID], &OBJPaletteBuffer[160], 8);
		else	// 直接扩展色板支持
			if(*(int *)characterBattlePalTable[characterBattlePaletteID].pal == -1)
				FE7JCPUFastSet((int)characterBattlePalTable[characterBattlePaletteID].pal + 4 + 0x20, &OBJPaletteBuffer[160], 8);
		// DEBUG("characterBattlePaletteID = %d",characterBattlePaletteID)
	}
	else
	{
		if(animationID < sizeof(battleAnimationSecondPalTable)/sizeof(battleAnimationSecondPalTable[0]) && battleAnimationSecondPalTable[animationID])
			FE7JCPUFastSet(battleAnimationSecondPalTable[animationID] + 16 * palSlotIDInPalGroup, &OBJPaletteBuffer[160], 8);
		else	// 直接扩展色板支持
			if(*(int *)animation_p->palGroup == -1)
				FE7JCPUFastSet((int)animation_p->palGroup + 4 + 0x20 * 2 * palSlotIDInPalGroup + 0x20, &OBJPaletteBuffer[160], 8);
		// DEBUG("animationID = 0x%x",animationID)
	}
	
    EnablePaletteSync();
//    FE7JLZ77UnCompWram(animation->oamR2L, BattleAnimationOAMR2LBuffer);

/*
//	 无压缩data3支持
	if(*(u8 *)(animation->oamR2L) == 0x10)
		FE7JLZ77UnCompWram(animation->oamR2L, BattleAnimationOAMR2LBuffer);
	else
	{
		((u32 *)BattleAnimationOAMR2LBuffer)[0] = 'l' + ('a' << 8) + ('q' << 16);
		((void **)BattleAnimationOAMR2LBuffer)[1] = animation->oamR2L;
	}
*/
	//	 无压缩data3支持
		if(*(u8 *)(animation->oamR2L) == 0x10)
			FE7JLZ77UnCompWram(animation->oamR2L, BattleAnimationOAMR2LBuffer);
		else
			//	不要拷贝到RAM里的无压缩格式(头部4字节:字符串'laq',大小固定,以01000000 00000000 00000000 00000000结尾,总计0x5800+4字节)
			if(*(u32 *)(animation->oamR2L) == 'l' + ('a' << 8) + ('q' << 16))
			{
				((u32 *)BattleAnimationOAMR2LBuffer)[0] = 'l' + ('a' << 8) + ('q' << 16);
				((void **)BattleAnimationOAMR2LBuffer)[1] = (u32 *)animation->oamR2L+1;
			}
			//	需要拷贝到RAM里的无压缩格式(无头部,大小不定,以连续12个0xFF结尾,节约空间)
			else
			{
				/*
				int *p = animation->oamR2L;
				int *q = BattleAnimationOAMR2LBuffer;
				for(int i=0;;i++)
				{
					if(p[i] == -1 && p[i+1] == -1 && p[i+2] == -1)
						break;
					q[i] = p[i];
				}
				*/
				
				for(int i=0;i<0x5800/4;i++)
				{
					if(((int *)animation->oamR2L)[i] == -1 && ((int *)animation->oamR2L)[i+1] == -1 && ((int *)animation->oamR2L)[i+2] == -1)
						break;
					((int *)BattleAnimationOAMR2LBuffer)[i] = ((int *)animation->oamR2L)[i];
				}	
				
//				FE7JCPUFastSet(animation->oamR2L, BattleAnimationOAMR2LBuffer, 0x57f0/4);
			}
	
    *(u32 *)0x200F1B8 = 1;	// 在OAM信息缓存(大小0x5800字节)的最后一行加01000000 00000000 00000000 00000000(标识一个Frame的结束?)
  }
  if ( *(u32 *)0x203E078 )
  {
//    *(u16 **)0x203E080 = (char *)(FE7BattleAnimationBank->palGroup)
	animationID_PalGroup = sub(8053040)(*(u32 *)0x203E078, *(u32 *)(*(u32 *)(*(u32 *)0x203E078 + 4) + 52), 0, &v12);
	*(u16 **)0x203E080 = battleAnimationBank[animationID_PalGroup>>8][0xFF & animationID_PalGroup].palGroup;
//                           + (32 * sub(8053040)(*(u32 *)0x203E078, *(u32 *)(*(u32 *)(*(u32 *)0x203E078 + 4) + 52), 0, &v12) & 0x1FFFFF);
    v10 = sub(8053A14)(*(u32 *)0x203E078);
    if ( v10 != -1 )
      *(u16 **)0x203E080 = characterBattlePalTable[v10].pal;
//    *(u16 **)0x203E084 = (char *)(FE7BattleAnimationBank->palGroup)
//                           + (32 * sub(8053040)(*(u32 *)0x203E07C, *(u32 *)(*(u32 *)(*(u32 *)0x203E07C + 4) + 52), 0, &v12) & 0x1FFFFF);
	animationID_PalGroup = sub(8053040)(*(u32 *)0x203E07C, *(u32 *)(*(u32 *)(*(u32 *)0x203E07C + 4) + 52), 0, &v12);
	*(u16 **)0x203E084 = battleAnimationBank[animationID_PalGroup>>8][0xFF & animationID_PalGroup].palGroup;
	v11 = sub(8053A14)(*(u32 *)0x203E07C);
    if ( v11 != -1 )
      *(u16 **)0x203E084 = characterBattlePalTable[v11].pal;
  }

  // 第二调色板扩展
  /*
  if(CharaterBattleAnimationPaletteIDRightSide == 0x79-1)
  	*(u16 **)0x203E084 = &PriscillaAnimationTest_PalA;  
  if(CharaterBattleAnimationPaletteIDLeftSide == 0x79-1)
  	*(u16 **)0x203E080 = &PriscillaAnimationTest_PalA;
  */
}


__attribute__((section(".callBattleAnimationInit")))
void callBattleAnimationInit()
{
	battleAnimationInit();
}

// 扩展后的UnitKakudai1
void UnitKakudai1Ex(struct context *ctx)
{
  int mode; // r6@1
  char *v3; // r1@5
  void *v4; // r0@5
  char *v5; // r1@7
  void *v6; // r0@7
  short v7; // r5@12
  short v8; // r3@12

  mode = ((u32 *)0x81DE1E0)[*((u8 *)0x81DE208 + *(u16 *)0x203E004)] & 0xFF;
  battleAnimationInit();
  if ( !*(u32 *)&ctx->userSpace[27] && *(u16 *)0x203A3D4 & 0x40 )
    sub(806788C)(BGPaletteBuffer, 23, 1);
  if ( IfBattleAnimationIsAtTheLeftSide == 1 )
  {
//    v3 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[mode];

//	无压缩data2支持
	if(BattleAnimationEventBufferLeftSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v3 = (char *)BattleAnimationEventBufferLeftSide[1] + BattleAnimationSectionInfoLeftSide[mode];
	else
		v3 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[mode];
	
//    v4 = (void *)*((u32 *)v3 + 1);
	v4 = *((void **)v3 + 1);
//    *(u32 *)&ctx->userSpace[43] = (char *)BattleAnimationOAML2RBuffer + *((u32 *)v3 + 2);

// 无压缩data4支持
	if(*(u32 *)BattleAnimationOAML2RBuffer == 'l' + ('a'<<8) + ('q'<<16))
		*(u32 *)&ctx->userSpace[43] = *((char **)BattleAnimationOAML2RBuffer + 1) + *((u32 *)v3 + 2);
	else
		*(u32 *)&ctx->userSpace[43] = (char *)BattleAnimationOAML2RBuffer + *((u32 *)v3 + 2);
	
//    FE7JLZ77UnCompWram(v4, 0x2000088);	
// 无压缩sheet支持
	if(*(u32 *)v4 == 0x200010)
    	FE7JLZ77UnCompWram(v4, 0x2000088);
	else
		FE7JCPUFastSet(v4, 0x2000088, 0x2000/4);
	
  }
  if ( IfBattleAnimationIsAtTheRightSide == 1 )
  {
//    v5 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[mode];

//	无压缩data2支持
	if(BattleAnimationEventBufferRightSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v5 = (char *)BattleAnimationEventBufferRightSide[1] + BattleAnimationSectionInfoRightSide[mode];
	else
		v5 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[mode];
	
    v6 = *((void **)v5 + 1);
//    *(u32 *)&ctx->userSpace[47] = (char *)BattleAnimationOAMR2LBuffer + *((u32 *)v5 + 2);

// 无压缩data3支持
	if(*(u32 *)BattleAnimationOAMR2LBuffer == 'l' + ('a'<<8) + ('q'<<16))
		*(u32 *)&ctx->userSpace[47] = *((char **)BattleAnimationOAMR2LBuffer + 1) + *((u32 *)v5 + 2);
	else
		*(u32 *)&ctx->userSpace[47] = (char *)BattleAnimationOAMR2LBuffer + *((u32 *)v5 + 2);

//	FE7JLZ77UnCompWram(v6, 0x2002088);	
// 无压缩sheet支持
	if(*(u32 *)v6 == 0x200010)
    	FE7JLZ77UnCompWram(v6, 0x2002088);
	else
		FE7JCPUFastSet(v6, 0x2002088, 0x2000/4);
		
  }
  if ( *(u32 *)0x203E088 )
  {
//    FE7JLZ77UnCompWram(*(void **)0x203E088, 0x2001088);	

// 无压缩sheet支持(?)
	if(**(u32 **)0x203E088 == 0x200010)
    	FE7JLZ77UnCompWram(*(void **)0x203E088, 0x2001088);
	else
		FE7JCPUFastSet(*(void **)0x203E088, 0x2001088, 0x2000/4);
  }

  if ( *(u32 *)0x203E08C )
  {
//    FE7JLZ77UnCompWram(*(void **)0x203E08C, 0x2003088);	

// 无压缩sheet支持(?)
	if(**(u32 **)0x203E08C == 0x200010)
    	FE7JLZ77UnCompWram(*(void **)0x203E08C, 0x2003088);
	else
		FE7JCPUFastSet(*(void **)0x203E08C, 0x2003088, 0x2000/4);
  }
	
//  TileTransferInfoAdd(*(void **)0x2000088, (void *)0x6014000, 0x4000);
	TileTransferInfoAdd(0x2000088, (void *)0x6014000, 0x4000);
  *(u16 *)&ctx->userSpace[3] = 0;
  *(u16 *)&ctx->userSpace[5] = 11;
  *(u16 *)&ctx->userSpace[9] = 16 * *(u16 *)0x203E006 + 8;
  *(u16 *)&ctx->userSpace[17] = 16 * *(u16 *)0x203E008 + 8;
  *(u16 *)&ctx->userSpace[11] = 16 * *(u16 *)0x203E00A + 8;
  *(u16 *)&ctx->userSpace[19] = 16 * *(u16 *)0x203E00C + 8;
  v7 = ((unsigned char *)0x81DE20D)[*(u16 *)0x203E004];
  *(u16 *)&ctx->userSpace[13] = v7;
  v8 = ((unsigned char *)0x81DE212)[*(u16 *)0x203E004];
  *(u16 *)&ctx->userSpace[15] = v8;
  if ( *(u32 *)0x2017744 )
    *(u16 *)&ctx->userSpace[13] = v7 - *(*(u16 **)0x81DE218 + *(u16 *)0x203E004);
  else
    *(u16 *)&ctx->userSpace[15] = *(*(u16 **)0x81DE218 + *(u16 *)0x203E004) + v8;
  breakLoop(ctx);
}

/*
// 处理所有动画脚本
void battleAnimationScriptProc()
{
	signed int flag; // r5@1
	AnimationInterpreter *AIS; // r4@2
	u16 currentState; // r1@4
	int delayCount; // r1@6

	flag = 0;
	if ( RootAIS )
	{
		for ( AIS = (AnimationInterpreter *)RootAIS; ; AIS = AIS->child )
		{
			currentState = AIS->state;
			if ( AIS->state )
			{
				if ( currentState & 8 )
					goto label_8;
				delayCount = AIS->delayCountdown;
				if ( !AIS->delayCountdown || (AIS->delayCountdown = delayCount - 1, !((delayCount - 1) << 16)) )
				{
					do
					{
						if ( BattleAnimationScriptHandler(AIS) == 1 )
							flag = 1;
					}
					while ( !AIS->delayCountdown );
				}
				currentState = AIS->state;
				if ( AIS->state )
				{
label_8:
					if ( !(currentState & 2) )
						BattleAnimationOAMInfoHandler2(AIS);
					if ( !AIS->child )
						break;
				}
			}
		}
		if ( flag == 1 )
			ForAllAIS();
	}
}
*/

/*	动画脚本事件指令解析:
	4字节为一个单位,bit31-0
	(1) bit31 = 1
		①	bit30 = 0
			bit29-24 : 指令分类号CmdType
			(a) CmdType = 0	[0x80000000]
			结束当前动画模式的事件序列(用作模式之间的分隔符)
			(b) CmdType = 1	[0x81000000]
			暂停动画?
			(c) CmdType = 2	[0x82000000]
			移动当前处理指针到上个位置?
			(d) CmdType = 3	[0x8300YYXX]
			偏移屏幕
			bit7-0 : 横向(水平)偏移 [XX]
			bit15-8 : 纵向(垂直)偏移 [YY]
			(e) CmdType = 4	[0x8400XXXX]
			设置延迟帧数
			bit15-0 : 延迟帧数 [XXXX]
			(f) CmdType = 5	[0x850000XX]
			触发各种事件
			bit7-0 : 事件号 [XX] (会先被缓存在一个buffer里,以便之后在battleAnimationEventHandler里继续进一步处理)
			根据事件号区分是否需要停滞处理
			会停滞当前解析进程的事件有:
				0x18 Use this instead of 0x02 to dodge toward the foreground instead of toward the background
				0x39 Pauses the attacker, makes them flash white and makes the screen flash white
					Essentially makes it look as though the attacker was hit, but without blue sparks
				0x2D ? (Assassin critical) (Lethality activator that is dependent on other commands?)
				0x52 See command 0x2D
				0x13 ? (ranged attack - hand axe for Hector)
				0x01 Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
					(should be used even in missed attack) (should end standing animations)
				0x02 Start of dodge
				0x03 Start attack animation; should be followed by 0x07; should head "dodged attack"
					(melee that will miss)
				0x04 Prepare HP depletion routine; needed to animate return to standing frame after hit
				0x05 Call spell associated with equipped weapon
			(g) CmdType = 6	[0x86XXYYYY,&sheet,section offset]
			显示精灵组
			bit23-16 : 帧编号 [XX]
			bit15-0 : 显示帧数 [YYYY]
			下一个4字节是指向sheet的指针
			再下一个4字节是要显示的精灵组的OAM信息在data3/4中的偏移地址
			(h) CmdType = 7	[0x870000XX] (扩展)
			执行函数指针表数组中的某一个函数(扩展事件)
			bit7-0 : 事件号 [XX]
			(i) CmdType = 8/9 [0x8XXXXXXX] (扩展)
			更换精灵色板
			bit27-0 : 色板地址 [XXXXXXX]
			(j) CmdType = 0xA [0x8ANNXXXX] (扩展)
			载入BG图片
			bit23-16 : BGn (0-3) [NN]
			bit15-0 : 图片序号 [XXXX] 用一个结构体数组存储每张图的图片数据,调色板和TSA
		②	bit30 = 1
			(a) bit29 = 0
				(i) bit28 = 0 [0xC000000000 + function pointer]
				调用外部函数(第一个参数是AIS指针，第二个参数是0?(不存在这个参数?))
				bit27-0: 函数指针
				(ii) bit28 = 1 [0xD0000000 + &Cmd]
				置指向当前位置和上个位置的指针
				bit27-0: 指向指令的指针
			(b) bit29 = 1
	(2) bit31 = 0
		置当前OAM信息指针且设置延迟帧数
		bit27-2 : 指向OAMInfo的指针(最低两位为0，即4字节对齐)
		bit30-28,1-0 : 延迟帧数(3位+2位构成总共5位)

*/

// 处理单个动画脚本
int BattleAnimationScriptHandler(AnimationInterpreter *AIS)
{
	bool flag; // r4@1
	u32 *pCmd; // r0@1
	unsigned int Cmd; // r3@1
	int v5; // r1@4
	unsigned int CmdType; // r1@9
	__int16 v7; // r0@11
	signed __int16 v8; // r1@11
	u32 *pSheet; // r0@28
	void *sheet; // r1@28
	u32 frameSection; // r1@28
	int v12; // r0@2
	int n;

	flag = 0;
	pCmd = AIS->nextCmd;
	Cmd = *pCmd;
	AIS->nextCmd = pCmd + 1;
	if ( (Cmd & 0x80000000) != 0 )
	{
		if ( !(Cmd & 0x40000000) )
		{
			CmdType = (Cmd >> 24) & 0x3F;
			// if ( CmdType > 6 )
			if ( CmdType > 0xA )
				return flag;
			switch ( CmdType )
			{
				case 0u:
					--AIS->nextCmd;
					AIS->delayCountdown = 1;
					v7 = AIS->unk_C & 0xFFF;
					v8 = 0x4000;
					goto LABEL_29;
				case 1u:
					AIS->state = 0;
					AIS->delayCountdown = 1;
					return 1;
				case 2u:
					AIS->nextCmd = AIS->lastCmd;
					LOWORD(v12) = 1;
					goto LABEL_30;
				case 4u:
					AIS->delayCountdown = Cmd;
					return flag;
				case 3u:
					AIS->XOffset += (char)Cmd;
					AIS->YOffset += (signed int)(Cmd << 16) >> 24;
					v12 = (Cmd >> 16) & 0xFF;
					goto LABEL_30;
				case 5u:
					AIS->unk_C = AIS->unk_C & 0xFFF | 0x1000;
					AIS->C85IDBuffer[AIS->C85IDBufferIndex++] = Cmd;
					AIS->delayCountdown = 1;
					if ( (unsigned __int8)Cmd == 0x18 )
						goto LABEL_27;
					if ( (unsigned __int8)Cmd > 0x18u )
					{
						if ( (unsigned __int8)Cmd != 0x39 )
						{
							if ( (unsigned __int8)Cmd > 0x39u )
							{
								if ( (unsigned __int8)Cmd != 0x52 )
									return flag;
							}
							else if ( (unsigned __int8)Cmd != 0x2D )
							{
								return flag;
							}
						}
					}
					else if ( (unsigned __int8)Cmd < 1u || (unsigned __int8)Cmd > 5u && (unsigned __int8)Cmd != 0x13 )
					{
						return flag;
					}
LABEL_27:
					--AIS->nextCmd;
					return flag;
				case 6u:
					AIS->delayCountdown = Cmd;
					AIS->frameID = Cmd >> 16;
					pSheet = AIS->nextCmd;
					sheet = (void *)*pSheet;
					++pSheet;
					AIS->sheet = sheet;
					AIS->nextCmd = pSheet;
					frameSection = *pSheet;
					AIS->nextCmd = pSheet + 1;
					AIS->currentOAMInfo = (char *)AIS->OAMInfoBuffer + frameSection;
					v7 = AIS->unk_C & 0xFFF;
					v8 = 0x2000;
LABEL_29:
					AIS->unk_C = v7 | v8;
					return flag;
				case 7u:
					BattleAnimationEventEX[Cmd&0xFF](AIS);
					return flag;
				case 8u:
				case 9u:
					if(isUnitAtRightOrLeft(AIS))
						FE7JCPUFastSet(Cmd&0x9FFFFFC,&OBJPaletteBuffer[144],16);
					else
						FE7JCPUFastSet(Cmd&0x9FFFFFC,&OBJPaletteBuffer[112],16);
					EnablePaletteSync();
					/*
					if(isUnitAtRightOrLeft(AIS))
						FE7JCPUFastSet(Cmd&0x9FFFFFC,OBJ_PLTT + 32 * 9,16);
					else
						FE7JCPUFastSet(Cmd&0x9FFFFFC,OBJ_PLTT + 32 * 7,16);
					*/
					// FE7JCPUFastSet(OBJ_PLTT + 32 * 9,OBJ_PLTT + 32 * 9,16); // 不做点什么"有意义"的事情就直接返回的话会死机,莫名其妙
					return flag;
				case 0xA:
					n = (Cmd>>16)&0xFF;
					// Set Character Base Block
					BGnCNTBuffer(n) = BGnCNTBuffer(n) & (~(3<<2)) | (2<<2);
					if(Cmd&0xFFFF == 0)
						{
							// 清第一个tile的图像数据
							int zero = 0;
							FE7JCPUFastSet(&zero,0x6008000,(1<<24)|((8*8/2)/4));
							// 清整张map
							// Set BG Map Buffer
							memClear2K(BGnMapBuffer(n),0);
							// Enable Buffer Sync
							EnableBGMapSync(n);
						}
					else
						{
							BGImage image = C8ABGBank[Cmd&0xFFFF];
							// 图像,色板,TSA都压缩
							FE7JLZ77UnCompVram(image.img, 0x6008000);
							FE7JLZ77UnCompWram(image.pal, &BGPaletteBuffer[16*6]);
							EnableBGPaletteSync();
							FE7JLZ77UnCompWram(image.tsa, BGnMapBuffer(n));
							for(int i = 0; i < 0x800/4; i++)
							{
								*((u32 *)BGnMapBuffer(n) + i) |= (6<<12) * 0x10001;
								if(!isUnitAtRightOrLeft(AIS))
									*((u32 *)BGnMapBuffer(n) + i) |= (1<<10) * 0x10001;
							}
							if(!isUnitAtRightOrLeft(AIS))
							{
								for(int i = 0; i < 32; i++)
									for(int j = 0; j < 15; j++)
										// swap(((u16 **)BG3MapBuffer)[i][j],((u16 **)BG3MapBuffer)[i][31-j]);
										// swap_u16(((u16 **)BG3MapBuffer+32*i)+j,((u16 **)BG3MapBuffer+32*i)+31-j);
										swap_u16(BGnMapBuffer(n)+32*i+j,BGnMapBuffer(n)+32*i+31-j);
							}
							EnableBGMapSync(n);
						}
					return flag;
				default:
					return flag;
			}
		}
		v5 = (Cmd >> 28) & 3;
		if ( v5 )
		{
			if ( v5 == 1 )
			{
				AIS->lastCmd = (u32 *)(Cmd & 0xFFFFFFF);
				AIS->nextCmd = (u32 *)(Cmd & 0xFFFFFFF);
				AIS->delayCountdown = 1;
			}
		}
		else
		{
		//	call_via_r3((int)AIS, 0, (int)AIS, (int (*)(void))(Cmd & 0xFFFFFFF));
			((void (*)(AnimationInterpreter *))(Cmd & 0xFFFFFFF))(AIS);
		}
	}
	else
	{
		AIS->currentOAMInfo = (void *)(Cmd & 0xFFFFFFC);
		LOWORD(v12) = ((Cmd >> 26) & 0x1C) + (Cmd & 3);
LABEL_30:
		AIS->delayCountdown = v12;
	}
	return flag;
}

__attribute__((section(".callBattleAnimationScriptHandler")))
int callBattleAnimationScriptHandler(AnimationInterpreter *AIS)
{
	return BattleAnimationScriptHandler(AIS);
}

/*
// 处理动画事件(扩展)
void battleAnimationEventHandlerEx()
{
  int v0; // r2@1
  int v1; // r7@2
  unsigned int v2; // r9@2
  signed int v3; // r8@3
  int v4; // r0@5
  unsigned int v5; // r1@6
  int v6; // r0@9
  __int16 v7; // r1@10
  int v8; // r0@13
  signed __int16 v9; // r1@15
  signed __int16 v10; // r0@16
  __int16 v11; // r1@17
  __int16 v12; // r1@20
  __int16 v13; // r1@21
  __int16 v14; // r2@23
  signed int v15; // r0@24
  int v16; // r4@24
  int v17; // r0@27
  __int16 v18; // r1@28
  __int16 v19; // r2@30
  int v20; // r0@32
  int v21; // r0@34
  __int16 v22; // r0@38
  signed int v23; // r0@38
  int v24; // r2@38
  __int16 v25; // r0@39
  bool v26; // r0@40
  int v27; // r0@46
  int v28; // r6@47
  unsigned int v29; // r0@47
  int v30; // r4@50
  int **v31; // r0@51
  int v32; // r4@53
  char *v33; // r1@53
  bool v34; // r0@53
  int v35; // r2@53
  bool v36; // r0@54
  bool v37; // r0@55
  __int16 v38; // r2@59
  __int16 v39; // r0@62
  __int16 v40; // r1@67
  int v41; // r0@70
  int v42; // r2@70
  int v43; // ST00_4@71
  __int16 v44; // r0@71
  int v45; // r0@71
  bool v46; // r0@73
  bool v47; // r0@82
  __int16 v48; // r1@99
  bool v49; // r0@109
  int v50; // r8@131
  int *v51; // r6@132
  signed __int16 v52; // r4@132
  bool v53; // r0@133
  bool v54; // r0@133
  int v55; // r6@137
  bool v56; // r0@139
  int a1; // [sp+0h] [bp-20h]@24
//  int a1a; // [sp+0h] [bp-20h]@35
//  int a1b; // [sp+0h] [bp-20h]@38
//  int a1c; // [sp+0h] [bp-20h]@47
//  int a1d; // [sp+0h] [bp-20h]@72
//  int a1e; // [sp+0h] [bp-20h]@132

  v0 = 0;
  do
  {
    *(u32 *)0x3004750 = v0;
    v1 = ((u32 *)0x2000000)[v0];
    v2 = v0 + 1;
    if ( v1 )
    {
//      LOWORD(v3) = *(_WORD *)(v1 + 12) & 0xF000;
//	  v3 = *(_WORD *)(v1 + 12) & 0xF000 | (v3 & 0xFFFF0000);
	  v3 = *(_WORD *)(v1 + 12) & 0xF000;
      if ( (_WORD)v3 )
      {
        if ( *(_WORD *)(v1 + 12) & 0x1000 )
        {
          while ( 1 )
          {
            v4 = *(_BYTE *)(v1 + 20);
            if ( !*(_BYTE *)(v1 + 20) )
              break;
            v5 = *(_BYTE *)(v1 + 21 + v4 - 1);
            if ( v5 <= 0x52 )
            {
              switch ( v5 )
              {
                case 1u:
                  if ( *(u32 *)0x2000024 == 1 )
                  {
                    v6 = *(_DWORD *)(v1 + 36);
                    goto LABEL_118;
                  }
                  v7 = *(_WORD *)(v1 + 16);
                  if ( !(v7 & 4) )
                    goto LABEL_117;
                  if ( v7 & 8 && sub(804DD50)() == 1 )
                  {
                    *(_WORD *)(v1 + 16) &= 0xFFF2u;
                    v8 = *(_DWORD *)(v1 + 32) + 4;
                    *(_DWORD *)(v1 + 32) = v8;
                    if ( sub(8050FE4)(v8) )
                      sub(8050FF0)(0);
                  }
                  break;
                case 2u:
                  v9 = *(_WORD *)(v1 + 16);
                  if ( !(v9 & 1) )
                    break;
                  v10 = -2;
                  goto LABEL_115;
                case 3u:
                  v11 = *(_WORD *)(v1 + 16);
                  if ( !(v11 & 0x20) )
                  {
                    *(_WORD *)(v1 + 16) = v11 | 0x20;
                    if ( !sub(8054E4C)(v1) )
                      sub(8063B64)(v1);
                  }
                  goto LABEL_20;
                case 4u:
                  v13 = *(_WORD *)(v1 + 16);
                  if ( !(v13 & 0x20) )
                    *(_WORD *)(v1 + 16) = v13 | 0x60;
                  v14 = *(_WORD *)(v1 + 16);
                  if ( !(v14 & 0x40) )
                    break;
                  *(_DWORD *)(v1 + 32) += 4;
                  *(_WORD *)(v1 + 16) = v14 & 0xFF9F | 9;
                  a1 = sub(8054F90)(v1);
                  v15 = sub(8054FEC)(v1) << 16;
                  v3 = v15 >> 16;
                  v16 = v15 >> 16;
                  if ( sub(8054E74)(v15 >> 16) != 1 )
                    break;
                  if ( !a1 )
                    break;
                  *(_WORD *)(a1 + 16) |= 9u;
                  if ( sub(8054E4C)(v1) )
                    break;
                  v17 = v16;
                  goto LABEL_46;
                case 5u:
                  v18 = *(_WORD *)(v1 + 16);
                  if ( !(v18 & 0x20) )
                    *(_WORD *)(v1 + 16) = v18 | 0x60;
                  v19 = *(_WORD *)(v1 + 16);
                  if ( v19 & 0x40 )
                  {
                    *(_DWORD *)(v1 + 32) += 4;
                    *(_WORD *)(v1 + 16) = v19 & 0xFF9F | 9;
                    if ( !sub(8054E4C)(v1) )
                    {
                      v20 = sub(8056070)(v1);
                      if ( sub(8050FE4)(v20) )
                        sub(8050FF0)(2);
                    }
                  }
                  break;
                case 6u:
                  v21 = sub(8054F90)(v1);
                  if ( v21 )
                  {
                    a1a = v21;
                    v3 = (signed __int16)sub(8055010)();
                    if ( v3 != -1 )
                      *(_WORD *)(a1a + 16) |= 2u;
                  }
                  break;
                case 8u:
                case 9u:
                case 0xAu:
                case 0xBu:
                case 0xCu:
                  if ( !sub(8054E4C)(v1) )
                  {
                    a1b = sub(8054F90)(v1);
                    v22 = sub(8054FEC)(v1);
//                    LOWORD(v3) = v22;
//					v3 = (v22 & 0xFFFF) | (v3 & 0xFFFF0000);
					v3 = v22;
                    v23 = sub(8054E74)(v22);
                    v24 = a1b;
                    if ( !v23 )
                    {
                      v25 = sub(80684B0)(a1b);
                      v24 = a1b;
                      if ( v25 != 2 )
                      {
                        v26 = sub(8054E60)(v1);
                        if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v26) & 0x1000 )
                          sub(80641B0)(a1b);
                        else
                          criticalEffect(a1b);
                        v24 = a1b;
                      }
                    }
                    if ( v24 )
                    {
                      *(_WORD *)(v24 + 16) |= 9u;
                      a1 = v24;
                      v17 = (signed __int16)sub(8054FEC)(v1);
//                      LOWORD(v3) = v17;
//					  v3 = (v17 & 0xFFFF) | (v3 & 0xFFFF0000);
					  v3 = v17;
LABEL_46:
                      v27 = sub(8054E74)(v17);
                      reduceHPBar(a1, v27);
                    }
                  }
                  break;
                case 0xDu:
                  v3 = (signed __int16)sub(8054FCC)(v1);
                  a1c = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
                  v28 = ((u32 *)0x2000000)[2 * sub(8054E60)(v1) + 1];
                  v29 = *(_BYTE *)(v1 + 18);
                  if ( v29 > 9 )
                    break;
                  switch ( v29 )
                  {
                    case 0u:
                    case 1u:
                    case 2u:
                    case 3u:
                    case 9u:
                      if ( v3 == -1 )
                        goto LABEL_56;
                      ++*(_WORD *)(a1c + 14);
                      ++*(_WORD *)(v28 + 14);
                      sub(8054D7C)(a1c, v3);
                      sub(8054D7C)(v28, v3);
                      *(_WORD *)(a1c + 16) |= 4u;
                      *(_WORD *)(v28 + 16) |= 4u;
                      v3 = *((_BYTE *)0x81DE208 + *(u16 *)0x203E004);
//                      v30 = LOBYTE(((u32 *)0x81DE1E0)[v3]);
					  v30 = ((u32 *)0x81DE1E0)[v3] & 0xFF;
                      if ( sub(8054E60)(v1) )
//                        v31 = &BattleAnimationSectionInfoRightSide;
						v31 = 0x2000060;
                      else
//                        v31 = &BattleAnimationSectionInfoLeftSide;
					  	v31 = 0x200005C;
                      v32 = (*v31)[v30];
                      v33 = (char *)BattleAnimationEventBufferLeftSide + 0x2A00 * sub(8054E60)(v1) + v32;
                      *(_DWORD *)(a1c + 40) = *((_DWORD *)v33 + 1);
                      *(_DWORD *)(a1c + 60) = *(_DWORD *)(a1c + 48) + *((_DWORD *)v33 + 2);
                      *(_DWORD *)(v28 + 60) = *(_DWORD *)(v28 + 48) + 0x57F0;
                      v34 = sub(8054E60)(v1);
                      v35 = a1c;
                      if ( !((u32 *)0x203E088)[v34] )
                      {
                        v36 = sub(8054E60)(a1c);
                        v35 = a1c;
                        if ( ((u32 *)0x201FB10)[v36] != *(_DWORD *)(a1c + 40) )
                        {
                          sub(8054734)(a1c);
                          v37 = sub(8054E60)(a1c);
                          v35 = a1c;
                          ((u32 *)0x201FB10)[v37] = *(_DWORD *)(a1c + 40);
                        }
                      }
                      goto LABEL_58;
                    case 4u:
                    case 5u:
LABEL_56:
                      v3 = *((_BYTE *)0x81DE208 + *(u16 *)0x203E004);
                      break;
                    case 6u:
                    case 7u:
                    case 8u:
                      break;
                    default:
                      goto def_8054080;
                  }
                  sub(8054D7C)(a1c, v3);
                  sub(8054D7C)(v28, v3);
                  v35 = a1c;
LABEL_58:
                  sub(80546F0)(v35);
                  sub(80546F0)(v28);
                  goto LABEL_120;
                case 0x13u:
                  v38 = *(_WORD *)(v1 + 16);
                  if ( !(v38 & 0x20) )
                  {
                    *(_WORD *)(v1 + 16) = v38 | 0x20;
                    break;
                  }
                  if ( *(u32 *)0x2017758 != 1 )
                    break;
                  *(u32 *)0x2017758 = 0;
                  v39 = v38 & 0xFFDF;
                  goto LABEL_116;
                case 0x14u:
                  if ( !sub(8054E4C)(v1) )
                    sub(804EFE0)(3);
                  break;
                case 0x15u:
                  if ( !sub(8054E4C)(v1) )
                    sub(804EFE0)(0);
                  break;
                case 0x18u:
                  v40 = *(_WORD *)(v1 + 16);
                  if ( v40 & 1 )
                  {
                    *(_WORD *)(v1 + 16) = v40 & 0xFFFE;
                    *(_DWORD *)(v1 + 32) += 4;
                    *(_WORD *)(v1 + 8) = *(_WORD *)(v1 + 8) & 0xF3FF | 0x400;
                    *(_WORD *)(v1 + 10) = 140;
                    sub(8006488)(140);
                  }
                  break;
                case 0x1Au:
                  if ( !sub(8054E4C)(v1) )
                  {
                    v41 = sub(8054F90)(v1);
                    v42 = v41;
                    if ( v41 )
                    {
                      *(_WORD *)(v41 + 16) |= 9u;
                      v43 = v41;
                      v44 = sub(8054FEC)(v1);
//                      LOWORD(v3) = v44;
//					  v3 = (v3 & 0xFFFF0000) | (v44 & 0xFFFF);
					  v3 = v44;
                      v45 = sub(8054E74)(v44);
                      reduceHPBar(v43, v45);
                      v42 = v43;
                    }
                    a1d = v42;
                    if ( (signed __int16)sub(80684B0)(v42) != 2 )
                    {
                      v46 = sub(8054E60)(v1);
                      if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v46) & 0x1000 )
                        sub(80641B0)(a1d);
                      else
                        normalAttackEffect(v1);
                    }
                  }
                  break;
                case 0x26u:
                  if ( !sub(8054E4C)(v1) )
                    sub(8062FE0)(v1, 0);
                  break;
                case 0x27u:
                  if ( !sub(8054E4C)(v1) )
                    sub(8062FE0)(v1, 1);
                  break;
                case 0x2Cu:
                  if ( !sub(8054E4C)(v1) )
                    sub(80631B0)(v1);
                  break;
                case 0x2Du:
                  v47 = sub(8054E60)(v1);
                  if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v47) & 0x1000) )
                    goto LABEL_117;
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                    goto LABEL_113;
                  *(_WORD *)(v1 + 16) = v12 | 0x20;
                  if ( !sub(8054E4C)(v1) )
                    sub(8064330)(v1, 0);
                  break;
                case 0x2Eu:
                  if ( !sub(8054E4C)(v1) )
                    sub(8063400)(v1, 0);
                  break;
                case 0x2Fu:
                  if ( !sub(8054E4C)(v1) )
                    sub(8063400)(v1, 1);
                  break;
                case 0x30u:
                  if ( !sub(8054E4C)(v1) )
                    sub(80635B4)(v1, 0);
                  break;
                case 0x31u:
                  if ( !sub(8054E4C)(v1) )
                    sub(80635B4)(v1, 1);
                  break;
                case 0x32u:
                  if ( !sub(8054E4C)(v1) )
                    sub(80635B4)(v1, 2);
                  break;
                case 0x39u:
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                    goto LABEL_113;
                  *(_WORD *)(v1 + 16) = v12 | 0x20;
                  if ( !sub(8054E4C)(v1) )
                    sub(80638F0)(v1);
                  break;
                case 0x3Du:
                  v48 = *(_WORD *)(v1 + 16);
                  if ( !(v48 & 0x20) )
                  {
                    *(_WORD *)(v1 + 16) = v48 | 0x20;
                    if ( !sub(8054E4C)(v1) )
                      sub(8050FF0)(1);
                    sub(8064458)(v1);
                    sub(8050FFC)(v1);
                  }
LABEL_20:
                  v12 = *(_WORD *)(v1 + 16);
                  goto LABEL_113;
                case 0x47u:
                  sub(8063FBC)(v1);
                  break;
                case 0x4Eu:
                  sub(8063804)(v1);
                  break;
                case 0x19u:
                case 0x1Bu:
                case 0x1Cu:
                case 0x1Du:
                case 0x1Eu:
                case 0x1Fu:
                case 0x20u:
                case 0x21u:
                case 0x22u:
                case 0x23u:
                case 0x24u:
                case 0x25u:
                case 0x28u:
                case 0x29u:
                case 0x2Au:
                case 0x2Bu:
                case 0x33u:
                case 0x34u:
                case 0x35u:
                case 0x36u:
                case 0x37u:
                case 0x38u:
                case 0x3Au:
                case 0x3Bu:
                case 0x3Cu:
                case 0x3Eu:
                case 0x3Fu:
                case 0x40u:
                case 0x41u:
                case 0x42u:
                case 0x43u:
                case 0x44u:
                case 0x45u:
                case 0x46u:
                case 0x48u:
                case 0x49u:
                case 0x4Au:
                case 0x4Bu:
                case 0x4Cu:
                case 0x4Du:
                case 0x4Fu:
                  sub(8067F90)(v1, *(_BYTE *)(v1 + 21 + v4 - 1));
                  break;
                case 0x51u:
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                    goto LABEL_113;
                  *(_WORD *)(v1 + 16) = v12 | 0x20;
                  if ( !sub(8054E4C)(v1) )
                    sub(806397C)(v1);
                  break;
                case 0x52u:
                  v49 = sub(8054E60)(v1);
                  if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v49) & 0x1000) )
                    goto LABEL_117;
                  v12 = *(_WORD *)(v1 + 16);
                  if ( v12 & 0x20 )
                  {
LABEL_113:
                    if ( v12 & 0x40 )
                    {
                      v10 = v12 & 0xFFDF;
                      v9 = -65;
LABEL_115:
                      v39 = v10 & v9;
LABEL_116:
                      *(_WORD *)(v1 + 16) = v39;
LABEL_117:
                      v6 = *(_DWORD *)(v1 + 32) + 4;
LABEL_118:
                      *(_DWORD *)(v1 + 32) = v6;
                    }
                  }
                  else
                  {
                    *(_WORD *)(v1 + 16) = v12 | 0x20;
                    if ( !sub(8054E4C)(v1) )
                      sub(8064330)(v1, 1);
                  }
                  break;
                default:
                  break;
              }
            }
def_8054080:
            --*(_BYTE *)(v1 + 20);
          }
LABEL_120:
          *(_WORD *)(v1 + 12) &= 0xE700u;
        }
        if ( v3 & 0x2000 )
        {
          if ( !sub(8054E4C)(v1)
            && !((u32 *)0x203E088)[sub(8054E60)(v1)]
            && !(*(_WORD *)(v1 + 16) & 0x4000)
            && ((u32 *)0x201FB10)[sub(8054E60)(v1)] != *(_DWORD *)(v1 + 40) )
          {
            sub(8054764)(v1);
            ((u32 *)0x201FB10)[sub(8054E60)(v1)] = *(_DWORD *)(v1 + 40);
          }
          *(_WORD *)(v1 + 12) &= 0xD700u;
        }
        if ( v3 & 0x4000 || *(u32 *)0x2000024 == 1 )
        {
          if ( *(_WORD *)(v1 + 16) & 2 )
          {
            v50 = (signed __int16)sub(8054FCC)(v1);
            if ( v50 == -1 )
            {
              v53 = sub(8054E60)(v1);
              *(_WORD *)(((u32 *)0x2000000)[2 * v53] + 16) &= 0xFFFDu;
              v54 = sub(8054E60)(v1);
              *(_WORD *)(((u32 *)0x2000000)[2 * v54 + 1] + 16) &= 0xFFFDu;
              goto LABEL_141;
            }
            v51 = *(u32 *)0x2000000;
            a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
            sub(8054D7C)(a1e, v50);
            v52 = -3;
LABEL_137:
            *(_WORD *)(a1e + 16) = v52 & *(_WORD *)(a1e + 16) | 4;
            v55 = v51[2 * sub(8054E60)(v1) + 1];
            sub(8054D7C)(v55, v50);
            *(_WORD *)(v55 + 16) = v52 & *(_WORD *)(v55 + 16) | 4;
            ++*(_WORD *)(a1e + 14);
            ++*(_WORD *)(v55 + 14);
            sub(80546F0)(a1e);
            sub(80546F0)(v55);
            goto LABEL_141;
          }
          if ( *(_WORD *)(v1 + 16) & 0x8000 )
          {
            v50 = (signed __int16)sub(8054FCC)(v1);
            if ( v50 == -1 )
              goto LABEL_141;
            v51 = *(u32 *)0x2000000;
            a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
            sub(8054D7C)(a1e, v50);
            v52 = 0x7FFF;
            goto LABEL_137;
          }
          if ( !sub(8054E4C)(v1) )
          {
            v56 = sub(8054E60)(v1);
            if ( (signed __int16)sub(8053AD4)(2 * *(_WORD *)(v1 + 14) + v56) == -1 )
              ((u32 *)0x201FAF8)[sub(8054E60)(v1)] = 1;
          }
        }
      }
    }
LABEL_141:
    v0 = v2;
  }
  while ( v2 <= 3 );
}
*/

/*
// 处理动画事件
void battleAnimationEventHandlerEx()
{
	int v0; // r2@1
	int v1; // r7@2
	unsigned int v2; // r9@2
	signed int v3; // r8@3
	int v4; // r0@5
	unsigned int v5; // r1@6
	int v6; // r0@9
	__int16 v7; // r1@10
	signed __int16 v8; // r1@15
	signed __int16 v9; // r0@16
	__int16 v10; // r1@17
	__int16 v11; // r1@20
	__int16 v12; // r1@21
	__int16 v13; // r2@23
	signed int v14; // r0@24
	int v15; // r4@24
	int v16; // r0@27
	__int16 v17; // r1@28
	__int16 v18; // r2@30
	int v19; // r0@34
	__int16 v20; // r0@38
	signed int v21; // r0@38
	int v22; // r2@38
	__int16 v23; // r0@39
	bool v24; // r0@40
	int v25; // r0@46
	int v26; // r6@47
	unsigned int v27; // r0@47
	int v28; // r4@50
	int **v29; // r0@51
	int v30; // r4@53
	char *v31; // r1@53
	bool v32; // r0@53
	int v33; // r2@53
	bool v34; // r0@54
	bool v35; // r0@55
	__int16 v36; // r2@59
	__int16 v37; // r0@62
	__int16 v38; // r1@67
	int v39; // r0@70
	int v40; // r2@70
	int v41; // ST00_4@71
	__int16 v42; // r0@71
	int v43; // r0@71
	bool v44; // r0@73
	bool v45; // r0@82
	__int16 v46; // r1@99
	bool v47; // r0@109
	int v48; // r8@131
	int *v49; // r6@132
	signed __int16 v50; // r4@132
	bool v51; // r0@133
	bool v52; // r0@133
	int v53; // r6@137
	bool v54; // r0@139
	int a1; // [sp+0h] [bp-20h]@24
	int a1a; // [sp+0h] [bp-20h]@35
	int a1b; // [sp+0h] [bp-20h]@38
	int a1c; // [sp+0h] [bp-20h]@47
	int a1d; // [sp+0h] [bp-20h]@72
	int a1e; // [sp+0h] [bp-20h]@132

	v0 = 0;
	do
	{
		(*(u32 *)0x3004750) = v0;
		v1 = ((u32 *)0x2000000)[v0];
		v2 = v0 + 1;
		if ( v1 )
		{
			LOWORD(v3) = *(_WORD *)(v1 + 12) & 0xF000;
			if ( (_WORD)v3 )
			{
				if ( *(_WORD *)(v1 + 12) & 0x1000 )
				{
					while ( 1 )
					{
						v4 = *(_BYTE *)(v1 + 20);
						if ( !*(_BYTE *)(v1 + 20) )
							break;
						v5 = *(_BYTE *)(v1 + 21 + v4 - 1);
						if ( v5 <= 0x52 )
						{
							switch ( v5 )
							{
								case 1u:
									if ( (*(u32 *)0x2000024) == 1 )
									{
										v6 = *(_DWORD *)(v1 + 36);
										goto LABEL_118;
									}
									v7 = *(_WORD *)(v1 + 16);
									if ( !(v7 & 4) )
										goto LABEL_117;
									if ( v7 & 8 && sub(804DD50)() == 1 )
									{
										*(_WORD *)(v1 + 16) &= 0xFFF2u;
										*(_DWORD *)(v1 + 32) += 4;
										if ( sub(8050FE4)() )
											sub(8050FF0)(0);
									}
									break;
								case 2u:
									v8 = *(_WORD *)(v1 + 16);
									if ( !(v8 & 1) )
										break;
									v9 = -2;
									goto LABEL_115;
								case 3u:
									v10 = *(_WORD *)(v1 + 16);
									if ( !(v10 & 0x20) )
									{
										*(_WORD *)(v1 + 16) = v10 | 0x20;
										if ( !sub(8054E4C)(v1) )
											sub(8063B64)(v1);
									}
									goto LABEL_20;
								case 4u:
									v12 = *(_WORD *)(v1 + 16);
									if ( !(v12 & 0x20) )
										*(_WORD *)(v1 + 16) = v12 | 0x60;
									v13 = *(_WORD *)(v1 + 16);
									if ( !(v13 & 0x40) )
										break;
									*(_DWORD *)(v1 + 32) += 4;
									*(_WORD *)(v1 + 16) = v13 & 0xFF9F | 9;
									a1 = sub(8054F90)(v1);
									v14 = sub(8054FEC)(v1) << 16;
									v3 = v14 >> 16;
									v15 = v14 >> 16;
									if ( sub(8054E74)(v14 >> 16) != 1 )
										break;
									if ( !a1 )
										break;
									*(_WORD *)(a1 + 16) |= 9u;
									if ( sub(8054E4C)(v1) )
										break;
									v16 = v15;
									goto LABEL_46;
								case 5u:
									v17 = *(_WORD *)(v1 + 16);
									if ( !(v17 & 0x20) )
										*(_WORD *)(v1 + 16) = v17 | 0x60;
									v18 = *(_WORD *)(v1 + 16);
									if ( v18 & 0x40 )
									{
										*(_DWORD *)(v1 + 32) += 4;
										*(_WORD *)(v1 + 16) = v18 & 0xFF9F | 9;
										if ( !sub(8054E4C)(v1) )
										{
											sub(8056070)(v1);
											if ( sub(8050FE4)() )
												sub(8050FF0)(2);
										}
									}
									break;
								case 6u:
									v19 = sub(8054F90)(v1);
									if ( v19 )
									{
										a1a = v19;
										v3 = (signed __int16)sub(8055010)();
										if ( v3 != -1 )
											*(_WORD *)(a1a + 16) |= 2u;
									}
									break;
								case 8u:
								case 9u:
								case 0xAu:
								case 0xBu:
								case 0xCu:
									if ( !sub(8054E4C)(v1) )
									{
										a1b = sub(8054F90)(v1);
										v20 = sub(8054FEC)(v1);
										LOWORD(v3) = v20;
										v21 = sub(8054E74)(v20);
										v22 = a1b;
										if ( !v21 )
										{
											v23 = sub(80684B0)(a1b);
											v22 = a1b;
											if ( v23 != 2 )
											{
												v24 = sub(8054E60)(v1);
												if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v24) & 0x1000 )
													sub(80641B0)(a1b);
												else
													criticalEffect(a1b);
												v22 = a1b;
											}
										}
										if ( v22 )
										{
											*(_WORD *)(v22 + 16) |= 9u;
											a1 = v22;
											v16 = (signed __int16)sub(8054FEC)(v1);
											LOWORD(v3) = v16;
LABEL_46:
											v25 = sub(8054E74)(v16);
											reduceHPBar(a1, v25);
										}
									}
									break;
								case 0xDu:
									v3 = (signed __int16)sub(8054FCC)(v1);
									a1c = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
									v26 = ((u32 *)0x2000000)[2 * sub(8054E60)(v1) + 1];
									v27 = *(_BYTE *)(v1 + 18);
									if ( v27 > 9 )
										break;
									switch ( v27 )
									{
										case 0u:
										case 1u:
										case 2u:
										case 3u:
										case 9u:
											if ( v3 == -1 )
												goto LABEL_56;
											++*(_WORD *)(a1c + 14);
											++*(_WORD *)(v26 + 14);
											sub(8054D7C)(a1c, v3);
											sub(8054D7C)(v26, v3);
											*(_WORD *)(a1c + 16) |= 4u;
											*(_WORD *)(v26 + 16) |= 4u;
											v3 = *((_BYTE *)0x81DE208 + (*(u16 *)0x203E004));
											v28 = LOBYTE(((u32 *)0x81DE1E0)[v3]);
											if ( sub(8054E60)(v1) )
												v29 = &BattleAnimationSectionInfoRightSide;
											else
												v29 = &BattleAnimationSectionInfoLeftSide;
											v30 = (*v29)[v28];
											v31 = (char *)BattleAnimationEventBufferLeftSide + 0x2A00 * sub(8054E60)(v1) + v30;
											*(_DWORD *)(a1c + 40) = *((_DWORD *)v31 + 1);
											*(_DWORD *)(a1c + 60) = *(_DWORD *)(a1c + 48) + *((_DWORD *)v31 + 2);
											*(_DWORD *)(v26 + 60) = *(_DWORD *)(v26 + 48) + 0x57F0;
											v32 = sub(8054E60)(v1);
											v33 = a1c;
											if ( !((u32 *)0x203E088)[v32] )
											{
												v34 = sub(8054E60)(a1c);
												v33 = a1c;
												if ( ((u32 *)0x201FB10)[v34] != *(_DWORD *)(a1c + 40) )
												{
													sub(8054734)(a1c);
													v35 = sub(8054E60)(a1c);
													v33 = a1c;
													((u32 *)0x201FB10)[v35] = *(_DWORD *)(a1c + 40);
												}
											}
											goto LABEL_58;
										case 4u:
										case 5u:
LABEL_56:
											v3 = *((_BYTE *)0x81DE208 + (*(u16 *)0x203E004));
											break;
										case 6u:
										case 7u:
										case 8u:
											break;
										default:
											goto def_8054080;
									}
									sub(8054D7C)(a1c, v3);
									sub(8054D7C)(v26, v3);
									v33 = a1c;
LABEL_58:
									sub(80546F0)(v33);
									sub(80546F0)(v26);
									goto LABEL_120;
								case 0x13u:
									v36 = *(_WORD *)(v1 + 16);
									if ( !(v36 & 0x20) )
									{
										*(_WORD *)(v1 + 16) = v36 | 0x20;
										break;
									}
									if ( (*(u32 *)0x2017758) != 1 )
										break;
									(*(u32 *)0x2017758) = 0;
									v37 = v36 & 0xFFDF;
									goto LABEL_116;
								case 0x14u:
									if ( !sub(8054E4C)(v1) )
										sub(804EFE0)(3);
									break;
								case 0x15u:
									if ( !sub(8054E4C)(v1) )
										sub(804EFE0)(0);
									break;
								case 0x18u:
									v38 = *(_WORD *)(v1 + 16);
									if ( v38 & 1 )
									{
										*(_WORD *)(v1 + 16) = v38 & 0xFFFE;
										*(_DWORD *)(v1 + 32) += 4;
										*(_WORD *)(v1 + 8) = *(_WORD *)(v1 + 8) & 0xF3FF | 0x400;
										*(_WORD *)(v1 + 10) = 140;
										sub(8006488)(140);
									}
									break;
								case 0x1Au:
									if ( !sub(8054E4C)(v1) )
									{
										v39 = sub(8054F90)(v1);
										v40 = v39;
										if ( v39 )
										{
											*(_WORD *)(v39 + 16) |= 9u;
											v41 = v39;
											v42 = sub(8054FEC)(v1);
											LOWORD(v3) = v42;
											v43 = sub(8054E74)(v42);
											reduceHPBar(v41, v43);
											v40 = v41;
										}
										a1d = v40;
										if ( (signed __int16)sub(80684B0)(v40) != 2 )
										{
											v44 = sub(8054E60)(v1);
											if ( sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v44) & 0x1000 )
												sub(80641B0)(a1d);
											else
												normalEffect(v1);
										}
									}
									break;
								case 0x26u:
									if ( !sub(8054E4C)(v1) )
										sub(8062FE0)(v1, 0);
									break;
								case 0x27u:
									if ( !sub(8054E4C)(v1) )
										sub(8062FE0)(v1, 1);
									break;
								case 0x2Cu:
									if ( !sub(8054E4C)(v1) )
										sub(80631B0)(v1);
									break;
								case 0x2Du:
									v45 = sub(8054E60)(v1);
									if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v45) & 0x1000) )
										goto LABEL_117;
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
										goto LABEL_113;
									*(_WORD *)(v1 + 16) = v11 | 0x20;
									if ( !sub(8054E4C)(v1) )
										sub(8064330)(v1, 0);
									break;
								case 0x2Eu:
									if ( !sub(8054E4C)(v1) )
										sub(8063400)(v1, 0);
									break;
								case 0x2Fu:
									if ( !sub(8054E4C)(v1) )
										sub(8063400)(v1, 1);
									break;
								case 0x30u:
									if ( !sub(8054E4C)(v1) )
										sub(80635B4)(v1, 0);
									break;
								case 0x31u:
									if ( !sub(8054E4C)(v1) )
										sub(80635B4)(v1, 1);
									break;
								case 0x32u:
									if ( !sub(8054E4C)(v1) )
										sub(80635B4)(v1, 2);
									break;
								case 0x39u:
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
										goto LABEL_113;
									*(_WORD *)(v1 + 16) = v11 | 0x20;
									if ( !sub(8054E4C)(v1) )
										sub(80638F0)(v1);
									break;
								case 0x3Du:
									v46 = *(_WORD *)(v1 + 16);
									if ( !(v46 & 0x20) )
									{
										*(_WORD *)(v1 + 16) = v46 | 0x20;
										if ( !sub(8054E4C)(v1) )
											sub(8050FF0)(1);
										sub(8064458)(v1);
										sub(8050FFC)(v1);
									}
LABEL_20:
									v11 = *(_WORD *)(v1 + 16);
									goto LABEL_113;
								case 0x47u:
									sub(8063FBC)(v1);
									break;
								case 0x4Eu:
									sub(8063804)(v1);
									break;
								case 0x19u:
								case 0x1Bu:
								case 0x1Cu:
								case 0x1Du:
								case 0x1Eu:
								case 0x1Fu:
								case 0x20u:
								case 0x21u:
								case 0x22u:
								case 0x23u:
								case 0x24u:
								case 0x25u:
								case 0x28u:
								case 0x29u:
								case 0x2Au:
								case 0x2Bu:
								case 0x33u:
								case 0x34u:
								case 0x35u:
								case 0x36u:
								case 0x37u:
								case 0x38u:
								case 0x3Au:
								case 0x3Bu:
								case 0x3Cu:
								case 0x3Eu:
								case 0x3Fu:
								case 0x40u:
								case 0x41u:
								case 0x42u:
								case 0x43u:
								case 0x44u:
								case 0x45u:
								case 0x46u:
								case 0x48u:
								case 0x49u:
								case 0x4Au:
								case 0x4Bu:
								case 0x4Cu:
								case 0x4Du:
								case 0x4Fu:
									sub(8067F90)(v1, *(_BYTE *)(v1 + 21 + v4 - 1));
									break;
								case 0x51u:
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
										goto LABEL_113;
									*(_WORD *)(v1 + 16) = v11 | 0x20;
									if ( !sub(8054E4C)(v1) )
										sub(806397C)(v1);
									break;
								case 0x52u:
									v47 = sub(8054E60)(v1);
									if ( !(sub(8053AFC)(2 * (*(_WORD *)(v1 + 14) - 1) + v47) & 0x1000) )
										goto LABEL_117;
									v11 = *(_WORD *)(v1 + 16);
									if ( v11 & 0x20 )
									{
LABEL_113:
										if ( v11 & 0x40 )
										{
											v9 = v11 & 0xFFDF;
											v8 = -65;
LABEL_115:
											v37 = v9 & v8;
LABEL_116:
											*(_WORD *)(v1 + 16) = v37;
LABEL_117:
											v6 = *(_DWORD *)(v1 + 32) + 4;
LABEL_118:
											*(_DWORD *)(v1 + 32) = v6;
										}
									}
									else
									{
										*(_WORD *)(v1 + 16) = v11 | 0x20;
										if ( !sub(8054E4C)(v1) )
											sub(8064330)(v1, 1);
									}
									break;
								default:
									break;
							}
						}
def_8054080:
						--*(_BYTE *)(v1 + 20);
					}
LABEL_120:
					*(_WORD *)(v1 + 12) &= 0xE700u;
				}
				if ( v3 & 0x2000 )
				{
					if ( !sub(8054E4C)(v1)
						&& !((u32 *)0x203E088)[sub(8054E60)(v1)]
						&& !(*(_WORD *)(v1 + 16) & 0x4000)
						&& ((u32 *)0x201FB10)[sub(8054E60)(v1)] != *(_DWORD *)(v1 + 40) )
					{
						sub(8054764)(v1);
						((u32 *)0x201FB10)[sub(8054E60)(v1)] = *(_DWORD *)(v1 + 40);
					}
					*(_WORD *)(v1 + 12) &= 0xD700u;
				}
				if ( v3 & 0x4000 || (*(u32 *)0x2000024) == 1 )
				{
					if ( *(_WORD *)(v1 + 16) & 2 )
					{
						v48 = (signed __int16)sub(8054FCC)(v1);
						if ( v48 == -1 )
						{
							v51 = sub(8054E60)(v1);
							*(_WORD *)(((u32 *)0x2000000)[2 * v51] + 16) &= 0xFFFDu;
							v52 = sub(8054E60)(v1);
							*(_WORD *)(((u32 *)0x2000000)[2 * v52 + 1] + 16) &= 0xFFFDu;
							goto LABEL_141;
						}
						v49 = (*(u32 *)0x2000000);
						a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
						sub(8054D7C)(a1e, v48);
						v50 = -3;
LABEL_137:
						*(_WORD *)(a1e + 16) = v50 & *(_WORD *)(a1e + 16) | 4;
						v53 = v49[2 * sub(8054E60)(v1) + 1];
						sub(8054D7C)(v53, v48);
						*(_WORD *)(v53 + 16) = v50 & *(_WORD *)(v53 + 16) | 4;
						++*(_WORD *)(a1e + 14);
						++*(_WORD *)(v53 + 14);
						sub(80546F0)(a1e);
						sub(80546F0)(v53);
						goto LABEL_141;
					}
					if ( *(_WORD *)(v1 + 16) & 0x8000 )
					{
						v48 = (signed __int16)sub(8054FCC)(v1);
						if ( v48 == -1 )
							goto LABEL_141;
						v49 = (*(u32 *)0x2000000);
						a1e = ((u32 *)0x2000000)[2 * sub(8054E60)(v1)];
						sub(8054D7C)(a1e, v48);
						v50 = 0x7FFF;
						goto LABEL_137;
					}
					if ( !sub(8054E4C)(v1) )
					{
						v54 = sub(8054E60)(v1);
						if ( (signed __int16)sub(8053AD4)(2 * *(_WORD *)(v1 + 14) + v54) == -1 )
							((u32 *)0x201FAF8)[sub(8054E60)(v1)] = 1;
					}
				}
			}
		}
LABEL_141:
		v0 = v2;
	}
	while ( v2 <= 3 );
}
*/

/*
__attribute__((section(".callBattleAnimationEventHandlerEx")))
void callBattleAnimationEventHandlerEx()
{
	battleAnimationEventHandlerEx();
}
*/

// 左侧AIS初始化
// x控制近接还是远程
void InitLeftAIS(int x)
{
	char v1; // r7@1
	int v2; // r5@1
	__int16 v3; // r6@1
	int v4; // r8@1
	__int16 v5; // r9@1
	__int16 v6; // r4@1
	char *v7; // r0@1
	int *v8; // r0@3
	char *v9; // r0@3
	int *v10; // r0@5

	v1 = x;
	/*
	v2 = LOBYTE(((u32 *)0x81DE1E0)[x]);
	v3 = BYTE1(((u32 *)0x81DE1E0)[x]);
	v4 = BYTE2(((u32 *)0x81DE1E0)[x]);
	v5 = BYTE3(((u32 *)0x81DE1E0)[x]);
	*/
	v2 = ((u8 *)0x81DE1E0)[4*x];
	v3 = ((u8 *)0x81DE1E0)[4*x+1];
	v4 = ((u8 *)0x81DE1E0)[4*x+2];
	v5 = ((u8 *)0x81DE1E0)[4*x+3];
//	v6 = (unsigned __int8)((u8 *)0x81DE20D)[(*(u16 *)0x203E004)];
	v6 = ((u8 *)0x81DE20D)[(*(u16 *)0x203E004)];
//	LOWORD((*(u32 *)0x2000030)) = -*((_WORD *)(*(u32 *)0x81DE218) + (*(u16 *)0x203E004));
//	LOWORD((*(u32 *)0x2000030)) = -*((_WORD *)0x81DE218 + *(u16 *)0x203E004);
	*(u16 *)0x2000030 = -*((_WORD *)0x81DE218 + *(u16 *)0x203E004);
	(*(u16 *)0x2000034) = 0;
//	LOWORD((*(u32 *)0x2000028)) = (*(u32 *)0x2000030) + v6;
	*(u16 *)0x2000028 = (*(u32 *)0x2000030) + v6;
	(*(u16 *)0x200002C) = 88;
//	v7 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v2];

	// 扩展非压缩data2
	if(BattleAnimationEventBufferLeftSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v7 = (char *)BattleAnimationEventBufferLeftSide[1] + BattleAnimationSectionInfoLeftSide[v2];
	else
		v7 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v2];
	
	if ( v2 == 255 )
		v7 = (char *)0x8C0A5D8;
	v8 = sub(8006424)((int)v7, v3);
	*((_WORD *)v8 + 1) = (*(u32 *)0x2000028) - (*(u32 *)0x201FB00);
	*((_WORD *)v8 + 2) = (*(u16 *)0x200002C);
	*((_WORD *)v8 + 4) = 0x7A00;
	*((_WORD *)v8 + 6) |= 0x400u;
	*((_WORD *)v8 + 7) = 0;
	*((_BYTE *)v8 + 18) = v1;
	v8[11] = 0x2000088;
//	v8[12] = BattleAnimationOAML2RBuffer;

	// 扩展无压缩data4
	v8[12] = (((u32 *)BattleAnimationOAML2RBuffer)[0] == 'l' + ('a'<<8) +('q'<<16))?((void **)BattleAnimationOAML2RBuffer)[1]:BattleAnimationOAML2RBuffer;

	((u32 *)0x2000000)[0] = (int)v8;
//	v9 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v4];

	// 扩展非压缩data2
	if(BattleAnimationEventBufferLeftSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v9 = (char *)BattleAnimationEventBufferLeftSide[1] + BattleAnimationSectionInfoLeftSide[v4];
	else
		v9 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v4];

	if ( v4 == 255 )
		v9 = (char *)0x8C0A5D8;
	v10 = sub(8006424)((int)v9, v5);
	*((_WORD *)v10 + 1) = (*(u32 *)0x2000028) - (*(u32 *)0x201FB00);
	*((_WORD *)v10 + 2) = (*(u16 *)0x200002C);
	*((_WORD *)v10 + 4) = 0x7A00;
	*((_WORD *)v10 + 6) |= 0x500u;
	*((_WORD *)v10 + 7) = 0;
	*((_BYTE *)v10 + 18) = v1;
	v10[11] = 0x2000088;
//	v10[12] = BattleAnimationOAML2RBuffer;

	// 扩展无压缩data4
	v10[12] = (((u32 *)BattleAnimationOAML2RBuffer)[0] == 'l' + ('a'<<8) +('q'<<16))?((void **)BattleAnimationOAML2RBuffer)[1]:BattleAnimationOAML2RBuffer;

	(*(u32 *)0x2000004) = (int)v10;
}

//  右侧AIS初始化
// x控制近接还是远程
void InitRightAIS(int x)
{
	char v1; // r5@1
	int v2; // r3@1
	__int16 v3; // r4@1
	int v4; // r6@1
	__int16 v5; // r7@1
	__int16 v6; // r2@1
	char *v7; // r0@1
	int *v8; // r0@3
	char *v9; // r0@3
	int *v10; // r0@5

	v1 = x;
	/*
	v2 = LOBYTE(((u32 *)0x81DE1E0)[x]);
	v3 = BYTE1(((u32 *)0x81DE1E0)[x]);
	v4 = BYTE2(((u32 *)0x81DE1E0)[x]);
	v5 = BYTE3(((u32 *)0x81DE1E0)[x]);
	*/
	v2 = ((u8 *)0x81DE1E0)[4*x];
	v3 = ((u8 *)0x81DE1E0)[4*x+1];
	v4 = ((u8 *)0x81DE1E0)[4*x+2];
	v5 = ((u8 *)0x81DE1E0)[4*x+3];
	v6 = (unsigned __int8)((u8 *)0x81DE212)[(*(u16 *)0x203E004)];
//	HIWORD((*(u32 *)0x2000030)) = 0;
	*(u16 *)0x2000032 = 0;
	(*(u16 *)0x2000036) = 0;
//	HIWORD((*(u32 *)0x2000028)) = v6;
	*(u16 *)0x200002A = v6;
	(*(u16 *)0x200002E) = 88;
//	v7 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[v2];

	// 扩展无压缩data2
	if(BattleAnimationEventBufferRightSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v7 = (char *)BattleAnimationEventBufferRightSide[1] + BattleAnimationSectionInfoRightSide[v2];
	else
		v7 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[v2];

	// 恶搞:先变身成左边的
//	v7 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v2];
	
	if ( v2 == 255 )
		v7 = (char *)0x8C0A5D8;
	v8 = sub(8006424)((int)v7, v3);
	*((_WORD *)v8 + 1) = HIWORD((*(u32 *)0x2000028)) - (*(u32 *)0x201FB00);
	*((_WORD *)v8 + 2) = (*(u16 *)0x200002E);
	*((_WORD *)v8 + 4) = -25856;
	*((_WORD *)v8 + 6) |= 0x600u;
	*((_WORD *)v8 + 7) = 0;
	*((_BYTE *)v8 + 18) = v1;
	v8[11] = 0x2002088;
//	v8[12] = BattleAnimationOAMR2LBuffer;

	// 扩展无压缩data3
	v8[12] = (((u32 *)BattleAnimationOAMR2LBuffer)[0] == 'l' + ('a'<<8) +('q'<<16))?((void **)BattleAnimationOAMR2LBuffer)[1]:BattleAnimationOAMR2LBuffer;
//	v8[12] = (((u32 *)BattleAnimationOAMR2LBuffer)[0] == 'l' + ('a'<<8) +('q'<<16))?((u32 *)BattleAnimationOAMR2LBuffer)[1]:(int)BattleAnimationOAMR2LBuffer;
	(*(u32 *)0x2000008) = (int)v8;
//	v9 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[v4];
	
	//	恶搞:先变身成左边的
//	v8[12] = BattleAnimationOAML2RBuffer;

	// 扩展非压缩data2
	if(BattleAnimationEventBufferRightSide[0] == 'l' + ('a'<<8) +('q'<<16))
		v9 = (char *)BattleAnimationEventBufferRightSide[1] + BattleAnimationSectionInfoRightSide[v4];
	else
		v9 = (char *)BattleAnimationEventBufferRightSide + BattleAnimationSectionInfoRightSide[v4];

	// 恶搞:先变身成左边的
//	v9 = (char *)BattleAnimationEventBufferLeftSide + BattleAnimationSectionInfoLeftSide[v4];

	if ( v4 == 255 )
		v9 = (char *)0x8C0A5D8;
	v10 = sub(8006424)((int)v9, v5);
	*((_WORD *)v10 + 1) = HIWORD((*(u32 *)0x2000028)) - (*(u32 *)0x201FB00);
	*((_WORD *)v10 + 2) = (*(u16 *)0x200002E);
	*((_WORD *)v10 + 4) = -25856;
	*((_WORD *)v10 + 6) |= 0x700u;
	*((_WORD *)v10 + 7) = 0;
	*((_BYTE *)v10 + 18) = v1;
	v10[11] = (int)0x2002088;
//	v10[12] = BattleAnimationOAMR2LBuffer;

	// 扩展无压缩data3
	v10[12] = (((u32 *)BattleAnimationOAMR2LBuffer)[0] == 'l' + ('a'<<8) +('q'<<16))?((void **)BattleAnimationOAMR2LBuffer)[1]:BattleAnimationOAMR2LBuffer;
//	v10[12] = (((u32 *)BattleAnimationOAMR2LBuffer)[0] == 'l' + ('a'<<8) +('q'<<16))?((u32 *)BattleAnimationOAMR2LBuffer)[1]:(int)BattleAnimationOAMR2LBuffer;

	//	恶搞:先变身成左边的
//	v10[12] = BattleAnimationOAML2RBuffer;

	(*(u32 *)0x200000C) = (int)v10;
}

__attribute__((section(".callBattleAnimationAISInit")))
void call_sub_8054AC0(int xl, int xr)
{
	sub_8054AC0(xl,xr);
}

// 战斗双方AIS初始化
// xl和xr控制近接还是远程
// 进接攻击: xl = xr = 6
// 远程攻击: xl = xr = 8
void sub_8054AC0(int xl, int xr)
{
	// AIS指针数组初始化
	*(u32 *)0x2000000 = 0;
	*(u32 *)0x2000004 = 0;
	*(u32 *)0x2000008 = 0;
	*(u32 *)0x200000C = 0;
	// 分别初始化左右两侧的AIS
	if(IfBattleAnimationIsAtTheLeftSide == 1)
		InitLeftAIS(xl);
	if(IfBattleAnimationIsAtTheRightSide == 1)
		InitRightAIS(xr);
	// 法师斗篷循环标识	[0x203E004]=4
	if(*(u16 *)0x203E004 == 4)
	{
//		*(u16 *)(*(u32 *)0x2000000) |= 2;
//		*(u16 *)(*(u32 *)0x2000004) |= 2;
		**(u16 **)0x2000000 |= 2u;
		**(u16 **)0x2000004 |= 2u;
	}
}

// 命中的时候地面消失和miss的时候自己消失的bug
/*
void sub_8054D7C(int a1, int a2)
{
	int v2; // r4@1
	int v3; // r6@1
	int v4; // r5@2
	char *v5; // r1@2
	__int16 v6; // r7@4
	int v7; // r1@6
	u32 *v8; // r0@6
	int v9; // r1@8

	v2 = a1;
	v3 = a2;
	if ( sub(8054E4C)(a1) )
	{
		v4 = BYTE2(((u32 *)0x81DE1E0)[v3]);
		v5 = (char *)(0x81DE1E0 + 4 * (v3)) + 3;
	}
	else
	{
		v4 = LOBYTE(((u32 *)0x81DE1E0)[v3]);
		v5 = (char *)(0x81DE1E0 + 4 * (v3)) + 1;
	}
	v6 = (unsigned __int8)*v5;
	if ( v4 == 255 )
	{
		*(_DWORD *)(v2 + 36) = (*(u32 *)0x8C0A5D8);
		*(_DWORD *)(v2 + 32) = (*(u32 *)0x8C0A5D8);
		*(_WORD *)(v2 + 16) = 0;
	}
	else
	{
		if ( isUnitAtRightOrLeft(v2) )
		{
			v7 = BattleAnimationSectionInfoRightSide[v4];
			v8 = BattleAnimationEventBufferRightSide;
		}
		else
		{
			v7 = BattleAnimationSectionInfoLeftSide[v4];
			v8 = BattleAnimationEventBufferLeftSide;
		}
		v9 = (int)v8 + v7;
		*(_DWORD *)(v2 + 36) = v9;
		*(_DWORD *)(v2 + 32) = v9;
	}
	*(_WORD *)(v2 + 10) = v6;
	*(_WORD *)(v2 + 8) = *(_WORD *)(v2 + 8) & 0xF3FF | 0x800;
	*(_WORD *)(v2 + 6) = 0;
	*(_WORD *)(v2 + 12) &= 0x700u;
	*(_BYTE *)(v2 + 18) = v3;
	*(_BYTE *)(v2 + 20) = 0;
	*(_DWORD *)(v2 + 48) = (char *)BattleAnimationOAML2RBuffer + 0x5800 * isUnitAtRightOrLeft(v2);
	sub(8006488)();
}
*/

/*
__attribute__((section(".call_sub_8054D7C")))
void call_sub_8054D7C(int a1, int a2)
{
	sub_8054D7C(a1,a2);
//	sub(8054D7C)(a1,a2);
}
*/

void InitAIS(AnimationInterpreter *AIS, int x)
{
	int mode; // r5@2
	char *v5; // r1@2
	u16 v6; // r7@4
	int v7; // r1@6
	u32 *v8; // r0@6
	int v9; // r1@8

	if ( sub(8054E4C)(AIS) )
	{
		mode = ((((u32 *)0x81DE1E0)[x])>>16) & 0xFF;
		v5 = (char *)0x81DE1E0 + 4 * x + 3;
	}
	else
	{
		mode = (((u32 *)0x81DE1E0)[x]) & 0xFF;
		v5 = (char *)0x81DE1E0 + 4 * x + 1;
	}
	v6 = (unsigned __int8)*v5;
	if ( mode == 255 )
	{
		AIS->lastCmd = (u32 *)0x8C0A5D8;
		AIS->nextCmd = (u32 *)0x8C0A5D8;
		AIS->unk_10 = 0;
	}
	else
	{
		if ( isUnitAtRightOrLeft(AIS) )
		{
			v7 = BattleAnimationSectionInfoRightSide[mode];
			v8 = BattleAnimationEventBufferRightSide;
		}
		else
		{
			v7 = BattleAnimationSectionInfoLeftSide[mode];
			v8 = BattleAnimationEventBufferLeftSide;
		}
		// 添加无压缩data2支持
		if(v8[0] == 'l' + ('a'<<8) +('q'<<16))
			v8 = v8[1];
		v9 = (int)v8 + v7;
		AIS->lastCmd = (u32 *)v9;
		AIS->nextCmd = (u32 *)v9;
	}
	AIS->unk_A = v6;
	AIS->OBJAttr2Base = AIS->OBJAttr2Base & 0xF3FF | 0x800;
	AIS->delayCountdown = 0;
	AIS->unk_C &= 0x700u;
	AIS->modeX = x;
	AIS->C85IDBufferIndex = 0;
	AIS->OAMInfoBuffer = (char *)BattleAnimationOAML2RBuffer + 0x5800 * isUnitAtRightOrLeft(AIS);
	// 添加无压缩data3和data4支持
	if(*(u32 *)AIS->OAMInfoBuffer == 'l' + ('a'<<8) +('q'<<16))
		AIS->OAMInfoBuffer = ((u32 *)AIS->OAMInfoBuffer)[1];
	ForAllAIS();
}

__attribute__((section(".callInitAIS")))
void callInitAIS(AnimationInterpreter *AIS, int x)
{
	InitAIS(AIS,x);
}

// 外挂背景动画扩展
// 扩展C2E和C2F指令
// ifCritical是否必杀
void battleExtraAnimation(void *AIS, bool ifCritical)
{
	u32 *position;	// 当前执行到的位置的下一条指令(事件脚本)
	u8 index;	// 要调用的函数索引

	position = *((u32 **)AIS + 0x20/4);
//	index = *position << 16 >> 24;
	index = *(position - 1) << 16 >> 24;
	// 要取的是当前执行的指令(即position指向的位置的上一条指令)
	(*ExtraAnimation[index])(AIS,ifCritical);
}

// 更新战斗动画sheet
void sub_8054764(void *AIS)
{
//	LZ77UnCompWram(*((void **)AIS + 10), *((void **)AIS + 11));
	// 添加压缩data3&4支持
	if(**((u32 **)AIS + 10) == 0x200010)
		FE7JLZ77UnCompWram(*((void **)AIS + 10), *((void **)AIS + 11));
	else
		FE7JCPUFastSet(*((void **)AIS + 10), *((void **)AIS + 11),0x2000/4);
	
	TileTransferInfoAdd(*((void **)AIS + 11), (void *)(32 * (*((_WORD *)AIS + 4) & 0x3FF) + 0x6010000), 0x2000);
}

__attribute__((section(".call_sub_8054764")))
void call_sub_8054764(void *AIS)
{
	sub_8054764(AIS);
}

// 职业介绍的DEMO战斗动画初始化
// 因为只有一个动画，所以AIS就在0x02000000
void DemoBattleAnimationInit(void *AIS)
{
	int v2; // r3@1
	int v3; // r4@1
	__int16 v4; // r8@1
	int v5; // r6@1
	BattleAnimation *animation; // r1@1
	int *sectionOffset; // r2@1
	int v8; // r3@1
	int *v9; // r7@1
	int *v10; // r10@3
	int v11; // r4@6
	_DWORD *v12; // r1@6
	int v13; // r4@7
	int *v14; // r0@8
	int *v15; // r0@8
	int v16; // r1@8
	__int16 v17; // [sp+0h] [bp-24h]@1
	u16 animationID;
	int i;

	v2 = *((_WORD *)AIS + 5);
	// IDA的BYTEn系列宏请勿使用
	/*
	v3 = LOBYTE(((u32 *)0x81DE1E0)[v2]);
	v4 = BYTE1(((u32 *)0x81DE1E0)[v2]);
	v5 = BYTE2(((u32 *)0x81DE1E0)[v2]);
	v17 = BYTE3(((u32 *)0x81DE1E0)[v2]);
	*/
	v3 = ((u32 *)0x81DE1E0)[v2] & 0xFF;
	v4 = ((u32 *)0x81DE1E0)[v2] & 0xFF00 >> 8;
	v5 = ((u32 *)0x81DE1E0)[v2] & 0xFF0000 >> 16;
	v17 = ((u32 *)0x81DE1E0)[v2] & 0xFF000000 >> 24;
	// 双字节动画ID
	animationID = *((_WORD *)AIS + 3);
	// 高字节选择动画库，低字节选择动画
//	animation = &battleAnimationBank[animationID>>8][animationID & 0xFF];
	animation = GetBattleAnimation(animationID);
//	FE7JLZ77UnCompWram(*(&FE7BattleAnimationBank.event + 8 * *((_WORD *)AIS + 3)), *((void **)AIS + 10));
//	animation = &FE7BattleAnimationBank + *((_WORD *)AIS + 3);
	// data2
	if(*(u8 *)(animation->event) == 0x10)
		FE7JLZ77UnCompWram(animation->event, *((void **)AIS + 10));
	else
	{
		**((u32 **)AIS + 10) = 'l' + ('a'<<8) +('q'<<16);
		*(*((u32 **)AIS + 10) +1) = animation->event;
	}	
	sectionOffset = animation->sectionOffset;
	v8 = *((_DWORD *)AIS + 10);
	v9 = (*(u32 *)0x8C0A5D8);
	if ( v3 != 255 )
		v9 = (int *)(v8 + sectionOffset[v3]);
	v10 = (*(u32 *)0x8C0A5D8);
	if ( v5 != 255 )
		v10 = (int *)(v8 + sectionOffset[v5]);
	if ( *((_WORD *)AIS + 6) )
	{
		v13 = *((_DWORD *)AIS + 9);
//		FE7JLZ77UnCompWram(animation->oamR2L, *((void **)AIS + 9));
		// data3
		if(*(u8 *)(animation->oamR2L) == 0x10)
			FE7JLZ77UnCompWram(animation->oamR2L, *((void **)AIS + 9));
		else
			//	不要拷贝到RAM里的无压缩格式(头部4字节:字符串'laq',大小固定,以01000000 00000000 00000000 00000000结尾,总计0x5800+4字节)
			if(*(u32 *)(animation->oamR2L) == 'l' + ('a' << 8) + ('q' << 16))
			{
				**((u32 **)AIS + 9) = 'l' + ('a' << 8) + ('q' << 16);
				*(*((u32 ***)AIS + 9) + 1) = (u32 *)animation->oamR2L+1;
			}
			//	需要拷贝到RAM里的无压缩格式(无头部,大小不定,以连续12个0xFF结尾,节约空间)
			else
			{
				for(int i=0;i<0x5800/4;i++)
				{
					if(((int *)animation->oamR2L)[i] == -1 && ((int *)animation->oamR2L)[i+1] == -1 && ((int *)animation->oamR2L)[i+2] == -1)
						break;
					(*((int **)AIS + 9))[i] = ((int *)animation->oamR2L)[i];
				}
			}

		v12 = (_DWORD *)(v13 + 0x57F0);
	}
	else
	{
		v11 = *((_DWORD *)AIS + 9);
//		FE7JLZ77UnCompWram(animation->oamL2R, *((void **)AIS + 9));
		// data4
		if(*(u8 *)(animation->oamL2R) == 0x10)
			FE7JLZ77UnCompWram(animation->oamL2R, *((void **)AIS + 9));
		else
			//	不要拷贝到RAM里的无压缩格式(头部4字节:字符串'laq',大小固定,以01000000 00000000 00000000 00000000结尾,总计0x5800+4字节)
			if(*(u32 *)(animation->oamL2R) == 'l' + ('a' << 8) + ('q' << 16))
			{
				**((u32 **)AIS + 9) = 'l' + ('a' << 8) + ('q' << 16);
				*(*((u32 ***)AIS + 9) + 1) = (u32 *)animation->oamL2R+1;
			}
			//	需要拷贝到RAM里的无压缩格式(无头部,大小不定,以连续12个0xFF结尾,节约空间)
			else
			{
				for(int i=0;i<0x5800/4;i++)
				{
					if(((int *)animation->oamL2R)[i] == -1 && ((int *)animation->oamL2R)[i+1] == -1 && ((int *)animation->oamL2R)[i+2] == -1)
						break;
					(*((int **)AIS + 9))[i] = ((int *)animation->oamL2R)[i];
				}
			}

		v12 = (_DWORD *)(v11 + 0x57F0);
	}
	*v12 = 1;
	v14 = sub(8006424)((int)v9, v4);
	v14[12] = *((_DWORD *)AIS + 9);
	*((_WORD *)v14 + 1) = *((_WORD *)AIS + 1);
	*((_WORD *)v14 + 2) = *((_WORD *)AIS + 2);
	*((_WORD *)v14 + 4) = (*((_WORD *)AIS + 8) << 12) | 0x800 | *((_WORD *)AIS + 7);
	*((_WORD *)v14 + 6) |= (unsigned __int16)(*((_WORD *)AIS + 6) << 9) | 0x400;
	*((_WORD *)v14 + 7) = 0;
	*((_BYTE *)v14 + 18) = *((_WORD *)AIS + 5);
	v14[11] = *((_DWORD *)AIS + 7);
	*((_DWORD *)AIS + 5) = v14;
	v14[17] = (int)AIS;
	v15 = sub(8006424)((int)v10, v17);
	v15[12] = *((_DWORD *)AIS + 9);
	*((_WORD *)v15 + 1) = *((_WORD *)AIS + 1);
	*((_WORD *)v15 + 2) = *((_WORD *)AIS + 2);
	*((_WORD *)v15 + 4) = (*((_WORD *)AIS + 8) << 12) | 0x800 | *((_WORD *)AIS + 7);
	*((_WORD *)v15 + 6) |= (unsigned __int16)(*((_WORD *)AIS + 6) << 9) | 0x500;
	*((_WORD *)v15 + 7) = 0;
	*((_BYTE *)v15 + 18) = *((_WORD *)AIS + 5);
	v15[11] = *((_DWORD *)AIS + 7);
	*((_DWORD *)AIS + 6) = v15;
	v15[17] = (int)AIS;
	// data5
//	FE7JLZ77UnCompWram(*(&FE7BattleAnimationBank.palGroup + 8 * *((_WORD *)AIS + 3)), *((void **)AIS + 8));
	// 直接扩展色板支持
	if(*(int *)animation->palGroup == -1)
		for(i = 0; i < 5; i++)
			FE7JCPUFastSet((int)animation->palGroup + 4 + 0x20 * 2 * i, (int)(*((void **)AIS + 8)) + 0x20 * i, 0x20/4);
	else
		if(*(u8 *)animation->palGroup == 0x10)
			FE7JLZ77UnCompWram(animation->palGroup, *((void **)AIS + 8));
		else
			FE7JCPUFastSet(animation->palGroup, *((void **)AIS + 8), 0xA0/4);
	v16 = *((_WORD *)AIS + 4);
	if ( v16 != -1 )
//		FE7JLZ77UnCompWram(*(&characterBattlePalTable.pal + 4 * v16), *((void **)AIS + 8));
		// 个人专用调色板
	{
		if(*(int *)characterBattlePalTable[v16].pal == -1)
			FE7JCPUFastSet((int)characterBattlePalTable[v16].pal + 4, *((void **)AIS + 8), 0x20/4);
		else
			if(*(u8 *)characterBattlePalTable[v16].pal == 0x10)
				FE7JLZ77UnCompWram(characterBattlePalTable[v16].pal, *((void **)AIS + 8));
			else
				FE7JCPUFastSet(characterBattlePalTable[v16].pal, *((void **)AIS + 8), 0x20/4);
	}
	FE7JCPUFastSet(
		(void *)(*((_DWORD *)AIS + 8) + 32 * *((_BYTE *)AIS + 1)),
		(u16 *)OBJPaletteBuffer+16 * *((_WORD *)AIS + 8),
		8u);
	// 双色板扩展
	if(v16 != -1)	// 人物特殊色板
	{
		if(v16 < sizeof(characterBattleSecondPalTable)/sizeof(characterBattleSecondPalTable[0]) && characterBattleSecondPalTable[v16])
			FE7JCPUFastSet(characterBattleSecondPalTable[v16], (u16 *)OBJPaletteBuffer+16 * (*((_WORD *)AIS + 8) + 1), 8);
		else	// 直接扩展色板支持
			if(*(int *)characterBattlePalTable[v16].pal == -1)
				FE7JCPUFastSet((int)characterBattlePalTable[v16].pal + 4 + 0x20, (u16 *)OBJPaletteBuffer+16 * (*((_WORD *)AIS + 8) + 1), 8);
	}
	else	// 动画自带色板
	{
		if(animationID < sizeof(battleAnimationSecondPalTable)/sizeof(battleAnimationSecondPalTable[0]) && battleAnimationSecondPalTable[animationID])
			FE7JCPUFastSet(battleAnimationSecondPalTable[animationID] + 16 * (*((_BYTE *)AIS + 1)), (u16 *)OBJPaletteBuffer+16 * (*((_WORD *)AIS + 8) + 1), 8);
		else	// 直接扩展色板支持
			if(*(int *)animation->palGroup == -1)
				FE7JCPUFastSet((int)animation->palGroup + 4 + 0x20 * 2 * (*((_BYTE *)AIS + 1)) + 0x20, (u16 *)OBJPaletteBuffer+16 * (*((_WORD *)AIS + 8) + 1), 8);
	}
	EnablePaletteSync();
	*((_DWORD *)AIS + 11) = 0;
}

/*
//	原版
void DemoBattleAnimationInit(void *AIS)
{
	int v2; // r3@1
	int v3; // r4@1
	__int16 v4; // r8@1
	int v5; // r6@1
	BattleAnimation *animation; // r1@1
	int *sectionOffset; // r2@1
	int v8; // r3@1
	int *v9; // r7@1
	int *v10; // r10@3
	int v11; // r4@6
	_DWORD *v12; // r1@6
	int v13; // r4@7
	int *v14; // r0@8
	int *v15; // r0@8
	int v16; // r1@8
	__int16 v17; // [sp+0h] [bp-24h]@1

	v2 = *((_WORD *)AIS + 5);
	v3 = LOBYTE(((u32 *)0x81DE1E0)[v2]);
	v4 = BYTE1(((u32 *)0x81DE1E0)[v2]);
	v5 = BYTE2(((u32 *)0x81DE1E0)[v2]);
	v17 = BYTE3(((u32 *)0x81DE1E0)[v2]);
	FE7JLZ77UnCompWram(*(&FE7BattleAnimationBank[0].event + 8 * *((_WORD *)AIS + 3)), *((void **)AIS + 10));
	animation = &FE7BattleAnimationBank[0] + *((_WORD *)AIS + 3);
	sectionOffset = animation->sectionOffset;
	v8 = *((_DWORD *)AIS + 10);
	v9 = (*(u32 *)0x8C0A5D8);
	if ( v3 != 255 )
		v9 = (int *)(v8 + sectionOffset[v3]);
	v10 = (*(u32 *)0x8C0A5D8);
	if ( v5 != 255 )
		v10 = (int *)(v8 + sectionOffset[v5]);
	if ( *((_WORD *)AIS + 6) )
	{
		v13 = *((_DWORD *)AIS + 9);
		FE7JLZ77UnCompWram(animation->oamR2L, *((void **)AIS + 9));
		v12 = (_DWORD *)(v13 + 0x57F0);
	}
	else
	{
		v11 = *((_DWORD *)AIS + 9);
		FE7JLZ77UnCompWram(animation->oamL2R, *((void **)AIS + 9));
		v12 = (_DWORD *)(v11 + 0x57F0);
	}
	*v12 = 1;
	v14 = sub(8006424)((int)v9, v4);
	v14[12] = *((_DWORD *)AIS + 9);
	*((_WORD *)v14 + 1) = *((_WORD *)AIS + 1);
	*((_WORD *)v14 + 2) = *((_WORD *)AIS + 2);
	*((_WORD *)v14 + 4) = (*((_WORD *)AIS + 8) << 12) | 0x800 | *((_WORD *)AIS + 7);
	*((_WORD *)v14 + 6) |= (unsigned __int16)(*((_WORD *)AIS + 6) << 9) | 0x400;
	*((_WORD *)v14 + 7) = 0;
	*((_BYTE *)v14 + 18) = *((_WORD *)AIS + 5);
	v14[11] = *((_DWORD *)AIS + 7);
	*((_DWORD *)AIS + 5) = v14;
	v14[17] = (int)AIS;
	v15 = sub(8006424)((int)v10, v17);
	v15[12] = *((_DWORD *)AIS + 9);
	*((_WORD *)v15 + 1) = *((_WORD *)AIS + 1);
	*((_WORD *)v15 + 2) = *((_WORD *)AIS + 2);
	*((_WORD *)v15 + 4) = (*((_WORD *)AIS + 8) << 12) | 0x800 | *((_WORD *)AIS + 7);
	*((_WORD *)v15 + 6) |= (unsigned __int16)(*((_WORD *)AIS + 6) << 9) | 0x500;
	*((_WORD *)v15 + 7) = 0;
	*((_BYTE *)v15 + 18) = *((_WORD *)AIS + 5);
	v15[11] = *((_DWORD *)AIS + 7);
	*((_DWORD *)AIS + 6) = v15;
	v15[17] = (int)AIS;
	FE7JLZ77UnCompWram(*(&FE7BattleAnimationBank[0].palGroup + 8 * *((_WORD *)AIS + 3)), *((void **)AIS + 8));
	v16 = *((_WORD *)AIS + 4);
	if ( v16 != -1 )
		FE7JLZ77UnCompWram(*(&characterBattlePalTable[0].pal + 4 * v16), *((void **)AIS + 8));
	FE7JCPUFastSet(
		(void *)(*((_DWORD *)AIS + 8) + 32 * *((_BYTE *)AIS + 1)),
		&OBJPaletteBuffer[16 * *((_WORD *)AIS + 8)],
		8u);
	EnablePaletteSync();
	*((_DWORD *)AIS + 11) = 0;
}
*/

__attribute__((section(".callDemoBattleAnimationInit")))
void callDemoBattleAnimationInit(void *AIS)
{
	DemoBattleAnimationInit(AIS);
}

