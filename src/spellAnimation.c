// by laqieer
// 2017/1/28
// 魔法动画

#include "spellAnimation.h"

// 独立出去写的魔法动画

// 纳格尔法尔
#include "spellNaglfar.h"

// 光箭
#include "spellArou.h"

// 冰世界
#include "spellIceWorld.h"

// Blood Moon
#include "spellBloodMoon.h"

// 魔法动画指针表
const PTRFUN spellAnimationTable[] = {
	NoneSpellAnimation,
	ThrowingAxeSpellAnimation,
	ArrowSpellAnimation,
	Javelin1SpellAnimation,
	Javelin2SpellAnimation,
	Javelin3SpellAnimation,
	Javelin4SpellAnimation,
	Javelin5SpellAnimation,
	Javelin6SpellAnimation,
	Javelin7SpellAnimation,
	Javelin8SpellAnimation,
	Javelin9SpellAnimation,
	Javelin10SpellAnimation,
	Javelin11SpellAnimation,
	DancePlay1SpellAnimation,
	DancePlay2SpellAnimation,
	BalistaArrowSpellAnimation,
	ExaccusWaveSpellAnimation,
	SoSFireSpellAnimation,
	FlametongueSpellAnimation,
	FaHolyDragonStoneSpellAnimation,
	IdunDarkDragonStoneSpellAnimation,
	FireSpellAnimation,
	ElfireSpellAnimation,
	ForblazeSpellAnimation,
	ThunderSpellAnimation,
	BoltingSpellAnimation,
	FimbulvetrSpellAnimation,
	AircaliburSpellAnimation,
	FluxSpellAnimation,
	NosferatuSpellAnimation,
	LightningSpellAnimation,
	PurgeSpellAnimation,
	AureolaSpellAnimation,
	DivineSpellAnimation,
	ApocalypseSpellAnimation,
	EclipseSpellAnimation,
	FenrirSpellAnimation,
	HealSpellAnimation,
	MendSpellAnimation,
	RecoverSpellAnimation,
	PhysicSpellAnimation,
	FortifySpellAnimation,
	FortifyGreenSpellAnimation,
	RestoreSpellAnimation,
	SilenceSpellAnimation,
	SleepSpellAnimation,
	HammerneSpellAnimation,
	BerserkSpellAnimation,
	BarrierSpellAnimation,
	0,
	ShineSpellAnimation,
	LunaSpellAnimation,
	ExcaliburSpellAnimation,
	GespenstSpellAnimation,
	AuraSpellAnimation,
	LuceSpellAnimation,
	ErishkigalAnimation,
	FillaMight1SpellAnimation,
	NinisGraceSpellAnimation,
	ThorIreSpellAnimation,
	SetLitanySpellAnimation,
	OldTemplateSpellAnimation,
	spellNaglfar,
	spellArou,
	spellIceWorld,
	spellBloodMoon,
	0,
	0
};

__attribute__((section(".spellAnimationTableBase")))
// const PTRFUN (* spellAnimationTableBase)[] = &spellAnimationTable;
const u32 spellAnimationTableBase = &spellAnimationTable;

// 修改火球的魔法动画ID，便于测试
__attribute__((section(".fireAnimationID")))
const int fireAnimationID = FireSpell;

// 吸血魔法动画测试
__attribute__((section(".NosferatuAnimationID")))
const int NosferatuAnimationID = BloodMoonSpell;

// 776中圣风魔法动画

const u32 OldTemplateData[] = {
	0x19,0,3,(u32)OldTemplate,0,0
};

int OldTemplateSpellAnimation(int a1)
{
	int v1;
	int v2;
	sub(80507CC)();
	sub(8050348)();
	sub(80507E4)();
  	v1 = SpellCallBack(OldTemplateData, 3);
 	*(_DWORD *)(v1 + 92) = a1;
	*(_WORD *)(v1 + 44) = 0;
	v2 = sub(8054FEC)(a1);
	*(_BYTE *)(v1 + 41) = sub(8054E74)(v2);
	return 1;
}

int OldTemplate(int a1)
{
	int v1;
	int v2;
	__int16 FrameID;
	
	v1 = sub(8054F90)(*(_DWORD *)(a1 + 92));
	v2 = sub(8050F54)();
	FrameID = ++*(_WORD *)(a1 + 44);
	if(1 == FrameID)
		ScrollScreen(*(_DWORD *)(a1 + 92), 0xFFFFu);
	switch(FrameID - v2)
		{
			case 1:
				PlaySFX(260,256,120,0);
				break;
			case 10:
				*(_WORD *)(v1 + 16) |= 9u;
				sub(805091C)(v1,*(_BYTE *)(a1 + 41));
				if(!*(_BYTE *)(a1 + 41))
					sub(8068500)(v1);
				break;
			case 20:
				sub(80507D8)();
				sub(80503A0)();
				sub(800457C)(a1);
				break;
			default:
				break;
		}
	return 1;
}