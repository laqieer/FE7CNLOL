// 存档和中断相关程序
// by laqieer
// 2018-04-21

#pragma once

#include "AgbTypes.h"
// #include "Gba_base.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"
#include "FE7JStructDef.h"
#include "IDAPro.h"
#include "FE7JItemList.h"

// 游戏存档主程序

// 原来的

// 输入参数：saveslotNum 存档号
// void SaveGame(enum saveslot saveslotNum);
#define SaveGame	sub(80A119C)

// 存档号定义
// 0-6: 存档槽1，存档槽2，存档槽3，中断备份(校验和验证不通过时载入)，中断，通信斗技场，空位置
enum saveslot {Saveslot1, Saveslot2, Saveslot3, SuspendBackup, Suspend, LinkArena, SaveEmpty, Saveslot4, Saveslot5, Saveslot6, Saveslot7, Saveslot8, Saveslot9, Saveslot10, Saveslot11, Saveslot12};

// 存档索引与存档号映射表
extern const enum saveslot saveslotNumTable[];

// 扩展的
#pragma long_calls
void SaveGameEx(enum saveslot saveslotNum);
#pragma long_calls_off

void callSaveGameEx(enum saveslot saveslotNum);

// SRAM map
// 存档区内存布局

// Save Slot 1
#define	Saveslot1Addr		0xE003F2C
// Save Slot 2
#define	Saveslot2Addr		0xE004CB8
// Save Slot 3
#define	Saveslot3Addr		0xE005A44
// Suspend Slot backup if checksum finds error
#define	SuspendBackupAddr	0xE0000D4
// Suspend Slot
#define	SuspendAddr			0xE002000
// Link Arena
#define	LinkArenaAddr		0xE0067D0
// Save Empty
#define	SaveEmptyAddr		0xE007400

// Save Extension
#define SramExAddr		0xE008000

// Save Slot Size
#define SaveslotSize		0xD8C

// extend save slots
#define Saveslot4Addr		SramExAddr
#define Saveslot5Addr		(SramExAddr + SaveslotSize)
#define Saveslot6Addr		(SramExAddr + SaveslotSize * 2)
#define Saveslot7Addr		(SramExAddr + SaveslotSize * 3)
#define Saveslot8Addr		(SramExAddr + SaveslotSize * 4)
#define Saveslot9Addr		(SramExAddr + SaveslotSize * 5)
#define Saveslot10Addr		(SramExAddr + SaveslotSize * 6)
#define Saveslot11Addr		(SramExAddr + SaveslotSize * 7)
#define Saveslot12Addr		(SramExAddr + SaveslotSize * 8)

// 根据存档号取存档地址
// 输入参数：存档号
// 返回值：存档地址
#pragma long_calls
_BYTE *GetSaveslotAddrEx(enum saveslot saveslotNum);
#pragma long_calls_off

_BYTE *callGetSaveslotAddrEx(enum saveslot saveslotNum);

// 读取存档位的头部来校验存档位
#pragma long_calls
bool ChechSave(int *saveslotHead, enum saveslot saveslotNum);
#pragma long_calls_off

// 检查存档头部的校验和
// bool SaveMetadata_VerifyChecksum(unsigned __int16 *saveslotHead);
#define SaveMetadata_VerifyChecksum	sub(80A232C)

// 从SRAM地址传输数据到RAM
// void (*pprSRAMTransfer)(void *src, void *dst, int length);
// length 单位: byte
#define pprSRAMTransfer		(*(void (**)(void *, void *, int))0x3005D90)

// from Stan
/*It's not technically header, because it's not saved in the corresponding save block; instead they seem to be located at an array located at E000064 (indexed by save block id or whatever you want to call that, the same number you pass to GetSaveDataLocation)
speaking of GetSaveDataLocation; sramOffset is just the result of that. And sramSize is probably (99.9%) the size of the block, as it is the size used to compute the checksum*/
typedef struct SaveDataHeader{
    u32 magicA; // 40624/20112/20223
    u16 magicB; // fixed 200A
    u8  saveType; // 0 is Save; 1 is Suspend; 2 is link arena; 3 is ???; FF is ???
    u8	pad_7;
    u16 sramOffset;
    u16 sramSize;
    u32 checksum;
}SaveHeader;

#define chapterDataInSaveBuffer	(*(int *)0x202BBF4)

/*拷贝数据到SRAM（带检查）
输入参数：
pSrc 指向源地址的指针
pDest 指向目的地址的指针
count 拷贝的字节数*/
// int SRAMTransfer_WithCheck(_BYTE *pSrc, _BYTE *pDest, int count, int a4)
#define SRAMTransfer_WithCheck	sub(80C071C)

/*保存人物数据到存档
输入参数：
pUnitInWRAM 指向内存中人物数据的指针
pUnitInSave 指向存档中人物数据的指针*/
// int SaveUnit(Unit *pUnitInWRAM, UnitInSave *pUnitInSave);
#define SaveUnit	sub(80A13E8)

// signed int LoadSomeUnitStatThingUnlockIdk(int *a1);
#define	LoadSomeUnitStatThingUnlockIdk	sub(809EF08)

// 输入参数：unitID 内存中人物的编号ID
// void __fastcall SetSomeUnitStatThingUnlockMaybeIdk(signed int unitID, int *a2);
#define SetSomeUnitStatThingUnlockMaybeIdk	sub(809F908)

// void SaveSomeUnitStatThingUnlockIdk(_WORD *a1);
#define	SaveSomeUnitStatThingUnlockIdk		sub(809EF88)

/*保存运输队物品到存档
输入参数：
pDest 指向目的地址的指针*/
// void SaveConvoyItems(_BYTE *pDest);
#define SaveConvoyItems	sub(809F3D4)

/*保存人物战绩表到存档
输入参数：
pDest 指向目的地址的指针*/
// void SaveBWLEntries(_BYTE *pDest, int a2, int a3, int a4);
#define SaveBWLEntries	sub(80A04B8)

/*保存章节胜利数据到存档
输入参数：
pDest 指向目的地址的指针*/
// void SaveChapterWinData(_BYTE *pDest, int a2, int a3, int a4);
#define SaveChapterWinData	sub(80A04DC)

//void Save0203EC98(int a1, int a2, int a3, int a4);
#define Save0203EC98		sub(80A0F20)

/*保存全局事件ID到存档
输入参数：
pDest 指向目的地址的指针*/
// void SaveGlobalEventIds(_BYTE *pDest);
#define SaveGlobalEventIds	sub(809F364)

/*设置存档槽头部描述信息
输入参数：
pSaveHeader 指向存档头结构体的指针
saveslotNum 存档槽编号*/
// void setSaveHeader(SaveHeader *pSaveHeader, unsigned int saveslotNum);
#define setSaveHeader		sub(809F1B0)
// 重写这个函数
// void setSaveHeader(SaveHeader *pSaveHeader, unsigned int saveslotNum);

// 存档中的人物数据
// based on Stan's note
typedef struct UnitDataInSave{
	u32 class:7; // Class Index <= 0x7F
	u32 lv:5; // <= 31
	u32 exp:7; // <= 127
	u32 posX:6; // <= 63
	u32 posY:6; // <= 63
	u32 ifDead:1; // set if dead

	u32 ifNotDeployed:1; // set if not deployed
	u32 ifSoloAnimation1:1; // set if solo anim 1
	u32 ifSoloAnimation2:1; // set if solo anim 2
	u32 ifGrowRateUp:1; // set if metis tome or afa drop (成长率上升)
	u32 ifUnk_1:1; // set if "something about not being drawn? Checked at 34298, 27262, amongst others"
	u32 ifUnk_2:1; // set if "no idea, but is checked at 34298"
	u32 ifNotDeployedInPreviousChap:1; // set if not deployed in previous chapter
	u32 unk_3:5; // free? 存档不需要保存现在的hp(因为章节开始时人物一定满血)
	u32 maxHp:6; // <= 63
	u32 pow:5; // <= 31
	u32 skl:5; // <= 31
	u32 spd_lo:4;

	u32 spd_hi:1; // spd <= 31
	u32 def:5; // <= 31
	u32 res:5; // <= 31
	u32 luk:5; // <= 31
	u32 conBonus:5; // <= 31
	u32 movBonus:5; // <= 31
	u32 item_1_id_lo:6;

	u32 item_1_id_hi:2;
	u32 item_1_number:6;
	u32 item_2_id:8; // <= 0xFF
	u32 item_2_number:6; // <= 63
	u32 item_3_id:8;
	u32 item_3_number_lo:2;

	u32 item_3_number_hi:4;
	u32 item_4_id:8;
	u32 item_4_number:6;
	u32 item_5_id:8;
	u32 item_5_number:6;

	u8 character; //  Char Index  <= 0xFF
	
	// 武器熟练度

	// 剑等级
	u8 levelSword;
	// 枪等级
	u8 levelLance;
	// 斧等级
	u8 levelAxe;
	// 弓等级
	u8 levelBow;
	// 杖等级
	u8 levelStaff;
	// 理等级
	u8 levelAnima;
	// 光等级
	u8 levelLight;
	// 闇等级
	u8 levelDark;

	// 支援等级
	u8 levelSupport[7];	
}UnitInSave;

// 最大存档人数
#define maxUnitNumberInSave 	52

// 读中断档或者中断备份档
// void LoadSuspendedGame(int saveslotNum);
// saveslotNum = SuspendBackup / Suspend
#define LoadSuspendedGame		sub(80A1BEC)

// 读存档
// void LoadGame(int saveslotNum);
#define	LoadGame				sub(80A1278)