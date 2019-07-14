// by laqieer
// 2017/4/15
// �ı��������

#include "FE7CNText.h"
// �ı����Ʒ�����
#include "textControlCodes.h"
// �ı�
#include "text.h"

#include "AgbDebug.h"

//#include <string.h>
unsigned int strlen (const char *s);

/*
// �������ı���ָ�����ѹ��
// �������е�����Ԫ����ָ���ַ������ָ��
// C�����ַ��������ַ���: http://c.biancheng.net/cpp/html/80.html
const char* const text[] =
{
	// �յ�����
//	[0x01B4] = "��ԭ����Ů",
//	[0x01B4] = "\x84\xC5\x94\xAD\x85\xFC\x8F\xB4\x8D\xBD",
	[0x01B4] = "���Դ�������",
//	[0x01B4] = "\x83\xac\x85\x80\x85\xc4\x8b\xf8\x8b\xbe\x94\x95",

	// �յ�����
//	[0x04E6] = "�յ�˹"
//	[0x04E6] = "\x8B\xE9\x86\x82\x90\xA4"
	[0x04E6] = "����"
//	[0x04E6] = "\x83\xc4\x94\xbe"
};
*/

// ���뻻�з�
void insertNewLine(char *text)
{
	DEBUG("insert new line at 0x%x", text)
	for(char *p = text + strlen(text); p >= text; p--)
	{
		*(p + 1) = *p;
	}
	*text = 1;
}

// ȡһ���ı�����ʾ���(�ı���󳤶�length)
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

// ȡһ���ı�����ʾ���
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

// �ı��Զ�����
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

// �����ı�
// �����ı�ID,����ָ���ַ�����(�������ı�)��ָ��
char *decodeText(int textID)
{
// ֱ�ӷ���rom����ѹ���ı���ַ�������ᵼ�¶Ի�˵����(��ɫ��)�ı���ʾ����һ���ı���������(��ɫ��)�ı�����
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
// ����ѹ�����ı�Ҳ������RAM
	int i;	// �ַ���������ѭ������

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

// �����ı������ӿ�
__attribute__((section(".callDecodeText")))
char *callDecodeText(int textID)
{
	return decodeText(textID);
}

