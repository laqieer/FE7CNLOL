#ifndef SOUND_H
#define SOUND_H



#define SOUND_LEFT 0
#define SOUND_RIGHT 1

//通道号， 高/低位	， 声音源，  频率
//direct sound
extern void GsPlaySound(u8 no,u8 lh,const u8 *sound, u16 sampleRate);
extern void GsSetDSoundVol(u8 left, u8 right);
extern void GsSwitchSOUND(u8 no,u8 lr,u8 stat);



//sound ctrl
extern void GsOpenSound(u8 sno);		// 打开声音部件
extern void GsSetSound1(GsSound1Cnt *ps1cnt);	//设置声音1
extern void GsSetSound2(GsSound2Cnt *ps2cnt);	//设置声音2
extern void GsSetSound3(GsSound3Cnt *ps3cnt);	//设置声音3
extern void GsSetSound4(GsSound4Cnt *ps4cnt);	//设置声音4

typedef struct GsSoundEffect
{
	u8 SoundNo;				//通道号
	u32 SndCnt0;			//控制字0
	u32 SndCnt1;			//控制字1
}GsSoundEffect;

void GsPlaySE(const GsSoundEffect *pse);			//播放效果音

void GsInitMod();
#endif