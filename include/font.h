// by laqieer
// 2017/4/17
// 字库 字模 字体

#ifndef	__GUI_FONT_LIB_H__
#define	__GUI_FONT_LIB_H__

#include "callFunc.h"
#include "FE7JFunc.h"
#include "Tonc_types.h"
#include "Tonc_bios.h"

// 字库头
typedef struct gui_font_header{
	unsigned char	magic[4];	//'U'('S', 'M'), 'F', 'L', X---Unicode(Simple or MBCS) Font Library, X: 表示版本号. 分高低4位。如 0x12表示 Ver 1.2
	unsigned char	nSection; // 共分几段数据。
	unsigned char	YSize;    /* height of font  */  	
	unsigned short	wCpFlag;    // codepageflag:  bit0~bit13 每个bit分别代表一个CodePage 标志，如果是1，则表示当前CodePage 被选定，否则为非选定。
	unsigned short	nTotalChars;  // 总的字符数
	unsigned char	ScanMode;   // 扫描模式
} GUI_FONT_HEADER, *PGUI_FONT_HEADER;

/*
// 仿宋 16px
extern const GUI_FONT_HEADER fontHeaderSimfangM16;
extern const unsigned char fontsDataSimfangM16[];

// 宋体 16px
extern const GUI_FONT_HEADER fontHeaderSimsunM16;
extern const unsigned char fontsDataSimsunM16[];

// 黑体 16px
extern const GUI_FONT_HEADER fontHeaderSimheiM16;
extern const unsigned char fontsDataSimheiM16[];

// 宋体 14px
extern const GUI_FONT_HEADER fontHeaderSimsunM14;
extern const unsigned char fontsDataSimsunM14[];

// 微软雅黑 常规 14px
extern const GUI_FONT_HEADER fontHeaderMsyhM14;
extern const unsigned char fontsDataMsyhM14[];
*/

// 微软雅黑 细体 14px
extern const GUI_FONT_HEADER fontHeaderMsyhlM14;
extern const unsigned char fontsDataMsyhlM14[];

// Zpix 12px
extern const GUI_FONT_HEADER fontHeaderZpixM12;
extern const unsigned char fontsDataZpixM12[];

// 汉化组定义的字体结构
typedef struct{
	u8 dataWidth; 	// 点阵宽度
	u8 height;		// 高度
	u8 fontWidth;	// 字体宽度
	u8 dummy;		// 无用
	u8 data[0x50];	// 字模数据
}FanTranslationFont;

#pragma long_calls
// 显示对话说明类文字(黑体字)
byte *showFont1(void *mempool, byte *text);
// 显示名称类文字(白体字)
void showFont2(void *mempool, byte *text);
#pragma long_calls_off

byte *callShowFont1(void *mempool, byte *text);
void callShowFont2(void *mempool, byte *text);

#endif	//__GUI_FONT_LIB_H__
