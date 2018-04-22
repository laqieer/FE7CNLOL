// �浵���ж���س���
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

// ��Ϸ�浵������

// ԭ����

// ���������saveslotNum �浵��
// void SaveGame(saveslot saveslotNum);
#define SaveGame	sub(80A119C)

// ��չ��
#pragma long_calls
void SaveGameEx(saveslot saveslotNum);
#pragma long_calls_off

void callSaveGameEx(saveslot saveslotNum);

// �浵�Ŷ���
// 0-6: �浵��1���浵��2���浵��3���жϱ���(У�����֤��ͨ��ʱ����)���жϣ�ͨ�Ŷ���������λ��
enum saveslot {Saveslot1, Saveslot2, Saveslot3, SuspendBackup, Suspend, LinkArena, SaveEmpty};

// SRAM map
// �浵���ڴ沼��

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

// ���ݴ浵��ȡ�浵��ַ
// ����������浵��
// ����ֵ���浵��ַ
_BYTE *GetSaveslotAddr(saveslot saveslotNum);


