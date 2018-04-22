// 存档和中断相关程序
// by laqieer
// 2018-04-21

#pragma once

#include "AgbTypes.h"
#include "Gba_base.h"
#include "FE7JFunc.h"
#include "FE7JMemoryMap.h"
#include "FE7JStructDef.h"
#include "IDAPro.h"
#include "FE7JItemList.h"

// 游戏存档主程序

// 原来的

// 输入参数：saveslotNum 存档号
// void SaveGame(saveslot saveslotNum);
#define SaveGame	sub(80A119C)

// 扩展的
#pragma long_calls
void SaveGameEx(saveslot saveslotNum);
#pragma long_calls_off

void callSaveGameEx(saveslot saveslotNum);

// 存档号定义
// 0-6: 存档槽1，存档槽2，存档槽3，中断备份(校验和验证不通过时载入)，中断，通信斗技场，空位置
enum saveslot {Saveslot1, Saveslot2, Saveslot3, SuspendBackup, Suspend, LinkArena, SaveEmpty};

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

// 根据存档号取存档地址
// 输入参数：存档号
// 返回值：存档地址
_BYTE *GetSaveslotAddr(saveslot saveslotNum);


