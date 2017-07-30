@ by laqieer
@ 2017/4/21
@ 事件结构和代码

@ 镜头和光标控制

	@ 开启镜头自动追随移动人物
	@.equ	cameraOn,		0x3A
	.macro	cameraOn
	.word	0x3A
	.endm
				
	@ 固定镜头
	@.equ	cameraOff,	0x3B
	.macro	cameraOff
	.word	0x3B
	.endm
	
@ 在地图上加载人物配置
	@ 载入人物
	@.equ	loadUnits,	0x30
	.macro	loadUnits	unitList
	.word	0x30,	\unitList
	.endm

@ 人物配置列表结束
	.macro	endList
	.word 0,0,0,0
	.endm
				
@ 等待事件结束
	@.equ	wait,			0x39
	.macro	wait
	.word	0x39
	.endm

@ 函数调用
	@.equ	call,			0x3C
	.macro	call	function
	.word	0x3C,	\function + 1
	.endm
	
@ 淡入淡出
	@ CG淡入
	.macro	fadeInCG	frames=2
	.hword	0xD8,	\frames,	0x91
	.endm
	@ CG淡出
	.macro	fadeOutCG	frames=0
	.hword	0xD9,	\frames,	0x90
	.endm
	
	