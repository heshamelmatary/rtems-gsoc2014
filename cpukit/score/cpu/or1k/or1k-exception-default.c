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

void rtems_exception_init_mngt(void)
{
      _CPU_ISR_install_vector(OR1K_EXCEPTION_TICK_TIMER,
                              NULL,
                              NULL);
}
