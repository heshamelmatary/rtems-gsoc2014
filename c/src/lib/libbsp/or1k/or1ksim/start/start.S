#include <bsp/linker-symbols.h>

/* The following macro defines the first instructions every exception 
 * should execute before jumping to its handler function from the 
 * exception vector table. First, r13 is saved to a dedicated word of
 * memory because it will be used to load the address of the handler 
 * within the vector table. After serving the exception, r13 is loaded
 * back, and pc, sp registers are restored using l.rfe instruction which
 * returns back to the origianl place where the exceptions happended.
 */
#define EXCEPTION_SETUP(vector) \
  l.sw   lo(bsp_start_vector_table_begin)(r0), r3; \
  l.addi r3, r0, vector; \
  l.jal  _OR1K_Exception_Process; \
  l.nop; \
  l.lwz  r3, lo(bsp_start_vector_table_begin)(r0);\
  l.rfe;\
  l.nop ; 

  /*l.sw   lo(bsp_start_vector_table_begin)(r0), r13; \
  l.ori  r13, r0, lo(bsp_start_vector_table_begin + ((vector) * 4)); \
  l.lwz  r13, 0(r13); \
  l.jalr r13; \
  l.lwz  r13, lo(bsp_start_vector_table_begin)(r0); \
  l.rfe ; \
  */

#define EXCEPTION_SETUP1(vector) \
  l.sw   lo(bsp_start_vector_table_begin)(r0), r13; \
  l.addi r3, r0, vector; \
  l.movhi r13, hi(_OR1K_Exception_Process); \
  l.ori   r13, r13, lo(_OR1K_Exception_Process); \
  l.jalr r13; \
  l.nop
  l.rfe ; \
  l.nop ;

  .extern bsp_start
  .extern boot_card
  .extern bsp_section_bss_begin
  .extern bsp_section_bss_end

  .extern  bsp_start_vector_table_end
  .extern  bsp_start_vector_table_size
  .extern  bsp_vector_table_size
  .extern  bsp_section_stack_begin 

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
  EXCEPTION_SETUP(2)

.org 0x300
_dPageFault:
  EXCEPTION_SETUP(3)

.org 0x400
_iPageFaule:
  EXCEPTION_SETUP(4)

.org 0x500
_timer:
  EXCEPTION_SETUP(5)


  /*l.addi r3,r0,5
  l.jal _OR1K_Exception_Process
  l.rfe
  l.nop
  */

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
  .word _OR1K_Exception_default /* Bus Error */ 
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

.type _start,@function

  .section  ".bsp_start_text", "ax"
_start:
  /* Set SP register to SP mode */
  l.ori  r1,r0,0x1
  l.mtspr r0,r1,17

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

  l.j boot_card
  l.nop


/* Temporary code for unhandeled exceptions */
.section .text
.align 
.global _unhandled_exception

unhandled_exception:
  l.nop
