// by laqieer
// 2017/4/15
// 文本处理相关

#include "FE7CNText.h"
// 文本控制符定义
#include "textControlCodes.h"
// 文本
#include "text.h"

#include "AgbDebug.h"

//#include <string.h>
unsigned int strlen (const char *s);

/*
// 新增的文本的指针表，非压缩
// 该数组中的数组元素是指向字符数组的指针
// C语言字符数组与字符串: http://c.biancheng.net/cpp/html/80.html
const char* const text[] =
{
	// 琳的描述
//	[0x01B4] = "草原的少女",
//	[0x01B4] = "\x84\xC5\x94\xAD\x85\xFC\x8F\xB4\x8D\xBD",
	[0x01B4] = "爱吃醋溜鲤鱼",
//	[0x01B4] = "\x83\xac\x85\x80\x85\xc4\x8b\xf8\x8b\xbe\x94\x95",

	// 琳的名字
//	[0x04E6] = "琳迪斯"
//	[0x04E6] = "\x8B\xE9\x86\x82\x90\xA4"
	[0x04E6] = "白云"
//	[0x04E6] = "\x83\xc4\x94\xbe"
};
*/

// 插入换行符
void insertNewLine(char *text)
{
	DEBUG("insert new line at 0x%x", text)
	for(char *p = text + strlen(text); p >= text; p--)
	{
		*(p + 1) = *p;
	}
	*text = 1;
}

// 取一行文本的显示宽度(文本最大长度length)
int getLineWidthByLength(unsigned char *text, int length)
{
	int w = 0;
	unsigned char R, C;
	
	for(unsigned char *p = text; *p > 2 && !(*p >= 8 && *p <= 0x11) && p <= text + length; p++)
	{
		if(*p >= 0x81)
		{
			R = *p;
			C = *(++p);
			if((R >= 0xA1 && R <= 0xFE) && (C >= 0xA1 && C <= 0xFE))
			{
				w += 14; // extended gbk font width
			}
			else
			{
				if(R > 0x98 || C < 0x80)
				{
					R = 0x83;
					C = 0x9B;
				}
				w += *((unsigned char *)ppFontStruct->pCharGlyphs + 84 * (C - 128 + ((R - 129) << 7)) + 2);
			}
		}
		else if(*p == 0x80)
		{
			C = *(++p);
			if(C == 0x20)
			{
				w += getLineWidth(getTacticianName());
			}
			//TODO: C == 5, C == 6
		}
		//TODO: Ascii text
	}
	return w;
};

// 取一行文本的显示宽度
int getLineWidth(unsigned char *text)
{
	int w = 0;
	unsigned char R, C;
	
	for(unsigned char *p = text; *p > 2 && !(*p >= 8 && *p <= 0x11); p++)
	{
		if(*p >= 0x81)
		{
			R = *p;
			C = *(++p);
			if((R >= 0xA1 && R <= 0xFE) && (C >= 0xA1 && C <= 0xFE))
			{
				w += 14; // extended gbk font width
			}
			else
			{
				if(R > 0x98 || C < 0x80)
				{
					R = 0x83;
					C = 0x9B;
				}
				w += *((unsigned char *)ppFontStruct->pCharGlyphs + 84 * (C - 128 + ((R - 129) << 7)) + 2);
			}
		}
		else if(*p == 0x80)
		{
			C = *(++p);
			if(C == 0x20)
			{
				w += getLineWidth(getTacticianName());
			}
			//TODO: C == 5, C == 6
		}
		//TODO: Ascii text
	}
	return w;
};

// 文本自动换行
void autoInsertNewLine(unsigned char *text)
{
	int w = 0;
	unsigned char R, C;
	
	for(unsigned char *p = text; *p > 0; w = 0)
	{
		if(*p == 0x10)
			p += 2;
		if(*p > 2 && !(*p >= 8 && *p <= 0x11))
			p--;
		for(p++; *p > 2 && !(*p >= 8 && *p <= 0x11); p++)
		{
			if(*p >= 0x81)
			{
				R = *p;
				C = *(++p);
				if((R >= 0xA1 && R <= 0xFE) && (C >= 0xA1 && C <= 0xFE))
				{
					w += 14; // extended gbk font width
				}
				else
				{
					if(R > 0x98 || C < 0x80)
					{
						R = 0x83;
						C = 0x9B;
					}
					w += *((unsigned char *)ppFontStruct->pCharGlyphs + 84 * (C - 128 + ((R - 129) << 7)) + 2);
//					return;
				}
			
				if(w > TEXT_LINE_WIDTH_MAX && *(p + 1) != 1 && *(p + 1) != 2)
				{
					insertNewLine(--p);
					w = 0;
				}
			}
			else if(*p == 0x80)
			{
				C = *(++p);
				if(C == 0x20)
				{
					w += getLineWidth(getTacticianName());
				}
				//TODO: C == 5, C == 6
			
				if(w > TEXT_LINE_WIDTH_MAX && *(p + 1) != 1 && *(p + 1) != 2)
				{
					insertNewLine(--p);
					w = 0;
				}
			}
		
		//TODO: Ascii text			
		}
	}
};

// 解码文本
// 输入文本ID,返回指向字符数组(解码后的文本)的指针
char *decodeText(int textID)
{
// 直接返回rom内无压缩文本地址的做法会导致对话说明类(黑色字)文本显示成上一个文本，名称类(白色字)文本正常
/*		if(textID < lengthof(text) && text[textID] != 0)
		{
			lastTextID = textID;
			return text[textID];
		}
		else
			if(textID == lastTextID)
				return decodedText;
			else
				huffmanDecompressText(compressedText[textID],decodedText);
		lastTextID = textID;
		return decodedText;	*/
// 把无压缩的文本也拷贝进RAM
	int i;	// 字符串拷贝用循环变量

	if(textID == lastTextID)
		return decodedText;
	lastTextID = textID;
	if(textID < lengthof(text) && text[textID] != 0)
		for(i=0;decodedText[i] = text[textID][i];i++)
			;	
	else
		huffmanDecompressText(compressedText[textID],decodedText);
	autoInsertNewLine(decodedText);
	return decodedText;
}

// 解码文本函数接口
__attribute__((section(".callDecodeText")))
char *callDecodeText(int textID)
{
	return decodeText(textID);
}

