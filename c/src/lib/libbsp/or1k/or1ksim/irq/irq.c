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
#include <bsp/irq-generic.h>

<<<<<<< HEAD
/* Almost all of the jobs that the following functions should 
 * do are implemented in cpukit 
 */
 
=======
/* Almost all of the jobs that the following functions should
 * do are implemented in cpukit
 */

>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
void bsp_interrupt_handler_default(rtems_vector_number vector)
{
    printk("spurious interrupt: %u\n", vector);
}

rtems_status_code bsp_interrupt_facility_initialize()
{
  return 0;
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
<<<<<<< HEAD
  return 0; 
=======
  return 0;
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
}

rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  return 0;
}
