// by laqieer
// 2017/4/15
// 文本处理相关

#pragma once

#include "AgbTypes.h"
#include "callFunc.h"

// 上一个处理的文本ID
#define	lastTextID		*(int *)0x202B5B0
// 解码后的文本的存储地
#define decodedText		((char *)0x202A5B0)

// 压缩文本指针表
#define compressedText	((char **)0x8BBB370)
// C语言下标运算符[]
// a[b] <==> *(a+b) <==> *(b+a) <==> b[a]

// 取数组长度(数组内元素个数)
#define lengthof(array)	sizeof(array)/sizeof(array[0])

// 哈夫曼解压缩文本
#define	huffmanDecompressText	sub(8004240)

#pragma long_calls
// 解码文本
// 输入文本ID,返回指向字符数组(解码后的文本)的指针
char *decodeText(int textID);
#pragma long_calls_off

char *callDecodeText(int textID);

typedef struct {
	void *pVRAMRootPointer;
	void *pCharGlyphs;
	void *pDrawGlyphRoutine;
	void *pVRAMPtrGetterMaybe;
	short VRAMTileValueBase;
	short nextTileIndex;
	short paletteId;
	unsigned char unk_16;
	unsigned char unk_17;
} FontInfo, *pFontInfo;

#define	ppFontStruct	(*(pFontInfo *)0x2028D68)

// 获取军师名字
// char *getTacticianName();
#define getTacticianName	sub(802EBB0)

// 单行文本最大显示宽度（像素）
#define TEXT_LINE_WIDTH_MAX	0xC0
//#define TEXT_LINE_WIDTH_MAX	(0xC0 - 14 * 2)