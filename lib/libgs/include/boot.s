REG_BASE        	EQU   0x04000000
REG_IME			EQU   (REG_BASE + 0x208)  ; Interrupt Master Enable
REG_IE			EQU   (REG_BASE + 0x200)  ; Interrupt Enable
REG_IF			EQU   (REG_BASE + 0x202)  ; Interrupt Request

OFFSET_REG_IME          EQU   0x208       ; Interrupt Master Enable
OFFSET_REG_IE           EQU   0x200       ; Interrupt Enable
OFFSET_REG_IF           EQU   0x202       ; Interrupt Request

PSR_CPU_MODE_MASK       EQU   0x1f        ; CPU Mode

PSR_USER_MODE           EQU   0x10        ; User
PSR_FIQ_MODE            EQU   0x11        ; FIQ
PSR_IRQ_MODE            EQU   0x12        ; IRQ
PSR_SVC_MODE            EQU   0x13        ; Supervisor
PSR_ABORT_MODE          EQU   0x17        ; Abort (Prefetch/Data)
PSR_UNDEF_MODE          EQU   0x1b        ; Undefined Command
PSR_SYS_MODE            EQU   0x1f        ; System

BOOT_ROM                EQU   0x00000000          ; Boot ROM
BOOT_ROM_END            EQU   (BOOT_ROM + 0x4000)
EX_WRAM                 EQU   0x02000000          ; CPU External Work RAM
EX_WRAM_END             EQU   (EX_WRAM + 0x40000)
CPU_WRAM                EQU   0x03000000          ; CPU Internal Work RAM
CPU_WRAM_END            EQU   (CPU_WRAM + 0x8000)
WRAM                    EQU    EX_WRAM            ; Entire Work RAM
WRAM_END                EQU    CPU_WRAM_END
SOUND_AREA_ADDR_BUF     EQU   (CPU_WRAM_END - 0x10); Sound Driver Work Address
INTR_CHECK_BUF          EQU   (CPU_WRAM_END - 0x8); Interrupt Check
SOFT_RESET_DIRECT_BUF   EQU   (CPU_WRAM_END - 0x6); SoftReset() Specify Return to
INTR_VECTOR_BUF         EQU   (CPU_WRAM_END - 0x4); Interrupt Branch Address

Cpu_Mode_USR	EQU 	0x10
Cpu_Mode_IRQ 	EQU 	0x12
Cpu_Mode_SVC 	EQU 	0x13

Cpu_Stack_USR	EQU	0x03007F00	; GBA USR stack adress
Cpu_Stack_IRQ	EQU	0x03007FA0	; GBA IRQ stack adress
Cpu_Stack_SVC	EQU	0x03007FE0	; GBA SVC stack adress
Cpu_Int_Handler EQU 	0x03007FFC	; GBA Interupt handler address

	AREA        Init, CODE, READONLY
	
	IMPORT |Image$$RO$$Limit| 	; End of ROM code (=start of ROM data)
	IMPORT |Image$$RW$$Base| 	; Base of RAM to initialize
	IMPORT |Image$$ZI$$Base| 	; Base and limit of area
	IMPORT |Image$$ZI$$Limit| 	; to zero initialize
	IMPORT      AgbMain

	ENTRY
	
start
	INCLUDE     rom_header.s
	CODE32
start_vector
	mov	r0,#PSR_IRQ_MODE	; 准备切换到IRQ管理模式
	msr     cpsr_c,r0		; 切换到IRQ管理模式
        ldr     sp, sp_irq              ; 设置堆栈,为IRQ中断作准备
        
        mov	r0,#PSR_SYS_MODE	; 准备切换到系统模式
	msr     cpsr_c,r0		; 切换到系统模式
	ldr     sp, sp_usr              ; 设置堆栈用户模式

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ldr 	r0, =|Image$$RO$$Limit| 	; Get pointer to ROM data
	ldr 	r1, =|Image$$RW$$Base| 		; and RAM copy
	ldr 	r3, =|Image$$ZI$$Base| 		; Zero init base => top of initialized data
	cmp 	r0, r1 				; Check that they are different
	beq 	%F1
0 	cmp 	r1, r3 				; Copy init data
	ldrcc 	r2, [r0], #4
	strcc 	r2, [r1], #4
	bcc	%B0
1	ldr 	r1, =|Image$$ZI$$Limit| 	; Top of zero init segment
	mov 	r2, #0
2 	cmp 	r3, r1 				; Zero init
	strcc 	r2, [r3], #4
	bcc	%B2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ldr     r1, =INTR_VECTOR_BUF    ; 设置中断向量缓冲
        adr     r0, intr_main		; 设置中断控制函数
        str     r0, [r1]
        ldr     r1, =AgbMain            ; 进入C语言主循环体
        mov     lr, pc
        bx      r1
        
        b       start_vector            ; 程序执行完毕后重启

    ALIGN
sp_usr  DCD     WRAM_END - 0x100
sp_irq  DCD     WRAM_END - 0x60

    EXTERN      IntrTable		;中断向量表
    GLOBAL      intr_main		;中断控制
    ALIGN
    CODE32
intr_main
        mov     r3, #0x4000000				; Check IE/IF
        add     r3, r3, #0x200				; r3: REG_IE
        ldr     r2, [r3]
        and     r1, r2, r2, lsr #16 		; r1: IE & IF
        ands    r0, r1, #0x2000  		; Game Pak Interrupt
loop    bne     loop
        mov     r2, #0
        ands    r0, r1, #0x0001   		; V-blank Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0002   ; H-blank Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0004   ; V-counter Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0008    ; Timer 0 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0010    ; Timer 1 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0020    ; Timer 2 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0040    ; Timer 3 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0080       ; Serial Communication Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0100      ; DMA0 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0200      ; DMA1 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0400      ; DMA2 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x0800      ; DMA3 Interrupt
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #0x1000       ; Key Interrupt

jump_intr
        strh    r0, [r3, #2]            ; IF Clear           11c
        ldr     r1, =IntrTable          ; Jump to user IRQ process
        add     r1, r1, r2
        ldr     r0, [r1]
        bx      r0

    END

