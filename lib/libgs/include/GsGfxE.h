//developed by HuangYZ
#ifndef GsLIB_GFX_EXTEND
#define GsLIB_GFX_EXTEND


#define SCREEN_W	240
#define SCREEN_H	160


#define RGB(r,g,b) ((r)+((g)<<5)+((b)<<10))

#define SetPix(x,y,c) 	GsSetPix(x,y,c)

typedef struct GsDOT
{
	u8 x,y;			//XY坐标
	u16 color;		//颜色
}GsDOT;

typedef struct GsLINE				//线
{
	s16 sx,sy;		//源
	s16 dx,dy;		//目
	u16 color;		//颜色
}GsLINE;


typedef struct GsTRIANG				//三边型
{
	u8 x1,y1;
	u8 x2,y2;
	u8 x3,y3;
	u16 color;
}GsTRIANG;


typedef struct GsBOX				//四边型
{
	u8 sx,sy;		//源
	u8 dx,dy;		//目
	u16 color;		//颜色
}GsBOX;

typedef struct GsCIRCLE				//圆
{
	u8 x,y;
	u16 radius;
	u16 color;
}GsCIRCLE;


typedef struct GsELLIPSE		//椭圆
{
	u8  x,y;
	u8	rx,ry;
	u16 color;
}GsELLIPSE;
//MAP

//把MAP载入BGNO层 // loc 是0~31		palno是选择的调色盘编号
void GsLoadBgMapSelectPal(const u16 *map,u16 size,u8 locate,u8 palno);

//v2.5

typedef struct GsBgMapPro
{
	const u16 *map;
	u16 size;				//MAP数据长度
	u8 locate;				//从哪个块开始
	u8 palno;				//选择调色盘
	u16 offset;				//表示TILE数据偏移量
}GsBgMapPro;


typedef struct GsCameraMan	//摄像机结构
{
	//map数据描述
	const u16 *pmapdata;	//MAP数据
	u16 Hsize;				// (地图大小 / 8)
	u16 Vsize;				// (地图大小 / 8)
	u8 locate;				//载入位置
	//OFFSET
	int offsetX;			//摄像机在虚地图上的X
	int offsetY;			//摄像机在虚地图上的Y
}GsCameraMan;

void GsSetCamera(u8 bgno,GsCameraMan *p);		//设置一个摄像机位置

//把MAP数据载入VRAM 高级应用函数
void GsLoadBgMapAdvance(GsBgMapPro *mp);
//把TILE数据载入VRAM的某个段
void GsLoadBgTileOffset(const u8 *tile,u16 size,u8 locate,u16 offset);
//创建动态MAP数据
void GsCreateDMap(u8 locate,u16 offset,u8 wide,u8 x,u8 y,u8 palno);

//再入目的的MAP
void GsLoadRectMap(const u16 *map,u16 mapheight,u16 mapwidth,u16 startH,u16 startV,u8 locate);


//MODE4 基本图形函数///////////////////////////////////////////////////////////////////////////


//直接画线
extern void Line(s16  x1,s16  y1,s16  x2,s16  y2,u16 color);
extern void GsSortLine(GsLINE *line);		//画线
extern void GsSortBox(GsBOX *box);			//画方块
extern void GsSortCircle(GsCIRCLE *cir);	//画圆
extern void GsSortEllipse(GsELLIPSE *esp);	//画椭圆
extern void GsFill(u8 x,u8 y,u8 fillColor,u8 oldColor);



//调色盘增强指令////////////////////////////////////////////////////////////
//调色盘向end->start方向滚动一次

//addr :   BG_PLTT ,  OBJ_PLTT
extern void GsLoadBgPalEx(const u16 *addr,u8 start,int size);		//直接载入BGPAL对应位置
extern void GsLoadObjPalEx(const u16 *addr,u8 start,int size);		//直接载入OBJPAL对应位置	2.5
extern void GsPalRotate(u16 *addr,u8 start ,u8 end);		//滚动操作
extern void GsPalColorFadeIn(u16 *addr,u8 start ,u8 num);	// FADE IN 操作.
extern void GsPalColorFadeOut(u16 *addr,u8 start,u8 num);	// FADE OUT 操作.
//SRC向DEC调色盘匹配.
extern void GsPalColorFade(u16 *addr,u16 *descpal,u8 start,u8 num);



#endif