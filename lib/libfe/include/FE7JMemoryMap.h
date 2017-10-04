// by laqieer
// 2017/1/29
// VRAM和IO等在内存中的映射缓冲区定义

#pragma once

#include "AgbTypes.h"

// 总控标识，决定VBlank期间是否需要同步LCD屏幕信息
#define LCDIOBufferSyncFlag		*(u8 *)0x202BBB4
#define LCDIOBufferSyncEnable	1
#define LCDIOBufferSyncDisable	0

// LCD屏幕IO Map
// 同步函数 LCDIOMapSync()
// IO寄存器Buffer可以直接赋值，其他的Buffer定义成了指针，需要先解引用后赋值
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

// 控制标识，决定VBlank期间是否需要同步BG Map
#define BGMapBufferSyncFlag			*(u8 *)0x300000C
#define BGMapBufferSyncEnable(n)	(1<<(n)) //或，置位
#define BGMapBufferSyncDisable(n)	~(1<<(n))//与，清位
// 同步函数 BGMapBGPaletteSync()
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
// 控制标识，决定VBlank期间是否需要同步BG调色板
#define BGPaletteBufferSyncFlag		*(u8 *)0x300000D
#define BGPaletteBufferSyncEnable	1
#define BGPaletteBufferSyncDisable	0
// VBlank期间同步BG调色板的颜色过滤值
#define BGPaletteBufferSyncFilter	*(s8 *)0x30027F8
// BG调色板
// #define BGPaletteBuffer	(u16 (*)[16][16])0x2022860
#define	BGPaletteBuffer		((u16 *)0x2022860)
// OBJ调色板
// #define OBJPaletteBuffer	(u16 (*)[16][16])0x2022A60
#define	OBJPaletteBuffer	((u16 *)0x2022A60)
// OBJ调色板同步标识和BG调色板是共用的一个，故追加
#define PaletteBufferSyncFlag		*(u8 *)0x300000D

// Tile在内存中没有固定的缓冲区，而是一片指示如何将数据从rom或者wram传到vram的信息
// 传输函数 TileTransferInfoSync()
struct TileTransferInfo{
	void *src; // 源地址
	void *dst; // 目的地址
	u16 len; // 要传输的数据长度(字节数)
	s16 type; // 类型: 0-双字节拷贝 1-四字节拷贝 2-初始化(重复源地址的第一个数据)
};
struct TileTransferInfoBuff{
	u32 totalNum; // 数组长度
	u32 totalLen; // 要传输的数据总长度(字节数)
	struct TileTransferInfo TileTransferInfoTable[0]; // 数组长度可以动态变化
};
#define TileTransferInfoBuffer	(TileTransferInfoBuff *)0x2024C8C
enum TileTransferType{
	wordCopy,
	dwordCopy,
	quickSet
};

// OAM
// 同步函数 OAM1BufferSync() OAM1BufferSync()
// 同步信息初始化函数 OAMBufferSyncInfoInitialize(int SpriteNum1)
// 取精灵数函数	GetSpriteNum1();
#define OAMBuffer	(u16 (*)[128][4])0x3002850
// OAM数据划分成紧邻的前后两部分
#define SpriteNum1	*(_WORD *)0x3000032
#define SpriteNum2	*(_WORD *)0x3000022
// SpriteNum2 = 128 - SpriteNum1
#define OAMBuffer1	*(u16 (**)[4])0x3000028
#define OAMBuffer2	*(u16 (**)[4])0x3000018
#define OAM1		(**(u16 (**)[4])0x300002C)
#define OAM2		(**(u16 (**)[4])0x300001C)

// 魔法动画BGTile地址
#define spellBGTile		((void *)0x6001C00)
