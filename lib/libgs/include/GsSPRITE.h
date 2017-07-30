#ifndef  GBA_SPRITE_H
#define GBA_SPRITE_H


//标志
#define Gs_OBJ_MODE0_START_CHARNO 0
#define Gs_OBJ_MODE3_START_CHARNO 512
//形状
#define Gs_OAM_SQUARE 0
#define Gs_OAM_HRECT  1
#define Gs_OAM_VRECT  2
//大小
#define Gs_OAM_SMALL  0
#define Gs_OAM_MIDDLE 1
#define Gs_OAM_BIG    2
#define Gs_OAM_LARGE  3

//色彩模式
#define Gs_OAM_COLOR16  0
#define Gs_OAM_COLOR256 1

//模式
#define Gs_OAM_NORMAL   0
#define Gs_OAM_SEMI		1
#define Gs_OAM_WINDOW   2
//特效模式
#define Gs_OAM_ROTATE_ENABLE 3

//char最大数量
#define Gs_OAM_MODET_CHAR_C16  1024
#define Gs_OAM_MODET_CHAR_C256 512
#define Gs_OAM_MODEB_CHAR_C16  512
#define Gs_OAM_MODEB_CHAR_C256 256

// OBJ
//把CHAR数据传输到VRAM的OBJ RAM位置
#define GsLoadObjChar(src,mode)			DmaArrayCopy(3, src, mode, 32)
//得到CHAR数据的大小
#define GsGetObjSize16(src)				(sizeof(src)/32)
#define GsGetObjSize256(src)			(sizeof(src)/64)

//define function

extern SPRITE	OAM_Buffer[128];						//OAM缓冲

extern void GsLoadObjTile(const u8 *src,u16 size,int loc,int COLORDEP); //载入TILE ,放到OBJRAM的LOC位置
extern void GsOamCopy();										//更新OAM区
extern void GsSortSPRITE(GsSPRITE *p);							//把OBJ复制到屏幕上
extern void GsKillSPRITE(GsSPRITE *p);							//把OBJ删除
extern void GsAffineSelectParameter(GsSPRITE *p,u8 no);			//选择一个仿射变换参数组
extern void GsAffineSPRITE(GsSPRITE *p,GsSPRITEAffine *affsrc);	//设置仿射变换参数 no = 0~31
extern void GsScaleSPRITE(GsSPRITE *p,GsSPRITEAffine *affsrc);		//设置放缩参数 no = 0~31	//syscall 
extern void GsCloseSPRITEAffine(GsSPRITE *p);					//关闭某个OBJ的旋转放缩属性


#endif