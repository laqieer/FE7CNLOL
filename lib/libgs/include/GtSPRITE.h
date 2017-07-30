#ifndef _GtSPRITE_
#define _GtSPRITE_

typedef struct GtSPRAnim_Frame				//4 byte	only one obj
{
	u16 shape:2;	//形状
	u16 size:2;		//大小
	u16 vflip:1;	//是否V翻转
	u16 hflip:1;	//是否H翻转
	u16 charno:10;	//CHAR地址
	s8  dx;		
	s8  dy;
}GtSPRAnim_Frame;

typedef struct GtSPRFrameList			//only one obj
{
	const GtSPRAnim_Frame *frames;
	u8 MaxFrame;						//最大帧
}GtSPRFrameList;

typedef struct GtSPRITE					//一个组合精灵
{
	//u8 oam_locate;						//OAM位置
	const GtSPRFrameList *SubObjFrame;		//帧序列
	u8 part;							//一共包含的部分数
}GtSPRITE;

typedef struct GtSPRITERect
{
	u8 width;
	u8 height;
}GtSPRITERect;
//////////////////////////////////////////////////////////////////
typedef struct GtSPRBitmap
{
	const u16 *Paddr;	//调色盘地址
	const u8  *Daddr;	//数据地址
	u16  width;
	u16  height;
	u8  ObjPalNo;
	u16 StartChar;
}GtSPRBitmap;

extern u8 GtGetObjSizeW(u8 shape,u8 size);
extern u8 GtGetObjSizeH(u8 shape,u8 size);

extern void GtLoadObjChar2D	(const u8 *p,u16 hc,u16 vc,u16 offset);			//载入
extern void GtSPRLoadBitmap	(const GtSPRBitmap *bmp);				//load bmp to OBJVRAM
extern void GtSPRCreate		(const GtSPRITE *p,u8 oam_locate,u8 OBJMODE,u8 PlttNo,u8 prioi);		//创建一个组合OBJ
extern void GtSPRSetPal		(const GtSPRITE *p,u8 oam_locate,u8 part,u8 PlttNo);
extern void GtSPRGetSize	(const GtSPRITE *p,GtSPRITERect	*dec);					//得到组合OBJ的大小
extern void GtSPRSetAffine	(const GtSPRITE *p,u8 oam_locate,u8 number);			//设置仿射参数组

extern void GtSPRAnimate	(const GtSPRITE *p,u8 oam_locate,u8 part,u8 frame);		//动画
extern void GtSPRSetXY		(const GtSPRITE *p,u8 oam_locate,int x,int y);							//直接设置坐标
extern void GtSPRMove		(const GtSPRITE *p,u8 oam_locate,int dx,int dy);							//移动
extern void GtSPRFlipH		(const GtSPRITE *p,u8 oam_locate,u8 part);						//翻转
extern void GtSPRFlipV		(const GtSPRITE *p,u8 oam_locate,u8 part);						//翻转
extern void GtSPRRotate		(const GtSPRITE *p,u8 oam_locate,u8 part,GsSPRITEAffine *affine,u8 AffineNo,u8 centerx,u8 centery,s16 Theta);//旋转

//extern int Adjust(const GtSPRITE *s,u8 oam_locate,u8 desx,u8 desy);



#endif
