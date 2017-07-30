//
#ifndef GsGBA_TEXT_H
#define GsGBA_TEXT_H



extern void GsASCText(int x,int y,const char *s,u16 color);
extern void GsCText(int x,int y,const char *str,u16 color);
extern void GsTextOut(int x,int y,const char *s,u16 color);
extern void GsTextOutMask(int x,int y,const char *s,u16 color,u16 mcolor);

//tile

extern void GsTileTextInit(u8 bg, u8 dist,u8 blockLoc,u8 PalNo);

extern void TsetPix(int block,u8 index,u8 line,u16 color);
extern void GsTextPix(int x,int y,u16 color);

extern void GsTileASCText(int x,int y,const char *str,u16 color);
extern void GsTileCText(  int x,int y,const char *str,u16 color);

extern void GsTileTextOut(int x,int y,const char *str,u16 color);
extern void GsTileTextOutMask(int x,int y,const char *str,u16 color,u16 maskcolor);
extern void GsTileClearAll();
extern void GsObjTilePix(int x,int y,u16 color);



#endif