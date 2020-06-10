	.word = 0
	.word = 0
	.word = 0
	.word = 0x80000
.global _start
_start:
	ldr r0, =0xE0200C00
	ldr r1, =0x1111
	str r1, [r0]
	
	ldr r0, =0xE0200C04
	ldr r1, =0x08
	str r1, [r0]
	
loop:
	b loop
	
