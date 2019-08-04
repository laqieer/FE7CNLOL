// 存档和中断相关程序
// by laqieer
// 2018-04-21

#include "FE7JSave.h"

// 根据存档号取存档地址
// 输入参数：存档号
// 返回值：存档地址(指向存档槽的指针)
/*
_BYTE *GetSaveslotAddr(enum saveslot saveslotNum)
{
	_BYTE *pSaveslot;

	switch(saveslotNum)
	{
		case Saveslot1:
			pSaveslot = Saveslot1Addr;
			break;
		case Saveslot2:
			pSaveslot = Saveslot2Addr;
			break;
		case Saveslot3:
			pSaveslot = Saveslot3Addr;
			break;
		case SuspendBackup:
			pSaveslot = SuspendBackupAddr;
			break;
		case Suspend:
			pSaveslot = SuspendAddr;
			break;
		case LinkArena:
			pSaveslot = LinkArenaAddr;
			break;
		case SaveEmpty:
			pSaveslot = SaveEmptyAddr;
			break;
		default:
			pSaveslot = NULL;
	}

	return pSaveslot;
}
*/

// 存档索引与存档号映射表
const enum saveslot saveslotNumTable[12] = {Saveslot1, Saveslot2, Saveslot3, Saveslot4, Saveslot5, Saveslot6, Saveslot7, Saveslot8, Saveslot9, Saveslot10, Saveslot11, Saveslot12};

_BYTE *GetSaveslotAddrEx(enum saveslot saveslotNum)
{
	_BYTE *pSaveslot;

	switch(saveslotNum)
	{
		case Saveslot1:
			pSaveslot = Saveslot1Addr;
			break;
		case Saveslot2:
			pSaveslot = Saveslot2Addr;
			break;
		case Saveslot3:
			pSaveslot = Saveslot3Addr;
			break;
		case Saveslot4:
			pSaveslot = Saveslot4Addr;
			break;
		case Saveslot5:
			pSaveslot = Saveslot5Addr;
			break;
		case Saveslot6:
			pSaveslot = Saveslot6Addr;
			break;
		case Saveslot7:
			pSaveslot = Saveslot7Addr;
			break;
		case Saveslot8:
			pSaveslot = Saveslot8Addr;
			break;
		case Saveslot9:
			pSaveslot = Saveslot9Addr;
			break;
		case Saveslot10:
			pSaveslot = Saveslot10Addr;
			break;
		case Saveslot11:
			pSaveslot = Saveslot11Addr;
			break;
		case Saveslot12:
			pSaveslot = Saveslot12Addr;
			break;
		case SuspendBackup:
			pSaveslot = SuspendBackupAddr;
			break;
		case Suspend:
			pSaveslot = SuspendAddr;
			break;
		case LinkArena:
			pSaveslot = LinkArenaAddr;
			break;
		case SaveEmpty:
			pSaveslot = SaveEmptyAddr;
			break;
		default:
			pSaveslot = NULL;
	}

	return pSaveslot;
}

#ifndef __INTELLISENSE__
__attribute__((section(".callGetSaveslotAddrEx")))
#endif
_BYTE *callGetSaveslotAddrEx(enum saveslot saveslotNum)
{
	return GetSaveslotAddrEx(saveslotNum);
}
/*
// buggy
bool ChechSave(int *saveslotHead, enum saveslot saveslotNum)
{
  int *saveslotHead2; // r4
  signed int v4; // r1
  int saveslotHead1; // [sp+0h] [bp-1Ch]

  saveslotHead2 = saveslotHead;
  if ( !saveslotHead )
    saveslotHead2 = &saveslotHead1;
  (*pprSRAMTransfer)(16 * saveslotNum + 0xE000064, saveslotHead2, 16);
  if ( *((_WORD *)saveslotHead2 + 2) != 0x200A || saveslotNum > 6 )
    return 0;
  switch ( saveslotNum )
  {
    case Saveslot1:
    case Saveslot2:
    case Saveslot3:
      v4 = 0x11217;
      break;
    case SuspendBackup:
    case Suspend:
      v4 = 0x20509;
      break;
    case LinkArena:
      v4 = 0x20112;
      break;
    case SaveEmpty:
      v4 = 0x20223;
      break;
    default:
      return 0;
  }
  if ( *saveslotHead2 != v4 )
    return 0;
  return SaveMetadata_VerifyChecksum(saveslotHead2);
}
*/
/*
// white screen when starting game
bool ChechSaveEx(int *saveslotHead, enum saveslot saveslotNum)
{
	int saveslotHead1;
	int *saveslotHead2;
	
	if(saveslotNum > Saveslot12)
		return 0;
	saveslotHead2 = saveslotHead ? saveslotHead : &saveslotHead1;
	(*pprSRAMTransfer)(16 * saveslotNum + 0xE000064, saveslotHead2, 16);
	if(*saveslotHead2 == 0)
		return 0;
	return SaveMetadata_VerifyChecksum(saveslotHead2);
}

// check extended save slot by play time
#ifndef __INTELLISENSE__
__attribute__((section(".callChechSaveEx")))
#endif
bool callChechSaveEx(int *saveslotHead, unsigned int saveslotNum)
{
	return ChechSaveEx(saveslotHead, saveslotNum);
}
*/
// disable save check
#ifndef __INTELLISENSE__
__attribute__((section(".callCheckSaveAndGetPointerEx")))
#endif
_BYTE *callCheckSaveAndGetPointerEx(enum saveslot saveslotNum)
{
	return GetSaveslotAddrEx(saveslotNum);
}

// 扩展后的存档程序
// 输入参数: saveslotNum 存档槽序号
void SaveGameEx(enum saveslot saveslotNum)
{
	_BYTE *pSaveslot; // 指向存档槽的指针
	UnitInSave *p; // 指向写入存档的位置
	int i; // 人数
	SaveHeader header; // [sp+0h] [bp-94h]
	int v17[32]; // [sp+10h] [bp-84h]
	// int v9, v10, v11, v12, v13, v14, v15;
	
	// 获取存档槽地址
	pSaveslot = GetSaveslotAddrEx(saveslotNum);
	
	sub(80A1A60)(3);
	*(_BYTE *)0x202BC00 = saveslotNum;
	
	// 保存游戏时长
	chapterDataInSaveBuffer = getPlayTime();

	// 存档槽的前72字节记录了章节数据(Chapter Data)
	SRAMTransfer_WithCheck(&chapterDataInSaveBuffer, pSaveslot, 72);

	// 保存所有人物数据
	p = pSaveslot + 72;
	i = maxUnitNumberInSave - 1;
	do
		SaveUnit(&units_player[51-i--], p++);
	while(i >= 0);
	LoadSomeUnitStatThingUnlockIdk(v17);
	i = maxUnitNumberInSave - 1;
	do
		SetSomeUnitStatThingUnlockMaybeIdk(units_player[51-i--].character->id, v17);
	while(i >= 0);
	SaveSomeUnitStatThingUnlockIdk(v17);

	SaveConvoyItems(pSaveslot + 1944);
	
	/*
	SaveBWLEntries(pSaveslot + 2144, 2144, v9, v10);
	SaveChapterWinData(pSaveslot + 3264, 3264, v11, v12);
	Save0203EC98((int)pSaveslot, v13, v14, v15);
	*/
	SaveBWLEntries(pSaveslot + 2144);
	SaveChapterWinData(pSaveslot + 3264);
	Save0203EC98(pSaveslot);

	SaveGlobalEventIds(pSaveslot + 3456);
	header.magicA = 0x11217;
	header.saveType = 0;
	// setSaveHeader(header, saveslotNum);
	setSaveHeader(&header, saveslotNum);
	sub(80A0F60)(saveslotNum);
}

#ifndef __INTELLISENSE__
__attribute__((section(".callSaveGameEx")))
#endif
void callSaveGameEx(enum saveslot saveslotNum)
{
	SaveGameEx(saveslotNum);
}

/*
void setSaveHeader(SaveHeader *pSaveHeader, unsigned int saveslotNum)
{
  SaveHeader *pHeader; // r4
  signed int saveNum; // r6
  signed int saveType; // r0
  int v5; // r3

  pHeader = pSaveHeader;
  saveNum = saveslotNum;
  pSaveHeader->magicB = 0x200A;
  pSaveHeader->sramOffset = (unsigned int)GetSaveslotAddr(saveslotNum);
  if ( saveNum <= 6 )
  {
    saveType = pHeader->saveType;
    if ( saveType == 2 )
    {
      pHeader->sramSize = 0x874;
      goto LABEL_15;
    }
    if ( saveType <= 2 )
    {
      if ( pHeader->saveType )
      {
        if ( saveType != 1 )
          return;
        pHeader->sramSize = 0x1800+4*459;
      }
      else
      {
        pHeader->sramSize = 0xD8C;
      }
LABEL_15:
      sub(80A2350)(pHeader);
      SRAMTransfer_WithCheck(pHeader, (_BYTE *)(16 * saveNum + 0xE000064), 16, v5);
      return;
    }
    if ( saveType == 3 )
    {
      pHeader->sramSize = 0xC00;
      goto LABEL_15;
    }
    if ( saveType == 255 )
    {
      pHeader->sramSize = 0;
      pHeader->sramOffset = 0;
      pHeader->magicB = 0;
      goto LABEL_15;
    }
  }
}
*/

