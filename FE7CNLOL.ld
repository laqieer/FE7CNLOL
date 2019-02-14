/*	by laqieer
	2017/1/27
	Ö÷Á´½Ó½Å±¾
*/

SECTIONS
{
	. = 0x8000000;
	.rom : {*.o(.rom)}
	.text : {*(.text)}
	.rodata : {*(.rodata) . = ALIGN(4);}
	/DISCARD/ : { *(.data) *(.bss) }	
	INCLUDE Hook.ld
	INCLUDE Data.ld
	INCLUDE build\auto.lds
}


