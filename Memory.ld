/* 变量的内存布局 */

SRAM_Ex = 0xE008000;

. = SRAM_Ex;
/* .sram : {skill.o(.bss)} */