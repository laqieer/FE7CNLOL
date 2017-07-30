//
#ifndef GsGBA_GFX_H
#define GsGBA_GFX_H

//mode
#define MODE_0			DISP_MODE_0 | DISP_OBJ_BG_ALL_ON
#define MODE_1			DISP_MODE_1 | DISP_BG0_ON | DISP_BG1_ON | DISP_BG2_ON | DISP_OBJ_ON
#define MODE_2			DISP_MODE_2 | DISP_BG2_ON | DISP_BG3_ON | DISP_OBJ_ON
#define MODE_3			DISP_MODE_3 | DISP_BG2_ON | DISP_OBJ_BG_ALL_ON
#define MODE_4			DISP_MODE_4 | DISP_BG2_ON | DISP_OBJ_BG_ALL_ON
#define MODE_5		    DISP_MODE_5 | DISP_OBJ_BG_ALL_ON
#define Gs_BG_COLOR16  0
#define Gs_BG_COLOR256 1
#define Gs_BG_TEXT_SIZE_256x256		0
#define Gs_BG_TEXT_SIZE_512x256		1
#define Gs_BG_TEXT_SIZE_256x512		2
#define Gs_BG_TEXT_SIZE_512x512		3
#define Gs_BG_AFFINE_SIZE_128x128   0
#define Gs_BG_AFFINE_SIZE_256x256   1
#define Gs_BG_AFFINE_SIZE_512x512   2
#define Gs_BG_AFFINE_SIZE_1024x1024 3

// DISPCNT DEFINE

#define BACKBUFFER		BIT04
#define H_BLANK_OAM		BIT05 
#define FORCE_BLANK		BIT07


extern u16 *VideoBuffer		;



//MODE_0.....MODE_5
#define GsSetMode(mode)	REG_DISPCNT = (mode)
#define GsGetTileSize(tile)  (sizeof(tile)/0x800 + 1)

//调色盘函数
//载入BG调色盘256色
// pal   : 载入调色盘的地址
// count : 载入字节数
void GsLoadBgPal(const u16 *pal,int count);


//载入BG调色盘16色
//pal : 载入调色盘的地址
//no  : 目标段
void GsLoadBgPal16(const u16 *pal,int no);

//载入OBJ调色盘256色	
//数据	数量
void GsLoadObjPal(const u16 *pal,int count);

//载入OBJ调色盘16色
//数据	,位置
void GsLoadObjPal16(const u16 *pal,int no);

//初始化

void GsClearRamAll( void );
void GsClearWorkRam( void );
void GsClearGraphicRam( void );
void GsClearVram( void );
void GsClearOamRam( void );
void GsClearPaletteRam( void );


//以下为MODE0~2函数

//map函数
//初步始化BG
void GsInitBG();		

//把MAP载入BGNO层 // loc 是0~31
void GsLoadBgMap(const u16 *map,u16 size,u8 locate);

//把TILE载入BGNO层 // loc 是0~3
void GsLoadBgTile(const u8 *tile,u16 size,u8 locate);

//设置BG模式
void GsSetBg(int bgno,int size,int colormode,int charbase,int scbase,int mosaic);

//设置BG优先级
void GsBgPriority(int bgno,int prio);

//开/关某一BG
void GsSetBgState(int bgno,u8 state);

//卷轴BG
void GsBgOffset(int bgno,  u16 x , u16 y);

//MODE1，MODE2，时 BG2，BG3  专用

//初始化一个变化对象
void GsBgAffineInit(GsBGAffine *aff);

//创建变化数据
void GsBgAffine(int bgno,  GsBGAffine *aff);

//变化影响BG
void GsBgMakeAffine(int bgno,GsBGAffine *aff);

//初始化旋转BG的积存器
void GsBgAffineRegInit(int bgno);	

//设置BG为平铺
void GsSetBgLoop(int bgno,u8 flag);


//-----------------------------------------------------------------------------
//以下全为MODE4专用函数

//画点
void GsSetPix(u8 x,u8 y,u16 color);

//画点 在屏幕外的点不会被显示
void GsSetPixLimit(u8 x,u8 y,u16 color);

//等待
void GsWaitSync(void);

//翻转
void GsFlip();

//图象数据,	//MODE3,4专用
void GsSortImage(const u16 *IndexData, unsigned long size);


//清除背面
void GsClearBackBuffer(void);


//特效

//设置马塞克特效
void GsSetMosaic(u8 bh,u8 bv,u8 oh,u8 ov);

//设置ALPHA混合度
void GsSetAlpha(u8 ap_eva,u8 ap_evb);

//设置亮度						dark		light
void GsSetBright(s16 level);	// -15 ~ 15 
//设置目标
void GsSetEffect(u16 tg1,u16 tg2);

//关闭特效
void GsCloseEffect();



//  窗口

void GsCreateWin(u8 winno,u8 x1,u8 y1,u8 x2,u8 y2,u8 INWINDOW,u8 OUTWINDOW,u8 fx0_on,u8 fx1_on);
void GsReleaseWin();

void GsSetWinState(u8 winno,u8 state);

#endif

  