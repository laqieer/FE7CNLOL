// by laqieer
// 2017/1/28
// FE7J�Դ�����

#pragma once

#include "callFunc.h"

// BIOS functions
#define FE7JArcTan2			sub(80C0548)
#define FE7JBgAffineSet		sub(80C054C)
#define FE7JCPUFastSet		sub(80C0550)
#define FE7JCPUSet			sub(80C0554)
#define FE7JDiv				sub(80C0558)
#define FE7JMod				sub(80C055C)
#define FE7JHuffUnComp		sub(80C0564)
#define FE7JLZ77UnCompVram	sub(80C0568)
#define FE7JLZ77UnCompWram	sub(80C056C)
#define FE7JMultiBoot		sub(80C0570)
#define FE7JObjAffineSet	sub(80C0578)
#define FE7JRLUnCompVram	sub(80C057C)
#define FE7JRLUnCompWram	sub(80C0580)
#define FE7JSoundBiasReset	sub(80C059C)
#define FE7JSoundBiasSet	sub(80C05A4)
#define FE7JSqrt			sub(80C05AC)
#define FE7JVBlankIntrWait	sub(80C05B0)

// Spell Anmations
#define	NoneSpellAnimation			sub32(08056BC9)
#define	ThrowingAxeSpellAnimation	sub32(08056C41)
#define ArrowSpellAnimation			sub32(08056F99)
#define Javelin1SpellAnimation		sub32(08057121)
#define	Javelin2SpellAnimation		sub32(0805717D)
#define Javelin3SpellAnimation		sub32(080571D9)
#define	Javelin4SpellAnimation		sub32(08057235)
#define Javelin5SpellAnimation		sub32(08057291)
#define	Javelin6SpellAnimation		sub32(080572ED)
#define Javelin7SpellAnimation		sub32(08057349)
#define	Javelin8SpellAnimation		sub32(080573A5)
#define Javelin9SpellAnimation		sub32(08057401)
#define	Javelin10SpellAnimation		sub32(0805745D)
#define Javelin11SpellAnimation		sub32(080574B9)
#define	DancePlay1SpellAnimation	sub32(08057665)
#define	DancePlay2SpellAnimation	sub32(08057925)
#define	BalistaArrowSpellAnimation	sub32(08057A6D)
#define	ExaccusWaveSpellAnimation	sub32(08057C25)
#define	SoSFireSpellAnimation		sub32(08057F85)
#define	FlametongueSpellAnimation	sub32(08058121)
#define	FaHolyDragonStoneSpellAnimation		sub32(0805843D)
#define	IdunDarkDragonStoneSpellAnimation	sub32(08058585)
#define	FireSpellAnimation			sub32(08058B29)
#define	ElfireSpellAnimation		sub32(08058B6D)
#define	ForblazeSpellAnimation		sub32(0805ABD9)
#define	ThunderSpellAnimation		sub32(0805882D)
#define	BoltingSpellAnimation		sub32(0805979D)
#define	FimbulvetrSpellAnimation	sub32(08059139)
#define	AircaliburSpellAnimation	sub32(08059BF1)
#define	FluxSpellAnimation			sub32(08059BF5)
#define	NosferatuSpellAnimation		sub32(0805A091)
#define	LightningSpellAnimation		sub32(0805A60D)
#define	PurgeSpellAnimation			sub32(0805A839)
#define	AureolaSpellAnimation		sub32(0805BA79)
#define	DivineSpellAnimation		sub32(0805B679)
#define	ApocalypseSpellAnimation	sub32(0805C3D5)
#define	EclipseSpellAnimation		sub32(0805C3D9)
#define	FenrirSpellAnimation		sub32(0805CA39)
#define	HealSpellAnimation			sub32(0805D1D9)
#define	MendSpellAnimation			sub32(0805D329)
#define	RecoverSpellAnimation		sub32(0805D4CD)
#define	PhysicSpellAnimation		sub32(0805D671)
#define	FortifySpellAnimation		sub32(0805DEC1)
#define	FortifyGreenSpellAnimation	sub32(0805DEF1)
#define	RestoreSpellAnimation		sub32(0805E3B1)
#define	SilenceSpellAnimation		sub32(0805E651)
#define	SleepSpellAnimation			sub32(0805E8E9)
#define	HammerneSpellAnimation		sub32(0805EC09)
#define	BerserkSpellAnimation		sub32(0805EE85)
#define	BarrierSpellAnimation		sub32(0805F48D)
#define	ShineSpellAnimation			sub32(0805F6F9)
#define	LunaSpellAnimation			sub32(0805FBE9)
#define	ExcaliburSpellAnimation		sub32(080605A5)
#define	GespenstSpellAnimation		sub32(08060E71)
#define	AuraSpellAnimation			sub32(080615C5)
#define	LuceSpellAnimation			sub32(08061BE1)
#define	ErishkigalAnimation			sub32(08062351)
#define	FillaMight1SpellAnimation	sub32(08062AAD)
#define	NinisGraceSpellAnimation	sub32(08062AE9)
#define	ThorIreSpellAnimation		sub32(08062B25)
#define	SetLitanySpellAnimation		sub32(08062B61)
// void XXXSpellAnimation(int a1);

// Spell Animation Engine

// �ص�����
#define SpellCallBack	sub(8004370)
// _DWORD * sub_8004370(void *funcSequence, signed int callNum);
// funcSquence��rom��Ԥ�����0��0��β��(����������ָ��)�����еĵ�ַ
// callNum������7��ʱ���ʾ���úţ�����Ҳ��һ��ָ��

// ����
#define ScrollScreen	sub(804EC74)
// void ScrollScreen(int a1, unsigned __int16 a2);

// ������Ч
#define PlaySFX			sub(80689D0)
// void PlaySFX(int SFXID, int a2, int a3, int a4);

// ��2K��С��һƬ�����ڴ�
// mem����ʼ��ַ,num��Ҫ�õ�����
// void memClear2K(void *mem, int num);
#define memClear2K		sub(80017E8)

// ͬ��LCD��Ļ��IO�˿ڼĴ���
#define LCDIOMapSync		sub(8001188)
// void LCDIOMapSync();

// ȡBGnCNT�����ַ(����һ��ָ��)
#define GetBGnCNTBufferAddr	sub(8001320)
// u16 *GetBGnCNTBufferAddr(u16 *result);

// ͬ��BG Map��BG��ɫ��
#define BGMapBGPaletteSync	sub(80016C4)
// void BGMapBGPaletteSync();

// ����BGMapͬ����ʶ(ֱ�Ӹ�ֵ)
#define SetBGMapSyncFlag	sub(8000FD4)
// void SetBGMapSyncFlag(u8 flag);

// ����BGn Map��ͬ��(=SetBGMapSyncFlag(1<<n))
#define EnableBGMapSync		sub(8000FF0)
// void EnableBGMapSync(u8 n);

// ����BG��ɫ��ͬ��
#define EnableBGPaletteSync	sub(8001034)
// void EnableBGPaletteSync();
// ��ʵ�������ͬʱ�Ǹ������е�ɫ��ģ���׷��
#define	EnablePaletteSync	sub(8001034)

// д���ɫ�建��
#define OutputToBGPaletteBuffer	sub(800105C)
// void OutputToBGPaletteBuffer(void *src, signed int paletteOffset, signed int len);
// �������paletteOffset��ʼ��λ�ã�˫�ֽڶ���

// д���ɫ�建��(RGB������������ϵ��(alpha/64))
#define OutputToBGPaletteBufferWithAlpha	sub(80010CC)
// void OutputToBGPaletteBufferWithAlpha(_WORD *src, signed int paletteOffset, int len, int alpha);

// ����Tile��VRAM

// VBLANK�ڼ�ͬ��Tile���ݵ�VRAM
#define TileTransferInfoSync	sub(8003054)
// void TileTransferInfoSync();

// ͬ����ɺ��������
#define TileTransferInfoClear	sub(8002EB8)
// void TileTransferInfoClear();

// ����һ���������Tile������Ϣ
#define TileTransferInfoAdd		sub(8002F54)
// void TileTransferInfoAdd(void *src, void *dst, int len);

// ����һ����VRAM����Ϣ
#define TileIntializeInfoAdd	sub(8002FD8)
// void TileIntializeInfoAdd(void *src, void *dst, int len);

// ����OAM��OAM

// ͬ��OAM1��������
#define OAM1BufferSync sub(8003214)
// void OAM1BufferSync();

// ͬ��OAM2��������
#define OAM2BufferSync sub(80031BC)
// void OAM2BufferSync();

// ��ʼ��OAM����ͬ����Ϣ
#define OAMBufferSyncInfoInitialize sub(8003108)
// void OAMBufferSyncInfoInitialize(int SpriteNum1);

// ȡ������
#define GetSpriteNum1			sub(80031A4)
// int GetSpriteNum1();

// �趨�ڼ��������OAM����
#define	SetOBJAttribute			sub(8003264)
// void SetOBJAttribute(int OBJIndex, __int16 Attribute0, __int16 Attribute1, __int16 Attribute2, __int16 RSParameter)

// ����ROM����ѹ����λͼ���ݵ�VRAM
#define	OutputBitmapToVRAM		sub(8013614)
// void OutputBitmapToVRAM(unsigned int *bitmap, void *dst)

// �Զ��ж�ͼƬ����ѹ�����Ͳ�ֱ�ӿ������߽�ѹ������VRAM
#define	AutoCopyOrDecompressImageToVRAM	sub(8013688)
// void AutoCopyOrDecompressImageToVRAM(_BYTE *src, int dst)

// ����û������TSA��ͼƬдͨ�õ�TSA
#define	writePlainTSA			sub(801383C)
// void writePlainTSA(u16 *TSABufferInWRAM, int tileIndexAndPaletteIndex, int height, int width)
// �߶ȺͿ�ȵĵ�λ����Tile������������

// ��дVRAM�ڵ����ɸ�Tile����
#define	changeTiles				sub(801372C)
// void changeTiles(void *src, void *dst, int width, int height)

// ����Ԥ���TSAģ��дBG��TSA������
#define writeTemplateTSA		sub(80C0C28)
// _WORD *writeTemplateTSA(_WORD *TSABufferInWRAM, _WORD *TSATemplate, __int16 TSABaseValue)

// ����Ԥ���ģ�崴���������
#define AddSprite				sub(80068C4)
//	void AddSprite(int priorityInLinkedList, s16 x, s16 y, int templateAddr, s16 tileNo)

// ����BGn��λ��(n=0,1,2,3)
#define	setBGnPosition			sub(8001D64)
// void __fastcall setBGnPosition(unsigned __int16 n, __int16 x, __int16 y);

// ��OBJ
#define	loadArrowOBJ			sub(8057088)
// void loadArrowOBJ(void *AIS);

// ħ��ʩ�����
// void loadSpellCast();
#define	loadSpellCast			sub(8050348)

// ս���м�HP��
// ��Ѫ��(�����AISָ��,�Ƿ�����)
// void reduceHPBar(void *targetAIS, bool ifMiss)
#define	reduceHPBar				sub(805091C)

// ��ѪHP������
// void suckBloodAnimation(int a1, int ifMiss);
#define	suckBloodAnimation		sub(8050AC8)

// ����Ƿ񷢶��˱�ɱ
// int checkIfCritical(void *AIS);
#define	checkIfCritical			sub(8054F4C)

// ��ɱ��������Ч��

// void criticalAttackEffect(int a1);
#define	criticalAttackEffect	sub(8062D68)

// void criticalEffect(int a1);
#define	criticalEffect	sub(8062D68)

// ��ͨ��������Ч��

// void normalAttackEffect(int a1);
#define	normalAttackEffect		sub(8062E9C)

// void normalEffect(int a1);
#define	normalEffect			normalAttackEffect

// ����������Ч
// int playHitSound(void *AIS);
#define	playHitSound			sub(8068500)

// �¼������������

// 0xDF �һ����º�벿���ݰ��Ĵ�ѩ
// int eventCodeFunc_DF(struct context *parent);
#define	eventCodeFunc_DF		sub(80117AC)
// #define loadFubuki				eventCodeFunc_DF

// �һ��������ݰ������ı��ᾧ
// void loadIceCrystal(int a1);
#define	loadIceCrystal				sub(807D314)

// ��Ѫħ���������Э��
#define efxResire					((struct context*)0x8C11370)
#define	efxResireBG					((struct context*)0x8C11388)
#define	efxResireBG2				((struct context*)0x8C113B8)
#define	efxResireRST				((struct context*)0x8C11568)

// ��Ѫħ��������غ���
// void loadResireBG2(int a1);
#define	loadResireBG2				sub(805A29C)
// void loadResireBG(int a1, u8 ifMiss);
#define	loadResireBG				sub(805A210)
// struct context *loadResireRST5(int a1, int a2, int a3, int a4, int a5);
#define	loadResireRST5				sub(80560A4)
// void loadResireRST3(int a1, struct context *a2, u16 a3)
#define loadResireRST3				sub(805A594)

// RestWINH
#define	efxRestWINH				((struct context*)0x8C108A0)	
// void loadRestWINH(int a1, int a2, u16 a3, u32 a4);
#define	loadRestWINH				sub(80564B8)
// void loadRestWINH1(int a1, int a2, u32 a3);
#define	loadRestWINH1				sub(80565FC)
// void __fastcall loadRestWINH1(int a1, int a2, u32 a3)
// {
// 		loadRestWINH(a1, a2, 0, a3);
// }

// ��ʳħ���������Э��
#define efxHazymoon			((struct context*)0x8C11FA4)
#define efxHazymoonBG		((struct context*)0x8C11FBC)
#define efxHazymoonOBJ2		((struct context*)0x8C120AC)
#define efxHazymoonOBJ3		((struct context*)0x8C120F4)
#define efxHazymoonOBJ3RND	((struct context*)0x8C12124)

// ��ʳħ��������غ���
// void loadHazymoonBG1(void *AIS);
#define loadHazymoonBG1		sub(805C5B4)
// void loadHazymoonOBJ3(void *AIS);
#define	loadHazymoonOBJ3	sub(805C924)
// void loadHazymoonBG2(void *AIS);
#define	loadHazymoonBG2		sub(805C624)
// void loadHazymoonBG3(void *AIS);
#define loadHazymoonBG3		sub(805C6A8)
// void loadHazymoonOBJ2(void *AIS);
#define	loadHazymoonOBJ2	sub(805C77C)

// ���������

// ����һ��0-65535���������
// int geneateRN65536();
#define	geneateRN65536		sub(8000BB8)

// ����һ��0-99���������
// int geneateRN100();
#define	geneateRN100		sub(8000DDC)

// ����0-(range-1)���������
// �������Զ��巶Χ
// int geneateRNRange(int range);
#define	geneateRNRange		sub(8000E08)

// ��ȡ�Է�(��������)��AISָ��
// void *getTargetAIS(int a1);
#define	getTargetAIS		sub(8054F90)

#define loadFlashBG			sub(804F7B8)
