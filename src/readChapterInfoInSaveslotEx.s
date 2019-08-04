@ 读取存档中的章节信息已在存档UI上显示
@ by laqieer
@ 2019/8/4

.thumb

.equ	CheckSaveslot, 0x80A1328 + 1
.equ	ReadSaveslotChapterData, 0x80A133C + 1
.equ	sub_8082F30, 0x8082F30 + 1
.equ	sub_80A1398, 0x80A1398 + 1
.equ	sub_80A1384, 0x80A1384 + 1
.equ	sub_80A1D18, 0x80A1D18 + 1
.equ	sub_80A1D6C, 0x80A1D6C + 1

.section .text
.global readChapterInfoInSaveslotEx
@ void readChapterInfoInSaveslotEx(enum saveslot saveslotNum, struct context *ctx, int i);
@ i = 0, 1, 2 表示从上到下的第几个位置
readChapterInfoInSaveslotEx:
                PUSH    {R4-R7,LR}
                SUB     SP, SP, #0x4C
				@ test: all no data
				@ B 		loc_80A70E8
				MOV		R4, #3
				AND		R2, R4
				STR		R2, [SP, #0x48]
                mov    R5, R1
                lsl    R0, R0, #0x18
                lsr    R4, R0, #0x18
                mov    R6, R4
				CMP		R4, #6
				BHI	l_extended_save
                CMP     R4, #2
@                BHI     loc_80A711C
				BHI	loc_80A7152
l_extended_save:
                mov    R0, R4
                ldr r7, =CheckSaveslot
				bl bx_r7
                lsl    R0, R0, #0x18
                asr    R2, R0, #0x18
                CMP     R2, #0
                BEQ     loc_80A70E8
                mov    R0, R4
                MOV     R1, SP
                ldr r7, =ReadSaveslotChapterData
				bl bx_r7
                MOV     R0, SP
				ldr r7, =sub_8082F30
				bl bx_r7
                mov    R1, R5
                add    R1, #0x37
				LDR		R4, [SP, #0x48]
                add    R1, R1, R4
                mov    R2, #0
                STRB    R0, [R1]
                lsl    R1, R4, #2
                mov    R0, R5
                add    R0, #0x48
                add    R0, R0, R1
                LDR     R1, [SP]
                STR     R1, [R0]
                mov    R0, R5
                add    R0, #0x3A
                add    R5, R0, R4
                STRB    R2, [R5]
                mov    R0, R4
                ldr r7, =sub_80A1398
				bl bx_r7
                lsl    R0, R0, #0x18
                CMP     R0, #0
                BEQ     loc_80A70B6
                mov    R0, #1
                LDRB    R1, [R5]
                orr    R0, R1
                STRB    R0, [R5]
loc_80A70B6:
                MOV     R0, SP
				ldr r7, =sub_80A1384
				bl bx_r7
                lsl    R0, R0, #0x18
                CMP     R0, #0
                BEQ     loc_80A70CA
                mov    R0, #2
                LDRB    R1, [R5]
                orr    R0, R1
                STRB    R0, [R5]
loc_80A70CA:
                LDR     R0, =#0x2000064
                add    R0, R4, R0
                MOV     R1, SP
                LDRB    R1, [R1,#0x14]
                STRB    R1, [R0]	@
                LDR     R0, =#0x2000068
                add    R0, R4, R0
                MOV     R1, SP
                LDRB    R1, [R1,#0x1B]
                STRB    R1, [R0]	@
                B       loc_80A7152
loc_80A70E8:
                mov    R0, R5
                add    R0, #0x37
				LDR		R6, [SP, #0x48]
                add    R0, R0, R6
                mov    R1, #0xFF
                STRB    R1, [R0]
                mov    R0, R5
                add    R0, #0x3A
                add    R0, R0, R6
                STRB    R2, [R0]
                lsl    R1, R6, #2
                mov    R0, R5
                add    R0, #0x48
                add    R0, R0, R1
                STR     R2, [R0]
                LDR     R0, =#0x2000064
                add    R0, R6, R0
                STRB    R2, [R0]	@
                LDR     R0, =#0x2000068
                add    R0, R6, R0
                STRB    R2, [R0]	@
                B       loc_80A7152
loc_80A711C:
                mov    R4, R5
                add    R4, #0x44
                mov    R0, #1
				lsl    R0, R0, #8
                LDRH    R1, [R4]
                CMP     R1, R0
                BNE     loc_80A7152
                mov    R0, #3
				ldr r7, =sub_80A1D18
				bl bx_r7
                lsl    R0, R0, #0x18
                CMP     R0, #0
                BEQ     loc_80A714E
                mov    R0, #3 
                MOV     R1, SP
				ldr r7, =sub_80A1D6C
				bl bx_r7
                MOV     R0, SP
                LDRB    R0, [R0,#0xC]
                mov    R1, R5
                add    R1, #0x3F
                STRB    R0, [R1]
                LDR     R0, [SP]
                STR     R0, [R5,#0x54]
                B       loc_80A7152
loc_80A714E:
                mov    R0, #0xF0
                STRH    R0, [R4]
loc_80A7152:
                ADD     SP, SP, #0x4C
                POP     {R4-R7}
                POP     {R0}
                BX      R0
bx_r7:
				bx r7