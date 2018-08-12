	.thumb
	.thumb_func
	.global TestFunc2
TestFunc2:
	push {lr}
	mov r0, #2
	pop {r1}
	bx r1
	