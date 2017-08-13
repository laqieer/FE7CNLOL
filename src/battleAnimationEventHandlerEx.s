@ 职业战斗动画指令扩展
@ by laqieer
@ 2017/8/9

.thumb

.equ BattleAnimationSectionInfoRightSide,0x2000060
.equ BattleAnimationEventBufferLeftSide,0x200F1C8
.equ BattleAnimationSectionInfoLeftSide,0x200005C
.equ isUnitAtRightOrLeft,0x8054E60
.equ BattleAnimationEventBufferRightSide,0x2011BC8
.equ BattleAnimationOAML2RBuffer,0x20041C8

@ .equ loc_80541DA,0x80541DA
@ .equ loc_80541B8,0x80541B8
@ battleAnimationEventHandlerEx.s:34:(.text+0x8): relocation truncated to fit: R_ARM_THM_JUMP11 against `*ABS*0x80541b8'

@ 在汇编里指定.word 标签并无卵用！实际根本不会更改

@ 注意:def_???????的地址并不是0x???????,而是0x???????处switch语句的default case,jpt_???????同理，是0x???????(mov pc,rx)处switch语句的跳转表

/*
@ C0D指令处理函数中的跳转表
.section .C0DHandlerJPT
.align
@ .word 0x080540B4 @ case 0
@ .word 0x080540B4 @ case 1
@ .word 0x080540B4 @ case 2
@ .word 0x080540B4 @ case 3 
.word C0DHandlerJPTCase0_1_2_3_9
.word C0DHandlerJPTCase0_1_2_3_9
.word C0DHandlerJPTCase0_1_2_3_9
.word C0DHandlerJPTCase0_1_2_3_9
.word 0x080541B8 @ case 4
.word 0x080541B8 @ case 5
.word 0x080541C6 @ case 6
.word 0x080541C6 @ case 7
.word 0x080541C6 @ case 8
@ .word 0x080540B4 @ case 9
.word C0DHandlerJPTCase0_1_2_3_9
*/

@ case 0,1,2,3,9 的分支
@ 还有卡机bug(已修复 2017/8/13)
@ .section .text
.text
.global	C0DHandlerJPTCase0_1_2_3_9
.align
C0DHandlerJPTCase0_1_2_3_9:
	MOVS    R0, #1          @ jumptable 08054080 cases 0-3,9
	NEG    R0, R0
	CMP     R8, R0
	BNE     loc_80540BE
	@ B       loc_80541B8     @ jumptable 08054080 cases 4,5
	ldr	r0,=0x80541B8
	mov pc,r0
	@ .ltorg
	@ ---------------------------------------------------------------------------
loc_80540BE:                             @ CODE XREF: battleAnimationEventHandler+47Ej
	LDRH    R0, [R2,#0xE]
	ADD    R0, #1
	STRH    R0, [R2,#0xE]
	LDRH    R0, [R6,#0xE]
	ADD    R0, #1
	STRH    R0, [R6,#0xE]
	MOVS    R0, R2
	MOV     R1, R8
	STR     R2, [sp]
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	BL	BX_r4
	POP	{R4}
	MOVS    R0, R6
	MOV     R1, R8
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	BL	BX_r4
	POP	{R4}
	MOVS    R1, #4
	LDR     R2, [sp]
	LDRH    R0, [R2,#0x10]
	ORR    R0, R1
	STRH    R0, [R2,#0x10]
	LDRH    R0, [R6,#0x10]
	ORR    R0, R1
	STRH    R0, [R6,#0x10]
	LDR     R1, =0x81DE208
	LDR     R0, =0x203E004
	MOVS    R3, #0
	LDRSH   R0, [R0,R3]
	ADD    R0, R0, R1
	LDRB    R0, [R0]
	MOV     R8, R0
	LDR     R1, =0x81DE1E0
	LSL    R0, R0, #2
	ADD    R0, R0, R1
	LDRB    R4, [R0]
	MOVS    R0, R7
	STR     R2, [sp]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	BL	BX_r4
	POP	{R4}
	LDR     R2, [sp]
	CMP     R0, #0
	BNE     loc_8054124
	LDR     R0, =BattleAnimationSectionInfoLeftSide
	B       loc_8054126
	.ltorg
	@ ---------------------------------------------------------------------------
/* off_8054114:     .word 0x81DE208       @ DATA XREF: battleAnimationEventHandler+4B0r
off_8054118:     .word 0x203E004        @ DATA XREF: battleAnimationEventHandler+4B2r
off_805411C:     .word 0x81DE1E0       @ DATA XREF: battleAnimationEventHandler+4BEr
off_8054120:     .word BattleAnimationSectionInfoLeftSide */
	@ DATA XREF: battleAnimationEventHandler+4D4r
	@ ---------------------------------------------------------------------------
loc_8054124:                             @ CODE XREF: battleAnimationEventHandler+4D2j
	LDR     R0, =BattleAnimationSectionInfoRightSide
loc_8054126:                             @ CODE XREF: battleAnimationEventHandler+4D6j
	LDR     R1, [R0]
	LSL    R0, R4, #2
	ADD    R0, R0, R1
	LDR     R4, [R0]
	MOVS    R0, R7
	STR     R2, [sp]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	BL	BX_r4
	POP	{R4}
	LSL    R1, R0, #2
	ADD    R1, R1, R0
	LSL    R1, R1, #2
	ADD    R1, R1, R0
	LSL    R1, R1, #9
	LDR     R0, =BattleAnimationEventBufferLeftSide
	ADD    R1, R1, R0
	@ 添加无压缩事件脚本的支持
	ldr	r0,=0x71616C		@ "laq"
	ldr r2,[r1]
	cmp r0,r2
	bne compressedEvent
@	ldr r1,[r0,#4]
	ldr r1,[r1,#4]
compressedEvent:
	@ 添加结束
	ADD    R1, R4, R1
	LDR     R0, [R1,#4]
	LDR     R2, [sp]
	STR     R0, [R2,#0x28]
	LDR     R4, [R2,#0x30]
	LDR     R1, [R1,#8]
	ADD    R4, R4, R1
	STR     R4, [R2,#0x3C]
	LDR     R4, [R6,#0x30]
	LDR     R0, =0x57F0
	ADD    R4, R4, R0
	STR     R4, [R6,#0x3C]
	LDR     R4, =0x203E088
	MOVS    R0, R7
	STR     R2, [sp]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	BL	BX_r4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R0, [R0]
	LDR     R2, [sp]
	CMP     R0, #0
	BNE     goto_80541DA
	LDR     R4, =0x201FB10
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	BL	BX_r4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R1, [R0]
	LDR     R2, [sp]
	LDR     R0, [R2,#0x28]
	CMP     R1, R0
	BEQ     goto_80541DA
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x8054734
	BL	BX_r4
	POP	{R4}
	LDR     R2, [sp]
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	BL	BX_r4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R2, [sp]
	LDR     R1, [R2,#0x28]
	STR     R1, [R0]
	@ B       loc_80541DA
goto_80541DA:
	ldr r0,=0x80541DA
	mov pc,r0
BX_r4:
	BX	R4
/* 	mov r0, #0x1
	neg r0, r0
	cmp r8, r0
	bne $540be
	b $541b8
	ldrh r0, [r2, #0xe]
	add r0, #0x1
	strh r0, [r2, #0xe]
	ldrh r0, [r6, #0xe]
	add r0, #0x1
	strh r0, [r6, #0xe]
	add r0, r2, #0x0
	mov r1, r8
	str r2, [sp, #0x0]
	bl $54d7c
	add r0, r6, #0x0
	mov r1, r8
	bl $54d7c
	mov r1, #0x4
	ldr r2, [sp, #0x0]
	ldrh r0, [r2, #0x10]
	orr r0, r1
	strh r0, [r2, #0x10]
	ldrh r0, [r6, #0x10]
	orr r0, r1
	strh r0, [r6, #0x10]
	ldr r1, =#0x81de208
	ldr r0, =#0x203e004
	mov r3, #0x0
	ldsh r0, [r0, r3]
	add r0, r0, r1
	ldrb r0, [r0, #0x0]
	mov r8, r0
	ldr r1, =#0x81de1e0
	lsl r0, r0, #0x2
	add r0, r0, r1
	ldrb r4, [r0, #0x0]
	add r0, r7, #0x0
	str r2, [sp, #0x0]
	bl $54e60
	ldr r2, [sp, #0x0]
	cmp r0, #0x0
	bne $54124
	ldr r0, =#0x200005c
	b $54126
	b $54528
	lsr r5, r3, #0x0
	b $54124
	lsl r3, r0, #0x8
	b $544e0
	lsr r5, r3, #0x0
	lsl r4, r3, #0x1
	lsl r0, r0, #0x8
	ldr r0, =#0x2000060
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r0, r1
	ldr r4, [r0, #0x0]
	add r0, r7, #0x0
	str r2, [sp, #0x0]
	bl $54e60
	lsl r1, r0, #0x2
	add r1, r1, r0
	lsl r1, r1, #0x2
	add r1, r1, r0
	lsl r1, r1, #0x9
	ldr r0, =#0x200f1c8
	add r1, r1, r0
	add r1, r4, r1
	ldr r0, [r1, #0x4]
	ldr r2, [sp, #0x0]
	str r0, [r2, #0x28]
	ldr r4, [r2, #0x30]
	ldr r1, [r1, #0x8]
	add r4, r4, r1
	str r4, [r2, #0x3c]
	ldr r4, [r6, #0x30]
	ldr r0, =#0x57f0
	add r4, r4, r0
	str r4, [r6, #0x3c]
	ldr r4, =#0x203e088
	add r0, r7, #0x0
	str r2, [sp, #0x0]
	bl $54e60
	lsl r0, r0, #0x2
	add r0, r0, r4
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x0]
	cmp r0, #0x0
	bne $541da
	ldr r4, =#0x201fb10
	add r0, r2, #0x0
	bl $54e60
	lsl r0, r0, #0x2
	add r0, r0, r4
	ldr r1, [r0, #0x0]
	ldr r2, [sp, #0x0]
	ldr r0, [r2, #0x28]
	cmp r1, r0
	beq $541da
	add r0, r2, #0x0
	bl $54734
	ldr r2, [sp, #0x0]
	add r0, r2, #0x0
	bl $54e60
	lsl r0, r0, #0x2
	add r0, r0, r4
	ldr r2, [sp, #0x0]
	ldr r1, [r2, #0x28]
	str r1, [r0, #0x0]
	b $541da
	lsl r0, r0, #0x0
	lsl r0, r4, #0x1
	lsl r0, r0, #0x8
	bl $21c5ac
	ldrh r0, [r6, r7]
	lsl r0, r0, #0x0
	b $542c4
	lsl r3, r0, #0x8
	blh $1568
	lsl r1, r0, #0x8 */

/*
@ 事件处理总跳转表
.section .battleAnimationEventHandlerJPT
.align
.word	0x080544EE @ case 0
.word	0x08053E00 @ case 1
.word	0x08053E54 @ case 2
.word	0x08053E68 @ case 3
.word	0x08053E8E @ case 4
.word	0x08053F14 @ case 5
.word	0x08053F78 @ case 6
.word	0x080544EE @ case 7
.word	0x08053FA8 @ case 8
.word	0x08053FA8 @ case 9
.word	0x08053FA8 @ case A
.word	0x08053FA8 @ case B
.word	0x08053FA8 @ case C
.word	0x08054042 @ case D
.word	0x080544EE @ case E
.word	0x080544EE @ case F
.word	0x080544EE @ case 10
.word	0x080544EE @ case 11
.word	0x080544EE @ case 12
.word	0x080541F0 @ case 13
.word	0x08054220 @ case 14
.word	0x08054234 @ case 15
.word	0x080544EE @ case 16
.word	0x080544EE @ case 17
.word	0x08054248 @ case 18
.word	0x08054460 @ case 19
.word	0x08054284 @ case 1A
.word	0x08054460 @ case 1B
.word	0x08054460 @ case 1C
.word	0x08054460 @ case 1D
.word	0x08054460 @ case 1E
.word	0x08054460 @ case 1F
.word	0x08054460 @ case 20
.word	0x08054460 @ case 21
.word	0x08054460 @ case 22
.word	0x08054460 @ case 23
.word	0x08054460 @ case 24
.word	0x08054460 @ case 25
.word	0x08054304 @ case 26
.word	0x0805431A @ case 27
.word	0x08054460 @ case 28
.word	0x08054460 @ case 29
.word	0x08054460 @ case 2A
.word	0x08054460 @ case 2B
.word	0x08054330 @ case 2C
.word	0x08054344 @ case 2D
@.word	0x0805438E @ case 2E
.word	callExtraAnimation
@.word	0x080543A4 @ case 2F
.word	callExtraAnimationCRT
.word	0x080543BA @ case 30
.word	0x080543D0 @ case 31
.word	0x080543E6 @ case 32
.word	0x08054460 @ case 33
.word	0x08054460 @ case 34
.word	0x08054460 @ case 35
.word	0x08054460 @ case 36
.word	0x08054460 @ case 37
.word	0x08054460 @ case 38
.word	0x080543FA @ case 39
.word	0x08054460 @ case 3A
.word	0x08054460 @ case 3B
.word	0x08054460 @ case 3C
.word	0x0805441E @ case 3D
.word	0x08054460 @ case 3E
.word	0x08054460 @ case 3F
.word	0x08054460 @ case 40
.word	0x08054460 @ case 41
.word	0x08054460 @ case 42
.word	0x08054460 @ case 43
.word	0x08054460 @ case 44
.word	0x08054460 @ case 45
.word	0x08054460 @ case 46
.word	0x08054450 @ case 47
.word	0x08054460 @ case 48
.word	0x08054460 @ case 49
.word	0x08054460 @ case 4A
.word	0x08054460 @ case 4B
.word	0x08054460 @ case 4C
.word	0x08054460 @ case 4D
.word	0x08054458 @ case 4E
.word	0x08054460 @ case 4F
.word	0x080544EE @ case 50
.word	0x0805446E @ case 51
.word	0x08054492 @ case 52
*/

@ 用C实现
.extern	battleExtraAnimation

@ 外挂背景动画扩展
@ 85 00 XX 2E	(普通)
@ 调用索引为XX的外挂程序
@ XX=00时，为原来的贤者施法魔法阵
.text
.align
.global	callExtraAnimation
callExtraAnimation:
	mov r0,r7
	ldr r4,=1+0x8054E4C
	bl BX_r4
	cmp r0,#0
	bne callExtraEnd
	mov r0,r7
	mov r1,#0
	ldr r4,=1+battleExtraAnimation
	bl BX_r4
callExtraEnd:
	ldr r4,=0x80544EE
	mov pc,r4
	
@ 外挂背景动画扩展
@ 85 00 XX 2F	(必杀)
@ 调用索引为XX的外挂程序
@ XX=00时，为原来的贤者施法魔法阵
.text
.align
.global	callExtraAnimationCRT
callExtraAnimationCRT:
	mov r0,r7
	ldr r4,=1+0x8054E4C
	bl BX_r4
	cmp r0,#0
	bne callExtraEnd
	mov r0,r7
	mov r1,#1
	ldr r4,=1+battleExtraAnimation
	bl BX_r4
callExtraCRTEnd:
	ldr r4,=0x80544EE
	mov pc,r4

/*	
@ 函数sub_8006518的跳转表
.section	.sub_8006518JPT
.align
.word	0x0800659C @ case 0
.word	0x080065B8 @ case 1
.word	0x080065C4 @ case 2
.word	0x080065D0 @ case 3
.word	0x080065CC @ case 4
@.word	0x080065EC @ case 5
.word	loc_80065EC_EX
.word	0x0800664A @ case 6
*/

@ 法师斗篷动画整体循环扩展(case 5)
@ 85 00 XX 01
@ XX为循环的4字节数
@ 有卡机bug
.text
.align
.global	loc_80065EC_EX
loc_80065EC_EX:
	LDR     R0, =0xFFF      @ jumptable 08006578 case 5
	LDRH    R5, [R2,#0xC]
	AND    R0, R5
	MOV    R5, #0x10
	LSL    R5, R5, #8
	MOVS    R1, R5
	ORR    R0, R1
	STRH    R0, [R2,#0xC]
	MOVS    R0, R2
	ADD    R0, #0x15
	LDRB    R1, [R2,#0x14]
	ADD    R0, R1, R0
	STRB    R3, [R0]
	LDRB    R0, [R2,#0x14]
	ADD    R0, #1
	STRB    R0, [R2,#0x14]
	MOVS    R0, #1
	STRH    R0, [R2,#6]
	MOVS    R0, #0xFF
	AND    R0, R3
	CMP     R0, #0x18
	BEQ     loc_8006642
	CMP     R0, #0x18
	BHI     loc_8006630
	CMP     R0, #1
	BCC     goto_8006578     @ jumptable 08006578 default case
	CMP     R0, #5
	BLS     loc_8006642
	CMP     R0, #0x13
	BEQ     loc_8006642
	B       goto_8006578     @ jumptable 08006578 default case
	.ltorg
	@ ---------------------------------------------------------------------------
@	.byte    0
@	.byte    0
@	.word 0xFFF               @ DATA XREF: 0x8006518:loc_80065ECr
	@ ---------------------------------------------------------------------------
loc_8006630:                             @ CODE XREF: 0x8006518+102j
	CMP     R0, #0x39 @ '9'
	BEQ     loc_8006642
	CMP     R0, #0x39 @ '9'
	BHI     loc_800663E
	CMP     R0, #0x2D @ '-'
	BEQ     loc_8006642
	B       goto_8006578     @ jumptable 08006578 default case
@	.ltorg
	@ ---------------------------------------------------------------------------
loc_800663E:                             @ CODE XREF: 0x8006518+11Ej
	CMP     R0, #0x52 @ 'R'
	BNE     goto_8006578     @ jumptable 08006578 default case
loc_8006642:                             @ CODE XREF: 0x8006518+FEj
	@ 0x8006518+10Aj ...
	lsl	r3,r3,#16
	lsr	r3,r3,#24
	lsl r3,r3,#2
@	bl	0x804dd50
	ldr r0,=0x804dd50
	bl	BX_r0
	cmp r0,#1
	bne	loop
	mov	r3,#0
loop:
	LDR     R0, [R2,#0x20]
	SUB    R0, #4
	sub	r0,r3
	STR     R0, [R2,#0x20]
@	B       def_8006578     @ jumptable 08006578 default case
goto_8006578:
	ldr r0,=0x800668C
	mov pc,r0
BX_r0:
	bx r0

/*
@ 职业战斗动画音效播放函数
@ 是C19,C1B-C25,C28-C2B,C33-C38,C3A-C3C,C3E-C46,C48-C4D,C4F的处理函数
@ C2E和C2F的处理也调用到了它
@ playBattleAnimationSFX(AIS, *(_BYTE *)(AIS + 21 + v4 - 1))
@ 位于0x8067F90
@ 它的跳转表
.section	.playBattleAnimationSFXJPT
.align
.word	0x08068130 @ case 25
.word	0x080682D6 @ case 26
.word	0x0806820A @ case 27
.word	0x08068134 @ case 28
.word	0x0806813C @ case 29
.word	0x08068144 @ case 30
.word	0x0806814C @ case 31
.word	0x0806816C @ case 32
.word	0x0806818C @ case 33
.word	0x080681D0 @ case 34
.word	0x080681D4 @ case 35
.word	0x080681D8 @ case 36
.word	0x080681DC @ case 37
.word	0x080682D6 @ case 38
.word	0x080682D6 @ case 39
.word	0x080681E4 @ case 40
.word	0x080681E8 @ case 41
.word	0x080681F0 @ case 42
.word	0x080681F6 @ case 43
.word	0x080682D6 @ case 44
.word	0x080682D6 @ case 45
.word	0x080682D6 @ case 46
.word	0x08068200 @ case 47
.word	0x080682D6 @ case 48
.word	0x080682D6 @ case 49
.word	0x080682D6 @ case 50
.word	0x08068206 @ case 51
.word	0x0806820A @ case 52
.word	0x08068224 @ case 53
.word	0x08068234 @ case 54
.word	0x08068238 @ case 55
.word	0x0806823C @ case 56
.word	0x080682D6 @ case 57
.word	0x08068240 @ case 58
.word	0x08068248 @ case 59
.word	0x0806824E @ case 60
.word	0x080682D6 @ case 61
.word	0x08068260 @ case 62
.word	0x08068264 @ case 63
.word	0x0806826A @ case 64
.word	0x08068274 @ case 65
.word	0x08068278 @ case 66
.word	0x0806827C @ case 67
.word	0x08068284 @ case 68
.word	0x0806828A @ case 69
.word	0x08068294 @ case 70
.word	0x080682D6 @ case 71
@.word	0x0806829C @ case 72
.word	loc_806829C_EX
.word	0x080682A0 @ case 73
.word	0x080682A8 @ case 74
.word	0x080682AE @ case 75
.word	0x080682B8 @ case 76
.word	0x080682C0 @ case 77
.word	0x080682D6 @ case 78
.word	0x080682C8 @ case 79
.word	0x080682D0 @ case 80
*/

@ 战斗动画音效播放指令扩展
@ 85 XX YY 48 播放音效XXYY
@ case 72(0x48)
.text
.align
.global	loc_806829C_EX
loc_806829C_EX:
	ldr r4,[sp,#0x1C]	@ 读取AIS地址
	ldr r4,[r4,#0x20]	@ 读取下一条指令地址
	sub r4,#4	@ 取得当前正在执行的指令地址
	ldr r4,[r4]	@ 读取当前正在执行的指令,即85 XX YY 48
	lsl r4,r4,#8
	lsr	r4,r4,#10	@ 取音效ID,即XXYY
	ldr r0,=0x80682D8
	mov pc,r0

.align
.global	sub_8054D7C
.thumb_func
sub_8054D7C:
	@ battleAnimationEventHandler+494p ...
	PUSH    {R4-R7,LR}
	MOVS    R4, R0
	MOVS    R6, R1
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	BL	BX_r4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8054D9C
	LDR     R0, =0x81DE1E0
	LSL    R1, R6, #2
	ADD    R2, R1, R0
	LDRB    R5, [R2]
	ADD    R1, #1
	ADD    R1, R1, R0
	B       loc_8054DAA
	.ltorg
	@ ---------------------------------------------------------------------------
@off_8054D98:     .word 0x81DE1E0       @ DATA XREF: 0x8054D7C+Er
	@ ---------------------------------------------------------------------------
loc_8054D9C:                             @ CODE XREF: 0x8054D7C+Cj
	LDR     R2, =0x81DE1E0
	LSL    R1, R6, #2
	ADD    R0, R1, #2
	ADD    R0, R0, R2
	LDRB    R5, [R0]
	ADD    R1, #3
	ADD    R1, R1, R2
loc_8054DAA:                             @ CODE XREF: 0x8054D7C+1Aj
	LDRB    R7, [R1]
	CMP     R5, #0xFF
	BEQ     loc_8054DF0
	MOVS    R0, R4
	PUSH	{R4}
@	LDR	R4, =1+isUnitAtRightOrLeft @ 判断动画是在左边还是右边
	@	gdb卡调试死的bug
	ldr r4,=0x8054E61
	BL	BX_r4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8054DD4
	LDR     R0, =BattleAnimationSectionInfoLeftSide
	LDR     R1, [R0]
	LSL    R0, R5, #2
	ADD    R0, R0, R1
	LDR     R1, [R0]
	LDR     R0, =BattleAnimationEventBufferLeftSide
	@ 添加无压缩动画事件脚本支持
	ldr	r2,[r0]
	ldr r3,=0x71616C
	cmp r2,r3
	bne	loc_8054DE0
	ldr r0,[r0,#4]
	@ 添加部分结束
	B       loc_8054DE0
	.ltorg
	@ ---------------------------------------------------------------------------
@off_8054DC8:     .word 0x81DE1E0       @ DATA XREF: 0x8054D7C:loc_8054D9Cr
@off_8054DCC:     .word BattleAnimationSectionInfoLeftSide
	@ DATA XREF: 0x8054D7C+3Er
@off_8054DD0:     .word BattleAnimationEventBufferLeftSide
	@ DATA XREF: 0x8054D7C+48r
	@ ---------------------------------------------------------------------------
loc_8054DD4:                             @ CODE XREF: 0x8054D7C+3Cj
	LDR     R0, =BattleAnimationSectionInfoRightSide
	LDR     R1, [R0]
	LSL    R0, R5, #2
	ADD    R0, R0, R1
	LDR     R1, [R0]
	LDR     R0, =BattleAnimationEventBufferRightSide
	@ 添加无压缩动画事件脚本支持
	ldr	r2,[r0]
	ldr r3,=0x71616C
	cmp r2,r3
	bne	loc_8054DE0
	ldr r0,[r0,#4]
	@ 添加部分结束
loc_8054DE0:                             @ CODE XREF: 0x8054D7C+4Aj
	ADD    R1, R1, R0
	STR     R1, [R4,#0x24]
	STR     R1, [R4,#0x20]
	B       loc_8054DFA
	.ltorg
	@ ---------------------------------------------------------------------------
@off_8054DE8:     .word BattleAnimationSectionInfoRightSide
	@ DATA XREF: 0x8054D7C:loc_8054DD4r
@off_8054DEC:     .word BattleAnimationEventBufferRightSide
	@ DATA XREF: 0x8054D7C+62r
	@ ---------------------------------------------------------------------------
loc_8054DF0:                             @ CODE XREF: 0x8054D7C+32j
	LDR     R0, =0x8C0A5D8
	STR     R0, [R4,#0x24]
	STR     R0, [R4,#0x20]
	MOVS    R0, #0
	STRH    R0, [R4,#0x10]
loc_8054DFA:                             @ CODE XREF: 0x8054D7C+6Aj
	MOVS    R3, #0
	MOVS    R2, #0
	STRH    R7, [R4,#0xA]
	LDR     R0, =0xF3FF
	LDRH    R1, [R4,#8]
	AND    R0, R1
	MOV    R5, #0x8
	LSL    R5, R5, #8
	MOVS    R1, R5
	ORR    R0, R1
	STRH    R0, [R4,#8]
	STRH    R2, [R4,#6]
	MOV    R0, #0x7
	LSL    R0, R0, #8
	LDRH    R1, [R4,#0xC]
	AND    R0, R1
	STRH    R0, [R4,#0xC]
	STRB    R6, [R4,#0x12]
	STRB    R3, [R4,#0x14]
	MOVS    R0, R4
	PUSH	{R4}
	LDR	R4, =1+isUnitAtRightOrLeft @ 判断动画是在左边还是右边
	BL	BX_r4
	POP	{R4}
	LSL    R1, R0, #1
	ADD    R1, R1, R0
	LSL    R1, R1, #2
	SUB    R1, R1, R0
	LSL    R1, R1, #0xB
	LDR     R0, =BattleAnimationOAML2RBuffer
	ADD    R1, R1, R0
	@ 添加无压缩OAM支持
	ldr	r2,[r1]
	ldr r3,=0x71616C	@ 用这个特征码区分是否压缩
	cmp r2,r3
	bne	compressedOAM
@ 用0x10压缩头区分
@	ldrb r2,[r1]
@	cmp	r2,#0x10
@	beq	compressedOAM
	ldr r1,[r1,#4]
compressedOAM:	
	@ 添加部分结束
	STR     R1, [R4,#0x30]
	PUSH	{R4}
	LDR	R4, =1+0x8006488
	BL	BX_r4
	POP	{R4}
	POP     {R4-R7}
	POP     {R0}
	BX      R0
	