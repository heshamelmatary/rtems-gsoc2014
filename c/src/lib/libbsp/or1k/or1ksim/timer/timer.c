/**
 * @file
 *
 * @ingroup or1ksim
 *
 * @brief Benchmark timer support.
 */

/*
 * Copyright (c) 2014 by Hesham ALMatary
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
<<<<<<< HEAD
 *
 *  http://www.rtems.org/license/LICENSE
 *
=======
 *  http://www.rtems.org/license/LICENSE
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
 */

#include <rtems.h>
#include <rtems/btimer.h>
#include <bsp/or1ksim.h>
<<<<<<< HEAD

static bool benchmark_timer_find_average_overhead = false;
static uint32_t tick_time;
static uint32_t benchmark_timer_base;

void benchmark_timer_initialize(void)
{

   asm volatile (
     "l.mfspr %0,r0,0x5001;":
     "=r" (benchmark_timer_base)::"memory");
=======
#include <rtems/score/or1k-utility.h>

#define OR1KSIM_NANOSECONDS_PER_CLK_CYCLE 10

static bool benchmark_timer_find_average_overhead = false;
static uint64_t benchmark_timer_base;

void benchmark_timer_initialize(void)
{
  benchmark_timer_base = _OR1K_mfspr(CPU_OR1K_SPR_TTCR);
>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
}

#define AVG_OVERHEAD  0
#define LEAST_VALID   1

uint32_t benchmark_timer_read( void )
{
<<<<<<< HEAD
  uint32_t         clicks;
  uint32_t         total;
  uint32_t         delta;
   
  /*
   *  Read the timer and see how many clicks it has been since we started.
   */
  asm volatile ("l.mfspr %0,r0,0x5001;":"=r" (clicks)::"memory");
  
 delta = clicks - benchmark_timer_base;
  
  /* total in microseconds */
  total = tick_time * (delta);
  
=======
  uint64_t         clicks;
  uint64_t         total;
  uint64_t         delta;
  /*
   *  Read the timer and see how many clicks (clock cycles)
   *  has passed since timer initialization.
   */
  clicks = _OR1K_mfspr(CPU_OR1K_SPR_TTCR);

  delta = clicks - benchmark_timer_base;

  /* total in nanoseconds */
  total = OR1KSIM_NANOSECONDS_PER_CLK_CYCLE * (delta);

>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
  if ( benchmark_timer_find_average_overhead == true )
    return total;          /* in nanoseconds microsecond units */
  else {
    if ( total < LEAST_VALID )
      return 0;            /* below timer resolution */
<<<<<<< HEAD
  
      return (total - AVG_OVERHEAD);
  }
}
   
=======

      return (total - AVG_OVERHEAD);
  }
}

>>>>>>> d13ce7553b86a5b86fb360d8fc530ddd3ceef14a
void benchmark_timer_disable_subtracting_average_overhead(bool find_flag)
{
  benchmark_timer_find_average_overhead = find_flag;
}
