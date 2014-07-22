/**
 * @file
 *
 * @ingroup ScoreCPU
 *
 * @brief OR1K exception support implementation.
 */

/*
 *  Copyright (c) 2014, Hesham ALMatary
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/asm.h>
#include <rtems/score/percpu.h>

.align 4
.text
.global _OR1K_Exception_Process 
.type	  _OR1K_Exception_Process,@function

_OR1K_Exception_Process:
  
  l.addi  r1, r1, -140
  /* r3 is saved by exception handler */
  l.sw  20(r1),r5
  l.sw  24(r1),r6
  /* Increment nesting level */
  l.movhi r6, hi(_Per_CPU_Information + 0)
  l.ori   r6, r6, lo(_Per_CPU_Information + 0)
  l.lwz   r5, 0(r6)
  l.addi  r5, r5, 1
  l.sw    0(r6), r5
  
  /* Disable multitasking */
  l.movhi r6, hi(_Per_CPU_Information + 4)
  l.ori   r6, r6, lo(_Per_CPU_Information + 4)
  l.lwz   r5, 0(r6)
  l.addi  r5, r5, 1
  l.sw    0(r6), r5
  
  l.sw  8(r1),r2
  
  l.sw  24(r1),r6 
  l.sw  28(r1),r7
  l.sw  32(r1),r8
  l.sw  36(r1),r9
  l.sw  40(r1),r10
  l.sw  44(r1),r11
  l.sw  48(r1),r12
  l.sw  52(r1),r13
  l.sw  56(r1),r14
  l.sw  60(r1),r15
  l.sw  64(r1),r16
  l.sw  68(r1),r17
  l.sw  72(r1),r18
  l.sw  76(r1),r19
  l.sw  80(r1),r20
  l.sw  84(r1),r21
  l.sw  88(r1),r22
  l.sw  92(r1),r23
  l.sw  96(r1),r24
  l.sw  100(r1),r25
  l.sw  104(r1),r26
  l.sw  108(r1),r27
  l.sw  112(r1),r28
  l.sw  116(r1),r29
  l.sw  120(r1),r30
  l.sw  124(r1),r31
  /* Exception level related registers */
  
  /* EPCR */
  l.mfspr r13, r0, 32 
  l.sw  128(r1), r13 /* epcr */

  /* EEAR */
  l.mfspr r13, r0, 48 
  l.sw  132(r1), r13 /* eear */
  
  /* ESR */
  l.mfspr r13, r0, 64 
  l.sw  136(r1), r13  /* esr */ 

  
  /* Call the exception handler from vector table */
  l.slli r3, r3, 2
  l.addi r3, r3, lo(bsp_start_vector_table_begin)
  l.lwz  r3, 0(r3)
  l.jalr r3
  l.nop
  
exception_frame_restore:

  /* Exception level related registers */
  
  /* EPCR */
  l.lwz  r13,  128(r1)
  l.mtspr r0, r13, 32 

  /* EEAR */
  l.lwz  r13,  132(r1)
  l.mtspr r0, r13, 48 
  
  /* ESR */
  l.lwz  r13,  136(r1)
  l.mtspr r0, r13, 64
  
  /* Decrement nesting level */
  l.movhi r6, hi(_Per_CPU_Information + 0)
  l.ori   r6, r6, lo(_Per_CPU_Information + 0)
  l.lwz   r5, 0(r6)
  l.addi  r5, r5, -1
  l.sw    0(r6), r5
  
  /* Enable multitasking */
  l.movhi r6, hi(_Per_CPU_Information + 4)
  l.ori   r6, r6, lo(_Per_CPU_Information + 4)
  l.lwz   r5, 0(r6)
  l.addi  r5, r5, -1
  l.sw    0(r6), r5
  
  l.lwz  r2,  8(r1)
  l.lwz  r3,  12(r1)
  l.lwz  r5,  20(r1)
  l.lwz  r6,  24(r1)
  l.lwz  r7,  28(r1)
  l.lwz  r8,  32(r1)
  l.lwz  r10, 40(r1)
  l.lwz  r11, 44(r1)
  l.lwz  r12, 48(r1)
  l.lwz  r13, 52(r1)
  l.lwz  r14, 56(r1)
  l.lwz  r15, 60(r1)
  l.lwz  r16, 64(r1)
  l.lwz  r17, 68(r1)
  l.lwz  r18, 72(r1)
  l.lwz  r19, 76(r1)
  l.lwz  r20, 80(r1)
  l.lwz  r21, 84(r1)
  l.lwz  r22, 88(r1)
  l.lwz  r23, 92(r1)
  l.lwz  r24, 96(r1)
  l.lwz  r25, 100(r1)
  l.lwz  r26, 104(r1)
  l.lwz  r27, 108(r1)
  l.lwz  r28, 112(r1)
  l.lwz  r29, 116(r1)
  l.lwz  r30, 120(r1)
  
  /* Enable interrupts */
  l.mfspr r31, r0, 17
  l.ori   r31, r31, 0x7
  l.mtspr r0, r31, 17
  
  l.movhi r3, hi(_Per_CPU_Information + 8)
  l.ori   r3, r3, lo(_Per_CPU_Information + 8)
  l.lwz   r31, 0(r3)
  l.sfles r31, r0 
  l.lwz  r31, 124(r1)
  l.bf    _ISR_Dispatch /* Thread dispatch necessary */
  l.nop 
  
  l.addi r1, r1, 140
  
  l.lwz  r3, 0(r1)
  l.lwz  r13, 4(r1)
  l.addi r1, r1, 8
  
  l.rfe
  l.nop

.global SYM (_ISR_Dispatch)
SYM (_ISR_Dispatch):

  l.sw  4(r1),r1
  l.sw  8(r1),r2
  l.sw  16(r1),r4 
  l.sw  20(r1),r5
  l.sw  24(r1),r6
  l.sw  28(r1),r7
  l.sw  32(r1),r8
  /* Skip r10 as it's preserved to be used by TLS */
  /* The following set if registers are preserved across function calls */
  l.sw  56(r1),r14
  l.sw  64(r1),r16
  l.sw  72(r1),r18
  l.sw  80(r1),r20
  l.sw  88(r1),r22
  l.sw  96(r1),r24
  l.sw  104(r1),r26
  l.sw  112(r1),r28
  l.sw  120(r1),r30
  
  l.jal _Thread_Dispatch
  l.nop
  
  /* Exception level related registers */
  
  /* EPCR */
  l.lwz  r13,  128(r1)
  l.mtspr r0, r13, 32 

  /* EEAR */
  l.lwz  r13,  132(r1)
  l.mtspr r0, r13, 48 
  
  /* ESR */
  l.lwz  r13,  136(r1)
  l.mtspr r0, r13, 64
  
  l.lwz  r1,  4(r1)
  l.lwz  r2,  8(r1)
  l.lwz  r5,  20(r1)
  l.lwz  r6,  24(r1)
  l.lwz  r7,  28(r1)
  l.lwz  r8,  32(r1)
  l.lwz  r9,  36(r1)
  l.lwz  r10, 40(r1)
  l.lwz  r11, 44(r1)
  l.lwz  r12, 48(r1)
  l.lwz  r13, 52(r1)
  l.lwz  r14, 56(r1)
  l.lwz  r15, 60(r1)
  l.lwz  r16, 64(r1)
  l.lwz  r17, 68(r1)
  l.lwz  r18, 72(r1)
  l.lwz  r19, 76(r1)
  l.lwz  r20, 80(r1)
  l.lwz  r21, 84(r1)
  l.lwz  r22, 88(r1)
  l.lwz  r23, 92(r1)
  l.lwz  r24, 96(r1)
  l.lwz  r25, 100(r1)
  l.lwz  r26, 104(r1)
  l.lwz  r27, 108(r1)
  l.lwz  r28, 112(r1)
  l.lwz  r29, 116(r1)
  l.lwz  r30, 120(r1)
  l.lwz  r31, 124(r1)
  
  l.addi r1, r1, 140
  
  l.lwz  r3, 0(r1)
  l.lwz  r13, 4(r1)
  l.addi r1, r1, 8
  
  l.rfe
  l.nop

