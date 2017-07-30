// by laqieer
// 2017/4/17
// �ֿ� ��ģ ����

#ifndef	__GUI_FONT_LIB_H__
#define	__GUI_FONT_LIB_H__

#include "callFunc.h"
#include "FE7JFunc.h"
#include "Tonc_types.h"
#include "Tonc_bios.h"

// �ֿ�ͷ
typedef struct gui_font_header{
	unsigned char	magic[4];	//'U'('S', 'M'), 'F', 'L', X---Unicode(Simple or MBCS) Font Library, X: ��ʾ�汾��. �ָߵ�4λ���� 0x12��ʾ Ver 1.2
	unsigned char	nSection; // ���ּ������ݡ�
	unsigned char	YSize;    /* height of font  */  	
	unsigned short	wCpFlag;    // codepageflag:  bit0~bit13 ÿ��bit�ֱ����һ��CodePage ��־�������1�����ʾ��ǰCodePage ��ѡ��������Ϊ��ѡ����
	unsigned short	nTotalChars;  // �ܵ��ַ���
	unsigned char	ScanMode;   // ɨ��ģʽ
} GUI_FONT_HEADER, *PGUI_FONT_HEADER;

/*
// ���� 16px
extern const GUI_FONT_HEADER fontHeaderSimfangM16;
extern const unsigned char fontsDataSimfangM16[];

// ���� 16px
extern const GUI_FONT_HEADER fontHeaderSimsunM16;
extern const unsigned char fontsDataSimsunM16[];

// ���� 16px
extern const GUI_FONT_HEADER fontHeaderSimheiM16;
extern const unsigned char fontsDataSimheiM16[];

// ���� 14px
extern const GUI_FONT_HEADER fontHeaderSimsunM14;
extern const unsigned char fontsDataSimsunM14[];

// ΢���ź� ���� 14px
extern const GUI_FONT_HEADER fontHeaderMsyhM14;
extern const unsigned char fontsDataMsyhM14[];
*/

// ΢���ź� ϸ�� 14px
extern const GUI_FONT_HEADER fontHeaderMsyhlM14;
extern const unsigned char fontsDataMsyhlM14[];

// Zpix 12px
extern const GUI_FONT_HEADER fontHeaderZpixM12;
extern const unsigned char fontsDataZpixM12[];

// �����鶨�������ṹ
typedef struct{
	u8 dataWidth; 	// ������
	u8 height;		// �߶�
	u8 fontWidth;	// ������
	u8 dummy;		// ����
	u8 data[0x50];	// ��ģ����
}FanTranslationFont;

#pragma long_calls
// ��ʾ�Ի�˵��������(������)
byte *showFont1(void *mempool, byte *text);
// ��ʾ����������(������)
void showFont2(void *mempool, byte *text);
#pragma long_calls_off

byte *callShowFont1(void *mempool, byte *text);
void callShowFont2(void *mempool, byte *text);

#endif	//__GUI_FONT_LIB_H__
