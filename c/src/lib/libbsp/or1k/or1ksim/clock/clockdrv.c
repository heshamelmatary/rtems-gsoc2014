/**
 * @file
 *
 * @ingroup bsp_clock
 *
 * @brief or1ksim clock support.
 */

/*
 * or1ksim Clock driver
 *
 * Copyright (c) 2014 Hesham ALMatary
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.org/license/LICENSE
 *
*/

#include <rtems.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/or1ksim.h>

static void or1ksim_clock_at_tick(void)
{
   return 0;
}

static void or1ksim_clock_handler_install(void)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  /* FIXME:
   Currently clock interrupt handler is statically
   installed at start.S 
   */ 
  if (sc != RTEMS_SUCCESSFUL) {
    rtems_fatal_error_occurred(0xdeadbeef);
  }
}

static void or1ksim_clock_initialize(void)
{
 /* Enable Timer interrupt, restart mode, zero counter register*/
  __asm__ __volatile__(
    "l.addi  r1,r0,0x00000201;"
    "l.mtspr r1,r0,0;"
    
    "l.addi  r1,r0,0x00000200;"
    "l.movhi r2,hi(0x50000000);"
    "l.ori   r2,r2,0xffff;"
    "l.mtspr r1,r2,0;"
    
    "l.addi  r1,r0,17;"
    "l.addi  r2,r0,0x3;"
    "l.mtspr r1,r2,0;"
  );
  
 }
 
 static void or1ksim_clock_cleanup(void)
{
  return 0;
}

/*
 *  Return the nanoseconds since last tick
 */
static uint32_t or1ksim_clock_nanoseconds_since_last_tick(void)
{
  return 0;
}

#define Clock_driver_support_at_tick() or1ksim_clock_at_tick()

#define Clock_driver_support_initialize_hardware() or1ksim_clock_initialize()

#define Clock_driver_support_install_isr(isr, old_isr) \
  do {                                                 \
    or1ksim_clock_handler_install();               \
    old_isr = NULL;                                    \
  } while (0)

#define Clock_driver_support_shutdown_hardware() or1ksim_clock_cleanup()

#define Clock_driver_nanoseconds_since_last_tick \
  or1ksim_clock_nanoseconds_since_last_tick


#include "../../../shared/clockdrv_shell.h"
