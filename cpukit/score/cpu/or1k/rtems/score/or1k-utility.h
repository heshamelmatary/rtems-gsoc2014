/**
 * @file
 *
 * @brief OR1K utility
 */
/*
 *  Copyright (c) 2014 Hesham ALMatary
 *
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */
 
#ifndef _RTEMS_SCORE_OR1K_UTILITY_H
#define _RTEMS_SCORE_OR1K_UTILITY_H

/**
 * @brief Supervision Mode registers definitions.
 *
 * @see OpenRISC architecture manual - revision 0.
 */
 
/* Supervision Mode Register */
#define CPU_OR1K_SR 17

#define CPU_OR1K_SR_SM    0x1       /* Supervisor Mode */ 
#define CPU_OR1K_SR_TEE   0x2       /* Tick Timer Exception Enabled */
#define CPU_OR1K_SR_IEE   0x4       /* Interrupt Exception Enabled */
#define CPU_OR1K_SR_DCE   0x8       /* Data Cache Enable */
#define CPU_OR1K_SR_ICE   0x10      /* Instruction Cache Enable */
#define CPU_OR1K_SR_DME   0x20      /* Data MMU Enable */
#define CPU_OR1K_SR_IME   0x40      /* Instruction MMU Enable */
#define CPU_OR1K_SR_LEE   0x80      /* Little Endian Enable */
#define CPU_OR1K_SR_CE    0x100     /* CID Enable */
#define CPU_OR1K_SR_F     0x200     /* Conditional branch flag */
#define CPU_OR1K_SR_CY    0x400     /* Carry flag */
#define CPU_OR1K_SR_OV    0x800     /* Overflow flag */
#define CPU_OR1K_SR_OVE   0x1000    /* Overflow flag Exception */
#define CPU_OR1K_SR_DSX   0x2000    /* Delay Slot Exception */
#define CPU_OR1K_SR_EPH   0x4000    /* Exception Prefix High */
#define CPU_OR1K_SR_FO    0x8000    /* Fixed One */
#define CPU_OR1K_SR_SUMRA 0x10000   /* SPRs User Mode Read Access */
#define CPU_OR1K_SR_CID   0xF0000000 /*Context ID (Fast Context Switching) */

/* Used to disable interrupts */
#define CPU_OR1K_ISR_STATUS_MASK_I_DIS  0xFFFFFFFB 

#ifndef ASM

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

 typedef enum {
  OR1K_EXCEPTION_RESET = 1, 
  OR1K_EXCEPTION_BUS_ERR = 2, 
  OR1K_EXCEPTION_D_PF = 3, /* Data Page Fault */
  OR1K_EXCEPTION_I_PF = 4, /* Instruction Page Fault */
  OR1K_EXCEPTION_TICK_TIMER = 5, 
  OR1K_EXCEPTION_ALIGNMENT = 6,
  OR1K_EXCEPTION_I_UNDEF= 7, /* Undefiend instruction */
  OR1K_EXCEPTION_IRQ = 8, /* External interrupt */
  OR1K_EXCPETION_D_TLB = 9, /* Data TLB miss */ 
  OR1K_EXCPETION_I_TLB = 10, /* Instruction TLB miss */
  OR1K_EXCPETION_RANGE = 11, /* Range exception */
  OR1K_EXCPETION_SYS_CALL = 12,
  OR1K_EXCPETION_FP = 13, /* Floating point exception */
  OR1K_EXCPETION_TRAP = 14, /* Caused by l.trap instruction or by debug unit */
  OR1K_EXCPETION_RESERVED1 = 15,
  OR1K_EXCPETION_RESERVED2 = 16,
  OR1K_EXCPETION_RESERVED3 = 17,
  MAX_EXCEPTIONS = 17,
  OR1K_EXCEPTION_MAKE_ENUM_32_BIT = 0xffffffff
} OR1K_symbolic_exception_name;

static inline uint32_t _OR1K_mfspr(uint32_t reg)
{
   uint32_t spr_value;
  
   __asm__ __volatile__ (
     "l.mfspr  %0, r0, %1"
     : "=r" (spr_value) : "K" (reg) : "memory");
   
   return spr_value;
}

static inline void _OR1K_mtspr(uint32_t reg, uint32_t value)
{ 
   __asm__ volatile (
     "l.mtspr  r0, %0, %1;"
     : 
     : "r" (value), "K" (reg)
     : "memory"
   );
}

static inline void _OR1K_Flush_pipeline( void )
{

}

#else /* ASM */


#endif /* ASM */

#endif /* _RTEMS_SCORE_OR1K_UTILITY_H */
