// 声音播放
// by laqieer
// 2017/6/9

#pragma once

#include "AgbSound.h"

// ---copied from mks4agbLib.h

//Structure of CGB Virtual Channel
typedef struct {
    u8 ch1[64];
    u8 ch2[64];
    u8 ch3[64];
    u8 ch4[64];
} CgbChannels;

//Structure of Music Player Table
typedef struct {
    MusicPlayerArea *ma;
    MusicPlayerTrack *ta;
    u32 tn;
} MPlayTable;

//Structure of Song Table
typedef struct {
    SongHeader *so;
    u16 ms, me;
} SongTable;


#define CGB1_P12 ((WaveData *)0)
#define CGB1_P25 ((WaveData *)1)
#define CGB1_P50 ((WaveData *)2)
#define CGB1_P75 ((WaveData *)3)
#define CGB2_P12 CGB1_P12
#define CGB2_P25 CGB1_P25
#define CGB2_P50 CGB1_P50
#define CGB2_P75 CGB1_P75
#define CGB4_C15 ((WaveData *)0)
#define CGB4_C07 ((WaveData *)1)

// ---copied from mks4agbLib.h

// Memory Map

// 需要在初始化时拷贝到内存中
#define		SoundMainRAM		((void *)0x80BE428)
// music player总数
// Total number of declared Music Players.
//#define		__total_mplay_n		(*(u8 *)0x86EA860)
//#define		total_mplay_n 		((u16)__total_mplay_n)
// music player表
// #define		mplay_table			((MPlayTable *)0x86EA862)
#define			mplay_table			((MPlayTable *)0x86EA858)
// 定义各个音乐播放器地址以便于使用

// Highest (BGM)
#define			m4a_mplay000		mplay_table[0].ma
// High (Map Music)
#define			m4a_mplay001		mplay_table[1].ma
// Mid-High
#define			m4a_mplay002		mplay_table[2].ma
// Medium
#define			m4a_mplay003		mplay_table[3].ma
// Medium
#define			m4a_mplay004		mplay_table[4].ma
// Mid-Low
#define			m4a_mplay005		mplay_table[5].ma
// Low (SFX)
#define			m4a_mplay006		mplay_table[6].ma
// Lowest (SFX)
#define			m4a_mplay007		mplay_table[7].ma
#define			m4a_mplay008		mplay_table[8].ma
// 简写
#define			mp00				m4a_mplay000
#define			mp01				m4a_mplay001
#define			mp02				m4a_mplay002
#define			mp03				m4a_mplay003
#define			mp04				m4a_mplay004
#define			mp05				m4a_mplay005
#define			mp06				m4a_mplay006
#define			mp07				m4a_mplay007
#define			mp08				m4a_mplay008

// 音乐表
#define		song_table			((SongTable *)0x86EA8D0)
// u8 m4a_memacc_area[];
#define		m4a_memacc_area		((u8 *)0x3005D00)
// MPlayExtender(m4a_cgbchn);
#define		m4a_cgbchn			(*(u8 **)0x80BF0B8)

// 播放函数指针表
// sound command handler functions
// void ply_??????(MusicPlayerArea *ma,MusicPlayerTrack *mt);
#define		MPlyJmpTbl			((PTRFUN)0x86C4560)

// [0x86EA858]=0x3005A30
//#define		musicPlayerArea		((MusicPlayerArea *)0x86EA858)

// [0x86EA85C]=0x3001628

// MidiKey2fr()函数中用到
#define		FreqTable			((u32 *)0x86C4600)
#define		ScaleTable			((u8 *)0x86C45F0)

// ply_note_rev01()函数中用到
#define		clock_tbl_rev01		((u8 *)0x86C47D4)

// 其他
#define		pcmVBtbl_rev		((u16 *)0x86C46D4)
#define		CgbScTable			((u8 *)0x86C46EC)
#define		CgbFrTable			((u16 *)0x86C4770)
#define		NoiseTable			((u8 *)0x86C4788)
#define		Cgb3vol				((u8 *)0x86C47C4)

// 一个跳转表
#define		ExtMPlyJmpTbl		((PTRFUN)0x3005A70)

// 又是一个函数指针表
// extended sound command handler functions
#define		xcmd_tbl			((PTRFUN)0x86C4808)

// 指针表xcmd_tbl里的函数
// extended sound command handler functions
// void ply_x+????(MusicPlayerArea *ma,MusicPlayerTrack *mt);

// void ply_xxx(int a1, int a2);
#define	ply_xxx		sub(80C0444)
// void ply_xwave(int a1, int a2);
#define	ply_xwave	sub(80C0458)
// int ply_xtype(int a1, int a2);
#define	ply_xtype	sub(80C04A0)
// int ply_xatta(int a1, int a2);
#define	ply_xatta	sub(80C04B4)
// int ply_xdeca(int a1, int a2);
#define	ply_xdeca	sub(80C04C8)
// int ply_xsust(int a1, int a2);
#define	ply_xsust	sub(80C04DC)
// int ply_xrele(int a1, int a2);
#define	ply_xrele	sub(80C04F0)
// int ply_xiecv(int a1, int a2);
#define	ply_xiecv	sub(80C0504)
// int ply_xiecl(int a1, int a2);
#define	ply_xiecl	sub(80C0510)
// int ply_xleng(int a1, int a2);
#define	ply_xleng	sub(80C051C)
// int ply_xswee(int a1, int a2);
#define	ply_xswee	sub(80C0530)

// Function List

// (1) 音乐引擎初始化

// (1) Initialization of Sound Functions
// void m4aSoundInit(void);
// This initializes the sound functions. Only call this once when starting up a game. 
#define		m4aSoundInit		sub(80BF054)

// void SoundInit_rev01(SoundArea *m4a_sound);
#define		SoundInit_rev01		sub(80BF454)

// void MPlayExtender(_BYTE *m4a_cgbchn);
#define		MPlayExtender		sub(80BF310)

// (2) 设置音乐函数操作模式

// (2) Setting Up the Sound Function Operating Modes

//  void m4aSoundMode(u32 mode);
//This sets up the sound function operating modes. The argument, mode, contains the following values. 

//Note: The following values for SOUND_MODE_xxxx_xxxx are constants defined in AgbSound.h.

//   *Direct Sound Reverb
// mode = SOUND_MODE_REVERB_SET + ( Reverb Value: 0 to 127 );

//   *Number of Simultaneously Produced Direct Sounds
//        mode = ( Number of Simultaneously-Produced Sounds: 1 to 12 )
//          << SOUND_MODE_MAXCHN_SHIFT;

//   *Direct Sound Master Volume
//        mode = ( Volume: 1 to 15 ) << SOUND_MODE_MASVOL_SHIFT;

//   *Direct Sound Playback Frequency
//        mode = SOUND_MODE_FREQ_?????;
//               The value ????? is defined in AgbSound.h.  (There are 12 types.)

//   *Number of Final Output D/A Conversion Bits
//        mode = SOUND_MODE_DA_BIT_?;
//               The ? range: 9 to 6

//   (The above values may be set up at the same time using OR.)
//Use the external variable sound_mode_i to return the operating mode to its original settings.
//    (Program Example) 
//    ... 
//    m4aSoundMode(sound_mode_i); 

#define m4aSoundMode(P1) SoundMode_rev01(P1)
// void SoundMode_rev01(u32 mode);

#define	SoundMode_rev01		sub(80BF5F0)


// 音乐函数操作模式

// const u8 __sound_mode_i[];
// #define sound_mode_i ((u32)__sound_mode_i)

// void MPlayOpen_rev01(int a1, _BYTE *a2, unsigned __int8 a3);
#define	MPlayOpen_rev01		sub(80BF794)

// signed int MPlayFadeOut(int a1, __int16 a2);
#define	MPlayFadeOut		sub(80BF034)

// int MPlayContinue(int a1);
#define	MPlayContinue		sub(80BF018)

// midi键值转换为频率
// u32 MidiKey2fr(int a1, unsigned __int8 a2, int a3);
#define	MidiKey2fr			sub(80BEFB0)

// int umul3232H32(unsigned int a1, unsigned int a2);
#define	umul3232H32			sub(80BE394)

// int ply_mod_rev01();
#define	ply_mod_rev01		sub(80BEF9C)

// void ld_r3_tp_adr_i_rev(int a1, int a2);
#define	ld_r3_tp_adr_i_rev	sub(80BEF7C)

// void clear_modM(int a1, int a2);
#define	clear_modM			sub(80BEF60)

// int ply_lfos_rev01(int a1, int a2);
#define	ply_lfos_rev01		sub(80BEF88)

// signed int ply_endtie_rev01(int a1, int a2);
#define	ply_endtie_rev01	sub(80BEF20)

// void ClearChain_rev(int a1);
#define	ClearChain_rev		sub(80BF42C)

// void TrkVolPitSet_rev01(int a1, int a2);
#define	TrkVolPitSet_rev01	sub(80BF9F8)

// unsigned int ChnVolSetAsm();
#define	ChnVolSetAsm		sub(80BECF0)

// void ply_note_rev01(int a1, int a2, unsigned int a3);
#define	ply_note_rev01		sub(80BED20)

// void TrackStop_rev01(int a1, int a2);
#define	TrackStop_rev01		sub(80BECAC)

// void FadeOutBody_rev01(int a1);
#define	FadeOutBody_rev01	sub(80BF930)

// void Clear64byte_rev(int a1);
#define	Clear64byte_rev		sub(80BF440)

// int MPlayMain_rev01(int result);
#define	MPlayMain_rev01		sub(80BEA44)

// int SoundVSync_rev01();
#define	SoundVSync_rev01	sub(80BE9F8)

// void ld_r3_tp_adr_i(int a1, int a2);
#define	ld_r3_tp_adr_i		sub(80BE868)

// sound command handler functions
// void ply_??????(MusicPlayerArea *ma,MusicPlayerTrack *mt);

// int ply_tune();
#define	ply_tune			sub(80BE9CC)

// int ply_modt();
#define	ply_modt			sub(80BE9B4)

// int ply_lfodl();
#define	ply_lfodl			sub(80BE9A8)

// int ply_bendr();
#define	ply_bendr			sub(80BE994)

// int ply_bend();
#define	ply_bend			sub(80BE980)

// int ply_pan();
#define	ply_pan				sub(80BE96C)

// int ply_vol();
#define	ply_vol				sub(80BE958)

// int ply_voice(int a1, int a2);
#define	ply_voice			sub(80BE928)

// int ply_keysh();
#define	ply_keysh			sub(80BE914)

// int ply_tempo();
#define	ply_tempo			sub(80BE900)

// int ply_prio();
#define	ply_prio			sub(80BE8F4)

// int ply_rept(int a1, int a2);
#define	ply_rept			sub(80BE8C4)

// void ply_pend(int a1, int a2);
#define ply_pend			sub(80BE8B0)

// int ply_patt(int a1, int a2);
#define	ply_patt			sub(80BE894)

// void ply_goto(int a1, int a2);
#define	ply_goto			sub(80BE874)

// void chk_adr_r2();
#define	chk_adr_r2			sub(80BE84E)

// void ldrb_r3_r2(int a1, int a2, _BYTE *a3);
#define	ldrb_r3_r2			sub(80BE84C)

// int MPlyJmpTblCopy();
#define	MPlyJmpTblCopy		sub(80BE834)

// void  ply_fine(int a1, int a2);
#define	ply_fine			sub(80BE804)

// int ClearChain(int result);
#define	ClearChain			sub(80BE7E4)

// int SoundMainBTM(int a1);
#define	SoundMainBTM		sub(80BE7C8)

// int SoundMain();
#define	SoundMain			sub(80BE3A4)

// (3) 声音引擎的主循环

// (3) Sound Driver Main Loop

//  void m4aSoundMain(void);
//This is the main loop of the sound driver. Call it every 1/60 of a second. 

//The process flow works as follows.   m4aSoundVSync()(mentioned below) is called immediately after the V-Blank interrupt.  Then after running BG or OBJ processes, this routine is called. 

#define	m4aSoundMain		sub(80BF0CC)

// (8) 根据歌曲编号播放对应的歌曲

// (8) Starting a Performance Using a Song Number

//  void m4aSongNumStart(u16 n);
//This starts playing the song with song number n. In this case, the Music Player to be used is already specified in the sound editor, so it is not necessary when this function is called. 

//  (Sample Program) 
//    ... 
//    //This starts playing the song with song number x.  
//    m4aSongNumStart( x ); 
//    ... 
// 

//Note: The number of the Music Player used by the song with the song number x can be obtained using song_table[x].ms. The work area of the Music Player with that number (???) can be obtained using mplay_table[???].ma.

#define	m4aSongNumStart		sub(80BF0D8)

// (9) 若指定的歌曲当前不在对应播放器上播放，则开始播放该曲，否则什么都不做

// (9) Starting or Changing a Performance Using a Song Number

//  void m4aSongNumStartOrChange(u16 n);
//This function starts playing the specified song when a different song is being played on the Music Player that is supposed to play the song with the song number n, or when the same song is currently stopped. When the same song is already being played, it does not do anything. 

#define	m4aSongNumStartOrChange		sub(80BF1A4)

// (10) 没看懂和(9)的区别

// (10) Starting or Restarting a Perfomance Using a Song Number

//  void m4aSongNumStartOrContinue(u16 n);
// This function starts playing a new song when a different song has been playing on the Music Player that is supposed to be playing song number n. When that song has been stopped, this function will restart it. When the same song is already being played, it does not do anything.

#define	m4aSongNumStartOrContinue	sub(80BF1D8)

// (7) 在指定的播放器上播放指定的曲子

// (7) Starting a Performance Using a Song Title

//  void m4aMPlayStart(MusicPlayerArea *&m4a_mplay???, SongHeader *SongName);
//Music Player number ??? is used to perform the song data in the song title  Songname. 
//(??? is a three-digit number, while Songname is the name of a file.) 
//(*It is also possible to write  &m4a_mplay??? as mplay_table[???].ma.)

//  (Sample Program) 
//    ... 
//    // Start the song SongName using the Number 1 Music Player.  
//    m4aMPlayStart(&m4a_mplay001, SongName); 
//    ... 
// 

//Note: In order to find out what song is playing currently on the music player, refer to the structural element m4a_mplay???.song in the work area.

//  (Sample Program) 
//    ... 
//    // Substitute the song name playing on Music Player 2 into the variable whatsong. 
//    (SongHeader *)whatsong = m4a_mplay001.song; 
//    ... 
// 

//Also, in order to find out whether or not a song is currently playing on the Music Player, refer to the structural element m4a_mplay???.stat in the work area.

//  (Sample Program) 
//    ... 
//    if ( (m4a_mplay001.stat & MUSICPLAYER_STATUS_TRACK) == 0 ) 
//    { 
//      // The track currently being played does not exist.

//      if ( (m4a_mplay001.stat & MUSICPLAYER_STATUS_PAUSE) != 0 ) 
//      { 
//        // The performance has been stopped (paused). 
//      } 
//      else 
//      { 
//        // The performance on all tracks is complete. 
//      } 
//    } 
//    else 
//    { 
//      //The track with the standing bit is being played. 
//      // ( bit0 = Track1, bit1 = Track2, ...) 
//    } 

// void MPlayStart_rev01(MusicPlayerArea *ma, SongHeader *so);
#define MPlayStart_rev01	sub(80BF80C)
#define	m4aMPlayStart(P1,P2) MPlayStart_rev01(P1,P2)

// (14) 重启指定播放器上播放的曲子


// (14) Restarting a Song Performance

//  void m4aMPlayContinue(MusicPlayerArea *&m4a_mplay???);
//This restarts the song being played by the Music Player number ???.  (??? is a three-digit number.)

// void m4aMPlayContinue(MusicPlayerArea *ma);
#define	m4aMPlayContinue	sub(80BF238)

// (11) 停止指定播放器播放曲子

//(11) Stopping (Pausing) a Song Performance

//  void m4aMPlayStop(MusicPlayerArea *&m4a_mplay???);
//This stops the song being played on Music Player number ???. (??? is a three-digit number) 

//Note: The sound that is output will actually be stopped the next time that m4aSoundMain() is called.

// void MPlayStop_rev01(MusicPlayerArea *ma);
#define	MPlayStop_rev01		sub(80BF8F0)
#define m4aMPlayStop(P1) 	MPlayStop_rev01(P1)

// (13) 停止所有的播放器

// (13) Stopping (Pausing) the Performance of All Songs 

//  void m4aMPlayAllStop(void);
//This stops all Music Players (set up with this system). 

//Note: The sound that is output will actually be stopped the next time that m4aSoundMain() is called.

// void m4aMPlayAllStop(void);
#define	m4aMPlayAllStop		sub(80BF20C)

// (16) 所有的播放器恢复播放

// (16) Restarting All Song Performances

//  void m4aMPlayAllContinue(void);
//All Music Players (set up using this system) will resume playing.

// void m4aMPlayAllContinue(void);
#define	m4aMPlayAllContinue		sub(80BF244)

// (17) 以指定速度渐弱指定播放器上的曲子，逐渐停止

// (17) Fading Out Songs

//  void m4aMPlayFadeOut(MusicPlayerArea *&m4a_mplay???, u16 sp);
//This function stops play after fading out the song running on number ??? Music Player at speed sp. 
//The time it takes to stop is ( sp * 16 / 60 ) of a second. 

//Note: m4aMPlayVolumeControl() (described below) cannot be used while using this fade out function. 

// void m4aMPlayFadeOut(MusicPlayerArea *ma, u16 sp);
#define	m4aMPlayFadeOut			sub(80BF270)

// (24) 立即为指定播放器上即将播放的曲子的每个音轨初始化参数

// (24) Immediately Initialize the Song that is Going to Play

//  void m4aMPlayImmInit(MusicPlayerArea *&m4a_mplay???);
//This immediately initializes the parameters of each track for the song you plan on performing with Music Player number ???.(??? is a three digit number)
//Usually, after the song start function is called, each track's parameters are actually initialized the next time m4aSoundMain() is called. Thus, even if you call the parameter change function previous to this it has no effect. However, if you call the parameter change function after calling this function it will be effective. 

// void m4aMPlayImmInit(MusicPlayerArea *ma);
#define	m4aMPlayImmInit			sub(80BF2C8)

// void SampFreqSet_rev01(int a1);
#define	SampFreqSet_rev01		sub(80BF54C)

// (6) 重启声音DMA

// (6) Restarting the Sound DMA 

//  void m4aSoundVSyncOn(void);
//This function restarts the sound DMA when it has been stopped with m4aSoundVSyncOff(). Within 1/60 of a second of callin g this function, the V-Blank interrupt will take effect, and call m4aSoundVSync().

// SoundVSyncOn_rev01(void);
#define	SoundVSyncOn_rev01		sub(80BF758)
#define m4aSoundVSyncOn() SoundVSyncOn_rev01()

// (5) 停止声音DMA

// (5) Stopping the Sound DMA

//  void m4aSoundVSyncOff(void);
//When stopping the V-Blank interrupt for the main program or for some other reason, or when it becomes no longer possible to call m4a SoundVSync() every 1/60 of a second, this function has t o be used to stop the sound DMA. If it is not, the DMS will not stop even if the transfer buffer becomes overloaded, and a terrible noise will result. Also, if DMA1, DMA2, or Timer 0 is used for another purpose when the sound DMA is stopped, it will become impossible to restart this system.   In this case it will be necessary to re-initialize using m4aSoundInit().

// void SoundVSyncOff_rev01(void);
#define	SoundVSyncOff_rev01		sub(80BF6DC)
#define m4aSoundVSyncOff() SoundVSyncOff_rev01()

// 更多详细信息参考:
// More Info:
// m4a_internal.h
// https://github.com/pret/pokeemerald/blob/master/include/gba/m4a_internal.h
// m4a.h
// https://github.com/pret/pokeemerald/blob/master/include/m4a.h

// FE7J自己的声音播放函数

// 自适应音乐播放函数
// 即他自己会根据输入参数取值判断调用对应播放函数
// 既可以通过指定曲子编号播放，也可以通过指定曲子地址播放
// 支持2种传参调用
// (1) 指定曲子ID
// void selfAdaptMPlayStart(u16 n, 0);
// (2) 指定曲子地址
// void selfAdaptMPlayStart(MusicPlayerArea *&m4a_mplay???, SongHeader *SongName);
// 若通过查表获得播放器地址
// void selfAdaptMPlayStart(mplay_table[???].ma, SongName);

#define	selfAdaptMPlayStart		sub(08003DF0)
#define	m4aSongAutoStart		selfAdaptMPlayStart

// 新增魔法音效播放函数
// 直接指定曲子地址
#define	playSpellSFX(songAddr)			m4aMPlayStart(mp08,songAddr)

