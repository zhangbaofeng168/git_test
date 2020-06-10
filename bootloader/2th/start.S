/*
 *bootloader的第一个文件
 */

	.word 0x2000
	.word 0x0
	.word 0x0
	.word 0x0
.global _start
_start:
	b reset

	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction:
	nop
_software_interrupt:
	nop
_prefetch_abort:
	nop
_data_abort:
	nop
_not_used:
	nop
_irq:
	nop
_fiq:
	nop
reset:
	bl init_clock
	ldr sp, =0xd0036000
	bl led_test
	bl uart_init
	bl mem_init
	ldr sp, =0x33dffff0 @ox33e00000-16 
	bl copy_uboot_to_ram
	ldr	pc, _start_main

_start_main:
	.word main

#define CLK_DIV0  0xE0100300
#define MPLL_CON  0xE0100108
#define APLL_CON0 0xE0100100
#define CLK_SRC0  0xE0100200

#define DIV_VAL  ((4<<4)|(4<<8)|(1<<12)|(3<<16)|(1<<20)|(4<<24)|(1<<28))
#define APLL_VAL ((1<<31)|(3<<8)|(125<<16)|(1<<0))
#define MPLL_VAL ((1<<31)|(12<<8)|(667<<16)|(1<<0))
init_clock:
	ldr r0, =CLK_DIV0
	ldr r1, =DIV_VAL
	str r1,[r0]

	ldr r0, =APLL_CON0
	ldr r1, =APLL_VAL
	str r1,[r0]

	ldr r0, =MPLL_CON
	ldr r1, =MPLL_VAL
	str r1,[r0]

	ldr r0, =CLK_SRC0
	ldr r1, =0x1111
	str r1,[r0]
	
	mov pc, lr
	
	