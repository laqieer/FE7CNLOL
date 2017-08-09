
@ 职业战斗动画指令扩展
@ by laqieer
@ 2017/8/9

.thumb

.equ BattleAnimationSectionInfoRightSide,0x2000060
.equ BattleAnimationEventBufferLeftSide,0x200F1C8
.equ BattleAnimationSectionInfoLeftSide,0x200005C
@ .equ loc_80541DA,0x80541DA
@ .equ loc_80541B8,0x80541B8
@ battleAnimationEventHandlerEx.s:34:(.text+0x8): relocation truncated to fit: R_ARM_THM_JUMP11 against `*ABS*0x80541b8'

@ C0D指令处理函数中的跳转表
.section .C0DHandlerJPT
.align
/* .word 0x080540B4 @ case 0
.word 0x080540B4 @ case 1
.word 0x080540B4 @ case 2
.word 0x080540B4 @ case 3 */
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

@ case 0,1,2,3,9 的分支
@ .section .text
.text
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
	