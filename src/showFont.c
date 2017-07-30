// by laqieer
// 2017/4/17
// 根据字符编码显示字模

#include "font.h"

// 比特解封装(扩展1bpp字模到2bpp)的参数
/*
const BUP fontM16UnpackInfo =
{
	32,
	1,
	2,
	2
};
*/

const BUP fontM12UnpackInfo =
{
	24,
	1,
	2,
	1
};

/*
// 试用12像素黑体字
const BUP fontM12UnpackInfoB =
{
	24,
	1,
	2,
	2
};	*/

// 14像素黑体字
const BUP fontM14UnpackInfo =
{
	28,
	1,
	2,
	2
};

// 2bpp下的一条16像素边
struct line{
	u32 dot0:2;
	u32 dot1:2;
	u32 dot2:2;
	u32 dot3:2;
	u32 dot4:2;
	u32 dot5:2;
	u32 dot6:2;
	u32 dot7:2;
	u32 dot8:2;
	u32 dot9:2;
	u32 dot10:2;
	u32 dot11:2;
	u32 dot12:2;
	u32 dot13:2;
	u32 dot14:2;
	u32 dot15:2;	
};

/*
// 逐点判断描灰边 该宏无意义
#define colorLine(n)	(if(font[i].dot##(n) == 0 && ((font[i].dot##(n-1) == fontColor) || (font[i].dot##(n+1) == fontColor) || (font[i-1].dot##(n) == fontColor) || (font[i+1].dot##(n) == fontColor))) \
							font[i].dot##(n) = outlineColor)
*/

// 对单色字模转换成的2bpp字模进行勾边
void outline(struct line *font, int fontColor, int outlineColor)
{
	int i;	// 行号

	// 第一行
	if(font[0].dot0 == 0 && (font[0].dot1 == fontColor || font[1].dot0 == fontColor))
		font[0].dot0 = outlineColor;
	if(font[0].dot1 == 0 && (font[0].dot0 == fontColor || font[0].dot2 == fontColor|| font[1].dot1 == fontColor))
		font[0].dot1 = outlineColor;
	if(font[0].dot2 == 0 && (font[0].dot1 == fontColor || font[0].dot3 == fontColor|| font[1].dot2 == fontColor))
		font[0].dot2 = outlineColor;
	if(font[0].dot3 == 0 && (font[0].dot2 == fontColor || font[0].dot4 == fontColor|| font[1].dot3 == fontColor))
		font[0].dot3 = outlineColor;
	if(font[0].dot4 == 0 && (font[0].dot3 == fontColor || font[0].dot5 == fontColor|| font[1].dot4 == fontColor))
		font[0].dot4 = outlineColor;
	if(font[0].dot5 == 0 && (font[0].dot4 == fontColor || font[0].dot6 == fontColor|| font[1].dot5 == fontColor))
		font[0].dot5 = outlineColor;
	if(font[0].dot6 == 0 && (font[0].dot5 == fontColor || font[0].dot7 == fontColor|| font[1].dot6 == fontColor))
		font[0].dot6 = outlineColor;
	if(font[0].dot7 == 0 && (font[0].dot6 == fontColor || font[0].dot8 == fontColor|| font[1].dot7 == fontColor))
		font[0].dot7 = outlineColor;
	if(font[0].dot8 == 0 && (font[0].dot7 == fontColor || font[0].dot9 == fontColor|| font[1].dot8 == fontColor))
		font[0].dot8 = outlineColor;
	if(font[0].dot9 == 0 && (font[0].dot8 == fontColor || font[0].dot10 == fontColor|| font[1].dot9 == fontColor))
		font[0].dot9 = outlineColor;
	if(font[0].dot10 == 0 && (font[0].dot9 == fontColor || font[0].dot11 == fontColor|| font[1].dot10 == fontColor))
		font[0].dot10 = outlineColor;
	if(font[0].dot11 == 0 && (font[0].dot10 == fontColor || font[0].dot12 == fontColor|| font[1].dot11 == fontColor))
		font[0].dot11 = outlineColor;
	if(font[0].dot12 == 0 && (font[0].dot11 == fontColor || font[0].dot13 == fontColor|| font[1].dot12 == fontColor))
		font[0].dot12 = outlineColor;
	if(font[0].dot13 == 0 && (font[0].dot12 == fontColor || font[0].dot14 == fontColor|| font[1].dot13 == fontColor))
		font[0].dot13 = outlineColor;
	if(font[0].dot14 == 0 && (font[0].dot13 == fontColor || font[0].dot15 == fontColor|| font[1].dot14 == fontColor))
		font[0].dot14 = outlineColor;	
	if(font[0].dot15 == 0 && (font[0].dot14 == fontColor || font[1].dot15 == fontColor))
		font[0].dot15 = outlineColor;

	// 中间行
	for(i=1;i<15;i++)
	{
		if(font[i].dot0 == 0 && (font[i].dot1 == fontColor || font[i-1].dot0 == fontColor || font[i+1].dot0 == fontColor))
			font[i].dot0 = outlineColor;
		if(font[i].dot1 == 0 && (font[i].dot0 == fontColor || font[i].dot2 == fontColor || font[i-1].dot1 == fontColor || font[i+1].dot1 == fontColor))
			font[i].dot1 = outlineColor;
		if(font[i].dot2 == 0 && (font[i].dot1 == fontColor || font[i].dot3 == fontColor || font[i-1].dot2 == fontColor || font[i+1].dot2 == fontColor))
			font[i].dot2 = outlineColor;
		if(font[i].dot3 == 0 && (font[i].dot2 == fontColor || font[i].dot4 == fontColor || font[i-1].dot3 == fontColor || font[i+1].dot3 == fontColor))
			font[i].dot3 = outlineColor;
		if(font[i].dot4 == 0 && (font[i].dot3 == fontColor || font[i].dot5 == fontColor || font[i-1].dot4 == fontColor || font[i+1].dot4 == fontColor))
			font[i].dot4 = outlineColor;
		if(font[i].dot5 == 0 && (font[i].dot4 == fontColor || font[i].dot6 == fontColor || font[i-1].dot5 == fontColor || font[i+1].dot5 == fontColor))
			font[i].dot5 = outlineColor;
		if(font[i].dot6 == 0 && (font[i].dot5 == fontColor || font[i].dot7 == fontColor || font[i-1].dot6 == fontColor || font[i+1].dot6 == fontColor))
			font[i].dot6 = outlineColor;
		if(font[i].dot7 == 0 && (font[i].dot6 == fontColor || font[i].dot8 == fontColor || font[i-1].dot7 == fontColor || font[i+1].dot7 == fontColor))
			font[i].dot7 = outlineColor;
		if(font[i].dot8 == 0 && (font[i].dot7 == fontColor || font[i].dot9 == fontColor || font[i-1].dot8 == fontColor || font[i+1].dot8 == fontColor))
			font[i].dot8 = outlineColor;
		if(font[i].dot9 == 0 && (font[i].dot8 == fontColor || font[i].dot10 == fontColor || font[i-1].dot9 == fontColor || font[i+1].dot9 == fontColor))
			font[i].dot9 = outlineColor;
		if(font[i].dot10 == 0 && (font[i].dot9 == fontColor || font[i].dot11 == fontColor || font[i-1].dot10 == fontColor || font[i+1].dot10 == fontColor))
			font[i].dot10 = outlineColor;
		if(font[i].dot11 == 0 && (font[i].dot10 == fontColor || font[i].dot12 == fontColor || font[i-1].dot11 == fontColor || font[i+1].dot11 == fontColor))
			font[i].dot11 = outlineColor;
		if(font[i].dot12 == 0 && (font[i].dot11 == fontColor || font[i].dot13 == fontColor || font[i-1].dot12 == fontColor || font[i+1].dot12 == fontColor))
			font[i].dot12 = outlineColor;
		if(font[i].dot13 == 0 && (font[i].dot12 == fontColor || font[i].dot14 == fontColor || font[i-1].dot13 == fontColor || font[i+1].dot13 == fontColor))
			font[i].dot13 = outlineColor;
		if(font[i].dot14 == 0 && (font[i].dot13 == fontColor || font[i].dot15 == fontColor || font[i-1].dot14 == fontColor || font[i+1].dot14 == fontColor))
			font[i].dot14 = outlineColor;
		if(font[i].dot15 == 0 && (font[i].dot14 == fontColor || font[i-1].dot15 == fontColor || font[i+1].dot15 == fontColor))
			font[i].dot15 = outlineColor;
	}

	// 末行
	if(font[15].dot0 == 0 && (font[15].dot1 == fontColor || font[14].dot0 == fontColor))
		font[15].dot0 = outlineColor;
	if(font[15].dot1 == 0 && (font[15].dot0 == fontColor || font[15].dot2 == fontColor|| font[14].dot1 == fontColor))
		font[15].dot1 = outlineColor;
	if(font[15].dot2 == 0 && (font[15].dot1 == fontColor || font[15].dot3 == fontColor|| font[14].dot2 == fontColor))
		font[15].dot2 = outlineColor;
	if(font[15].dot3 == 0 && (font[15].dot2 == fontColor || font[15].dot4 == fontColor|| font[14].dot3 == fontColor))
		font[15].dot3 = outlineColor;
	if(font[15].dot4 == 0 && (font[15].dot3 == fontColor || font[15].dot5 == fontColor|| font[14].dot4 == fontColor))
		font[15].dot4 = outlineColor;
	if(font[15].dot5 == 0 && (font[15].dot4 == fontColor || font[15].dot6 == fontColor|| font[14].dot5 == fontColor))
		font[15].dot5 = outlineColor;
	if(font[15].dot6 == 0 && (font[15].dot5 == fontColor || font[15].dot7 == fontColor|| font[14].dot6 == fontColor))
		font[15].dot6 = outlineColor;
	if(font[15].dot7 == 0 && (font[15].dot6 == fontColor || font[15].dot8 == fontColor|| font[14].dot7 == fontColor))
		font[15].dot7 = outlineColor;
	if(font[15].dot8 == 0 && (font[15].dot7 == fontColor || font[15].dot9 == fontColor|| font[14].dot8 == fontColor))
		font[15].dot8 = outlineColor;
	if(font[15].dot9 == 0 && (font[15].dot8 == fontColor || font[15].dot10 == fontColor|| font[14].dot9 == fontColor))
		font[15].dot9 = outlineColor;
	if(font[15].dot10 == 0 && (font[15].dot9 == fontColor || font[15].dot11 == fontColor|| font[14].dot10 == fontColor))
		font[15].dot10 = outlineColor;
	if(font[15].dot11 == 0 && (font[15].dot10 == fontColor || font[15].dot12 == fontColor|| font[14].dot11 == fontColor))
		font[15].dot11 = outlineColor;
	if(font[15].dot12 == 0 && (font[15].dot11 == fontColor || font[15].dot13 == fontColor|| font[14].dot12 == fontColor))
		font[15].dot12 = outlineColor;
	if(font[15].dot13 == 0 && (font[15].dot12 == fontColor || font[15].dot14 == fontColor|| font[14].dot13 == fontColor))
		font[15].dot13 = outlineColor;
	if(font[15].dot14 == 0 && (font[15].dot13 == fontColor || font[15].dot15 == fontColor|| font[14].dot14 == fontColor))
		font[15].dot14 = outlineColor;	
	if(font[15].dot15 == 0 && (font[15].dot14 == fontColor || font[14].dot15 == fontColor))
		font[15].dot15 = outlineColor;	
}

// 显示对话说明类文字(黑体字)
byte *showFont1(void *mempool, byte *text)
{
	byte R;	// 区码
	byte C;	// 位码
/*	FanTranslationFont font =
	{
		dataWidth: 	16,
		height:		fontHeaderSimfangM16.YSize,
		fontWidth:	16,	
		.dataWidth=16,
		.height=fontHeaderSimfangM16.YSize,
		.fontWidth=16,	
	};	// 转换自定义字模到汉化组规定的结构
	*/
	FanTranslationFont font;

	if(*(byte *)(*(word *)0x2028D68 + 22))
		return sub(8005A60)(mempool,text);
	R = text[0];
	C = text[1];
	text += 2;
	// gbk编码处理 codepage 936 简中
	if((R >= 0xA1 && R <= 0xFE) && (C >= 0xA1 && C <= 0xFE))
	{
/*		font->dataWidth = 16;
		font->height= fontHeaderSimfangM16.YSize;
		font->fontWidth = 16;	*/
		font.dataWidth = 16;
//		font.height= fontHeaderSimfangM16.YSize;
//		font.height= fontHeaderSimsunM16.YSize;
//		font.height= fontHeaderZpixM12.YSize;
//		font.height= fontHeaderSimheiM16.YSize;
//		font.height= fontHeaderSimsunM14.YSize;
		font.height = 14;
//		font.fontWidth = 16;
//		font.fontWidth = fontHeaderZpixM12.YSize;
//		font.fontWidth = fontHeaderSimheiM16.YSize;
//		font.fontWidth = fontHeaderSimsunM14.YSize;
		font.fontWidth = 14;
//		BitUnPack(&fontsDataSimfangM16[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* 16 * 16 / 8],font.data,&fontM16UnpackInfo);
//		BitUnPack(&fontsDataSimsunM16[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* font.dataWidth * font.height / 8],font.data,&fontM16UnpackInfo);
//		BitUnPack(&fontsDataZpixM12[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* 16 * fontHeaderZpixM12.YSize / 8],font.data,&fontM12UnpackInfoB);
//		BitUnPack(&fontsDataSimheiM16[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* 16 * 16 / 8],font.data,&fontM16UnpackInfo);
//		BitUnPack(&fontsDataSimsunM14[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* font.dataWidth * font.height / 8],font.data,&fontM14UnpackInfo);
//		BitUnPack(&fontsDataMsyhM14[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* 14 * 16 / 8],font.data,&fontM14UnpackInfo);
		BitUnPack(&fontsDataMsyhlM14[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* 14 * 16 / 8],font.data,&fontM14UnpackInfo);
		sub(80C0798)(mempool,&font,*(PTRFUN *)(*(word *)0x2028D68 + 8));
		return text;
	}
	// 汉化组的字模处理
	if ( R < 0x81 || R > 0x98 || C < 0x80 )
    {
      R = 0x83;
      C = 0x9B;
    }
    sub(80C0798)(
      mempool,
      84 * (C - 128 + ((R - 129) << 7)) + *(word *)(*(word *)0x2028D68 + 4),
      *(word *)(*(word *)0x2028D68 + 8));
	return text;
}

// 显示对话说明类文字(黑体字)的函数接口
__attribute__((section(".callShowFont1")))
byte *callShowFont1(void *mempool, byte *text)
{
	return showFont1(mempool,text);
}

// 显示名称类文字(白体字)
void showFont2(void *mempool, byte *text)
{
	byte R;	// 区码
	byte C;	// 位码
	FanTranslationFont font;

	if(*(byte *)(*(word *)0x2028D68 + 22))
		sub(8005A24)(mempool,text);
	else
		while(1)
		{
			R = *text;
			if(R <= 1)
				break;
			++text;
			if(R > 0x1F)
			{
				C = *text++;
				// gbk编码处理 codepage 936 简中
				if((R >= 0xA1 && R <= 0xFE) && (C >= 0xA1 && C <= 0xFE))
				{
					font.dataWidth = 16;
					font.height= fontHeaderZpixM12.YSize;
					font.fontWidth = fontHeaderZpixM12.YSize;
					BitUnPack(&fontsDataZpixM12[((R - 0xa1)*(0xFE - 0xA1 + 1) + (C - 0xa1))* 16 * fontHeaderZpixM12.YSize / 8],font.data,&fontM12UnpackInfo);
					outline(font.data,2,3);
					sub(80C0798)(mempool,&font,*(PTRFUN *)(*(word *)0x2028D68 + 8));
				}
				else
				{
					// 汉化组的字模处理
					if ( R < 0x81 || R > 0x98 || C < 0x80 )
    				{
      					R = 0x83;
      					C = 0x9A;
    				}
    				sub(80C0798)(mempool,84 * (C - 128 + ((R - 129) << 7)) + *(word *)(*(word *)0x2028D68 + 4),*(PTRFUN *)(*(word *)0x2028D68 + 8));
				}
			}
		}
}

// 显示名称类文字(白体字)的函数接口
__attribute__((section(".callShowFont2")))
void callShowFont2(void *mempool, byte *text)
{
	showFont2(mempool,text);
}
