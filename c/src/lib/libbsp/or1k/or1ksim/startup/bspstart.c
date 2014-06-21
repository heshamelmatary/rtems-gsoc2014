#include <bsp.h>
#include <bsp/uart.h>
#include <bsp/or1ksim.h>

extern const console_fns or1ksim_uart_fns;

void bsp_start()
{
  //uart_initialize(0);
  //OR1KSIM_REG(OR1KSIM_BSP_UART_REG_INT_ENABLE) = 0xff;
  //or1ksim_uart_fns.deviceInitialize(0);
  //printk("hi");
  return 0;
}
