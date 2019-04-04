// by laqieer
// 2017/4/19
// 插入的文本

#pragma once

#include "portraitID.h"

// 用字符数组赋值的方式要求:
// 1) 宏定义用字符('')，也可以直接定义成数值(会自动强制类型转换)
// 2) 汉字是双字节编码，要高低位分开赋值
// 琳篇序章琳开场对话
//const char text0835[] = {openRight,loadFace,'\x20',endl,'你'>>8,'你','好'>>8,'好','，'>>8,'，',endl,'我'>>8,'我','是'>>8,'是','琪'>>8,'琪','琪'>>8,'琪','。'>>8,'。',pushA,clearFace};

const char* const text[]=
{
	// 用字符串赋值
	// 字符串中可以用转义字符
	// 宏定义成字符串(""),C语言中多个字符串常量连在一起写表示拼接
/*	[0x0835] =	openRight loadFace "\x20" endl
				"你好，" endl
				"我是琪琪。" pushA
				clearFace	*/
/*	[0x0835] = talk(\x20,Right,	"你好，" endl
								"我是琪琪" pushA)	*/
/*	[0x0835] = sbsaysth(pSharon,Right,"你好，" endl
									"我是夏蓉。" pushA)	*/
/*	[0x0835] = openFarLeft loadFace pOswin openLeft loadFace pHector openFarRight loadFace pSurtrR openRight loadFace pSurtrL
				"就你们这小身板" endl
				"也叫重甲?" pushA
				clearFace openFarRight clearFace,	*/
	[0x0835] = openFarLeft loadFace pOswin
				"前面有座山" pushA
				openLeft loadFace pHectorNoble
				"不那是个人" pushA
				openFarRight loadFace pSurtrR
				openRight loadFace pSurtrL
				"一群战五渣" pushA
				clearFace openLeft clearFace openFarLeft clearFace
				openFarRight clearFace loadFace pBlackKnightR
				openRight loadFace pBlackKnightL
				"绿茶辛苦了" pushA,
	[0x0836] = openFarLeft loadFace pZelgius
				openLeft loadFace pZelgius
				openRight loadFace pZelgius
				openFarRight loadFace pZelgius
				//"绿茶什么时候画" endl
				//"眼睛和嘴的动作" pushA,
				toggleMouthMove
				"嘴部动画测试" endl pushA
				toggleMouthMove
				toggleSmile
				"微笑测试" endl pushA
				toggleMouthMove
				"微笑嘴部动画测试" endl pushA
				toggleMouthMove
				toggleSmile
				closeEyes "闭眼测试" endl pushA
				openEyes halfCloseEyes "半闭眼测试" endl pushA
				openEyes wink "使眼色测试" endl pushA
				openEyes "睁眼" endl pushA,
	[0x837] = openLeft loadFace pFenrir
				openFarLeft loadFace pFenrir
				openRight loadFace pFenrir
				openFarRight loadFace pFenrir
				"神兽芬利厄头像测试" pushA
				clearFace,
};
