@ 存档校验
@ by laqieer
@ 2019-08-04

.thumb
/*
.text
checkChapterSave:
	ldr r1, =#0x11217
	b endCheckSave
checkSuspendSave:
	ldr r1, =#0x20509
	b endCheckSave
checkLinkArenaSave:
	ldr r1, =#0x20112
	b endCheckSave
checkEmptySave:
	ldr r1, =#0x20223
endCheckSave:
	ldr r0, =#0x809F18E
	mov pc, r0
*/

.extern	GetSaveslotAddrEx

.equ checkChapterSave, 0x809F174
.equ checkSuspendSave, 0x809F17C
.equ checkLinkArenaSave, 0x809F184
.equ checkEmptySave, 0x809F18C
@.equ checkChapterSaveEx, 0x809F1A6

.equ pprSRAMTransfer, 0x3005D90

.section .text
@ todo: check save for extended save slots
checkChapterSaveEx:
	mov r0, r5
	bl GetSaveslotAddrEx
	mov r1, sp
	ldr r2, =pprSRAMTransfer
	ldr r3, [r2]
	mov r2, #0x10
	bl bx_r3
	ldr r0, [sp]
	cmp r0, #0
	beq l_check_fail @ 0
	mov r1, #1
	neg r1, r1
	cmp r0, r1
	beq l_check_fail @ 0xffffffff
	b l_check_success
l_check_fail:
	mov r0, #0
	b l_check_end
l_check_success:
	mov r0, #1
l_check_end:
	add sp, #0x10
	pop {r4, r5}
	pop {r1}
	bx r1
bx_r3:
	bx r3

.section .rodata
checkSaveExJpt:
	.word checkChapterSave	@ save slot 1
	.word checkChapterSave	@ save slot 2
	.word checkChapterSave	@ save slot 3
	.word checkSuspendSave @ suspend backup
	.word checkSuspendSave @ suspend
	.word checkLinkArenaSave @ link arena
	.word checkEmptySave @ empty save
/*	.word checkChapterSave	@ save slot 4
	.word checkChapterSave	@ save slot 5
	.word checkChapterSave	@ save slot 6
	.word checkChapterSave	@ save slot 7
	.word checkChapterSave	@ save slot 8
	.word checkChapterSave	@ save slot 9
	.word checkChapterSave	@ save slot 10
	.word checkChapterSave	@ save slot 11
	.word checkChapterSave	@ save slot 12	*/
	.word checkChapterSaveEx	@ save slot 4
	.word checkChapterSaveEx	@ save slot 5
	.word checkChapterSaveEx	@ save slot 6
	.word checkChapterSaveEx	@ save slot 7
	.word checkChapterSaveEx	@ save slot 8
	.word checkChapterSaveEx	@ save slot 9
	.word checkChapterSaveEx	@ save slot 10
	.word checkChapterSaveEx	@ save slot 11
	.word checkChapterSaveEx	@ save slot 12

.section .checkSaveExNumber,"ax"
	@ disable 0x200A check
	@ fixme: don't disable it when saveslotNum <= 6
	.word 0
@	cmp r5, #6
	cmp r5, #15
	
	
.section .checkSaveExJptAddr,"ax"
	.word checkSaveExJpt