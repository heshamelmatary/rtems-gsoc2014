/*  cpu_asm.c  ===> cpu_asm.S or cpu_asm.s
 *
 *  This file contains the basic algorithms for all assembly code used
 *  in an specific CPU port of RTEMS.  These algorithms must be implemented
 *  in assembly language
 *
 *  NOTE:  This is supposed to be a .S or .s file NOT a C file.
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

/*
 *  This is supposed to be an assembly file.  This means that system.h
 *  and cpu.h should not be included in a "real" cpu_asm file.  An
 *  implementation in assembly should include "cpu_asm.h>
 */

#include <rtems/system.h>
#include <rtems/score/cpu.h>
/* #include "cpu_asm.h> */

/*
 *  _CPU_Context_save_fp_context
 *
 *  This routine is responsible for saving the FP context
 *  at *fp_context_ptr.  If the point to load the FP context
 *  from is changed then the pointer is modified by this routine.
 *
 *  Sometimes a macro implementation of this is in cpu.h which dereferences
 *  the ** and a similarly named routine in this file is passed something
 *  like a (Context_Control_fp *).  The general rule on making this decision
 *  is to avoid writing assembly language.
 *
 *  or1k specific Information:
 *
 *  This implementation of RTEMS considers the concept of
 *  "fast context switching", as defined in the or1k architecture
 *  specification. Whether or not this makes a significant
 *  impact on speed is dubious, however it is not a significant
 *  impediment to include it. It probably wastes a few cycles on
 *  every floating point context switch.
 *
 *  This implementation will currently not work on a processor where
 *  the integer unit and floating point unit are not the same size. I
 *  am waiting on an architecture change to make this feasible. It
 *  should work fine on 64 bit architectures, except for the fact that
 *  the variables are declared as 32 bits. This shouldn't really make
 *  a difference, as the fact that they must be registers should force
 *  them into a 64 bit word anyway.
 *
 *  The decision as to whether to do 32 or 64 bit saves is performed
 *  at run time based on the configuration of the CPUCFGR register. This
 *  takes a performance hit of a few cycles, but this should be a very
 *  small percentage of the total number of cycles necessary to do the
 *  save, and doesn't require special code for 32 or 64 bit versions.
 *
 *  ADDITIONAL INFORMATION:
 *
 *  It has been unanimously agreed that floating point will not be
 *  included in the initial releases of the Or1k chips, and that
 *  significant changes to the floating point architecture may
 *  occur before any such release will ever be implemented. The code
 *  below is therefore never called and never used.
 */

void _CPU_Context_save_fp(
  void **fp_context_ptr
)
{
  register uint32_t   temp;
  register uint32_t   address = (uint32_t  )(*fp_context_ptr);
  register uint32_t   xfer;
  register uint32_t   loop;

  /* %0 is a temporary register which is used for several
     values throughout the code. %3 contains the address
     to save the context, and is modified during the course
     of the context save. %1 is a second dummy register
     which is used during transfer of the floating point
     value to memory. %2 is an end of loop marker which
     is compared against the pointer %3. */

}

/*
 *  _CPU_Context_restore_fp_context
 *
 *  This routine is responsible for restoring the FP context
 *  at *fp_context_ptr.  If the point to load the FP context
 *  from is changed then the pointer is modified by this routine.
 *
 *  
 */

void _CPU_Context_restore_fp(
  void **fp_context_ptr
)
{
  register uint32_t   temp;
  register uint32_t   address = (uint32_t  )(*fp_context_ptr);
  register uint32_t   xfer;
  register uint32_t   loop;

  /* The reverse of Context_save_fp */
  /* %0 is a temporary register which is used for several
     values throughout the code. %1 contains the address
     to save the context, and is modified during the course
     of the context save. %2 is a second dummy register
     which is used during transfer of the floating point
     value to memory. %3 is an end of loop marker which
     is compared against the pointer %1. */

}

/*  _CPU_Context_switch
 *
 *  This routine performs a normal non-FP context switch.
 *
 *  NO_CPU Specific Information:
 *
 *  XXX document implementation including references if appropriate
 */

void _CPU_Context_switch(
  Context_Control  *run,
  Context_Control  *heir
)
{
  register uint32_t   temp1 = 0;
  register uint32_t   temp2 = 0;

  /* This function is really tricky. When this function is called,
     we should save our state as we need it, and then grab the
     new state from the pointer. We then do a longjump to this
     code, replacing the current stack pointer with the new
     environment. This function never returns. Instead, at some
     later time, another person will call context switch with
     our pointer in the heir variable, and they will longjump
     to us. We will then continue. Let's see how this works... */

  /* Technically, we could probably not worry about saving r3
     and r4, since these are parameters guaranteed to be saved
     by the calling function. We could also probably get away
     without saving r11, as that is filled in by the return
     statement. But as a first cut I'm in favor of just saving
     everything.... */

  /* We could be more efficient and use compile time directives
     for 32 or 64 bit, but this will allow the code to run on
     everything without modification. Feel free to comment the
     relevant sections out if you don't need it. */

  /* We should probably write this whole routine in assembly
     so that we can have seperate entry points for self restore
     or context switch. You can't jump to local labels from
     inline assembly across function calls, and I don't feel
     like embedding all the .global directives here...it really
     screws up the debugger. Oh well, what's 2 more instructions
     and a branch really cost... */

  /* One thing which we should do is check for 32 or 64 bit models
     first, and then do one branch to the appropriate code section.
     Currently, we check the architecture bit in CPUCFGR twice. Once
     during the load section and again during restore. That is inefficient,
     and considering this code is huge anyway, saving the few bytes
     simply doesn't make any practical sense. FIX THIS LATER. */

  /* Note that this routine assumes software context switches are
     done with the same CID. In other words, it will not manage
     the CIDs and assign a new one as necessary. If you tell it
     to restore a context at CID 2, and the current one is at CID
     4, it will do what it is told. It will overwrite the registers
     for context ID 2, meaning they are irretrievably lost. I hope
     you saved them earlier.... */
 
  /* Note that you can have a context jump anywhere you want, although
     by default we will jump to the L_restore label. If you then modify
     the location in the Context_Control structure, it will continue
     whereever you told it to go. Note however that you had better
     also have cleaned up the stack and frame pointers though, because
     they are probably still set with the values obtained from
     entering this function... */

  
  /* Note that some registers were used for parameter passing and
     temporary registeres (temp1 and temp2). These values were
     saved and restored across context calls, but the values that
     the caller needs should have been stored on the stack. The
     C code should now restore these from the stack, since r1 and
     r2 have been restored, and return to the location specified
     by r9. Then, all should be happy in the world. */
}

/*
 *  _CPU_Context_restore
 *
 *  This routine is generally used only to restart self in an
 *  efficient manner.  It may simply be a label in _CPU_Context_switch.
 *
 *  NOTE: May be unnecessary to reload some registers.
 *
 *  Or1k Specific Information:
 *
 *  In our implementation, this simply redirects to swich context
 */

void _CPU_Context_restore(
  Context_Control  *run
)
{
  _CPU_Context_switch(run,NULL);
}


/*  void __ISR_Handler()
 *
 *  This routine provides the RTEMS interrupt management.
 *
 *  Or1k Specific Information:
 *
 *  Based on the Or1k interrupt architecture described in chapter 16
 *  and the exception architecture described in chapter 9
 */

void _ISR_Handler(uint32_t   vector,uint32_t   ProgramCounter,
		  uint32_t   EffectiveAddress,uint32_t   StatusRegister)
{
   /*
    *  This discussion ignores a lot of the ugly details in a real
    *  implementation such as saving enough registers/state to be
    *  able to do something real.  Keep in mind that the goal is
    *  to invoke a user's ISR handler which is written in C and
    *  uses a certain set of registers.
    *
    *  Also note that the exact order is to a large extent flexible.
    *  Hardware will dictate a sequence for a certain subset of
    *  _ISR_Handler while requirements for setting
    */

  /*
   *  At entry to "common" _ISR_Handler, the vector number must be
   *  available.  On some CPUs the hardware puts either the vector
   *  number or the offset into the vector table for this ISR in a
   *  known place.  If the hardware does not give us this information,
   *  then the assembly portion of RTEMS for this port will contain
   *  a set of distinct interrupt entry points which somehow place
   *  the vector number in a known place (which is safe if another
   *  interrupt nests this one) and branches to _ISR_Handler.
   *
   *  save some or all context on stack
   *  may need to save some special interrupt information for exit
   *
   *  #if ( CPU_HAS_SOFTWARE_INTERRUPT_STACK == TRUE )
   *    if ( _ISR_Nest_level == 0 )
   *      switch to software interrupt stack
   *  #endif
   *
   *  _ISR_Nest_level++;
   *
   *  _Thread_Dispatch_disable_level++;
   *
   *  (*_ISR_Vector_table[ vector ])( vector );
   *
   *  --_ISR_Nest_level;
   *
   *  if ( _ISR_Nest_level )
   *    goto the label "exit interrupt (simple case)"
   *
   *  #if ( CPU_HAS_SOFTWARE_INTERRUPT_STACK == TRUE )
   *    restore stack
   *  #endif
   *  
   *  if ( !_Context_Switch_necessary )
   *    goto the label "exit interrupt (simple case)"
   *  
   *  if ( !_ISR_Signals_to_thread_executing )
   *    _ISR_Signals_to_thread_executing = FALSE;
   *    goto the label "exit interrupt (simple case)"
   *
   *  call _Thread_Dispatch() or prepare to return to _ISR_Dispatch
   *
   *  prepare to get out of interrupt
   *  return from interrupt  (maybe to _ISR_Dispatch)
   *
   *  LABEL "exit interrupt (simple case):
   *  prepare to get out of interrupt
   *  return from interrupt
   */

  /* In the Or1k architecture, exceptions are handled in the
     startup code of the board support package. Thus, this
     routine is never called. Or1k exception routines are called
     with the following prototype:

     function(int vector#, int PC, int Address, int StatusRegister);

     These parameters are snapshots of the system when the exception
     was encountered. If virtual memory is active, things like the
     PC and Address may have little meaning, as they are referenced
     in physical space, not the virtual space of the process.
  */
}
