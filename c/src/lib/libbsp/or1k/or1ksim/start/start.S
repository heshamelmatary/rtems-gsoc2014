<<<<<<< HEAD
#include <bsp/linker-symbols.h>

/* The following macro defines the first instructions every exception 
 * should execute before jumping to its handler function from the 
 * exception vector table. First, r13 is saved to a dedicated word of
 * memory because it will be used to load the address of the handler 
 * within the vector table. After serving the exception, r13 is loaded
 * back, and pc, sp registers are restored using l.rfe instruction which
 * returns back to the origianl place where the exceptions happended.
=======
/*
 * Copyright (c) 2014 Hesham ALMatary <heshamelmatary@gmail.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE
 */
#include <bsp/linker-symbols.h>

/* The following macro defines the first instructions every exception
 * should execute before jumping to its handler function from the
 * exception vector table. r3 is saved into the stack and loaded with
 * vector number before jumping to _ISR_Handler. r3 value is restored
 * back from _ISR_Handler after handling the exception and before
 * returning from interrupt.
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
 */
#define EXCEPTION_SETUP(vector) \
  l.nop   ;\
  l.addi  r1, r1, -4 ;\
  l.sw    0(r1), r3; \
  l.addi  r3, r0, vector; \
  l.j     _ISR_Handler; \
<<<<<<< HEAD
  l.nop 
=======
  l.nop
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a

  .extern bsp_start
  .extern boot_card
  .extern bsp_section_bss_begin
  .extern bsp_section_bss_end

  .extern  bsp_start_vector_table_end
  .extern  bsp_start_vector_table_size
  .extern  bsp_vector_table_size
<<<<<<< HEAD
  .extern  bsp_section_stack_begin 
=======
  .extern  bsp_section_stack_begin
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a

  .extern exception_frame_save
  .extern _OR1K_Exception_Process
  .extern _OR1K_Exception_default
  .extern rtems_clock_tick
  .extern _exit
  .extern printk
  .extern bsp_interrupt_handler_default

  /* Global symbols */
  .global  _start
  .global bsp_start_vector_table_begin

/* Popualte HW vector table */

.section .vector, "ax"

.org 0x100
_reset:
  l.j _start
  l.nop

.org 0x200
_buserr:
<<<<<<< HEAD
 l.rfe
 l.nop
=======
  EXCEPTION_SETUP(2)
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a

.org 0x300
_dPageFault:
  EXCEPTION_SETUP(3)

.org 0x400
_iPageFaule:
  EXCEPTION_SETUP(4)

.org 0x500
_timer:
  EXCEPTION_SETUP(5)

.org 0x600
_unalign:
<<<<<<< HEAD
  l.rfe
  l.nop
=======
  EXCEPTION_SETUP(6)
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a

.org 0x700
_undefIns:
  EXCEPTION_SETUP(7)

.org 0x800
_exInt:
  EXCEPTION_SETUP(8)

.org 0x900
_dTLB:
  EXCEPTION_SETUP(9)

.org 0xA00
_iTLB:
  EXCEPTION_SETUP(10)

.org 0xB00
_range:
  EXCEPTION_SETUP(11)

.org 0xC00
_syscall:
  EXCEPTION_SETUP(12)

.org 0xD00
_fp:
  EXCEPTION_SETUP(13)

.org 0xE00
_trap:
  EXCEPTION_SETUP(14)

.org 0xF00
_undef1:
  EXCEPTION_SETUP(15)

.org 0x1500
_undef2:
  EXCEPTION_SETUP(16)

.org 0x1900
_undef3:
  EXCEPTION_SETUP(17)

.org 0x1F00

bsp_start_vector_table_begin:

  .word 0
  .word _start /* Reset */
<<<<<<< HEAD
  .word _OR1K_Exception_default /* Bus Error */ 
=======
  .word _OR1K_Exception_default /* Bus Error */
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
  .word _OR1K_Exception_default /* Data Page Fault */
  .word _OR1K_Exception_default /* Instruction Page Fault */
  .word _OR1K_Exception_default /* Tick timer */
  .word _OR1K_Exception_default /* Alignment */
  .word _OR1K_Exception_default /* Undefiend Instruction */
  .word _OR1K_Exception_default /* External Interrupt */
  .word _OR1K_Exception_default /* Data TLB Miss */
  .word _OR1K_Exception_default /* Instruction TLB Miss */
  .word _OR1K_Exception_default /* Range Exception */
  .word _OR1K_Exception_default /* System Call */
  .word _OR1K_Exception_default /* Floating Point Exception */
  .word _OR1K_Exception_default /* Trap */
  .word _OR1K_Exception_default /* Reserver for future use */
  .word _OR1K_Exception_default /* Reserved for implementation-specific */
  .word _OR1K_Exception_default /* Reserved for custom exceptions. */

bsp_start_vector_table_end:

  .section  ".bsp_start_text", "ax"
  .type _start,@function

_start:
<<<<<<< HEAD
  /* Set SP register to SP mode */
  l.ori  r1,r0,0x1
  l.mtspr r0,r1,17

  /* load stack and frame pointers */
  l.movhi r1,hi(bsp_section_stack_begin)
  l.ori   r1, r1, lo(bsp_section_stack_begin)
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
=======
  /* Set SR register to Supervision mode */
  l.ori  r1, r0, 0x1
  l.mtspr r0, r1, 17

  /* load stack and frame pointers */
  l.movhi r1, hi(bsp_section_stack_begin)
  l.ori   r1, r1, lo(bsp_section_stack_begin)
  l.add   r2, r0, r1

/* Clearing .bss */
  l.movhi r13, hi(bsp_section_bss_begin)
  l.ori   r13, r13, lo(bsp_section_bss_begin)
  l.movhi r15, hi(bsp_section_bss_end)
  l.ori   r15, r15, lo(bsp_section_bss_end)

_loop_clear_bss:
  l.sfgeu r13, r15
  l.bf    _end_clear_bss
  l.addi  r13, r13, 4
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
  l.sw    0(r13), r0
  l.j     _loop_clear_bss
  l.nop
_end_clear_bss:

  l.j boot_card
  l.nop

<<<<<<< HEAD

/* Temporary code for unhandeled exceptions */
.section .text
.align 
=======
/* Temporary code for unhandled exceptions */
.section .text
.align
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
.global _unhandled_exception

unhandled_exception:
  l.nop
<<<<<<< HEAD

=======
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
