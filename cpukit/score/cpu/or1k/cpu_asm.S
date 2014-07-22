/*  cpu_asm.s
 *
 *  This file contains all assembly code for the or1k implementation
 *  of RTEMS.
 *
 *  Copyright (c) 2014 Hesham ALMatary, <heshamelmatary@gmail.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */
 
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/asm.h>
#include <rtems/score/percpu.h>

/*void _ISR_Handler()
 *
 *  This routine provides the RTEMS interrupt management.
 *
 *  NOTE:
 *    Upon entry, the master stack will contain an interrupt stack frame
 *    back to the interrupted thread and the interrupt stack will contain
 *    a throwaway interrupt stack frame.  If dispatching is enabled, and this
 *    is the outer most interrupt, and a context switch is necessary or
 *    the current thread has pending signals, then set up the master stack to
 *    transfer control to the interrupt dispatcher.
 */
 
 SYM (_ISR_Handler):
   l.addi THREAD_DISPATCH_DISABLE_LEVEL
