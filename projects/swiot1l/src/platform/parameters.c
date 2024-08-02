
#include "parameters.h"


struct max_uart_init_param adin1110_uart_extra_ip = {
	.flow = UART_FLOW_DIS,
	.vssel = 1
};

struct max_spi_init_param adin1110_spi_extra_ip  = {
	.num_slaves = 1,
	.polarity = SPI_SS_POL_LOW,
	.vssel = MXC_GPIO_VSSEL_VDDIOH,
};

struct max_gpio_init_param vddioh_gpio_extra = {
	.vssel = MXC_GPIO_VSSEL_VDDIOH,
};

struct max_i2c_init_param vddioh_i2c_extra = {
	.vssel = MXC_GPIO_VSSEL_VDDIOH,
};

// Add in additional support for ADXL355 PMOD Interface 
struct max_uart_init_param adxl355_uart_extra_ip = {
	.flow = UART_FLOW_DIS
};

struct max_spi_init_param adxl355_spi_extra_ip = {
	.num_slaves = 2,
	.polarity = SPI_SS_POL_LOW,
	.vssel = MXC_GPIO_VSSEL_VDDIOH,
};
