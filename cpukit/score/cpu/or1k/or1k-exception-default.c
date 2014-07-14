/*
 * Copyright (c) 2014 Hesham ALMatary.  All rights reserved.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */
 
#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include <rtems/score/cpu.h>
#include <rtems/fatal.h>
#include <bsp/linker-symbols.h>

void __attribute__((naked)) _OR1K_Exception_default(void)
{
   register CPU_Exception_frame *frame;
  
   __asm__ volatile (
   "l.addi  r1, r1, -%[cpufsz]\n"
   "l.sw  4(r1),r1 \n"
   "l.sw  8(r1),r2 \n"
   "l.sw  12(r1),r3 \n"
   "l.sw  16(r1),r4 \n"
   "l.sw  20(r1),r5 \n"
   "l.sw  24(r1),r6 \n"
   "l.sw  28(r1),r7 \n"
   "l.sw  32(r1),r8 \n"
   "l.sw  36(r1),r9 \n"
   "l.sw  40(r1),r10\n"
   "l.sw  44(r1),r11\n"
   "l.sw  48(r1),r12\n"
   "l.sw  52(r1),r13\n"
   "l.sw  56(r1),r14\n"
   "l.sw  60(r1),r15\n"
   "l.sw  64(r1),r16\n"
   "l.sw  68(r1),r17\n"
   "l.sw  72(r1),r18\n"
   "l.sw  76(r1),r19\n"
   "l.sw  80(r1),r20\n"
   "l.sw  84(r1),r21\n"
   "l.sw  88(r1),r22\n"
   "l.sw  92(r1),r23\n"
   "l.sw  96(r1),r24\n"
   "l.sw  100(r1),r25\n"
   "l.sw  104(r1),r26\n"
   "l.sw  108(r1),r27\n"
   "l.sw  112(r1),r28\n"
   "l.sw  116(r1),r29\n"
   "l.sw  120(r1),r30\n"
   "l.sw  124(r1),r31\n"
   "l.add %0, r0, r1\n"
   : "=r" (frame)
   : [cpufsz] "i" (sizeof(CPU_Exception_frame))
   );
  rtems_fatal( RTEMS_FATAL_SOURCE_EXCEPTION, (rtems_fatal_code) frame );
}

/* Save exception frame context from exception */

void __attribute__((naked)) _OR1K_Exception(uint32_t vector_index)
{
   volatile CPU_Exception_frame *frame;
   volatile uint32_t *vector_base = bsp_start_vector_table_begin;
   volatile uint32_t *handler = vector_base + vector_index;
   volatile uint32_t tmp;
   
   __asm__ volatile (
   "l.addi  r1, r1, -%[cpufsz]\n"
   "l.sw  4(r1),r1 \n"
   "l.sw  8(r1),r2 \n"
   "l.sw  12(r1),r3 \n"
   "l.sw  16(r1),r4 \n"
   "l.sw  20(r1),r5 \n"
   "l.sw  24(r1),r6 \n"
   "l.sw  28(r1),r7 \n"
   "l.sw  32(r1),r8 \n"
   "l.sw  36(r1),r9 \n"
   "l.sw  40(r1),r10\n"
   "l.sw  44(r1),r11\n"
   "l.sw  48(r1),r12\n"
   "l.sw  52(r1),r13\n"
   "l.sw  56(r1),r14\n"
   "l.sw  60(r1),r15\n"
   "l.sw  64(r1),r16\n"
   "l.sw  68(r1),r17\n"
   "l.sw  72(r1),r18\n"
   "l.sw  76(r1),r19\n"
   "l.sw  80(r1),r20\n"
   "l.sw  84(r1),r21\n"
   "l.sw  88(r1),r22\n"
   "l.sw  92(r1),r23\n"
   "l.sw  96(r1),r24\n"
   "l.sw  100(r1),r25\n"
   "l.sw  104(r1),r26\n"
   "l.sw  108(r1),r27\n"
   "l.sw  112(r1),r28\n"
   "l.sw  116(r1),r29\n"
   "l.sw  120(r1),r30\n"
   "l.sw  124(r1),r31\n"
   "l.add %0, r0, r1\n"
   : "=r" (frame)
   : [cpufsz] "i" (sizeof(CPU_Exception_frame))
   : "memory"
   );
   
   __asm__ volatile (
   "l.jalr  %0;"
   : 
   : "r" (handler)
   : "memory"
   );
   
   /* restore exception frame back */
   __asm__ volatile (
   "l.lwz  r1,  4(%0);"
   "l.lwz  r2,  8(%0);"
   "l.lwz  r3,  12(%0);"
   "l.lwz  r4,  16(%0);"
   "l.lwz  r5,  20(%0);"
   "l.lwz  r6,  24(%0);"
   "l.lwz  r7,  28(%0);"
   "l.lwz  r8,  32(%0);"
   "l.lwz  r9,  36(%0);"
   "l.lwz  r10, 40(%0);"
   "l.lwz  r11, 44(%0);"
   "l.lwz  r12, 48(%0);"
   "l.lwz  r13, 52(%0);"
   "l.lwz  r14, 56(%0);"
   "l.lwz  r15, 60(%0);"
   "l.lwz  r16, 64(%0);"
   "l.lwz  r17, 68(%0);"
   "l.lwz  r18, 72(%0);"
   "l.lwz  r19, 76(%0);"
   "l.lwz  r20, 80(%0);"
   "l.lwz  r21, 84(%0);"
   "l.lwz  r22, 88(%0);"
   "l.lwz  r23, 92(%0);"
   "l.lwz  r24, 96(%0);"
   "l.lwz  r25, 100(%0);"
   "l.lwz  r26, 104(%0);"
   "l.lwz  r27, 108(%0);"
   "l.lwz  r28, 112(%0);"
   "l.lwz  r29, 116(%0);"
   "l.lwz  r30, 120(%0);"
   "l.lwz  r31, 124(%0);"
   "l.addi  r1, r1, %[cpufsz]\n"
   ::"r" (frame), 
   [cpufsz] "i" (sizeof(CPU_Exception_frame))
   :"memory"
   );
}
void rtems_exception_init_mngt(void)
{
    
}
