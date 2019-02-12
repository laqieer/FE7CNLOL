// by laqieer
// 2017/3/29
// 和新的自由头像系统相关的定义

#pragma once

#include "AgbTypes.h"
#include "FE7JFunc.h"
#include "IDAPro.h"

/*
// 原来的头像指针结构体
struct Portrait{
	void *mainPortrait;	// 指向大头像的指针
	void *miniPortrait;	// 指向小头像的指针
	void *portraitPalette;	// 指向调色板的指针
	void *mouthFrame;	// 指向嘴部帧的指针
	void *classCard;	// 指向职业卡的指针
	s8 mouthPositionX;	// 嘴部帧横位置
	s8 mouthPositionY;	// 嘴部帧纵位置
	s8 eyePositionX;		// 眼睛帧横位置
	s8 eyePositionY;		// 眼睛帧纵位置
	s8 eyeControlFlag;	// 眼睛控制标识
	s8 dummy1;
	s8 dummy2;
	s8 dummy3;
};
*/

// 定义眼睛帧的信息
struct EyeFrameInfo{
	s8 width;	// 宽(单位:tile)(只对blinkOrWink2有效)
	s8 height;	// 高(单位:tile)(只对blinkOrWink2有效)
	s8 winkWidth;	// 眨眼帧的宽度(单位:tile)(只对blinkOrWink2有效)
	s8 winkHeight;	// 眨眼帧的高度(单位:tile)(只对blinkOrWink2有效)
	u8 *eyeFrame[3];	// 指向眨眼帧的指针数组: 睁眼，半闭眼，闭眼
	s16 *blinkTemplate;	// 指向眨眼帧模板的指针(只对blinkOrWink2有效)
};

// 扩展的头像指针结构体
struct Portrait{
	void *mainPortrait;	// 指向大头像的指针
	void *miniPortrait;	// 指向小头像的指针
	void *portraitPalette;	// 指向调色板的指针
	void *mouthFrame;	// 指向嘴部帧的指针
	union
	{
		void *classCard;	// 指向职业卡的指针
		struct EyeFrameInfo*eyeFrameInfo;		// 非职业卡的情况下是指向眼睛帧信息的指针
	} ce;
	s8 mouthPositionX;	// 嘴部帧横位置
	s8 mouthPositionY;	// 嘴部帧纵位置
	union
	{
		s8 eyePositionX;		// 眼睛帧横位置
		s8 offsetX;			//TODO eyeControlFlag=3时为头像整体水平位移
	} x;
	union
	{
		s8 eyePositionY;		// 眼睛帧纵位置
		s8 offsetY;			//TODO eyeControlFlag=3时为头像整体垂直位移
	} y;
	s8 eyeControlFlag;	// 眼睛控制标识,眨眼方式
	s8 portraitTemplatePair;	// 对话大头像模板对序号
	s8 portraitTemplateInBox;	// 人物数据界面头像框模板序号
	s8 portraitMaskInBox:7;	// 人物数据界面头像框蒙版序号
	s8 eyeMouthPositionAlignmentFlag:1;		// 最高位标识眼睛和嘴的坐标是否是8像素的倍数还是精细到像素
};

// 大头像精灵组合模板

// 老模板, 4块，头像在右侧，面向左侧
#define	oldPortraitTemplate1Left		0x8BFF828
// 老模板，4块，头像在左侧，面向右侧
#define	oldPortraitTemplate1Right	0x8BFF842
// 老模板, 6块，头像在右侧，面向左侧
#define	oldPortraitTemplate2Left		0x8BFF85C
// 老模板，6块，头像在左侧，面向右侧
#define	oldPortraitTemplate2Right	0x8BFF882
// 老模板, 8块，头像在右侧，面向左侧
#define	oldPortraitTemplate3Left		0x8BFF8A8
// 老模板，8块，头像在左侧，面向右侧
#define	oldPortraitTemplate3Right	0x8BFF8DA
// 老模板, 8块，头像在右侧，面向左侧
#define	oldPortraitTemplate4Left		0x8BFF90C
// 老模板，8块，头像在左侧，面向右侧
#define	oldPortraitTemplate4Right	0x8BFF93E

// 人物详细界面头像框内TSA模板

// 老模板，矮
#define	oldPortraitInBoxTemplateLow		0x81911D4
// 老模板，高
#define	oldPortraitInBoxTemplateHigh	0x819128C

// 头像指针表
#define portraitTableBase	0x8D5E23C
#define	portraitTableOriginal	((struct Portrait*)portraitTableBase)

// 根据头像ID计算ROM中的头像地址
//#define	GetPortrait			sub(80069B0)
// Portrait * GetPortrait(int portraitIndex)

/*
// 原来的眨眼和使眼色函数
#define blinkOrWink0		sub(80075F0)
// void oldBlinkOrWink(u32 *mempool, int eyeStatus);
*/

// 新的眨眼/使眼色(眨半边眼)函数,新增一个精灵，然后实时覆写VRAM中的Tile数据，支持非8像素对齐
void blinkOrWink1(u32 *mempool, int eyeStatus);

// 新的眨眼/使眼色(眨半边眼)函数,直接实时覆写VRAM中的Tile数据，支持自定义形状尺寸
void blinkOrWink2(u32 *mempool, int eyeStatus);

// 调用不同的眨眼/使眼色函数
void callBlinkOrWink(u32 *mempool, int eyeStatus);

// 眨眼/使眼色函数接口
void callCallBlinkOrWink(u32 *mempool, int eyeStatus);

// 调用到BlinkOrWink的函数1
// 眨眼
#pragma long_calls
void blink(s16 *mempool);
#pragma long_calls_off

// 调用到BlinkOrWink的函数1接口
void callBlink(s16 *mempool);

// 调用到BlinkOrWink的函数2
void sub_80077E8(s16 *mempool);

// 调用到BlinkOrWink的函数2接口
void call_sub_80077E8(s16 *mempool);

// 调用到BlinkOrWink的函数3
#pragma long_calls
void sub_8007824(s16 *mempool);
#pragma long_calls_off

// 调用到BlinkOrWink的函数3接口
void call_sub_8007824(s16 *mempool);

// 调用到BlinkOrWink的函数4
// 使眼色
void wink(s16 *mempool);

// 调用到BlinkOrWink的函数4接口
void callWink(s16 *mempool);

// 选择大头像精灵组合模板
void chooseMainPortraitSpriteTemplate(u32 *mempool);

// 新的选择大头像精灵组合模板函数的接口
void callChooseMainPortraitSpriteTemplate(s16 *mempool);

// 头像指针表扩展到0x100之后
#pragma long_calls
struct Portrait *GetPortrait(int portraitIndex);
#pragma long_calls_off

// 头像指针表扩展函数的接口
struct Portrait *callGetPortrait(int portraitIndex);

// 根据头像ID判断头像框是否需要下移
#define	PortraitHeightFix	sub(80070AC)
// signed int PortraitHeightFix(int portraitID)

// 新的人物详情界面头像框绘制函数，支持自定义模板
void drawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex);

// 新的人物详情界面头像框绘制函数的接口
void callDrawPortraitInBox(u16 *TSABufferInWRAM, int portraitID, int presentBGTileIndex, int presentBGPaletteIndex);

// 计算头像模板中每个精灵的3个属性
// X和Y分别是对应原来横式头像的参考点的像素偏移量
#define	getObjectAttribute1(shape,Y)		((((shape)&3)<<14)|((Y)&255))
#define	getObjectAttribute2(size,HFlip,X)	((((size)&3)<<14)|(((HFlip)&1)<<12)|((X)&511))
#define	getObjectAttribute3(tileNo)			((tileNo)&1023)

// 计算人物界面头像框TSA(tile编号)
// x和y分别是对应Tile在256x32的图中的坐标
#define	getTileNo(x,y)						((32 * (y) + (x))&1023)

// 计算无压缩图片数据长度(字节数)作为数据头
#define getUncompressedImageLength(byteNum)	((byteNum)<<8)

// 取2个数的较小值
#define min(a,b)	((a)<(b)?(a):(b))

// 取2个数的较大值
#define max(a,b)	((a)>(b)?(a):(b))

// 获取头像显示控制标识
#define getPortraitControlFlag		sub(8006C2C)
// int getPortraitControlFlag(int *data)

// 检查头像是否需要左右翻转后显示
#define checkPortraitInvert(data)	((getPortraitControlFlag(data)) & 1)

// 新的支持非8像素对齐的眨眼/使眼色函数
void blinkOrWink0(int *mempool, int eyeStatus);

// 使眼色帧精灵属性
#define	winkFrameTemplate	0x8BFF768
// 眨眼帧的精灵属性
#define	blinkFrameTemplate	0x8BFF7A8

// 嘴部动画函数
#pragma long_calls
void mouthAnimation(int *mempool);
#pragma long_calls_off

// 嘴巴精灵属性
#define	mouthFrameTemplate	0x8BFF7A8

// 嘴部动画接口函数
void callMouthAnimation(int *mempool);

// 蒙版指针表
extern const u16* const portraitMaskTable[];

// 人物界面头像框模板表
extern const void * const portraitInBoxTemplateTable[];

// 模板组表
extern const u32 portraitTemplatePairTable[][2];

// 新头像指针表(从0x100开始)
extern const struct Portrait portraitTableNew[];