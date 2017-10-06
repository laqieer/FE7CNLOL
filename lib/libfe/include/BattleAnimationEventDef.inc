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

@ 整体循环指令
.macro	Loop count=1
.byte	1, \count, 0, 0x85
.endm

@ 音效播放指令
.macro	SFX soundID
.byte	0x48
.hword	\soundID
.byte	0x85
.endm

@ 外挂动画指令(普通)
.macro	EFX effectID
.byte 	0x2E, \effectID, 0, 0x85
.endm

@ 外挂动画指令(必杀)
.macro	EFXCRT effectID
.byte 	0x2F, \effectID, 0, 0x85
.endm

@ data3&4

@ 描述一个OBJ
@ shape是OBJAttribute0的bit14-15,size是OBJAttribute1的bit14-15,HFlip是OBJAttribute1的bit12
@ startX,startY是OBJ的左上角在sheet中的位置(单位:tile)
@ XOffset,YOffset是OBJ的左上角在游戏中相对于人物原点的位置偏移(在人物参考系中的坐标)(单位:像素)

/*
.macro	OAMInfo shape=0, size=0, HFlip=0, startX=0, startY=0, XOffset=0, YOffset=0
.hword	0x4000 * \shape, 0x4000 * \size + 0x1000 * \HFlip, \startX + 0x20 * \startY, \XOffset, \YOffset, 0
.endm
*/

.macro	OBJ Attribute0, Attribute1, Attribute2, XOffset, YOffset
.hword	\Attribute0, \Attribute1, \Attribute2, \XOffset, \YOffset, 0
.endm

@ 简化版
@ 单位:像素

@ 右侧
.macro	OBJR dimension=0, x0=0, y0=0, deltaX=0, deltaY=0
.word	\dimension
.byte	\x0 / 8 + 0x20 * \y0 / 8, 0
.hword	\deltaX, \deltaY, 0
.endm

@ 左侧
.macro	OBJL dimension=0, x0=0, y0=0, deltaX=0, deltaY=0
.word	\dimension + 0x10000000
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

@ 仿射参数(旋转缩放)

@ num表示连续的参数组数(每组4个:PA,PB,PC,PD)
.macro	AffineNum num
.hword	\num, -1
.endm

@ 第一组
.macro	Affine0 PA, PB, PCC ,PD
.hword	\PA, \PB, \PCC, \PD
.endm

@ 后面的
.macro	Affine PA, PB, PCC ,PD
.hword	0, 0, \PA, \PB, \PCC, \PD
.endm

@ 结束一帧
.macro	EndFrame
.word	1,0,0
.endm

@ 结束整个data3/4
.macro	EndOAMInfo
.word	-1,-1,-1
.endm

@ 扩展

@ 0x87指令组
.macro	CmdEx subCmd=0
.byte	\subCmd, 0, 0, 0x87
.endm

@ 龙人变身过程:原动画->变身动画->变身后的动画(由当前装备品ID决定)->变身解除动画->原动画
@ 原动画开头加Trans 1,x,变身动画结尾加Trans 2,变身后的动画结尾加Trans 3,变身解除动画结尾加Trans 4
@ t指定变身的阶段,x控制所在的模式(参见BattleAnimationModeConfig动画模式控制设置表)
@ Mode->x
@ 1,2->0
@ 3,4->1
@ 5->2
@ 6->3
@ 7->4
@ 8->5
@ 9->6
@ 10->7
@ 11->8
@ 12->9
.macro	Trans	t=1, x=0
.byte	\t, \x, 0, 0x87
.endm

@ 设置精灵调色板(0x88/0x89)
.macro	SetPal palAddr
.word	\palAddr + 0x80000000
.endm

@ 显示BG(0x8A)
@ 参数: n=0-3,要使用的BG层;No: 背景编号(结构体数组索引,记录图片数据,调色板和TSA的地址)
.macro	ShowBG n=1, No=0
.hword	No
.byte	n, 0x8A
.endm

@ 清BG
.macro	clearBG n=1
ShowBG \n,0
.endm
