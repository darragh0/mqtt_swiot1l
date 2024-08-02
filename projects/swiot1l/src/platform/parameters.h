#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "maxim_irq.h"
#include "maxim_spi.h"
#include "maxim_gpio.h"
#include "maxim_i2c.h"
#include "maxim_timer.h"
#include "maxim_uart.h"
#include "maxim_uart_stdio.h"


#ifdef IIO_SUPPORT
#define INTC_DEVICE_ID  0
#endif
#define UART_IRQ_ID     UART0_IRQn

#define UART_DEVICE_ID  0
#define UART_BAUDRATE   115200
#define UART_OPS        &max_uart_ops
#define UART_EXTRA      &adin1110_uart_extra_ip

#define SPI_DEVICE_ID   2
#define SPI_BAUDRATE    15000000
#define SPI_CS          0
#define SPI_OPS         &max_spi_ops
#define SPI_EXTRA       &adin1110_spi_extra_ip

#define SPI1_DEVICE_ID   1
#define SPI1_BAUDRATE    10000000
#define SPI1_CS          2
#define SPI1_OPS         &max_spi_ops
#define SPI1_EXTRA       &adxl355_spi_extra_ip

#define I2C_EXTRA	&vddioh_i2c_extra
#define GPIO_EXTRA	&vddioh_gpio_extra

#define AD74413R_GPIO_TRIG_IRQ_ID     22
#define AD74413R_GPIO_CB_HANDLE       NULL

#define GPIO_IRQ_ID             1 /* Pin 0 */
#define GPIO_IRQ_OPS            &max_gpio_irq_ops
#define GPIO_IRQ_EXTRA          NULL

extern struct max_uart_init_param adin1110_uart_extra_ip;
extern struct max_spi_init_param adin1110_spi_extra_ip;
extern struct max_spi_init_param adxl355_spi_extra_ip; 

extern struct max_i2c_init_param vddioh_i2c_extra;
extern struct max_gpio_init_param vddioh_gpio_extra;


#endif /* __PARAMETERS_H__ */
