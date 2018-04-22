// �浵���ж���س���
// by laqieer
// 2018-04-21

#include "FE7JSave.h"

// ���ݴ浵��ȡ�浵��ַ
// ����������浵��
// ����ֵ���浵��ַ(ָ��浵�۵�ָ��)
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


