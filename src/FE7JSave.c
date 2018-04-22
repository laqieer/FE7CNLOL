// 存档和中断相关程序
// by laqieer
// 2018-04-21

#include "FE7JSave.h"

// 根据存档号取存档地址
// 输入参数：存档号
// 返回值：存档地址(指向存档槽的指针)
_BYTE *GetSaveslotAddr(saveslot saveslotNum)
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


