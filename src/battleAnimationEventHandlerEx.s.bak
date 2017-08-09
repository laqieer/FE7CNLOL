@ 处理职业战斗动画脚本事件
@ by laqieer
@ 2017/8/7

.align
.arm
.global battleAnimationEventHandlerEx

.equ a1,-0x20

@ 调用的函数(代码段)定义
.equ reduceHPBar,0x805091C
.equ normalEffect,0x8062E9C
.equ criticalEffect,0x8062D68

@ 使用的变量(存储区)定义
.equ BattleAnimationSectionInfoLeftSide,0x200005C
.equ BattleAnimationSectionInfoRightSide,0x2000060
.equ BattleAnimationEventBufferLeftSide,0x200F1C8

battleAnimationEventHandlerEx:
sub_8053C3C:
	PUSH    {R4-R7,LR}
	MOV     R7, R9
	MOV     R6, R8
	PUSH    {R6,R7}
	SUB     SP, SP, #4
	MOVS    R2, #0
loc_8053C48:                             @ CODE XREF: battleAnimationEventHandler+A9Cj
	LDR     R0, =0x3004750
	STR     R2, [R0]
	LDR     R1, =0x2000000
	LSL    R0, R2, #2
	ADD    R0, R0, R1
	LDR     R7, [R0]
	ADD    R2, #1
	MOV     R9, R2
	CMP     R7, #0
	BNE     loc_8053C60
	PUSH	{R4}
	LDR	R4, =loc_80546D2
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
loc_8053C60:                             @ CODE XREF: battleAnimationEventHandler+1Ej
	MOV    R0, #0xF0
	LSL    R0, R0, #8
	LDRH    R1, [R7,#0xC]
	AND    R1, R0
	MOV     R8, R1
	CMP     R1, #0
	BNE     loc_8053C72
	PUSH	{R4}
	LDR	R4, =loc_80546D2
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
loc_8053C72:                             @ CODE XREF: battleAnimationEventHandler+30j
	MOV    R0, #0x10
	LSL    R0, R0, #8
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053C80
	PUSH	{R4}
	LDR	R4, =loc_805450A
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
loc_8053C80:                             @ CODE XREF: battleAnimationEventHandler+3Ej
	@ battleAnimationEventHandler+8B8j
	LDRB    R0, [R7,#0x14]
	CMP     R0, #0
	BNE     loc_8053C8A
	PUSH	{R4}
	LDR	R4, =loc_8054500
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
loc_8053C8A:                             @ CODE XREF: battleAnimationEventHandler+48j
	SUB    R1, R0, #1
	MOVS    R2, R7
	ADD    R2, #0x15
	ADD    R1, R2, R1
	LDRB    R1, [R1]
	MOVS    R3, R0
	CMP     R1, #0x52 @ 'R' @ switch 83 cases
	BLS     loc_8053C9E
	PUSH	{R4}
	LDR	R4, =1+def_8054080     @ jumptable 08053CA6 default case
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
loc_8053C9E:                             @ CODE XREF: battleAnimationEventHandler+5Cj
	LSL    R0, R1, #2
	LDR     R1, =jpt_8053CA6
	ADD    R0, R0, R1
	LDR     R0, [R0]
	MOV     PC, R0          @ switch jump
	@ ---------------------------------------------------------------------------
off_8053CA8:     .word 0x3004750       @ DATA XREF: battleAnimationEventHandler:loc_8053C48r
off_8053CAC:     .word 0x2000000       @ DATA XREF: battleAnimationEventHandler+10r
off_8053CB0:     .word jpt_8053CA6         @ DATA XREF: battleAnimationEventHandler+64r
jpt_8053CA6:     .word def_8054080         @ DATA XREF: battleAnimationEventHandler+64o
	@ battleAnimationEventHandler:off_8053CB0o
	@ jump table for switch statement
	.word loc_8053E00         @ jumptable 08053CA6 case 1
	.word loc_8053E54         @ jumptable 08053CA6 case 2
	.word loc_8053E68         @ jumptable 08053CA6 case 3
	.word loc_8053E8E         @ jumptable 08053CA6 case 4
	.word loc_8053F14         @ jumptable 08053CA6 case 5
	.word loc_8053F78         @ jumptable 08053CA6 case 6
	.word def_8054080         @ jumptable 08053CA6 default case
	.word loc_8053FA8         @ jumptable 08053CA6 cases 8-12
	.word loc_8053FA8         @ jumptable 08053CA6 cases 8-12
	.word loc_8053FA8         @ jumptable 08053CA6 cases 8-12
	.word loc_8053FA8         @ jumptable 08053CA6 cases 8-12
	.word loc_8053FA8         @ jumptable 08053CA6 cases 8-12
	.word loc_8054042         @ jumptable 08053CA6 case 13
	.word def_8054080         @ jumptable 08053CA6 default case
	.word def_8054080         @ jumptable 08053CA6 default case
	.word def_8054080         @ jumptable 08053CA6 default case
	.word def_8054080         @ jumptable 08053CA6 default case
	.word def_8054080         @ jumptable 08053CA6 default case
	.word loc_80541F0         @ jumptable 08053CA6 case 19
	.word loc_8054220         @ jumptable 08053CA6 case 20
	.word loc_8054234         @ jumptable 08053CA6 case 21
	.word def_8054080         @ jumptable 08053CA6 default case
	.word def_8054080         @ jumptable 08053CA6 default case
	.word loc_8054248         @ jumptable 08053CA6 case 24
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054284         @ jumptable 08053CA6 case 26
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054304         @ jumptable 08053CA6 case 38
	.word loc_805431A         @ jumptable 08053CA6 case 39
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054330         @ jumptable 08053CA6 case 44
	.word loc_8054344         @ jumptable 08053CA6 case 45
	.word loc_805438E         @ jumptable 08053CA6 case 46
	.word loc_80543A4         @ jumptable 08053CA6 case 47
	.word loc_80543BA         @ jumptable 08053CA6 case 48
	.word loc_80543D0         @ jumptable 08053CA6 case 49
	.word loc_80543E6         @ jumptable 08053CA6 case 50
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_80543FA         @ jumptable 08053CA6 case 57
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_805441E         @ jumptable 08053CA6 case 61
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054450         @ jumptable 08053CA6 case 71
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word loc_8054458         @ jumptable 08053CA6 case 78
	.word loc_8054460         @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	.word def_8054080         @ jumptable 08053CA6 default case
	.word loc_805446E         @ jumptable 08053CA6 case 81
	.word loc_8054492         @ jumptable 08053CA6 case 82
	@ ---------------------------------------------------------------------------
loc_8053E00:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+7Co
	LDR     R0, =0x2000024 @ jumptable 08053CA6 case 1
	LDR     R0, [R0]
	CMP     R0, #1
	BNE     loc_8053E10
	LDR     R0, [R7,#0x24]
	B       loc_80544EC
	.ltorg
	@ ---------------------------------------------------------------------------
off_8053E0C:     .word 0x2000024       @ DATA XREF: battleAnimationEventHandler:loc_8053E00r
	@ ---------------------------------------------------------------------------
loc_8053E10:                             @ CODE XREF: battleAnimationEventHandler+1CAj
	LDRH    R1, [R7,#0x10]
	MOVS    R0, #4
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053E1C
	B       loc_80544E8
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053E1C:                             @ CODE XREF: battleAnimationEventHandler+1DCj
	MOVS    R0, #8
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053E26
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053E26:                             @ CODE XREF: battleAnimationEventHandler+1E6j
	PUSH	{R4}
	LDR	R4, =1+0x804DD50
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #1
	BEQ     loc_8053E30
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053E30:                             @ CODE XREF: battleAnimationEventHandler+1F0j
	LDR     R0, =0xFFF2
	LDRH    R2, [R7,#0x10]
	AND    R0, R2
	STRH    R0, [R7,#0x10]
	LDR     R0, [R7,#0x20]
	ADD    R0, #4
	STR     R0, [R7,#0x20]
	PUSH	{R4}
	LDR	R4, =1+0x8050FE4
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8053E48
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053E48:                             @ CODE XREF: battleAnimationEventHandler+208j
	MOVS    R0, #0
	PUSH	{R4}
	LDR	R4, =1+0x8050FF0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
	.word 0xFFF2              @ DATA XREF: battleAnimationEventHandler:loc_8053E30r
	@ ---------------------------------------------------------------------------
loc_8053E54:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+80o
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 2
	MOVS    R0, #1
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053E60
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053E60:                             @ CODE XREF: battleAnimationEventHandler+220j
	LDR     R0, =0xFFFE
	B       loc_80544E4
	.ltorg
	@ ---------------------------------------------------------------------------
	.word 0xFFFE              @ DATA XREF: battleAnimationEventHandler:loc_8053E60r
	@ ---------------------------------------------------------------------------
loc_8053E68:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+84o
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 3
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053E8A
	MOVS    R0, R2
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8053E8A
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8063B64
	MOV	LR,PC
	BX	R4
	POP	{R4}
loc_8053E8A:                             @ CODE XREF: battleAnimationEventHandler+236j
	@ battleAnimationEventHandler+246j ...
	LDRH    R1, [R7,#0x10]
	B       loc_80544D6
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053E8E:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+88o
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 4
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053EA4
	MOVS    R0, R2
	ORR    R0, R1
	MOVS    R1, #0x40 @ '@'
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
loc_8053EA4:                             @ CODE XREF: battleAnimationEventHandler+25Cj
	LDRH    R2, [R7,#0x10]
	MOVS    R0, #0x40 @ '@'
	AND    R0, R2
	CMP     R0, #0
	BNE     loc_8053EB0
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053EB0:                             @ CODE XREF: battleAnimationEventHandler+270j
	LDR     R1, =0xFFDF
	AND    R1, R2
	LDR     R0, =0xFFBF
	AND    R1, R0
	LDR     R0, [R7,#0x20]
	ADD    R0, #4
	STR     R0, [R7,#0x20]
	MOVS    R5, #9
	MOVS    R6, #0
	ORR    R1, R5
	STRH    R1, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054F90
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R2, R0
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054FEC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	MOV     R4, R8
	MOVS    R0, R4
	PUSH	{R4}
	LDR	R4, =1+0x8054E74
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R2, [SP,#0x20+a1]
	CMP     R0, #1
	BEQ     loc_8053EEC
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053EEC:                             @ CODE XREF: battleAnimationEventHandler+2ACj
	CMP     R2, #0
	BNE     loc_8053EF2
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053EF2:                             @ CODE XREF: battleAnimationEventHandler+2B2j
	LDRH    R0, [R2,#0x10]
	ORR    R0, R5
	STRH    R0, [R2,#0x10]
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8053F06
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053F06:                             @ CODE XREF: battleAnimationEventHandler+2C6j
	MOVS    R0, R4
	B       loc_8054032
	.ltorg
	@ ---------------------------------------------------------------------------
	.word 0xFFDF              @ DATA XREF: battleAnimationEventHandler:loc_8053EB0r
	.word 0xFFBF              @ DATA XREF: battleAnimationEventHandler+278r
	@ ---------------------------------------------------------------------------
loc_8053F14:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+8Co
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 5
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8053F2A
	MOVS    R0, R2
	ORR    R0, R1
	MOVS    R1, #0x40 @ '@'
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
loc_8053F2A:                             @ CODE XREF: battleAnimationEventHandler+2E2j
	LDRH    R2, [R7,#0x10]
	MOVS    R0, #0x40 @ '@'
	AND    R0, R2
	CMP     R0, #0
	BNE     loc_8053F36
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053F36:                             @ CODE XREF: battleAnimationEventHandler+2F6j
	LDR     R1, =0xFFDF
	AND    R1, R2
	LDR     R0, =0xFFBF
	AND    R1, R0
	LDR     R0, [R7,#0x20]
	ADD    R0, #4
	STR     R0, [R7,#0x20]
	MOVS    R0, #9
	ORR    R1, R0
	STRH    R1, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8053F56
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053F56:                             @ CODE XREF: battleAnimationEventHandler+316j
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8056070
	MOV	LR,PC
	BX	R4
	POP	{R4}
	PUSH	{R4}
	LDR	R4, =1+0x8050FE4
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8053F66
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053F66:                             @ CODE XREF: battleAnimationEventHandler+326j
	MOVS    R0, #2
	PUSH	{R4}
	LDR	R4, =1+0x8050FF0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
	.word 0xFFDF              @ DATA XREF: battleAnimationEventHandler:loc_8053F36r
	.word 0xFFBF              @ DATA XREF: battleAnimationEventHandler+2FEr
	@ ---------------------------------------------------------------------------
loc_8053F78:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+90o
	MOVS    R0, R7          @ jumptable 08053CA6 case 6
	PUSH	{R4}
	LDR	R4, =1+0x8054F90
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R2, R0
	CMP     R2, #0
	BNE     loc_8053F86
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053F86:                             @ CODE XREF: battleAnimationEventHandler+346j
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8055010
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	MOVS    R0, #1
	NEG    R0, R0
	LDR     R2, [SP,#0x20+a1]
	CMP     R8, R0
	BNE     loc_8053F9E
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053F9E:                             @ CODE XREF: battleAnimationEventHandler+35Ej
	MOVS    R0, #2
	LDRH    R3, [R2,#0x10]
	ORR    R0, R3
	STRH    R0, [R2,#0x10]
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053FA8:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+98o ...
	MOVS    R0, R7          @ jumptable 08053CA6 cases 8-12
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8053FB4
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8053FB4:                             @ CODE XREF: battleAnimationEventHandler+374j
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054F90
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R2, R0
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054FEC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	PUSH	{R4}
	LDR	R4, =1+0x8054E74
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R2, [SP,#0x20+a1]
	CMP     R0, #0
	BNE     loc_8054016
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x80684B0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	LDR     R2, [SP,#0x20+a1]
	CMP     R0, #2
	BEQ     loc_8054016
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0
	LDRH    R0, [R7,#0xE]
	SUB    R0, #1
	LSL    R0, R0, #1
	ADD    R0, R0, R1
	PUSH	{R4}
	LDR	R4, =1+0x8053AFC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOV    R1, #0x10
	LSL    R1, R1, #8
	AND    R1, R0
	LDR     R2, [SP,#0x20+a1]
	CMP     R1, #0
	BEQ     loc_805400C
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x80641B0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       loc_8054014
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805400C:                             @ CODE XREF: battleAnimationEventHandler+3C6j
	MOVS    R0, R2          @ a1
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+criticalEffect
	MOV	LR,PC
	BX	R4
	POP	{R4}
loc_8054014:                             @ CODE XREF: battleAnimationEventHandler+3CEj
	LDR     R2, [SP,#0x20+a1]
loc_8054016:                             @ CODE XREF: battleAnimationEventHandler+396j
	@ battleAnimationEventHandler+3A6j
	CMP     R2, #0
	BNE     loc_805401C
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805401C:                             @ CODE XREF: battleAnimationEventHandler+3DCj
	MOVS    R0, #9
	LDRH    R1, [R2,#0x10]
	ORR    R0, R1
	STRH    R0, [R2,#0x10]
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054FEC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
loc_8054032:                             @ CODE XREF: battleAnimationEventHandler+2CCj
	PUSH	{R4}
	LDR	R4, =1+0x8054E74
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0          @ a2
	LDR     R2, [SP,#0x20+a1]
	MOVS    R0, R2          @ a1
	PUSH	{R4}
	LDR	R4, =1+reduceHPBar
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054042:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+ACo
	MOVS    R0, R7          @ jumptable 08053CA6 case 13
	PUSH	{R4}
	LDR	R4, =1+0x8054FCC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	LDR     R4, =0x2000000
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #3
	ADD    R0, R0, R4
	LDR     R2, [R0]
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #1
	ADD    R0, #1
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R6, [R0]
	LDRB    R0, [R7,#0x12]
	LDR     R2, [SP,#0x20+a1]
	CMP     R0, #9          @ switch 10 cases
	BLS     loc_8054078
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054078:                             @ CODE XREF: battleAnimationEventHandler+438j
	LSL    R0, R0, #2
	LDR     R1, =jpt_8054080
	ADD    R0, R0, R1
	LDR     R0, [R0]
	MOV     PC, R0          @ switch jump
	@ ---------------------------------------------------------------------------
off_8054084:     .word 0x2000000       @ DATA XREF: battleAnimationEventHandler+412r
off_8054088:     .word jpt_8054080         @ DATA XREF: battleAnimationEventHandler+43Er
jpt_8054080:     .word loc_80540B4         @ DATA XREF: battleAnimationEventHandler+43Eo
	@ battleAnimationEventHandler:off_8054088o
	@ jump table for switch statement
	.word loc_80540B4         @ jumptable 08054080 cases 0-3,9
	.word loc_80540B4         @ jumptable 08054080 cases 0-3,9
	.word loc_80540B4         @ jumptable 08054080 cases 0-3,9
	.word loc_80541B8         @ jumptable 08054080 cases 4,5
	.word loc_80541B8         @ jumptable 08054080 cases 4,5
	.word loc_80541C6         @ jumptable 08054080 cases 6-8
	.word loc_80541C6         @ jumptable 08054080 cases 6-8
	.word loc_80541C6         @ jumptable 08054080 cases 6-8
	.word loc_80540B4         @ jumptable 08054080 cases 0-3,9
	@ ---------------------------------------------------------------------------
loc_80540B4:                             @ CODE XREF: battleAnimationEventHandler+444j
	@ DATA XREF: battleAnimationEventHandler:jpt_8054080o ...
	MOVS    R0, #1          @ jumptable 08054080 cases 0-3,9
	NEG    R0, R0
	CMP     R8, R0
	BNE     loc_80540BE
	B       loc_80541B8     @ jumptable 08054080 cases 4,5
	.ltorg
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
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R0, R6
	MOV     R1, R8
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, #4
	LDR     R2, [SP,#0x20+a1]
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
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R2, [SP,#0x20+a1]
	CMP     R0, #0
	BNE     loc_8054124
	LDR     R0, =BattleAnimationSectionInfoLeftSide
	B       loc_8054126
	.ltorg
	@ ---------------------------------------------------------------------------
off_8054114:     .word 0x81DE208       @ DATA XREF: battleAnimationEventHandler+4B0r
off_8054118:     .word 0x203E004        @ DATA XREF: battleAnimationEventHandler+4B2r
off_805411C:     .word 0x81DE1E0       @ DATA XREF: battleAnimationEventHandler+4BEr
off_8054120:     .word BattleAnimationSectionInfoLeftSide
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
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
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
	LDR     R2, [SP,#0x20+a1]
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
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R0, [R0]
	LDR     R2, [SP,#0x20+a1]
	CMP     R0, #0
	BNE     loc_80541DA
	LDR     R4, =0x201FB10
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R1, [R0]
	LDR     R2, [SP,#0x20+a1]
	LDR     R0, [R2,#0x28]
	CMP     R1, R0
	BEQ     loc_80541DA
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x8054734
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R2, [SP,#0x20+a1]
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R2, [SP,#0x20+a1]
	LDR     R1, [R2,#0x28]
	STR     R1, [R0]
	B       loc_80541DA
	.ltorg
	@ ---------------------------------------------------------------------------
off_80541A4:     .word BattleAnimationSectionInfoRightSide
	@ DATA XREF: battleAnimationEventHandler:loc_8054124r
off_80541A8:     .word BattleAnimationEventBufferLeftSide
	@ DATA XREF: battleAnimationEventHandler+504r
	.word 0x57F0              @ DATA XREF: battleAnimationEventHandler+51Ar
off_80541B0:     .word 0x203E088       @ DATA XREF: battleAnimationEventHandler+520r
off_80541B4:     .word 0x201FB10       @ DATA XREF: battleAnimationEventHandler+536r
	@ ---------------------------------------------------------------------------
loc_80541B8:                             @ CODE XREF: battleAnimationEventHandler+444j
	@ battleAnimationEventHandler+480j
	@ DATA XREF: ...
	LDR     R1, =0x81DE208 @ jumptable 08054080 cases 4,5
	LDR     R0, =0x203E004
	MOVS    R3, #0
	LDRSH   R0, [R0,R3]
	ADD    R0, R0, R1
	LDRB    R0, [R0]
	MOV     R8, R0
loc_80541C6:                             @ CODE XREF: battleAnimationEventHandler+444j
	@ DATA XREF: battleAnimationEventHandler+468o ...
	MOVS    R0, R2          @ jumptable 08054080 cases 6-8
	MOV     R1, R8
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R0, R6
	MOV     R1, R8
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R2, [SP,#0x20+a1]
loc_80541DA:                             @ CODE XREF: battleAnimationEventHandler+534j
	@ battleAnimationEventHandler+54Aj ...
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x80546F0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R0, R6
	PUSH	{R4}
	LDR	R4, =1+0x80546F0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       loc_8054500
	.ltorg
	@ ---------------------------------------------------------------------------
off_80541E8:     .word 0x81DE208       @ DATA XREF: battleAnimationEventHandler:loc_80541B8r
off_80541EC:     .word 0x203E004        @ DATA XREF: battleAnimationEventHandler+57Er
	@ ---------------------------------------------------------------------------
loc_80541F0:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+C4o
	LDRH    R2, [R7,#0x10]  @ jumptable 08053CA6 case 19
	MOVS    R1, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R2
	CMP     R0, #0
	BNE     loc_8054204
	MOVS    R0, R1
	ORR    R0, R2
	STRH    R0, [R7,#0x10]
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054204:                             @ CODE XREF: battleAnimationEventHandler+5BEj
	LDR     R1, =0x2017758
	LDR     R0, [R1]
	CMP     R0, #1
	BEQ     loc_805420E
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805420E:                             @ CODE XREF: battleAnimationEventHandler+5CEj
	MOVS    R0, #0
	STR     R0, [R1]
	LDR     R0, =0xFFDF
	AND    R0, R2
	B       loc_80544E6
	.ltorg
	@ ---------------------------------------------------------------------------
off_8054218:     .word 0x2017758       @ DATA XREF: battleAnimationEventHandler:loc_8054204r
	.word 0xFFDF              @ DATA XREF: battleAnimationEventHandler+5D6r
	@ ---------------------------------------------------------------------------
loc_8054220:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+C8o
	MOVS    R0, R7          @ jumptable 08053CA6 case 20
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_805422C
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805422C:                             @ CODE XREF: battleAnimationEventHandler+5ECj
	MOVS    R0, #3
	PUSH	{R4}
	LDR	R4, =1+0x804EFE0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054234:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+CCo
	MOVS    R0, R7          @ jumptable 08053CA6 case 21
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8054240
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054240:                             @ CODE XREF: battleAnimationEventHandler+600j
	MOVS    R0, #0
	PUSH	{R4}
	LDR	R4, =1+0x804EFE0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054248:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+D8o
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 24
	MOVS    R0, #1
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_8054254
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054254:                             @ CODE XREF: battleAnimationEventHandler+614j
	LDR     R0, =0xFFFE
	AND    R0, R1
	STRH    R0, [R7,#0x10]
	LDR     R0, [R7,#0x20]
	ADD    R0, #4
	STR     R0, [R7,#0x20]
	LDR     R0, =0xF3FF
	LDRH    R1, [R7,#8]
	AND    R0, R1
	MOV    R2, #0x4
	LSL    R2, R2, #8
	MOVS    R1, R2
	ORR    R0, R1
	STRH    R0, [R7,#8]
	MOVS    R0, #0x8C @ '
	STRH    R0, [R7,#0xA]
	PUSH	{R4}
	LDR	R4, =1+0x8006488
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
	.word 0xFFFE              @ DATA XREF: battleAnimationEventHandler:loc_8054254r
	.word 0xF3FF              @ DATA XREF: battleAnimationEventHandler+624r
	@ ---------------------------------------------------------------------------
loc_8054284:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+E0o
	MOVS    R0, R7          @ jumptable 08053CA6 case 26
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8054290
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054290:                             @ CODE XREF: battleAnimationEventHandler+650j
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054F90
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R2, R0
	CMP     R2, #0
	BEQ     loc_80542C2
	MOVS    R0, #9
	LDRH    R3, [R2,#0x10]
	ORR    R0, R3
	STRH    R0, [R2,#0x10]
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054FEC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	PUSH	{R4}
	LDR	R4, =1+0x8054E74
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0          @ a2
	LDR     R2, [SP,#0x20+a1]
	MOVS    R0, R2          @ a1
	PUSH	{R4}
	LDR	R4, =1+reduceHPBar
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R2, [SP,#0x20+a1]
loc_80542C2:                             @ CODE XREF: battleAnimationEventHandler+65Ej
	MOVS    R0, R2
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x80684B0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	CMP     R0, #2
	BNE     loc_80542D4
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80542D4:                             @ CODE XREF: battleAnimationEventHandler+694j
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0
	LDRH    R0, [R7,#0xE]
	SUB    R0, #1
	LSL    R0, R0, #1
	ADD    R0, R0, R1
	PUSH	{R4}
	LDR	R4, =1+0x8053AFC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOV    R1, #0x10
	LSL    R1, R1, #8
	AND    R1, R0
	LDR     R2, [SP,#0x20+a1]
	CMP     R1, #0
	BEQ     loc_80542FC
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x80641B0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80542FC:                             @ CODE XREF: battleAnimationEventHandler+6B6j
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+normalEffect
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054304:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+110o
	MOVS    R0, R7          @ jumptable 08053CA6 case 38
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8054310
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054310:                             @ CODE XREF: battleAnimationEventHandler+6D0j
	MOVS    R0, R7
	MOVS    R1, #0
	PUSH	{R4}
	LDR	R4, =1+0x8062FE0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805431A:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+114o
	MOVS    R0, R7          @ jumptable 08053CA6 case 39
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8054326
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054326:                             @ CODE XREF: battleAnimationEventHandler+6E6j
	MOVS    R0, R7
	MOVS    R1, #1
	PUSH	{R4}
	LDR	R4, =1+0x8062FE0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054330:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+128o
	MOVS    R0, R7          @ jumptable 08053CA6 case 44
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_805433C
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805433C:                             @ CODE XREF: battleAnimationEventHandler+6FCj
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x80631B0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054344:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+12Co
	MOVS    R0, R7          @ jumptable 08053CA6 case 45
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0
	LDRH    R0, [R7,#0xE]
	SUB    R0, #1
	LSL    R0, R0, #1
	ADD    R0, R0, R1
	PUSH	{R4}
	LDR	R4, =1+0x8053AFC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOV    R1, #0x10
	LSL    R1, R1, #8
	AND    R1, R0
	CMP     R1, #0
	BNE     loc_8054364
	B       loc_80544E8
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054364:                             @ CODE XREF: battleAnimationEventHandler+724j
	LDRH    R1, [R7,#0x10]
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BEQ     loc_8054372
	B       loc_80544D6
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054372:                             @ CODE XREF: battleAnimationEventHandler+732j
	MOVS    R0, R2
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_8054384
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054384:                             @ CODE XREF: battleAnimationEventHandler+744j
	MOVS    R0, R7
	MOVS    R1, #0
	PUSH	{R4}
	LDR	R4, =1+0x8064330
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805438E:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+130o
	MOVS    R0, R7          @ jumptable 08053CA6 case 46
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_805439A
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805439A:                             @ CODE XREF: battleAnimationEventHandler+75Aj
	MOVS    R0, R7
	MOVS    R1, #0
	PUSH	{R4}
	LDR	R4, =1+0x8063400
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543A4:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+134o
	MOVS    R0, R7          @ jumptable 08053CA6 case 47
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_80543B0
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543B0:                             @ CODE XREF: battleAnimationEventHandler+770j
	MOVS    R0, R7
	MOVS    R1, #1
	PUSH	{R4}
	LDR	R4, =1+0x8063400
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543BA:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+138o
	MOVS    R0, R7          @ jumptable 08053CA6 case 48
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_80543C6
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543C6:                             @ CODE XREF: battleAnimationEventHandler+786j
	MOVS    R0, R7
	MOVS    R1, #0
	PUSH	{R4}
	LDR	R4, =1+0x80635B4
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543D0:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+13Co
	MOVS    R0, R7          @ jumptable 08053CA6 case 49
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BEQ     loc_80543DC
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543DC:                             @ CODE XREF: battleAnimationEventHandler+79Cj
	MOVS    R0, R7
	MOVS    R1, #1
	PUSH	{R4}
	LDR	R4, =1+0x80635B4
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543E6:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+140o
	MOVS    R0, R7          @ jumptable 08053CA6 case 50
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     def_8054080     @ jumptable 08053CA6 default case
	MOVS    R0, R7
	MOVS    R1, #2
	PUSH	{R4}
	LDR	R4, =1+0x80635B4
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80543FA:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+15Co
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 57
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_80544D6
	MOVS    R0, R2
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     def_8054080     @ jumptable 08053CA6 default case
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x80638F0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805441E:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+16Co
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 61
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BEQ     loc_805442C
	B       loc_8053E8A
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805442C:                             @ CODE XREF: battleAnimationEventHandler+7ECj
	MOVS    R0, R2
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8054442
	MOVS    R0, #1
	PUSH	{R4}
	LDR	R4, =1+0x8050FF0
	MOV	LR,PC
	BX	R4
	POP	{R4}
loc_8054442:                             @ CODE XREF: battleAnimationEventHandler+7FEj
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8064458
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8050FFC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       loc_8053E8A
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054450:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+194o
	MOVS    R0, R7          @ jumptable 08053CA6 case 71
	PUSH	{R4}
	LDR	R4, =1+0x8063FBC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054458:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+1B0o
	MOVS    R0, R7          @ jumptable 08053CA6 case 78
	PUSH	{R4}
	LDR	R4, =1+0x8063804
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054460:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+DCo ...
	SUB    R0, R3, #1      @ jumptable 08053CA6 cases 25,27-37,40-43,51-56,58-60,62-70,72-77,79
	ADD    R0, R2, R0
	LDRB    R1, [R0]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8067F90
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_805446E:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+1BCo
	LDRH    R1, [R7,#0x10]  @ jumptable 08053CA6 case 81
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_80544D6
	MOVS    R0, R2
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     def_8054080     @ jumptable 08053CA6 default case
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x806397C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054492:                             @ CODE XREF: battleAnimationEventHandler+6Aj
	@ DATA XREF: battleAnimationEventHandler+1C0o
	MOVS    R0, R7          @ jumptable 08053CA6 case 82
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0
	LDRH    R0, [R7,#0xE]
	SUB    R0, #1
	LSL    R0, R0, #1
	ADD    R0, R0, R1
	PUSH	{R4}
	LDR	R4, =1+0x8053AFC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOV    R1, #0x10
	LSL    R1, R1, #8
	AND    R1, R0
	CMP     R1, #0
	BEQ     loc_80544E8
	LDRH    R1, [R7,#0x10]
	MOVS    R2, #0x20 @ ' '
	MOVS    R0, #0x20 @ ' '
	AND    R0, R1
	CMP     R0, #0
	BNE     loc_80544D6
	MOVS    R0, R2
	ORR    R0, R1
	STRH    R0, [R7,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     def_8054080     @ jumptable 08053CA6 default case
	MOVS    R0, R7
	MOVS    R1, #1
	PUSH	{R4}
	LDR	R4, =1+0x8064330
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       def_8054080     @ jumptable 08053CA6 default case
	.ltorg
	@ ---------------------------------------------------------------------------
loc_80544D6:                             @ CODE XREF: battleAnimationEventHandler+250j
	@ battleAnimationEventHandler+734j ...
	MOVS    R0, #0x40 @ '@'
	AND    R0, R1
	CMP     R0, #0
	BEQ     def_8054080     @ jumptable 08053CA6 default case
	LDR     R0, =0xFFDF
	AND    R0, R1
	LDR     R1, =0xFFBF
loc_80544E4:                             @ CODE XREF: battleAnimationEventHandler+226j
	AND    R0, R1
loc_80544E6:                             @ CODE XREF: battleAnimationEventHandler+5DAj
	STRH    R0, [R7,#0x10]
loc_80544E8:                             @ CODE XREF: battleAnimationEventHandler+1DEj
	@ battleAnimationEventHandler+726j ...
	LDR     R0, [R7,#0x20]
	ADD    R0, #4
loc_80544EC:                             @ CODE XREF: battleAnimationEventHandler+1CEj
	STR     R0, [R7,#0x20]
def_8054080:                             @ CODE XREF: battleAnimationEventHandler+5Ej
	@ battleAnimationEventHandler+6Aj ...
	LDRB    R0, [R7,#0x14]  @ jumptable 08053CA6 default case
	SUB    R0, #1
	STRB    R0, [R7,#0x14]
	PUSH	{R4}
	LDR	R4, =loc_8053C80
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
	.word 0xFFDF              @ DATA XREF: battleAnimationEventHandler+8A2r
	.word 0xFFBF              @ DATA XREF: battleAnimationEventHandler+8A6r
	@ ---------------------------------------------------------------------------
loc_8054500:                             @ CODE XREF: battleAnimationEventHandler+4Aj
	@ battleAnimationEventHandler+5AAj
	MOV    R0, #0xE7
	LSL    R0, R0, #8
	LDRH    R1, [R7,#0xC]
	AND    R0, R1
	STRH    R0, [R7,#0xC]
loc_805450A:                             @ CODE XREF: battleAnimationEventHandler+40j
	MOV    R0, #0x20
	LSL    R0, R0, #8
	MOV     R2, R8
	AND    R0, R2
	CMP     R0, #0
	BEQ     loc_8054570
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_8054566
	LDR     R4, =0x203E088
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R0, [R0]
	CMP     R0, #0
	BNE     loc_8054566
	MOV    R0, #0x40
	LSL    R0, R0, #8
	LDRH    R3, [R7,#0x10]
	AND    R0, R3
	CMP     R0, #0
	BNE     loc_8054566
	LDR     R4, =0x201FB10
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R1, [R0]
	LDR     R0, [R7,#0x28]
	CMP     R1, R0
	BEQ     loc_8054566
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054764
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #2
	ADD    R0, R0, R4
	LDR     R1, [R7,#0x28]
	STR     R1, [R0]
loc_8054566:                             @ CODE XREF: battleAnimationEventHandler+8E2j
	@ battleAnimationEventHandler+8F4j ...
	MOV    R0, #0xD7
	LSL    R0, R0, #8
	LDRH    R1, [R7,#0xC]
	AND    R0, R1
	STRH    R0, [R7,#0xC]
loc_8054570:                             @ CODE XREF: battleAnimationEventHandler+8D8j
	MOV    R0, #0x40
	LSL    R0, R0, #8
	MOV     R2, R8
	AND    R2, R0
	CMP     R2, #0
	BNE     loc_8054586
	LDR     R0, =0x2000024
	LDR     R0, [R0]
	CMP     R0, #1
	BEQ     loc_8054586
	B       loc_80546D2
	.ltorg
	@ ---------------------------------------------------------------------------
loc_8054586:                             @ CODE XREF: battleAnimationEventHandler+93Ej
	@ battleAnimationEventHandler+946j
	LDRH    R1, [R7,#0x10]
	MOVS    R0, #2
	AND    R0, R1
	CMP     R0, #0
	BEQ     loc_805460C
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054FCC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	MOVS    R0, #1
	NEG    R0, R0
	CMP     R8, R0
	BEQ     loc_80545D4
	LDR     R6, =0x2000000
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #3
	ADD    R0, R0, R6
	LDR     R2, [R0]
	MOVS    R0, R2
	MOV     R1, R8
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R4, =0xFFFD
	B       loc_8054644
	.ltorg
	@ ---------------------------------------------------------------------------
off_80545C0:     .word 0x203E088       @ DATA XREF: battleAnimationEventHandler+8E4r
off_80545C4:     .word 0x201FB10       @ DATA XREF: battleAnimationEventHandler+902r
off_80545C8:     .word 0x2000024       @ DATA XREF: battleAnimationEventHandler+940r
off_80545CC:     .word 0x2000000       @ DATA XREF: battleAnimationEventHandler+968r
	.word 0xFFFD              @ DATA XREF: battleAnimationEventHandler+980r
	@ ---------------------------------------------------------------------------
loc_80545D4:                             @ CODE XREF: battleAnimationEventHandler+966j
	LDR     R5, =0x2000000
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #3
	ADD    R0, R0, R5
	LDR     R2, [R0]
	LDR     R4, =0xFFFD
	MOVS    R0, R4
	LDRH    R1, [R2,#0x10]
	AND    R0, R1
	STRH    R0, [R2,#0x10]
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #1
	ADD    R0, #1
	LSL    R0, R0, #2
	ADD    R0, R0, R5
	LDR     R6, [R0]
	LDRH    R2, [R6,#0x10]
	AND    R4, R2
	STRH    R4, [R6,#0x10]
	B       loc_80546D2
	.ltorg
	@ ---------------------------------------------------------------------------
off_8054604:     .word 0x2000000       @ DATA XREF: battleAnimationEventHandler:loc_80545D4r
	.word 0xFFFD              @ DATA XREF: battleAnimationEventHandler+9A6r
	@ ---------------------------------------------------------------------------
loc_805460C:                             @ CODE XREF: battleAnimationEventHandler+952j
	MOV    R0, #0x80
	LSL    R0, R0, #8
	AND    R0, R1
	CMP     R0, #0
	BEQ     loc_8054698
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054FCC
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	MOVS    R0, #1
	NEG    R0, R0
	CMP     R8, R0
	BEQ     loc_80546D2
	LDR     R6, =0x2000000
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #3
	ADD    R0, R0, R6
	LDR     R2, [R0]
	MOVS    R0, R2
	MOV     R1, R8
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R4, =0x7FFF
loc_8054644:                             @ CODE XREF: battleAnimationEventHandler+982j
	MOVS    R0, R4
	LDR     R2, [SP,#0x20+a1]
	LDRH    R3, [R2,#0x10]
	AND    R0, R3
	MOVS    R5, #4
	ORR    R0, R5
	STRH    R0, [R2,#0x10]
	MOVS    R0, R7
	STR     R2, [SP,#0x20+a1]
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #1
	ADD    R0, #1
	LSL    R0, R0, #2
	ADD    R0, R0, R6
	LDR     R6, [R0]
	MOVS    R0, R6
	MOV     R1, R8
	PUSH	{R4}
	LDR	R4, =1+0x8054D7C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDRH    R0, [R6,#0x10]
	AND    R4, R0
	ORR    R4, R5
	STRH    R4, [R6,#0x10]
	LDR     R2, [SP,#0x20+a1]
	LDRH    R0, [R2,#0xE]
	ADD    R0, #1
	STRH    R0, [R2,#0xE]
	LDRH    R0, [R6,#0xE]
	ADD    R0, #1
	STRH    R0, [R6,#0xE]
	MOVS    R0, R2
	PUSH	{R4}
	LDR	R4, =1+0x80546F0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R0, R6
	PUSH	{R4}
	LDR	R4, =1+0x80546F0
	MOV	LR,PC
	BX	R4
	POP	{R4}
	B       loc_80546D2
	.ltorg
	@ ---------------------------------------------------------------------------
off_8054690:     .word 0x2000000       @ DATA XREF: battleAnimationEventHandler+9EEr
	.word 0x7FFF              @ DATA XREF: battleAnimationEventHandler+A06r
	@ ---------------------------------------------------------------------------
loc_8054698:                             @ CODE XREF: battleAnimationEventHandler+9D8j
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E4C
	MOV	LR,PC
	BX	R4
	POP	{R4}
	CMP     R0, #0
	BNE     loc_80546D2
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	MOVS    R1, R0
	LDRH    R2, [R7,#0xE]
	LSL    R0, R2, #1
	ADD    R0, R0, R1
	PUSH	{R4}
	LDR	R4, =1+0x8053AD4
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LSL    R0, R0, #0x10
	ASR    R0, R0, #0x10
	MOV     R8, R0
	MOVS    R0, #1
	NEG    R0, R0
	CMP     R8, R0
	BNE     loc_80546D2
	MOVS    R0, R7
	PUSH	{R4}
	LDR	R4, =1+0x8054E60
	MOV	LR,PC
	BX	R4
	POP	{R4}
	LDR     R1, =0x201FAF8
	LSL    R0, R0, #2
	ADD    R0, R0, R1
	MOVS    R1, #1
	STR     R1, [R0]
loc_80546D2:                             @ CODE XREF: battleAnimationEventHandler+20j
	@ battleAnimationEventHandler+32j ...
	MOV     R2, R9
	CMP     R2, #3
	BHI     loc_80546DC
	PUSH	{R4}
	LDR	R4, =loc_8053C48
	MOV	LR,PC
	BX	R4
	POP	{R4}
	@ ---------------------------------------------------------------------------
loc_80546DC:                             @ CODE XREF: battleAnimationEventHandler+A9Aj
	ADD     SP, SP, #4
	POP     {R3,R4}
	MOV     R8, R3
	MOV     R9, R4
	POP     {R4-R7}
	POP     {R0}
	BX      R0
	@ End of function battleAnimationEventHandler
	@ ---------------------------------------------------------------------------
off_80546EC:     .word 0x201FAF8       @ DATA XREF: battleAnimationEventHandler+A8Cr

.end
