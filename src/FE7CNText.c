// by laqieer
// 2017/4/15
// 文本处理相关

#include "FE7CNText.h"
// 文本控制符定义
#include "textControlCodes.h"
// 文本
#include "text.h"

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
	return decodedText;
}

// 解码文本函数接口
__attribute__((section(".callDecodeText")))
char *callDecodeText(int textID)
{
	return decodeText(textID);
}

