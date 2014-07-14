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
#include <bsp/linker-symbols.h>

.align 4
.text
.global _OR1K_Exception_Process 

_OR1K_Exception_Process:
  l.addi  r1, r1, -128
  l.sw  8(r1),r2
  /* r3 is saved by exception handler */
  l.sw  20(r1),r5
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
  
  /* Call the exception handler from vector table */
  l.slli r3, r3, 2
  l.addi r3, r3, lo(bsp_start_vector_table_begin)
  l.lwz  r3, 0(r3)
  l.jalr r3
  l.nop
  
exception_frame_restore:
  l.lwz  r2,  8(r1)
  l.lwz  r3,  12(r1)
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
  l.lwz  r1, 4(r1)
  l.addi r1, r1, 128
 
  l.jr   r9
  l.nop

