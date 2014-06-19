/**
 * @file
 *
 * @ingroup or1ksim_uart
 *
 * @brief UART support.
 */


/**
 * @defgroup or1ksim_uart UART Support
 *
 * @ingroup or1k_or1ksim
 *
 * @brief Universal Asynchronous Receiver/Transmitter (UART) Support
 */

/*
 * Copyright (c) 2014 Hesham ALMatary.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE
 */

#ifndef LIBBSP_OR1K_OR1KSIM_UART_H
#define LIBBSP_OR1K_OR1KSIM_UART_H

#include <libchip/serial.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define OR1KSIM_UART_DEFAULT_BAUD  115200
#define OR1KSIM_BSP_UART_IRQ       13
extern const console_fns or1ksim_uart_fns;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_OR1K_OR1KSIM_UART_H */
