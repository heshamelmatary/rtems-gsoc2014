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
  _OR1K_mtspr(CPU_OR1K_SPR_TTMR, 0x600FFED9);
  _OR1K_mtspr(CPU_OR1K_SPR_TTCR, 0); 
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
  uint32_t sr;
 
  /* Set timer contents to restart mode */
  _OR1K_mtspr(CPU_OR1K_SPR_TTMR, 0x600FFED9);
  _OR1K_mtspr(CPU_OR1K_SPR_TTCR, 0);
   
   /* Enable tick timer */
  sr = _OR1K_mfspr(CPU_OR1K_SPR_SR);
  sr |= CPU_OR1K_SPR_SR_TEE;
  _OR1K_mtspr(CPU_OR1K_SPR_SR, sr);
}
 
 static void or1ksim_clock_cleanup(void)
{

}

/*
 *  Return the nanoseconds since last tick
 */
static uint32_t or1ksim_clock_nanoseconds_since_last_tick(void)
{
  return (uint32_t) 400000000UL;
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
