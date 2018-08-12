	@.arm
	.thumb
	@.thumb_func
	@https://sourceware.org/binutils/docs-2.22/as/Type.html#Type
	.type TestFunc2 STT_FUNC
	.global TestFunc2
TestFunc2:
	push {lr}
	@mov r0, #2
	ldr r0, =TestFunc2
	pop {r1}
	bx r1
	