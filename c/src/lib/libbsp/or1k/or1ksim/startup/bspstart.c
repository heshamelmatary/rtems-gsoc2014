#include <bsp.h>

extern void rtems_exception_init_mngt(void);

void bsp_start()
{
  /* Initialize exceptions management */
  rtems_exception_init_mngt();
  
  return 0;
}
