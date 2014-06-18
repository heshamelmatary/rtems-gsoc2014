#include <bsp/linker-symbols.h>

  .extern bsp_start
  .extern bsp_section_bss_begin
  .extern bsp_section_bss_end

  .extern  bsp_start_vector_table_begin
  .extern  bsp_start_vector_table_end
  .extern  bsp_start_vector_table_size
  .extern  bsp_vector_table_size
  .extern  bsp_section_stack_begin 

  /* Global symbols */
  .globl  _start

/* Popualte vector table */

.section .vector, "ax"

.org 0x100
bsp_start_vector_table_begin:
_reset:
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
  l.movhi r1,hi(bsp_section_stack_begin)
  l.add   r2,r0,r1 
  
/* Clearing .bss */
  l.movhi r13,hi(bsp_section_bss_begin)
  l.ori   r13,r13,lo(bsp_section_bss_begin)
  l.movhi r15,hi(bsp_section_bss_end)
  l.ori   r15,r15,lo(bsp_section_bss_end)

_loop_clear_bss:
  l.sfgeu r13,r15
  l.bf    _end_clear_bss
  l.addi  r13,r13,4
  l.sw    0(r13), r0
  l.j     _loop_clear_bss
  l.nop
_end_clear_bss:

  l.j bsp_start 
  l.nop


/* Temporary code for unhandeled exceptions */
.section .text
.align 
.global _unhandled_exception

unhandled_exception:
  l.j unhandled_exception
  l.nop

