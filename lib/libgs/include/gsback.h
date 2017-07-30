// 存盘 GSLIB 2.6

#ifndef _GsBack_
#define _GsBack_

#define SRAMCURRENT 0
#define	SRAMBEGIN	1
#define SRAMEND		2


extern u8 *p_SramPos;				

void GsSramInit();

int  GsSramReadWord();			//对字操作
void  GsSramWriteWord(int word);

char GsSramReadChar();				//对字节操作
void GsSramWriteChar(char c);

short GsSramReadHalfWord();				//对半字操作
void GsSramWriteHalfWord(short s);

void GsSramRead(u8 *buffer,long length);//大块结构体读取
void GsSramWrite(u8 *buffer,long length);//大块结构体写

void GsSramReadHuge(u8 *buffer,long size,long count);//大块结构体读取
void GsSramWriteHuge(u8 *buffer,long size,long count);//大块结构体写
 
void GsSramSeek(u8 flag,int step);		//指针移动
void GsSramSeektoBegin();					//指针移动到SRAM头部
void GsSramSeektoEnd();				//指针移动到SRAM底部

#endif