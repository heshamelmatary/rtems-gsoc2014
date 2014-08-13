void bsp_start()
{
  rtems_or1ksim_bsp_uart_init();
  main();
  return 0;
}
