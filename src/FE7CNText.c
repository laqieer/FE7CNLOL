// by laqieer
// 2017/4/15
// �ı��������

#include "FE7CNText.h"
// �ı����Ʒ�����
#include "textControlCodes.h"
// �ı�
#include "text.h"

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
	return decodedText;
}

// �����ı������ӿ�
__attribute__((section(".callDecodeText")))
char *callDecodeText(int textID)
{
	return decodeText(textID);
}

