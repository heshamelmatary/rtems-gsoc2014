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

#include <string.h>

#include <rtems/score/cpu.h>
#include <rtems/score/interr.h>
#include <rtems/score/or1k-utility.h>

void _CPU_Context_Initialize(
  Context_Control *context,
  void *stack_area_begin,
  size_t stack_area_size,
  uint32_t new_level,
  void (*entry_point)( void ),
  bool is_fp,
  void *tls_area
)
{
  uint32_t stack = (uint32_t) stack_area_begin;
  register uint32_t sr;
  
  sr = _OR1K_mfspr(CPU_OR1K_SR);
  
  memset(context, 0, sizeof(*context));
  
  context->r1 = stack;
  context->r2 = stack;
  context->r9 = (uint32_t) entry_point;
  context->sr = sr;
}
