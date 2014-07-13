/**
 * @file
 *
 * @ingroup or1k_interrupt
 *
 * @brief Interrupt support.
 */

/*
 * Copyright (c) 2014 Hesham ALMatary
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <bsp/irq.h>

void bsp_interrupt_handler_default(int vector)
{
    printk("spurious interrupt: %u\n", vector);
}

rtems_status_code bsp_interrupt_facility_initialize()
{


}

void bsp_interrupt_dispatch()
{

}

rtems_status_code bsp_interrupt_vector_enable()
{
  register uint32_t   sr;
  
  /* Enable CPU interrupts */
  asm volatile (
    "l.mfspr %0,r0,17;"
    "l.ori %0,%1,0x7;"
    "l.mtspr r0,%1,0x11\n\t" : "=r" (sr): "r" (sr)
    );
    
  /* Enable external interrupts */
  
  
}

rtems_status_code bsp_interrupt_vector_disable()
{

}
