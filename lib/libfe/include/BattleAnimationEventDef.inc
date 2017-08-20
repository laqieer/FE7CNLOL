@ 战斗动画事件定义
@ by laqieer
@ 2017/8/19

@ 0x80
.macro	EndMode
.word	0x80000000
.endm

@ 0x86
@ 帧数,标号, sheet地址, 帧OAM信息段偏移
.macro	ShowFrame frames=1, No=0, sheet, frameSection=0
.byte	\frames, 0, \No, 0x86
.word	\sheet
.hword	\frameSection, 0
.endm

@ 简化版
.macro Show No=0, sheet, frameSection=0, frames=1 
ShowFrame \frames, \No, \sheet, \frameSection
.endm

@ 0x85指令族

@ 通式
.macro	Cmd subCmd=0
.byte	\subCmd, 0, 0, 0x85
.endm

@ data3&4

@ 描述一个OBJ
@ shape是OBJAttribute0的bit14-15,size是OBJAttribute的bit14-15
@ startX,startY是OBJ的左上角在sheet中的位置(单位:tile)
@ XOffset,YOffset是OBJ的左上角在游戏中相对于人物原点的位置偏移(在人物参考系中的坐标)(单位:像素)
.macro	OAMInfo shape=0, size=0, startX=0, startY=0, XOffset=0, YOffset=0
.hword	0x4000 * \shape, 0x4000 * \size, \startX + 0x20 * \startY, \XOffset, \YOffset, 0
.endm

@ 简化版
@ 单位:像素
.macro	OBJ dimension=0, x0=0, y0=0, deltaX=0, deltaY=0
.word	\dimension
.byte	\x0 / 8 + 0x20 * \y0 / 8, 0
.hword	\deltaX, \deltaY, 0
.endm

@ OBJ尺寸定义
.set	_8x8,		0
.set	_16x16,	0x40000000
.set	_32x32,	0x80000000
.set	_64x64,	0xC0000000
.set	_16x8,		0x4000
.set	_32x8,		0x40004000
.set	_32x16,	0x80004000
.set	_64x32,	0xC0004000
.set	_8x16,		0x8000
.set	_8x32,		0x40008000
.set	_16x32,	0x80008000
.set	_32x64,	0xC0008000
