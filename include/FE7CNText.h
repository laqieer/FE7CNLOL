// by laqieer
// 2017/4/15
// �ı��������

#pragma once

#include "AgbTypes.h"
#include "IDAPro.h"
#include "callFunc.h"

// ��һ��������ı�ID
#define	lastTextID		*(int *)0x202B5B0
// �������ı��Ĵ洢��
#define decodedText		((char *)0x202A5B0)

// ѹ���ı�ָ���
#define compressedText	((char **)0x8BBB370)
// C�����±������[]
// a[b] <==> *(a+b) <==> *(b+a) <==> b[a]

// ȡ���鳤��(������Ԫ�ظ���)
#define lengthof(array)	sizeof(array)/sizeof(array[0])

// ��������ѹ���ı�
#define	huffmanDecompressText	sub(8004240)

#pragma long_calls
// �����ı�
// �����ı�ID,����ָ���ַ�����(�������ı�)��ָ��
char *decodeText(int textID);
#pragma long_calls_off

char *callDecodeText(int textID);

#pragma long_calls
int getStringTextWidth(unsigned __int8 *text);
#pragma long_calls_off

typedef struct {
	void *pVRAMRootPointer;
	void *pCharGlyphs;
	void *pDrawGlyphRoutine;
	void *pVRAMPtrGetterMaybe;
	short VRAMTileValueBase;
	short nextTileIndex;
	short paletteId;
	unsigned char isAscii;
	unsigned char unk_17;
} FontInfo, *pFontInfo;

#define	ppFontStruct	(*(pFontInfo *)0x2028D68)

// ��ȡ��ʦ����
// char *getTacticianName();
#define getTacticianName	sub(802EBB0)

// �����ı������ʾ��ȣ����أ�
#define TEXT_LINE_WIDTH_MAX	0xC0	// R help text box
//#define TEXT_LINE_WIDTH_MAX	0xC4	// speech bubble

// ����ascii�ı������ֽڣ���ʾ��ȣ����أ�
// int GetStringTextWidthAscii(char *text);
#define GetStringTextWidthAscii	sub(8005A94)
