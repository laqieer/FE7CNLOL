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
.macro Show No=0, sheet, frames=1, frameSection=0
ShowFrame \frames, \No, \sheet, \frameSection
.endm

@ 0x85指令族

@ 通式
.macro	Cmd subCmd=0
.byte	\subCmd, 0, 0, 0x85
.endm
