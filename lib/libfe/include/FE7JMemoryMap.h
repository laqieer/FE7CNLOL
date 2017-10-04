// by laqieer
// 2017/1/29
// VRAM��IO�����ڴ��е�ӳ�仺��������

#pragma once

#include "AgbTypes.h"

// �ܿر�ʶ������VBlank�ڼ��Ƿ���Ҫͬ��LCD��Ļ��Ϣ
#define LCDIOBufferSyncFlag		*(u8 *)0x202BBB4
#define LCDIOBufferSyncEnable	1
#define LCDIOBufferSyncDisable	0

// LCD��ĻIO Map
// ͬ������ LCDIOMapSync()
// IO�Ĵ���Buffer����ֱ�Ӹ�ֵ��������Buffer�������ָ�룬��Ҫ�Ƚ����ú�ֵ
#define DISPCNTBuffer	*(u16 *)0x3002790
#define GreenSwapBuffer	*(u16 *)0x3002792
#define DISPSTATBuffer	*(u16 *)0x3002794
#define VCOUNTBuffer	*(u16 *)0x3002796
#define BG0CNTBuffer	*(u16 *)0x300279C
#define BG1CNTBuffer	*(u16 *)0x30027A0
#define BG2CNTBuffer	*(u16 *)0x30027A4
#define BG3CNTBuffer	*(u16 *)0x30027A8
#define BGCNTBufferArray	((u16 *)0x300279C)
#define	BGnCNTBuffer(n)	BGCNTBufferArray[2*(n)]
#define BG0HOFSBuffer	*(u16 *)0x30027AC
#define BG0VOFSBuffer	*(u16 *)0x30027AE
#define BG1HOFSBuffer	*(u16 *)0x30027B0
#define BG1VOFSBuffer	*(u16 *)0x30027B2
#define BG2HOFSBuffer	*(u16 *)0x30027B4
#define BG2VOFSBuffer	*(u16 *)0x30027B6
#define BG3HOFSBuffer	*(u16 *)0x30027B8
#define BG3VOFSBuffer	*(u16 *)0x30027BA
#define WIN0HBuffer		*(u16 *)0x30027BC
#define WIN1HBuffer		*(u16 *)0x30027BE
#define WIN0VBuffer		*(u16 *)0x30027C0
#define WIN1VBuffer		*(u16 *)0x30027C2
#define WININBuffer		*(u16 *)0x30027C4
#define WINOUTBuffer	*(u16 *)0x30027C6
#define MOSAICBuffer	*(u16 *)0x30027C8
#define BLDCNTBuffer	*(u16 *)0x30027CC
#define BLDALPHABuffer	*(u16 *)0x30027D4
#define BLDYBuffer		*(u16 *)0x30027D6
#define BG2PABuffer		*(u16 *)0x30027D8
#define BG2PBBuffer		*(u16 *)0x30027DA
#define BG2PCBuffer		*(u16 *)0x30027DC
#define BG2PDBuffer		*(u16 *)0x30027DE
#define BG2XBuffer		*(u32 *)0x30027E0
#define BG2YBuffer		*(u32 *)0x30027E4
#define BG3PABuffer		*(u16 *)0x30027E8
#define BG3PBBuffer		*(u16 *)0x30027EA
#define BG3PCBuffer		*(u16 *)0x30027EC
#define BG3PDBuffer		*(u16 *)0x30027EE
#define BG3XBuffer		*(u32 *)0x30027F0
#define BG3YBuffer		*(u32 *)0x30027F4

// ���Ʊ�ʶ������VBlank�ڼ��Ƿ���Ҫͬ��BG Map
#define BGMapBufferSyncFlag			*(u8 *)0x300000C
#define BGMapBufferSyncEnable(n)	(1<<(n)) //����λ
#define BGMapBufferSyncDisable(n)	~(1<<(n))//�룬��λ
// ͬ������ BGMapBGPaletteSync()
// BG Map
#define BG0MapBaseAddr	*(u32 *)0x2024C60
#define BG1MapBaseAddr	*(u32 *)0x2024C64
#define BG2MapBaseAddr	*(u32 *)0x2024C68
#define BG3MapBaseAddr	*(u32 *)0x2024C6C
#define	BGnMapBaseAddrArray	((void **)0x2024C60)
#define	BGnMapBaseAddr(n)	BGnMapBaseAddrArray[n]
#define BG0Map			(*(u16 (*)[32][32])(BG0MapBaseAddr))
#define BG1Map			(*(u16 (*)[32][32])(BG1MapBaseAddr))
#define BG2Map			(*(u16 (*)[32][32])(BG2MapBaseAddr))
#define BG3Map			(*(u16 (*)[32][32])(BG3MapBaseAddr))
#define BG0MapBuffer	(u16 (*)[32][32])0x2022C60
#define BG1MapBuffer	(u16 (*)[32][32])0x2023460
#define BG2MapBuffer	(u16 (*)[32][32])0x2023C60
#define BG3MapBuffer	(u16 (*)[32][32])0x2024460
#define	BGnMapBuffer(n)	((u16 *)(0x2022C60 + 0x800 * (n)))
// ���Ʊ�ʶ������VBlank�ڼ��Ƿ���Ҫͬ��BG��ɫ��
#define BGPaletteBufferSyncFlag		*(u8 *)0x300000D
#define BGPaletteBufferSyncEnable	1
#define BGPaletteBufferSyncDisable	0
// VBlank�ڼ�ͬ��BG��ɫ�����ɫ����ֵ
#define BGPaletteBufferSyncFilter	*(s8 *)0x30027F8
// BG��ɫ��
// #define BGPaletteBuffer	(u16 (*)[16][16])0x2022860
#define	BGPaletteBuffer		((u16 *)0x2022860)
// OBJ��ɫ��
// #define OBJPaletteBuffer	(u16 (*)[16][16])0x2022A60
#define	OBJPaletteBuffer	((u16 *)0x2022A60)
// OBJ��ɫ��ͬ����ʶ��BG��ɫ���ǹ��õ�һ������׷��
#define PaletteBufferSyncFlag		*(u8 *)0x300000D

// Tile���ڴ���û�й̶��Ļ�����������һƬָʾ��ν����ݴ�rom����wram����vram����Ϣ
// ���亯�� TileTransferInfoSync()
struct TileTransferInfo{
	void *src; // Դ��ַ
	void *dst; // Ŀ�ĵ�ַ
	u16 len; // Ҫ��������ݳ���(�ֽ���)
	s16 type; // ����: 0-˫�ֽڿ��� 1-���ֽڿ��� 2-��ʼ��(�ظ�Դ��ַ�ĵ�һ������)
};
struct TileTransferInfoBuff{
	u32 totalNum; // ���鳤��
	u32 totalLen; // Ҫ����������ܳ���(�ֽ���)
	struct TileTransferInfo TileTransferInfoTable[0]; // ���鳤�ȿ��Զ�̬�仯
};
#define TileTransferInfoBuffer	(TileTransferInfoBuff *)0x2024C8C
enum TileTransferType{
	wordCopy,
	dwordCopy,
	quickSet
};

// OAM
// ͬ������ OAM1BufferSync() OAM1BufferSync()
// ͬ����Ϣ��ʼ������ OAMBufferSyncInfoInitialize(int SpriteNum1)
// ȡ����������	GetSpriteNum1();
#define OAMBuffer	(u16 (*)[128][4])0x3002850
// OAM���ݻ��ֳɽ��ڵ�ǰ��������
#define SpriteNum1	*(_WORD *)0x3000032
#define SpriteNum2	*(_WORD *)0x3000022
// SpriteNum2 = 128 - SpriteNum1
#define OAMBuffer1	*(u16 (**)[4])0x3000028
#define OAMBuffer2	*(u16 (**)[4])0x3000018
#define OAM1		(**(u16 (**)[4])0x300002C)
#define OAM2		(**(u16 (**)[4])0x300001C)

// ħ������BGTile��ַ
#define spellBGTile		((void *)0x6001C00)
