// 尼诺贤者动画测试
// by laqieer
// 2017/8/12

#include	"FE7JBattleAnimation.h"

#include	"NinoSageAnimationData2_bin.h"
#include	"NinoSageAnimationData3_bin.h"
#include	"NinoSageAnimationData4_bin.h"

// 注意: 无压缩的data3和data4(2个OAM)必须是0x5800字节大小，不足的用0补齐，而且最后一行(0x57F0)必须是以01开头一行00(15个)
// 还有bug: miss动画会花
// 0xE00008是第一个职业动画的地址
__attribute__((section(".NinoSageAnimation")))
const BattleAnimation NinoSageAnimation = {
	"sagnino_mg1",
	0x08F0826C,
//	0x08F07F34,
	NinoSageAnimationData2_bin,
//	0x08F078AC,
	NinoSageAnimationData3_bin,
//	0x08F07224,
	NinoSageAnimationData4_bin,
	0x08F071B0
};