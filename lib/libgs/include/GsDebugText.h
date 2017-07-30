#ifndef _GSDEBUGTEXT_H_
#define _GSDEBUGTEXT_H_

extern void GsDebugTextInit(u8 bgno, u8 tileloc, u8 screenoffset, u8 palno, u8 colno);//初始化文本层
//第一参数是要在输出字符是图层号
//第二参数是字库载入的块号 0 - 31 ，字库大小为1184Byte
//第三参数是MAP数据的载入块号 0 - 31 ，MAP数据为2KByte
//第四参数是字符用的调色板号，本字符用到该调色板的1号色即第二种颜色

extern void GsDebugTextOut(u8 x, u8 y, char *format,u32 age1, u32 age2);//输出字符串
//第一参数是列0-29，第二参数是行0-19，
//第三参数是输出的字符串，支持的格式符有%u,%d,%x,\n,\b,%u是以无符号整数输出，%s是以有符号整数输出,%x是以16进制显示,n为换行,\b为退格
//最后两个是要输出的数值的变量名，没有输出数值时要用0填充，否则会出错。 

extern void GsClearDebugText(void);
//清除写在屏幕上的文字

extern void GsCloseDebugText(void);
//关闭文本系统，清除字库和MAP等数据
#endif