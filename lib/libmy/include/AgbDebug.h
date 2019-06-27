// 调试gba程序用
// by laqieer
// 2017/8/26

#ifndef	agb_debug
#define	agb_debug

//#define __DEBUG_VBA_THUMB
//#define __DEBUG_VBA_ARM
//#define __DEBUG_NOCASH
#define __DEBUG_EZ_OMEGA

#include "FE7JFunc.h"

void print(char *s);

typedef char * va_list;
#define va_start(ap,p) (ap = (char *) (&(p)+1))
#define va_arg(ap, type) ((type *) (ap += sizeof(type)))[-1]
#define va_end(ap)

char * strcpy(char * dest,const char *src);
char * strcat(char * dest, const char * src);
unsigned int strlen(const char * s);
void * memset(void * s,int c,unsigned int count);
void * memcpy(void * dest,const void *src,unsigned int count);
int sprintf(char * str, const char *fmt, ...);
void itoa(unsigned int n, char * buf);
int atoi(char* pstr);
void xtoa(unsigned int n, char * buf);
int isDigit(unsigned char c);
int isLetter(unsigned char c);

//	int printf (const char * szFormat, ...);

// 输出缓冲区最大长度
#define	BufferMaxLength	100

// http://blog.csdn.net/cp1300/article/details/7773239
#ifdef __DEBUG

#define DEBUG(info,...)\
{\
	char szBuffer[BufferMaxLength];\
	sprintf(szBuffer,"FILE: "__FILE__", LINE: %d:\n\t"info"\n", __LINE__, ##__VA_ARGS__);\
	_print(szBuffer);\
}

#else
#define DEBUG(info,...) 
#endif

#endif
