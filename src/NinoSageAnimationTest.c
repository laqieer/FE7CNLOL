// ��ŵ���߶�������
// by laqieer
// 2017/8/12

#include	"FE7JBattleAnimation.h"

#include	"NinoSageAnimationData2_bin.h"
#include	"NinoSageAnimationData3_bin.h"
#include	"NinoSageAnimationData4_bin.h"

// ע��: ��ѹ����data3��data4(2��OAM)������0x5800�ֽڴ�С���������0���룬�������һ��(0x57F0)��������01��ͷһ��00(15��)
// ����bug: miss�����Ứ
// 0xE00008�ǵ�һ��ְҵ�����ĵ�ַ
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