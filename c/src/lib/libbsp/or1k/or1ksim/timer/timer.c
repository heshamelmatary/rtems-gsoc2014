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
 *
 *  http://www.rtems.org/license/LICENSE
 *
 */

#include <rtems.h>
#include <rtems/btimer.h>
#include <bsp/or1ksim.h>

static bool benchmark_timer_find_average_overhead = false;
static uint32_t tick_time;
static uint32_t benchmark_timer_base;

void benchmark_timer_initialize(void)
{

   asm volatile (
     "l.mfspr %0,r0,0x5001;":
     "=r" (benchmark_timer_base)::"memory");
}

#define AVG_OVERHEAD  0
#define LEAST_VALID   1

uint32_t benchmark_timer_read( void )
{
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
  
  if ( benchmark_timer_find_average_overhead == true )
    return total;          /* in nanoseconds microsecond units */
  else {
    if ( total < LEAST_VALID )
      return 0;            /* below timer resolution */
  
      return (total - AVG_OVERHEAD);
  }
}
   
void benchmark_timer_disable_subtracting_average_overhead(bool find_flag)
{
  benchmark_timer_find_average_overhead = find_flag;
}
