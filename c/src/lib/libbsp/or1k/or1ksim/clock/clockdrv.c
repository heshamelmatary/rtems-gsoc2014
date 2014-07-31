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
#include <rtems/score/cpu.h>

static void or1ksim_clock_at_tick(void)
{
  uint32_t TTMR = 0x600FFED9;
  asm volatile (  
    "l.mtspr r0,%0,0x5000;" /* load TTMR register */
    ::"r" (TTMR): "memory"
    );
    
  asm volatile ("l.mtspr r0,r0,0x5001;");
    
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
  register uint32_t   sr;
  register uint32_t   mask;

  asm volatile (
    "l.mfspr %0,r0,17;"
	  "l.addi  %1,r0, 0xfffffff9;"
	  "l.and   %1,%1,%0" : "=r" (sr) : "r" (mask)
    );
    
  
   /* Disable ISR */
   _ISR_Disable( level );
 
  /* Set timer contents to restrt mode */
  TTMR = 0x600FFED9;
   asm volatile (  
    "l.mtspr r0,%0,0x5000;" /* load TTMR register */
    :: "r" (TTMR): "memory"
    );
    
    asm volatile ("l.mtspr r0,r0,0x5001;");
    
    asm volatile (
    "l.ori %0,%1,0x7;"
    "l.mtspr r0,%1,0x11\n\t": "=r" (sr): "r" (sr));
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
  return (uint32_t) 100000000UL;
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
