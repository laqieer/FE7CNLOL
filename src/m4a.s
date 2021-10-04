    .include "../include/function.inc"
    .include "../include/gba_constants.inc"
    .include "../include/m4a_constants.inc"

    .syntax unified

    .set gSampleDecodingBuffer 0x3005DC0
    
    .text

    thumb_func_start SoundMainRAM
SoundMainRAM:
	ldrb r3, [r0, o_SoundInfo_reverb]
	cmp r3, 0
	beq SoundMainRAM_NoReverb
	adr r1, SoundMainRAM_Reverb
	bx r1
	.arm
SoundMainRAM_Reverb:
	cmp r4, 0x2
	addeq r7, r0, o_SoundInfo_pcmBuffer
	addne r7, r5, r8
	mov r4, r8
_081DCEC4:
	ldrsb r0, [r5, r6]
	ldrsb r1, [r5]
	add r0, r0, r1
	ldrsb r1, [r7, r6]
	add r0, r0, r1
	ldrsb r1, [r7], 0x1
	add r0, r0, r1
	mul r1, r0, r3
	mov r0, r1, asr 9
	tst r0, 0x80
	addne r0, r0, 0x1
	strb r0, [r5, r6]
	strb r0, [r5], 0x1
	subs r4, r4, 0x1
	bgt _081DCEC4
	adr r0, _081DCF36 + 1 @ plus 1 because THUMB
	bx r0
	.thumb
SoundMainRAM_NoReverb:
	movs r0, 0
	mov r1, r8
	adds r6, r5
	lsrs r1, 3
	bcc SoundMainRAM_NoReverb_Ok
	stm r5!, {r0}
	stm r6!, {r0}
SoundMainRAM_NoReverb_Ok:
	lsrs r1, 1
	bcc SoundMainRAM_NoReverb_Loop
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
SoundMainRAM_NoReverb_Loop:
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
	subs r1, 1
	bgt SoundMainRAM_NoReverb_Loop
_081DCF36:
	ldr r4, [sp, 0x18]
	ldr r0, [r4, o_SoundInfo_divFreq]
	mov r12, r0
	ldrb r0, [r4, o_SoundInfo_maxChans]
	adds r4, o_SoundInfo_chans

SoundMainRAM_ChanLoop:
	str r0, [sp, 0x4]
	ldr r3, [r4, o_SoundChannel_wav]
	ldr r0, [sp, 0x14]
	cmp r0, 0
	beq _081DCF60
	ldr r1, =REG_VCOUNT
	ldrb r1, [r1]
	cmp r1, VCOUNT_VBLANK
	bhs _081DCF54
	adds r1, TOTAL_SCANLINES
_081DCF54:
	cmp r1, r0
	blo _081DCF60
	b _081DD24A

	.pool

_081DCF60:
	ldrb r6, [r4, o_SoundChannel_status]
	movs r0, 0xC7
	tst r0, r6
	bne _081DCF6A
	b _081DD240
_081DCF6A:
	movs r0, 0x80
	tst r0, r6
	beq _081DCFA0
	movs r0, 0x40
	tst r0, r6
	bne _081DCFB0
	movs r6, 0x3
	strb r6, [r4, o_SoundChannel_status]
	adds r0, r3, 0
	adds r0, 0x10
	ldr r1, [r4, o_SoundChannel_ct]
	adds r0, r1
	str r0, [r4, o_SoundChannel_cp]
	ldr r0, [r3, 0xC]
	subs r0, r1
	str r0, [r4, o_SoundChannel_ct]
	movs r5, 0
	strb r5, [r4, o_SoundChannel_ev]
	str r5, [r4, o_SoundChannel_fw]
	ldrb r2, [r3, 0x3]
	movs r0, 0xC0
	tst r0, r2
	beq _081DCFF8
	movs r0, 0x10
	orrs r6, r0
	strb r6, [r4, o_SoundChannel_status]
	b _081DCFF8
_081DCFA0:
	ldrb r5, [r4, o_SoundChannel_ev]
	movs r0, 0x4
	tst r0, r6
	beq _081DCFB6
	ldrb r0, [r4, o_SoundChannel_iel]
	subs r0, 1
	strb r0, [r4, o_SoundChannel_iel]
	bhi _081DD006
_081DCFB0:
	movs r0, 0
	strb r0, [r4, o_SoundChannel_status]
	b _081DD240
_081DCFB6:
	movs r0, 0x40
	tst r0, r6
	beq _081DCFD6
	ldrb r0, [r4, o_SoundChannel_release]
	muls r5, r0
	lsrs r5, 8
	ldrb r0, [r4, o_SoundChannel_iev]
	cmp r5, r0
	bhi _081DD006
_081DCFC8:
	ldrb r5, [r4, o_SoundChannel_iev]
	cmp r5, 0
	beq _081DCFB0
	movs r0, 0x4
	orrs r6, r0
	strb r6, [r4, o_SoundChannel_status]
	b _081DD006
_081DCFD6:
	movs r2, 0x3
	ands r2, r6
	cmp r2, 0x2
	bne _081DCFF4
	ldrb r0, [r4, o_SoundChannel_decay]
	muls r5, r0
	lsrs r5, 8
	ldrb r0, [r4, o_SoundChannel_sustain]
	cmp r5, r0
	bhi _081DD006
	adds r5, r0, 0
	beq _081DCFC8
	subs r6, 0x1
	strb r6, [r4, o_SoundChannel_status]
	b _081DD006
_081DCFF4:
	cmp r2, 0x3
	bne _081DD006
_081DCFF8:
	ldrb r0, [r4, o_SoundChannel_attack]
	adds r5, r0
	cmp r5, 0xFF
	bcc _081DD006
	movs r5, 0xFF
	subs r6, 0x1
	strb r6, [r4, o_SoundChannel_status]
_081DD006:
	strb r5, [r4, o_SoundChannel_ev]
	ldr r0, [sp, 0x18]
	ldrb r0, [r0, o_SoundChannel_release]
	adds r0, 0x1
	muls r0, r5
	lsrs r5, r0, 4
	ldrb r0, [r4, o_SoundChannel_rightVolume]
	muls r0, r5
	lsrs r0, 8
	strb r0, [r4, o_SoundChannel_er]
	ldrb r0, [r4, o_SoundChannel_leftVolume]
	muls r0, r5
	lsrs r0, 8
	strb r0, [r4, o_SoundChannel_el]
	movs r0, 0x10
	ands r0, r6
	str r0, [sp, 0x10]
	beq _081DD03A
	adds r0, r3, 0
	adds r0, 0x10
	ldr r1, [r3, 0x8]
	adds r0, r1
	str r0, [sp, 0xC]
	ldr r0, [r3, 0xC]
	subs r0, r1
	str r0, [sp, 0x10]
_081DD03A:
	ldr r5, [sp, 0x8]
	ldr r2, [r4, o_SoundChannel_ct]
	ldr r3, [r4, o_SoundChannel_cp]
	adr r0, _081DD044
	bx r0
	.arm
_081DD044:
	str r8, [sp]
	ldr r9, [r4, o_SoundChannel_fw]
	ldrb r10, [r4, o_SoundChannel_er]
	ldrb r11, [r4, o_SoundChannel_el]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x30
	beq _081DD068
	bl sub_81DD264
	b _081DD228
_081DD068:
	mov r10, r10, lsl 16
	mov r11, r11, lsl 16
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x8
	beq _081DD19C
_081DD07C:
	cmp r2, 0x4
	ble _081DD0EC
	subs r2, r2, r8
	movgt r9, 0
	bgt _081DD0A8
	mov r9, r8
	add r2, r2, r8
	sub r8, r2, 0x4
	sub r9, r9, r8
	ands r2, r2, 0x3
	moveq r2, 0x4
_081DD0A8:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD0B0:
	ldrsb r0, [r3], 0x1
	mul r1, r10, r0
	bic r1, r1, 0xFF0000
	add r6, r1, r6, ror 8
	mul r1, r11, r0
	bic r1, r1, 0xFF0000
	add r7, r1, r7, ror 8
	adds r5, r5, 0x40000000
	bcc _081DD0B0
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	subs r8, r8, 0x4
	bgt _081DD0A8
	adds r8, r8, r9
	beq _081DD22C
_081DD0EC:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD0F4:
	ldrsb r0, [r3], 0x1
	mul r1, r10, r0
	bic r1, r1, 0xFF0000
	add r6, r1, r6, ror 8
	mul r1, r11, r0
	bic r1, r1, 0xFF0000
	add r7, r1, r7, ror 8
	subs r2, r2, 0x1
	beq _081DD164
_081DD118:
	adds r5, r5, 0x40000000
	bcc _081DD0F4
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	subs r8, r8, 0x4
	bgt _081DD07C
	b _081DD22C
_081DD134:
	ldr r0, [sp, 0x18]
	cmp r0, 0
	beq _081DD158
	ldr r3, [sp, 0x14]
	rsb lr, r2, 0
_081DD148:
	adds r2, r0, r2
	bgt _081DD1FC
	sub lr, lr, r0
	b _081DD148
_081DD158:
	pop {r4,r12}
	mov r2, 0
	b _081DD174
_081DD164:
	ldr r2, [sp, 0x10]
	cmp r2, 0
	ldrne r3, [sp, 0xC]
	bne _081DD118
_081DD174:
	strb r2, [r4, o_SoundChannel_status]
	mov r0, r5, lsr 30
	bic r5, r5, 0xC0000000
	rsb r0, r0, 0x3
	mov r0, r0, lsl 3
	mov r6, r6, ror r0
	mov r7, r7, ror r0
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	b _081DD234
_081DD19C:
	push {r4,r12}
	ldr r1, [r4, o_SoundChannel_freq]
	mul r4, r12, r1
	ldrsb r0, [r3]
	ldrsb r1, [r3, 0x1]!
	sub r1, r1, r0
_081DD1B4:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD1BC:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r4
	movs lr, r9, lsr 23
	beq _081DD208
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD134
	subs lr, lr, 0x1
	addeq r0, r0, r1
_081DD1FC:
	ldrsbne r0, [r3, lr]!
	ldrsb r1, [r3, 0x1]!
	sub r1, r1, r0
_081DD208:
	adds r5, r5, 0x40000000
	bcc _081DD1BC
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	subs r8, r8, 0x4
	bgt _081DD1B4
	sub r3, r3, 0x1
	pop {r4,r12}
_081DD228:
	str r9, [r4, o_SoundChannel_fw]
_081DD22C:
	str r2, [r4, o_SoundChannel_ct]
	str r3, [r4, o_SoundChannel_cp]
_081DD234:
	ldr r8, [sp]
	add r0, pc, 0x1
	bx r0
	.thumb
_081DD240:
	ldr r0, [sp, 0x4]
	subs r0, 1
	ble _081DD24A
	adds r4, SoundChannel_size
	b SoundMainRAM_ChanLoop
_081DD24A:
	ldr r0, [sp, 0x18]
	ldr r3, =ID_NUMBER
	str r3, [r0]
	add sp, 0x1C
	pop {r0-r7}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	pop {r3}
_081DD25E:
	bx r3
	.pool
	thumb_func_end SoundMainRAM

	arm_func_start sub_81DD264
sub_81DD264:
	ldr r6, [r4, o_SoundChannel_wav]
	ldrb r0, [r4, o_SoundChannel_status]
	tst r0, 0x20
	bne _081DD2B4
	orr r0, r0, 0x20
	strb r0, [r4, o_SoundChannel_status]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x10
	beq _081DD29C
	ldr r1, [r6, 0xC]
	add r1, r1, r6, lsl 1
	add r1, r1, 0x20
	sub r3, r1, r3
	str r3, [r4, o_SoundChannel_cp]
_081DD29C:
	ldrh r0, [r6]
	cmp r0, 0
	beq _081DD2B4
	sub r3, r3, r6
	sub r3, r3, 0x10
	str r3, [r4, o_SoundChannel_cp]
_081DD2B4:
	push {r8,r12,lr}
	mov r10, r10, lsl 16
	mov r11, r11, lsl 16
	ldr r1, [r4, o_SoundChannel_freq]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x8
	movne r8, 0x800000
	muleq r8, r12, r1
	ldrh r0, [r6]
	cmp r0, 0
	beq _081DD468
	mov r0, 0xFF000000
	str r0, [r4, o_SoundChannel_xpi]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x10
	bne _081DD3C0
	bl sub_81DD520
	mov r0, r1
	add r3, r3, 0x1
	bl sub_81DD520
	sub r1, r1, r0
_081DD308:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD310:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r8
	movs lr, r9, lsr 23
	beq _081DD370
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD398
	subs lr, lr, 0x1
	bne _081DD358
	add r0, r0, r1
	b _081DD364
_081DD358:
	add r3, r3, lr
	bl sub_81DD520
	mov r0, r1
_081DD364:
	add r3, r3, 0x1
	bl sub_81DD520
	sub r1, r1, r0
_081DD370:
	adds r5, r5, 0x40000000
	bcc _081DD310
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	ldr r6, [sp]
	subs r6, r6, 0x4
	str r6, [sp]
	bgt _081DD308
	sub r3, r3, 0x1
	b _081DD4F0
_081DD398:
	ldr r0, [sp, 0x1C]
	cmp r0, 0
	beq _081DD4F4
	ldr r3, [r4, o_SoundChannel_wav]
	ldr r3, [r3, 0x8]
	rsb lr, r2, 0
_081DD3B0:
	adds r2, r2, r0
	bgt _081DD358
	sub lr, lr, r0
	b _081DD3B0
_081DD3C0:
	sub r3, r3, 0x1
	bl sub_81DD520
	mov r0, r1
	sub r3, r3, 0x1
	bl sub_81DD520
	sub r1, r1, r0
_081DD3D8:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD3E0:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r8
	movs lr, r9, lsr 23
	beq _081DD440
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD4F4
	subs lr, lr, 0x1
	bne _081DD428
	add r0, r0, r1
	b _081DD434
_081DD428:
	sub r3, r3, lr
	bl sub_81DD520
	mov r0, r1
_081DD434:
	sub r3, r3, 0x1
	bl sub_81DD520
	sub r1, r1, r0
_081DD440:
	adds r5, r5, 0x40000000
	bcc _081DD3E0
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	ldr r6, [sp]
	subs r6, r6, 0x4
	str r6, [sp]
	bgt _081DD3D8
	add r3, r3, 0x2
	b _081DD4F0
_081DD468:
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x10
	beq _081DD4F0
	ldrsb r0, [r3, -0x1]!
	ldrsb r1, [r3, -0x1]
	sub r1, r1, r0
_081DD480:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD488:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r8
	movs lr, r9, lsr 23
	beq _081DD4CC
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD4F4
	ldrsb r0, [r3, -lr]!
	ldrsb r1, [r3, -0x1]
	sub r1, r1, r0
_081DD4CC:
	adds r5, r5, 0x40000000
	bcc _081DD488
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	ldr r6, [sp]
	subs r6, r6, 0x4
	str r6, [sp]
	bgt _081DD480
	add r3, r3, 0x1
_081DD4F0:
	pop {r8,r12,pc}
_081DD4F4:
	mov r2, 0
	strb r2, [r4, o_SoundChannel_status]
	mov r0, r5, lsr 30
	bic r5, r5, 0xC0000000
	rsb r0, r0, 0x3
	mov r0, r0, lsl 3
	mov r6, r6, ror r0
	mov r7, r7, ror r0
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	pop {r8,r12,pc}
	arm_func_end sub_81DD264

	arm_func_start sub_81DD520
sub_81DD520:
	push {r0,r2,r5-r7,lr}
	mov r0, r3, lsr 6
	ldr r1, [r4, o_SoundChannel_xpi]
	cmp r0, r1
	beq _081DD594
	str r0, [r4, o_SoundChannel_xpi]
	mov r1, 0x21
	mul r2, r1, r0
	ldr r1, [r4, o_SoundChannel_wav]
	add r2, r2, r1
	add r2, r2, 0x10
	ldr r5, =gSampleDecodingBuffer
	ldr r6, =gDeltaEncodingTable
	mov r7, 0x40
	ldrb lr, [r2], 1
	strb lr, [r5], 1
	ldrb r1, [r2], 1
	b _081DD57C
_081DD568:
	ldrb r1, [r2], 1
	mov r0, r1, lsr 4
	ldrsb r0, [r6, r0]
	add lr, lr, r0
	strb lr, [r5], 1
_081DD57C:
	and r0, r1, 0xF
	ldrsb r0, [r6, r0]
	add lr, lr, r0
	strb lr, [r5], 1
	subs r7, r7, 2
	bgt _081DD568
_081DD594:
	ldr r5, =gSampleDecodingBuffer
	and r0, r3, 0x3F
	ldrsb r1, [r5, r0]
	pop {r0,r2,r5-r7,pc}
	.pool
