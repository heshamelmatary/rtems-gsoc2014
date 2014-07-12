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

bsp_interrupt_dispatch()
{

}

rtems_status_code bsp_interrupt_vector_enable()
{

}

rtems_status_code bsp_interrupt_vector_disable()
{

}
