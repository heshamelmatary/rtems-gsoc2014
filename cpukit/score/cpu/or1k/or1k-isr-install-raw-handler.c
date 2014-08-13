/**
 * @file
 *
 * @brief OR1K CPU ISR Install Raw Handler
 */

/*
 * Copyright (c) 2014 Hesham ALMatary
 *
 * COPYRIGHT (c) 1989-2006
 * On-Line Applications Research Corporation (OAR).
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include <rtems/score/cpu.h>

/*
 *  _CPU_ISR_install_raw_handler
 *
 *  OR1K Specific Information:
 *
 *  XXX document implementation including references if appropriate
 */

void _CPU_ISR_install_raw_handler(
  uint32_t    vector,
  proc_ptr    new_handler,
  proc_ptr   *old_handler
)
{
  /*
   *  This is where we install the interrupt handler into the "raw" interrupt
   *  table used by the CPU to dispatch interrupt handlers.
   */
   
  register uint32_t   sr;
  register uint32_t   mask;

  asm volatile (
    "l.mfspr %0,r0,17;"
	  "l.addi  %1,r0, 0xfffffffb;"
	  "l.and   %1,%1,%0" : "=r" (sr) : "r" (mask));
	  
  *old_handler = _ISR_Vector_table[vector]
  
  _ISR_Vector_table[ vector ] = new_handler;
  
  /* Restore supervision register */
  asm volatile ("l.mtspr r0,%0,17":: "r" (sr));
}
