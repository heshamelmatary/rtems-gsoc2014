/*
 *  Opencore Or1k CPU Dependent Source
 *
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  This file adapted from no_bsp board library of the RTEMS distribution.
 *  The body has been modified for the Bender Or1k implementation by
 *  Chris Ziomkowski. <chris@asics.ws>
 */

#include <rtems/system.h>
#include <rtems/score/isr.h>
#include <rtems/score/wkspace.h>
#include <bsp/linker-symbols.h>

/*  _CPU_Initialize
 *
 *  This routine performs processor dependent initialization.
 *
 *  INPUT PARAMETERS:
 *    cpu_table       - CPU table to initialize
 *    thread_dispatch - address of disptaching routine
 *
 */

extern char bsp_start_vector_table_begin[];

void _CPU_Initialize(
void
)
{
  /*
   *  The thread_dispatch argument is the address of the entry point
   *  for the routine called at the end of an ISR once it has been
   *  decided a context switch is necessary.  On some compilation
   *  systems it is difficult to call a high-level language routine
   *  from assembly.  This allows us to trick these systems.
   *
   *  If you encounter this problem save the entry point in a CPU
   *  dependent variable.
   */


  /*
   *  If there is not an easy way to initialize the FP context
   *  during Context_Initialize, then it is usually easier to
   *  save an "uninitialized" FP context here and copy it to
   *  the task's during Context_Initialize.
   */

  /* FP context initialization support goes here */

 // _CPU_Table = *cpu_table;
}

/*PAGE
 *
 *  _CPU_ISR_Get_level
 *
 *  or1k Specific Information:
 *
 */

inline uint32_t   _CPU_ISR_Get_level( void )
{
  return 0;
}

/*PAGE
 *
 *  _CPU_ISR_install_raw_handler
 *
 *  or1k Specific Information:
 *
 *  As a general rule the following is done for interrupts:
 *  
 *  For normal exceptions, exceptions are immediately reenabled
 *  by setting the SR_EXR bit. For interrupt exceptions, the
 *  SR_EIR bit is first cleared, and then exceptions are reenabled.
 */
 
void _CPU_ISR_install_raw_handler(
  uint32_t   vector,
  proc_ptr    new_handler,
  proc_ptr   *old_handler
)
{

}

/*PAGE
 *
 *  _CPU_ISR_install_vector
 *
 *  This kernel routine installs the RTEMS handler for the
 *  specified vector.
 *
 *  Input parameters:
 *    vector      - interrupt vector number
 *    old_handler - former ISR for this vector number
 *    new_handler - replacement ISR for this vector number
 *
 *  Output parameters:  NONE
 *
 *
 *  NO_CPU Specific Information:
 *
 *  XXX document implementation including references if appropriate
 */

void _CPU_ISR_install_vector(
  uint32_t    vector,
  proc_ptr    new_handler,
  proc_ptr   *old_handler
)
{
   volatile uint32_t *table = 
     (volatile uint32_t *) bsp_start_vector_table_begin;
   uint32_t current_handler = table [vector];
   
   ISR_Level level;

  _ISR_Disable( level );

  /* The current handler is now the old one */
  if (old_handler != NULL) {
    *old_handler = (proc_ptr) current_handler;
  }

  /* Write only if necessary to avoid writes to a maybe read-only memory */
  if (current_handler != (uint32_t) new_handler) {
    table [vector] = (uint32_t) new_handler;
  }
    
   _ISR_Enable( level );
}

/*PAGE
 *
 *  _CPU_Install_interrupt_stack
 *  
 *  We don't use a separate interrupt stack.
 *
 */

void _CPU_Install_interrupt_stack( void )
{
}

void _CPU_Context_Initialize_fp (void)
{
}

/*PAGE
 *
 *  _CPU_Thread_Idle_body
 *
 *  NOTES:
 *
 *  1. This is the same as the regular CPU independent algorithm.
 *
 *  2. If you implement this using a "halt", "idle", or "shutdown"
 *     instruction, then don't forget to put it in an infinite loop.
 *
 *  3. Be warned. Some processors with onboard DMA have been known
 *     to stop the DMA if the CPU were put in IDLE mode.  This might
 *     also be a problem with other on-chip peripherals.  So use this
 *     hook with caution.
 *
 */

void _CPU_Thread_Idle_body( void )
{

  for( ; ; )
    /* insert your "halt" instruction here */ ;
}
