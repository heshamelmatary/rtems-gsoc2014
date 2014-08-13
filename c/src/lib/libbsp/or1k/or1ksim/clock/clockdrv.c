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
#include <rtems/score/or1k-utility.h>

static void or1ksim_clock_at_tick(void)
{
  uint32_t TTMR = 0x600FFED9;
  asm volatile (  
    "l.mtspr r0,%0,0x5000;" /* load TTMR register */
    ::"r" (TTMR): "memory"
    );
    
  asm volatile ("l.mtspr r0,r0,0x5001;");
    
}

static void or1ksim_clock_handler_install(proc_ptr new_isr, proc_ptr old_isr)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  
  _CPU_ISR_install_vector(OR1K_EXCEPTION_TICK_TIMER,
                          new_isr,
                          NULL);

  if (sc != RTEMS_SUCCESSFUL) {
    rtems_fatal_error_occurred(0xdeadbeef);
  }
}

static void or1ksim_clock_initialize(void)
{ 
  uint32_t   TTMR;
  ISR_Level level;
  
   /* Disable ISR */
   _ISR_Disable( level );
 
  /* Set timer contents to restart mode */
  TTMR = 0x600FFED9;
  
   asm volatile (  
    "l.mtspr r0,%0,0x5000;" /* load TTMR register */
    :: "r" (TTMR): "memory"
    );
    
    asm volatile ("l.mtspr r0,r0,0x5001;");
   
   /* Enable ISR */
    _ISR_Enable( level );
 }
 
 static void or1ksim_clock_cleanup(void)
{

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
    or1ksim_clock_handler_install(isr, old_isr);               \
    old_isr = NULL;                                    \
  } while (0)

#define Clock_driver_support_shutdown_hardware() or1ksim_clock_cleanup()

#define Clock_driver_nanoseconds_since_last_tick \
  or1ksim_clock_nanoseconds_since_last_tick


#include "../../../shared/clockdrv_shell.h"
