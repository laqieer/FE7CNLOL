// by laqieer
// 2017/1/28
// 函数调用

#pragma once

typedef int (*PTRFUN)();
#define sub(VMA) (*(PTRFUN)(0x##VMA+1))
#define sub32(VMA) (*(PTRFUN)(0x##VMA))

// FE7J中的函数指针跳转函数
// bx ladders
// (*func)();

// Attributes: thunk
// thunk函数即"传名调用"，与"传值调用"相对，由此提出
// 实际是有且仅有一个参数是函数指针,一种回调(callback)形式
// bx r0
#define	_call_via_r0	sub(80C0790)
// bx r1
#define	_call_via_r1	sub(80C0794)
// bx r2
#define	_call_via_r2	sub(80C0798)
// bx r3
#define	_call_via_r3	sub(80C079C)
// bx r4
#define	_call_via_r4	sub(80C07A0)
// bx r5
#define	_call_via_r5	sub(80C07A4)
// bx r6
#define	_call_via_r6	sub(80C07A8)
// bx r7
#define	_call_via_r7	sub(80C07AC)
// bx r8
#define	_call_via_r8	sub(80C07B0)
// bx r9
#define	_call_via_r9	sub(80C07B4)
// bx r10
#define	_call_via_r10	sub(80C07B8)
#define	_call_via_sl	_call_via_r10
// bx r11
#define	_call_via_r11	sub(80C07BC)
#define	_call_via_fp	_call_via_r11
// bx r12
#define	_call_via_r12	sub(80C07C0)
#define	_call_via_ip	_call_via_r12
// bx sp
#define _call_via_r13	sub(80C07C4)
#define	_call_via_sp	_call_via_r13
// bx lr
#define	_call_via_r14	sub(80C07C8)
#define	_call_via_lr	_call_via_r14
#define	retn			_call_via_r14
