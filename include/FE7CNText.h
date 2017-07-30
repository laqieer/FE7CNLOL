// by laqieer
// 2017/4/15
// �ı��������

#pragma once

#include "AgbTypes.h"
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
