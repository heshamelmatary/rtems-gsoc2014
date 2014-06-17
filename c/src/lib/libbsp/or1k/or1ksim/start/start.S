.file "start.S"

  .extern bsp_start

  /* Global symbols */
  .globl  _start
  .globl  bsp_start_vector_table_begin
  .globl  bsp_start_vector_table_end
  .globl  bsp_start_vector_table_size
  .globl  bsp_vector_table_size
  .global bsp_section_stack_begin 


/* Popualte vector table */

.section .text, "ax"

bsp_start_vector_table_begin:
.org 0x100
_reset:
  l.movhi	r0,0
	l.movhi	r1,0
	l.movhi	r2,0
	l.movhi	r3,0
	l.movhi	r4,0
	l.movhi	r5,0
	l.movhi	r6,0
	l.movhi	r7,0
	l.movhi	r8,0
	l.movhi	r9,0
	l.movhi	r10,0
	l.movhi	r11,0
	l.movhi	r12,0
	l.movhi	r13,0
	l.movhi	r14,0
	l.movhi	r15,0
	l.movhi	r16,0
	l.movhi	r17,0
	l.movhi	r18,0
	l.movhi	r19,0
	l.movhi	r20,0
	l.movhi	r21,0
	l.movhi	r22,0
	l.movhi	r23,0
	l.movhi	r24,0
	l.movhi	r25,0
	l.movhi	r26,0
	l.movhi	r27,0
	l.movhi	r28,0
	l.movhi	r29,0
	l.movhi	r30,0
	l.movhi	r31,0

  l.ori	r1,r0,0x1
  l.mtspr	r0,r1,17
  l.movhi  r4,hi(_start)
  l.mtspr  r0,r0,0x1000
  l.ori    r4,r4,lo(_start)
  l.jr     r4
  l.nop

.org 0x200
_buserr:
  l.j  unhandled_exception
  l.nop

.org 0x300
_dPageFault:
  l.j  unhandled_exception
  l.nop

.org 0x400
_iPageFaule:
  l.j  unhandled_exception
  l.nop

.org 0x500
_timer:
  l.j  unhandled_exception
  l.nop

.org 0x600
_misaligned:
  l.j  unhandled_exception
  l.nop

.org 0x700
_undefIns:
  l.j  unhandled_exception
  l.nop

.org 0x800
_exInt:
  l.j  unhandled_exception
  l.nop

.org 0x900
_dTLB:
  l.j  unhandled_exception
  l.nop

.org 0xA00
_iTLB:
  l.j  unhandled_exception
  l.nop

.org 0xB00
_range:
  l.j  unhandled_exception
  l.nop

.org 0xC00
_syscall:
  l.j  unhandled_exception
  l.nop

.org 0xD00
_fp:
  l.j  unhandled_exception
  l.nop

.org 0xE00
_trap:
  l.j  unhandled_exception
  l.nop

.org 0xF00
_undef1:
  l.j  unhandled_exception
  l.nop

.org 0x1000
_undef2:
  l.j  unhandled_exception
  l.nop

.org 0x1100
_undef3:
  l.j  unhandled_exception
  l.nop

.org 0x1200
_undef4:
  l.j  unhandled_exception
  l.nop

.org 0x1300
_undef5:
  l.j  unhandled_exception
  l.nop

.org 0x1400
_undef6:
  l.j  unhandled_exception
  l.nop

.org 0x1500
_undef7:
  l.j  unhandled_exception
  l.nop

.org 0x1600
_undef8:
  l.j  unhandled_exception
  l.nop

.org 0x1700
_undef9:
  l.j  unhandled_exception
  l.nop

.org 0x1800
_undef10:
  l.j  unhandled_exception
  l.nop

.org 0x1900
_undef11:
  l.j  unhandled_exception
  l.nop

.org 0x1A00
_undef12:
  l.j  unhandled_exception
  l.nop

.org 0x1B00
_undef13:
  l.j  unhandled_exception
  l.nop

.org 0x1C00
_undef14:
  l.j  unhandled_exception
  l.nop

.org 0x1D00
_undef15:
  l.j  unhandled_exception
  l.nop

.org 0x1E00
_undef16:
  l.j  unhandled_exception
  l.nop

.org 0x1F00
_undef17:
  l.j  unhandled_exception
  l.nop
bsp_start_vector_table_end:

.type _start,@function

  .section  ".bsp_start_text", "ax"
_start:
/* load stack and frame pointers */
  l.movhi r1,hi(0x18000000)
  l.ori   r1,r1,lo(0x18000000)
  l.add   r2,r0,r1 
  
  l.j bsp_start 
  l.nop


/* Temporary code for unhandeled exceptions */
.section .text
.align 
.global _unhandled_exception

unhandled_exception:
  l.j unhandled_exception
  l.nop

 .set  bsp_section_stack_begin, 0x18000000
 .set  bsp_start_vector_table_size, bsp_start_vector_table_end - bsp_start_vector_table_begin
 .set  bsp_vector_table_size, bsp_start_vector_table_size
