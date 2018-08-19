// �浵���ж���س���
// by laqieer
// 2018-04-21

#include "FE7JSave.h"

// ���ݴ浵��ȡ�浵��ַ
// ����������浵��
// ����ֵ���浵��ַ(ָ��浵�۵�ָ��)
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

// ��չ��Ĵ浵����
// �������: saveslotNum �浵�����
void SaveGameEx(enum saveslot saveslotNum)
{
	_BYTE *pSaveslot; // ָ��浵�۵�ָ��
	UnitInSave *p; // ָ��д��浵��λ��
	int i; // ����
	SaveHeader header; // [sp+0h] [bp-94h]
	int v17[32]; // [sp+10h] [bp-84h]
	// int v9, v10, v11, v12, v13, v14, v15;
	
	// ��ȡ�浵�۵�ַ
	pSaveslot = GetSaveslotAddr(saveslotNum);
	
	sub(80A1A60)(3);
	*(_BYTE *)0x202BC00 = saveslotNum;
	
	// ������Ϸʱ��
	chapterDataInSaveBuffer = getPlayTime();

	// �浵�۵�ǰ72�ֽڼ�¼���½�����(Chapter Data)
	SRAMTransfer_WithCheck(&chapterDataInSaveBuffer, pSaveslot, 72);

	// ����������������
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

