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

void _OR1K_Exception_default(uint32_t vector, CPU_Exception_frame *frame);

void _OR1K_Exception_default(uint32_t vector, CPU_Exception_frame *frame)
{
  printk("Exception occured with vector number %d", vector);
  rtems_fatal( RTEMS_FATAL_SOURCE_EXCEPTION, (rtems_fatal_code) frame );
}

